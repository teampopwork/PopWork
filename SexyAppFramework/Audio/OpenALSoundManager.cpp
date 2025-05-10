#include "OpenALSoundManager.h"
#include "OpenALSoundInstance.h"
#include "../PakLib/PakInterface.h"
#include "../Common.h"
#include "AUReader.h"
#define USE_OGG_LIB

#ifdef USE_OGG_LIB
#include "ogg/ivorbiscodec.h"
#include "ogg/ivorbisfile.h"
#endif

#include <miniaudio.h>
#include <SDL3/SDL.h>

#define AL_CHECK_ERROR() { \
if(alGetError() != AL_NO_ERROR) __debugbreak(); \
}

using namespace Sexy;

ALCdevice* mALDevice = nullptr;
ALCcontext* mALContext = nullptr;

OpenALSoundManager::OpenALSoundManager()
{

	mALDevice = alcOpenDevice(nullptr); // Default device
	if (!mALDevice) {
		printf("Failed to open OpenAL device!\n");
		return;
	}

	mALContext = alcCreateContext(mALDevice, nullptr);
	if (!mALContext) {
		printf("Failed to create OpenAL context!\n");
		alcCloseDevice(mALDevice);
		return;
	}

	alcMakeContextCurrent(mALContext);

	int i;

	for (i = 0; i < MAX_SOURCE_SOUNDS; i++)
	{
		mSourceSounds[i] = NULL;
		mBaseVolumes[i] = 1;
		mBasePans[i] = 0;
	}

	for (i = 0; i < MAX_CHANNELS; i++)
		mPlayingSounds[i] = NULL;

	mMasterVolume = 1.0;
}

OpenALSoundManager::~OpenALSoundManager()
{
	ReleaseChannels();
	ReleaseSounds();
	alcMakeContextCurrent(nullptr);
	if (mALContext) alcDestroyContext(mALContext);
	if (mALDevice) alcCloseDevice(mALDevice);
}

bool OpenALSoundManager::Initialized()
{
	return mALDevice != nullptr && mALContext != nullptr;
}

int OpenALSoundManager::FindFreeChannel()
{
	DWORD aTick = SDL_GetTicks();
	if (aTick - mLastReleaseTick > 1000)
	{
		ReleaseFreeChannels();
		mLastReleaseTick = aTick;
	}

	for (int i = 0; i < MAX_CHANNELS; i++)
	{
		if (mPlayingSounds[i] == NULL)
			return i;

		if (mPlayingSounds[i]->IsReleased())
		{
			delete mPlayingSounds[i];
			mPlayingSounds[i] = NULL;
			return i;
		}
	}

	return -1;
}

int OpenALSoundManager::VolumeToDB(double theVolume)
{
	int aVol = (int)((log10(1 + theVolume * 9) - 1.0) * 2333);
	if (aVol < -2000)
		aVol = -10000;

	return aVol;
}

void OpenALSoundManager::ReleaseFreeChannels()
{
	for (int i = 0; i < MAX_CHANNELS; i++)
		if (mPlayingSounds[i] != NULL && mPlayingSounds[i]->IsReleased())
		{
			delete mPlayingSounds[i];
			mPlayingSounds[i] = NULL;
		}
}

bool OpenALSoundManager::LoadSound(unsigned int theSfxID, const std::string& theFilename)
{
	if ((theSfxID < 0) || (theSfxID >= MAX_SOURCE_SOUNDS))
		return false;

	ReleaseSound(theSfxID);

	mSourceFileNames[theSfxID] = theFilename;

	if (LoadOGGSound(theSfxID, theFilename + ".ogg")) // do the ogg first
		return true;

	std::vector<std::string> aFileExtensions = {".mp3", ".flac", ".wav"};

	for (std::string aExt : aFileExtensions)
	{
		PFILE* fp = p_fopen((theFilename + aExt).c_str(), "rb");
		if (!fp)
			continue;

		p_fseek(fp, 0, SEEK_END);
		size_t fileSize = p_ftell(fp);
		p_fseek(fp, 0, SEEK_SET);
		uint8_t* data = new uint8_t[fileSize];
		p_fread(data, 1, fileSize, fp);
		p_fclose(fp);

		mSourceDataSizes[theSfxID] = fileSize;

		ma_decoder decoder;
		ma_result result = ma_decoder_init_memory(data, fileSize, NULL, &decoder);
		if (result != MA_SUCCESS) {
			delete[] data;
			continue;
		}

		const size_t bufferSize = 1024 * 1024;
		std::vector<float> pcmData(bufferSize);

		ma_result decoder_result = ma_decoder_read_pcm_frames(&decoder, pcmData.data(), pcmData.size(), NULL);
		if (decoder_result != MA_SUCCESS) {
			delete[] data;
			ma_decoder_uninit(&decoder);
			continue;
		}

		ALuint buffer;
		alGenBuffers(1, &buffer);
		alBufferData(buffer, AL_FORMAT_STEREO16, pcmData.data(), pcmData.size(), decoder.outputSampleRate);

		mSourceSounds[theSfxID] = buffer;

		delete[] data;
		ma_decoder_uninit(&decoder);
		return true;
	}

	if (LoadAUSound(theSfxID, theFilename + ".au"))
		return true;
	
	return false;
}

int OpenALSoundManager::LoadSound(const std::string& theFilename)
{
	int i;
	for (i = 0; i < MAX_SOURCE_SOUNDS; i++)
		if (mSourceFileNames[i] == theFilename)
			return i;

	for (i = MAX_SOURCE_SOUNDS - 1; i >= 0; i--)
	{
		if (mSourceSounds[i] == NULL)
		{
			if (!LoadSound(i, theFilename))
				return -1;
			else
				return i;
		}
	}

	return -1;
}

static int p_fseek64_wrap(PFILE* f, ogg_int64_t off, int whence) {
	if (f == NULL)return(-1);
	return p_fseek(f, (long)off, whence);
}

int ov_pak_open(PFILE* f, OggVorbis_File* vf, char* initial, long ibytes) {
	ov_callbacks callbacks = {
		(size_t(*)(void*, size_t, size_t, void*))  p_fread,
		(int (*)(void*, ogg_int64_t, int))             p_fseek64_wrap,
		(int (*)(void*))                             p_fclose,
		(long (*)(void*))                            p_ftell
	};

	return ov_open_callbacks((void*)f, vf, initial, ibytes, callbacks);
}


bool OpenALSoundManager::LoadOGGSound(unsigned int theSfxID, const std::string& theFilename)
{
	OggVorbis_File vf;
	int current_section;

	PFILE* aFile = p_fopen(theFilename.c_str(), "rb");
	if (aFile == NULL)
		return false;

	if (ov_pak_open(aFile, &vf, NULL, 0) < 0)
	{
		p_fclose(aFile);
		return false;
	}

	vorbis_info* anInfo = ov_info(&vf, -1);

	ALenum format;
	if (anInfo->channels == 1)
		format = AL_FORMAT_MONO16;
	else if (anInfo->channels == 2)
		format = AL_FORMAT_STEREO16;
	else
	{
		ov_clear(&vf);
		p_fclose(aFile);
		return false;
	}
	//get total size
	int aLenBytes = static_cast<int>(ov_pcm_total(&vf, -1) * anInfo->channels * 2);

	char* aBuf = new char[aLenBytes]; //temp buffer

	char* aPtr = aBuf;
	int aNumBytes = aLenBytes;
	while (aNumBytes > 0)
	{
		long ret = ov_read(&vf, aPtr, aNumBytes, &current_section);
		if (ret == 0)
			break;
		else if (ret < 0)
		{
			// this means something is wrong
			delete[] aBuf;
			ov_clear(&vf);
			return false;
		}
		else
		{
			aPtr += ret;
			aNumBytes -= ret;
		}
	}
	ALuint aBuffer;
	alGenBuffers(1, &aBuffer);
	alBufferData(aBuffer, format, aBuf, aLenBytes, anInfo->rate);

	mSourceSounds[theSfxID] = aBuffer;

	delete[] aBuf;
	ov_clear(&vf);

	return true;
}

bool OpenALSoundManager::LoadAUSound(unsigned int theSfxID, const std::string& theFilename)
{
	PFILE* fp = p_fopen(theFilename.c_str(), "rb");
	if (!fp)
		return false;

	p_fseek(fp, 0, SEEK_END);
	size_t fileSize = p_ftell(fp);
	p_fseek(fp, 0, SEEK_SET);
	uint8_t* data = new uint8_t[fileSize];
	p_fread(data, 1, fileSize, fp);
	p_fclose(fp);

	AuFile aAUFile;
	if (!LoadAU(data, fileSize, aAUFile))
	{
		delete[] data;
		return false;
	}

	mSourceDataSizes[theSfxID] = aAUFile.mSamples.size();

	ALenum format = (aAUFile.mChannels == 1 ? AL_FORMAT_MONO16 : AL_FORMAT_STEREO16);

	ALuint buffer;
	alGenBuffers(1, &buffer);
	alBufferData(buffer, format, aAUFile.mSamples.data(), aAUFile.mSamples.size() * sizeof(int16_t), aAUFile.mSampleRate);

	mSourceSounds[theSfxID] = buffer;

	delete[] data;

	return true;
}

void OpenALSoundManager::ReleaseSound(unsigned int theSfxID)
{
	if (mSourceSounds[theSfxID] != NULL)
	{
		ForceReleaseSources(mSourceSounds[theSfxID]);
		alDeleteBuffers(1, &mSourceSounds[theSfxID]);
		AL_CHECK_ERROR();
		mSourceSounds[theSfxID] = NULL;
		mSourceFileNames[theSfxID] = "";
	}
}

void OpenALSoundManager::StopAllSounds()
{
	for (int i = 0; i < MAX_CHANNELS; i++)
		if (mPlayingSounds[i] != NULL)
		{
			bool isAutoRelease = mPlayingSounds[i]->mAutoRelease;
			mPlayingSounds[i]->Stop();
			mPlayingSounds[i]->mAutoRelease = isAutoRelease;
		}
}

int OpenALSoundManager::GetFreeSoundId()
{
	for (int i = 0; i < MAX_SOURCE_SOUNDS; i++)
	{
		if (mSourceSounds[i] == NULL)
			return i;
	}

	return -1;
}

int OpenALSoundManager::GetNumSounds()
{
	int aCount = 0;
	for (int i = 0; i < MAX_SOURCE_SOUNDS; i++)
	{
		if (mSourceSounds[i] != NULL)
			aCount++;
	}

	return aCount;
}

void OpenALSoundManager::ForceReleaseSources(ALuint theBuffer)
{
	for (int i = 0; i < MAX_CHANNELS; i++)
	{
		if (mPlayingSounds[i] != NULL && mPlayingSounds[i]->mSourceSoundBuffer == theBuffer)
		{
			delete mPlayingSounds[i];
			mPlayingSounds[i] = NULL;
		}
	}
}

void OpenALSoundManager::SetVolume(double theVolume)
{
	mMasterVolume = theVolume;

	for (int i = 0; i < MAX_CHANNELS; i++)
		if (mPlayingSounds[i] != NULL)
			mPlayingSounds[i]->RehupVolume();
}

bool OpenALSoundManager::SetBaseVolume(unsigned int theSfxID, double theBaseVolume)
{
	if ((theSfxID < 0) || (theSfxID >= MAX_SOURCE_SOUNDS))
		return false;

	mBaseVolumes[theSfxID] = theBaseVolume;
	return true;
}

bool OpenALSoundManager::SetBasePan(unsigned int theSfxID, int theBasePan)
{
	if ((theSfxID < 0) || (theSfxID >= MAX_SOURCE_SOUNDS))
		return false;

	mBasePans[theSfxID] = theBasePan;
	return true;
}

SoundInstance* OpenALSoundManager::GetSoundInstance(unsigned int theSfxID)
{
	if (theSfxID > MAX_SOURCE_SOUNDS)
		return NULL;

	int aFreeChannel = FindFreeChannel();
	if (aFreeChannel < 0)
		return NULL;

	if (mSourceSounds[theSfxID] == NULL)
		return NULL;

	mPlayingSounds[aFreeChannel] = new OpenALSoundInstance(this, mSourceSounds[theSfxID]);

	mPlayingSounds[aFreeChannel]->SetBasePan(mBasePans[theSfxID]);
	mPlayingSounds[aFreeChannel]->SetBaseVolume(mBaseVolumes[theSfxID]);

	return mPlayingSounds[aFreeChannel];
}

void OpenALSoundManager::ReleaseSounds()
{
	for (int i = 0; i < MAX_SOURCE_SOUNDS; i++)
		if (mSourceSounds[i] != NULL)
		{
			alDeleteBuffers(1, &mSourceSounds[i]);
			mSourceSounds[i] = NULL;
		}
}

void OpenALSoundManager::ReleaseChannels()
{
	for (int i = 0; i < MAX_CHANNELS; i++)
		if (mPlayingSounds[i] != NULL)
		{
			delete mPlayingSounds[i];
			mPlayingSounds[i] = NULL;
		}
}

double OpenALSoundManager::GetMasterVolume()
{
	return mMasterVolume;
}

void OpenALSoundManager::SetMasterVolume(double theVolume)
{
	mMasterVolume = theVolume;
}

void OpenALSoundManager::Flush()
{
}

void OpenALSoundManager::SetCooperativeWindow(bool isWindowed)
{
}