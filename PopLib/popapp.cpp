#include "popapp.hpp"
#include "api/discord.hpp"

using namespace PopLib;

PopApp* PopLib::gPopApp = nullptr;
    
PopApp::PopApp()
{
    gPopApp = this;

	mTimesPlayed = 0;
	mTimesExecuted = 0;
	mTimedOut = false;

	mIsRegistered = false;
	mBuildUnlocked = false;
	mDownloadId = 0;
	mRegSource = "ingame";
	mSkipAd = false;
	mDontUpdate = false;
	mLastVerCheckQueryTime = 0;

	mCompanyName = "PLACEHOLDER";
	mFullCompanyName= "PLACEHOLDER";
	mBetaValidate = true;

    #ifdef _FEATURE_DISCORD_RPC
    mRPCAppID = "1369297870456488057";
    mDiscordRPC = nullptr;
    #endif
}
    
PopApp::~PopApp()
{
    #ifdef _FEATURE_DISCORD_RPC
    if (mDiscordRPC)
        delete mDiscordRPC;
    #endif
}

void PopApp::InitHook()
{
	#if _FEATURE_DISCORD_RPC
    InitDiscordRPC();
    #endif
}

bool PopApp::CheckSignature(const Buffer& theBuffer, const std::string& theFileName)
{
#ifdef _DEBUG
	// Don't check signatures on debug version because it's annoying and the build number
	//  will probably be 0 anyway
	return true;
#endif

	/*if (mSkipSignatureChecks)
		return true;

	char aSigStr[25];

	FILE* aFP = fopen((theFileName + ".sig").c_str(), "rb");
	if (aFP == NULL)
		return false;

	fread(aSigStr, 1, 24, aFP);
	aSigStr[24] = 0;

	fclose(aFP);

	char* aFileData = new char[theBuffer.GetDataLen()+4];
	int aFileDataPos = 0;
	
	char aStr[9] = {0};
	strncpy(aStr, SIGNATURE_CODE_MARKER, 8);
	int aSignatureCode = atoi(aStr);

	aFileData[aFileDataPos++] = (aSignatureCode & 0xFF);
	aFileData[aFileDataPos++] = ((aSignatureCode >> 8) & 0xFF);
	aFileData[aFileDataPos++] = ((aSignatureCode >> 16) & 0xFF);
	aFileData[aFileDataPos++] = ((aSignatureCode >> 24) & 0xFF);

	theBuffer.SeekFront();
	while (!theBuffer.AtEnd())
	{
		unsigned char c = theBuffer.ReadByte();
		fread(&c, 1, 1, aFP);
		if (!::isspace(c))
			aFileData[aFileDataPos++] = c;
	}	

	// Public RSA stuff
	BigInt n("D99BC76AB7B2578738E606F7");
	BigInt e("11");
			
	BigInt aHash = HashData(aFileData, aFileDataPos, 94);
	delete aFileData;
	
	BigInt aSignature(aSigStr);
	BigInt aHashTest = aSignature.ModPow(e, n);

	return aHashTest == aHash;*/
	return true;
}

void PopApp::InitPropertiesHook()
{
	// Load properties if we need to
	bool checkSig = !IsScreenSaver();
	LoadProperties("properties\\partner.xml", false, checkSig);

	// Check to see if this build is unlocked.
	if (GetBoolean("NoReg", false))
	{
		mIsRegistered = true;
		mBuildUnlocked = true;
	}

	mProdName = GetString("ProdName", mProdName);
	mIsWindowed = GetBoolean("DefaultWindowed", mIsWindowed);	

	PopString aNewTitle = GetString("Title", "");
	if (aNewTitle.length() > 0)
		mTitle = aNewTitle + " " + mProductVersion;	
		
}

bool PopApp::Validate(const std::string& theUserName, const std::string& theRegCode)
{
	/*BigInt n("42BF94023BBA6D040C8B81D9");
	BigInt e("11");

	ulong i;
	std::string aDataString;
	bool space = false;	
	for (i = 0; i < theUserName.size(); i++)
	{
		if (theUserName[i] == ' ')
		{
			if (aDataString.length() > 0)
				space = true;
		}
		else
		{
			if (space)
			{
				aDataString += " ";
				space = false;
			}

			char aChar = theUserName[i];
			for (int j = 0; gRegKeyTranslationTable[j][0] != 0; j++)
				if (gRegKeyTranslationTable[j][0] == aChar)
					aChar = gRegKeyTranslationTable[j][1];

			aDataString += toupper(aChar);
		}
	}

	std::string aProduct;
	aProduct = mProdName;
	for (i = 0; i < aProduct.length(); i++)
		aProduct[i] = toupper(aProduct[i]);

	aDataString += "\n";
	aDataString += aProduct;
	BigInt aHash = HashString(aDataString, 94);	
	
	BigInt aSignature = KeyToInt(theRegCode);
	BigInt aHashTest = aSignature.ModPow(e, n);

	return aHashTest == aHash;*/
	return true;
}


void PopApp::ReadFromRegistry()
{
	AppBase::ReadFromRegistry();

    mTimesPlayed = 0;
	mTimesExecuted = 0;

	char aFileName[256];
	GetWindowsDirectory(aFileName, 256);
	if (aFileName[strlen(aFileName)-1] != '\\')
	{
		strcat(aFileName, "\\");
	}

	strcat(aFileName, "popcinfo.dat");
	FILE* fp = fopen(aFileName, "rb");
	if (fp != NULL)
	{
		for (;;)
		{
			ushort aLen;
			if (fread(&aLen, 1, sizeof(short), fp) == 0)
				break;
			if (aLen < 256)
			{
				char aProdName[256];
				aProdName[aLen] = '\0';
				fread(aProdName, aLen, sizeof(char), fp);
				if (strcmp(aProdName, mProdName.c_str()) == 0)
				{
					short aShort;
					fread(&aShort, 1, sizeof(short), fp);
					mTimesPlayed = aShort;

					fread(&aShort, 1, sizeof(short), fp);
					mTimesExecuted = aShort;
					break;
				}
			}

			fseek(fp, sizeof(int), SEEK_CUR);
		}
		fclose(fp);
	}
	RegistryReadString("ReferId", &mReferId);
	mReferId = GetString("ReferId", mReferId);
	mRegisterLink = "http://www.popcap.com/register.php?theGame=" + mProdName + "&referid=" + mReferId;	
	RegistryReadString("RegisterLink", &mRegisterLink);

	int anInt;

	if (RegistryReadInteger("DontUpdate", &anInt))
		mDontUpdate = anInt != 0;

	if (RegistryReadInteger("DownloadId", &anInt))
		mDownloadId = anInt;

	RegistryReadString("Variation", &mVariation);

	if (RegistryReadInteger("TimesPlayed", &anInt))
	{
        if (mTimesPlayed != anInt)
                        mTimesPlayed = 100;
	}

	if (RegistryReadInteger("TimesExecuted", &anInt))
	{
		if (mTimesExecuted != anInt)
			mTimesExecuted = 100;
	}
	
	if (RegistryReadInteger("LastVerCheckQueryTime", &anInt))
	{
		mLastVerCheckQueryTime = anInt;
	}
	else
	{
		time_t aTimeNow;
		time(&aTimeNow);

		mLastVerCheckQueryTime = aTimeNow;
	}

	RegistryReadString("RegName", &mRegUserName);
	RegistryReadString("RegCode", &mRegCode);		

	mIsRegistered |= Validate(mRegUserName, mRegCode);	

	// Override registry values with partner.xml values
	mRegisterLink = GetString("RegisterLink", mRegisterLink);
	mDontUpdate = GetBoolean("DontUpdate", mDontUpdate);
}

void PopApp::UpdateHook()
{
    #ifdef _FEATURE_DISCORD_RPC
    if (mDiscordRPC && mDiscordRPC->mHasInitialized)
        mDiscordRPC->UpdateRPC();
    #endif
}

#ifdef _FEATURE_DISCORD_RPC
void PopApp::InitDiscordRPC()
{
    if (mDiscordRPC)
        delete mDiscordRPC;

    mDiscordRPC = new DiscordRPC(mRPCAppID.c_str());

}
#endif