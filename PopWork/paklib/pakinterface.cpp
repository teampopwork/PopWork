#include "pakinterface.hpp"
#include "common.hpp"
#include <algorithm>
#include <cstring>
#include <cstdlib>

using namespace std;

PakInterface *gPakInterface = new PakInterface();

//////////////////
static bool starts_with(const std::string &str, const std::string &prefix)
{
	return str.size() >= prefix.size() && str.compare(0, prefix.size(), prefix) == 0;
}

static inline std::string toupper(const std::string &theString)
{
	std::string aString;
	for (unsigned i = 0; i < theString.length(); i++)
		aString += toupper(theString[i]);
	return aString;
}
//////////////////

// Helper to convert wildcard patterns to simple matching
static bool matchPattern(const string &pattern, const string &name)
{
	size_t pos = pattern.find('*');
	if (pos == string::npos)
		return _stricmp(pattern.c_str(), name.c_str()) == 0;
	string prefix = pattern.substr(0, pos);
	string suffix = pattern.substr(pos + 1);
	if (!starts_with(name, prefix))
		return false;
	if (suffix.empty())
		return true;
	if (name.length() < prefix.length() + suffix.length())
		return false;
	return _stricmp(name.substr(name.size() - suffix.size()).c_str(), suffix.c_str()) == 0;
}

PakInterface::PakInterface()
{
	// nothing to initialize beyond base
}

PakInterface::~PakInterface()
{
}

bool PakInterface::AddPakFile(const string &fileName)
{
	FILE *fp = fopen(fileName.c_str(), "rb");
	if (!fp)
		return false;
	fseek(fp, 0, SEEK_END);
	size_t fileSize = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	mPakCollectionList.emplace_back(fileSize);
	PakCollection &collection = mPakCollectionList.back();
	fread(collection.data(), 1, fileSize, fp);
	fclose(fp);

	// simple XOR decode with password
	auto *bytes = reinterpret_cast<unsigned char *>(collection.data());
	for (size_t i = 0; i < fileSize; ++i)
		bytes[i] ^= static_cast<unsigned char>(mDecryptPassword[i % mDecryptPassword.size()]);

	// build one record covering full pak
	PakRecord rec;
	rec.mCollection = &collection;
	rec.mFileName = fileName;
	rec.mStartPos = 0;
	rec.mSize = fileSize;
	rec.mFileTime = filesystem::file_time_type::min();
	mPakRecordMap[toupper(fileName)] = rec;

	return true;
}

PFILE *PakInterface::FOpen(const char *fn, const char *mode)
{
	string name(fn);
	auto it = mPakRecordMap.find(toupper(name));
	if (it != mPakRecordMap.end())
	{
		PFILE *pf = new PFILE;
		pf->mRecord = &it->second;
		pf->mPos = 0;
		pf->mFP = nullptr;
		return pf;
	}
	FILE *real = fopen(fn, mode);
	if (!real)
		return nullptr;
	PFILE *pf = new PFILE;
	pf->mRecord = nullptr;
	pf->mFP = real;
	pf->mPos = 0;
	return pf;
}

int PakInterface::FClose(PFILE *pf)
{
	if (pf->mFP)
		fclose(pf->mFP);
	delete pf;
	return 0;
}

int PakInterface::FSeek(PFILE *pf, long offset, int whence)
{
	if (pf->mRecord)
	{
		auto &r = *pf->mRecord;
		switch (whence)
		{
		case SEEK_SET:
			pf->mPos = offset;
			break;
		case SEEK_CUR:
			pf->mPos += offset;
			break;
		case SEEK_END:
			pf->mPos = r.mSize + offset;
			break;
		}
		pf->mPos = std::min(std::max(pf->mPos, 0L), static_cast<long>(r.mSize));
		return 0;
	}
	return fseek(pf->mFP, offset, whence);
}

int PakInterface::FTell(PFILE *pf)
{
	return pf->mRecord ? static_cast<int>(pf->mPos) : ftell(pf->mFP);
}

size_t PakInterface::FRead(void *buf, int size, int count, PFILE *pf)
{
	if (pf->mRecord)
	{
		auto &r = *pf->mRecord;
		size_t toRead = min<size_t>(size * count, r.mSize - pf->mPos);
		unsigned char *src = reinterpret_cast<unsigned char *>(r.mCollection->data()) + r.mStartPos + pf->mPos;
		unsigned char *dst = reinterpret_cast<unsigned char *>(buf);
		for (size_t i = 0; i < toRead; ++i)
			dst[i] = src[i] ^ static_cast<unsigned char>(
								  mDecryptPassword[(r.mStartPos + pf->mPos + i) % mDecryptPassword.size()]);
		pf->mPos += toRead;
		return toRead / size;
	}
	return fread(buf, size, count, pf->mFP);
}

int PakInterface::FGetC(PFILE *pf)
{
	unsigned char c;
	return FRead(&c, 1, 1, pf) == 1 ? c : EOF;
}

int PakInterface::UnGetC(int c, PFILE *pf)
{
	if (pf->mRecord)
	{
		pf->mPos = std::max(0L, pf->mPos - 1);
		return c;
	}
	return ungetc(c, pf->mFP);
}

char *PakInterface::FGetS(char *str, int size, PFILE *pf)
{
	int i = 0;
	while (i + 1 < size)
	{
		int c = FGetC(pf);
		if (c == EOF || c == '\n')
			break;
		str[i++] = c;
	}
	str[i] = '\0';
	return i > 0 ? str : nullptr;
}

int PakInterface::FEof(PFILE *pf)
{
	return pf->mRecord ? pf->mPos >= pf->mRecord->mSize : feof(pf->mFP);
}

#ifdef _WIN32
#undef FindFirstFile
#undef FindNextFile
#endif

PFindData PakInterface::FindFirstFile(const string &pattern)
{
	PFindData fd;
	fd.it = filesystem::directory_iterator(".");
	fd.end = filesystem::directory_iterator();
	fd.pattern = pattern;
	return fd;
}

bool PakInterface::FindNextFile(PFindData &fd, string &outName)
{
	while (fd.it != fd.end)
	{
		auto entry = *fd.it++;
		string name = entry.path().filename().string();
		if (matchPattern(fd.pattern, name))
		{
			outName = name;
			return true;
		}
	}
	return false;
}

void PakInterface::FindClose(PFindData &fd)
{
	// nothing to clean
}
