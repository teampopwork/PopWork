// ***************************************************************
//  Profile   version:  2.0   �  date: 01/02/2008
//  -------------------------------------------------------------
//  Version 2.0 of the Profile class!  Allows you to retrieve
//	any of the four basic types {String, Int, Float, Boolean}
//	without explicitly defining the variable (with support for
//	returning a default value).
//
//	For example, let's say that later in development, a new variable
//	is added.  The variable can be accessed from the map with an
//	default parameter, such that if it hasn't been written yet, the
//	default will be returned.  No explicit variable definition or
//	subsequent updating/validation of previous save files.
//
//	User Profiles are always valid across all versions of the program!
//  -------------------------------------------------------------
//  Copyright (C) James Poag 2008 - All Rights Reserved
// ***************************************************************
//
// ***************************************************************

#include "profile.hpp"
#include "readwrite/xmlwriter.hpp" // Write
#include "readwrite/xmlparser.hpp" // Read
#include "appbase.hpp"

using namespace PopLib;

//************************************
// Method:      Profile
// FullName:    PopLib::Profile::Profile
// Access:      protected
//************************************
Profile::Profile()
{
}

//************************************
// Method:    GetProfile
// FullName:  PopLib::Profile::GetProfile
// Access:    public
// Returns:   Profile*
// Description: Singleton Access!  Only one user loaded at a time, this is so we
//				can access the Profile variables anywhere in code, quickly!
//************************************
Profile *PopLib::Profile::GetProfile()
{
	static Profile aProfile;
	return &aProfile;
}

//************************************
// Method:    GetStateFileName
// FullName:  PopLib::Profile::GetStateFileName
// Access:    public
// Returns:   std::string
// Description: returns the file name of the save state named 'theStateName'
//				This is very useful for saving mid-game progress.  Let's say
//				that a user quits out 1/2 way through a level.  Well, you're
//				going to want to save the state of the game.  This provides
//				a mechanism so that all users will have their own, individual
//				game state.  So mom and can can both pick up where they left off!
// Parameter: PopString theStateName
//************************************
std::string PopLib::Profile::GetStateFileName(PopString theStateName, PopString theUserName /*= ""*/)
{
	std::string aStateName = theStateName;
	std::string aUserName =
		(theUserName == "") ? mUserName : theUserName;

	return StrFormat("%susers/%s/%s.sav", GetAppDataFolder().c_str(), aUserName.c_str(), aStateName.c_str());
}

//************************************
// Method:    GetUserFileName
// FullName:  PopLib::Profile::GetUserFileName
// Access:    virtual public
// Returns:   std::string
// Description: Used internally to locate the XML Profile settings for the User.
//				This is a separate method (like the one above) in order to change
//				the location for the entire class.  This way you don't have to
//				Edit the save and load methods separately.  This GetStateFileName()
//				method is along the same idea, only it's used externally by you!
// Parameter: PopString theUserName
//************************************
std::string PopLib::Profile::GetUserFileName(PopString theUserName /*= ""*/)
{
	std::string aUserName =
		(theUserName == "") ? mUserName : theUserName;

	return StrFormat("%susers/%s.xml", GetAppDataFolder().c_str(), aUserName.c_str());
}

//************************************
// Method:    SetIntegerValue
// FullName:  PopLib::Profile::SetIntegerValue
// Access:    public
// Returns:   void
// Description: Lets you add values to the Profile based on a text key!
//				No more hard coding a value every time you want to expand the
//				Profile!
// Parameter: PopString theValueName
// Parameter: int theValue
//************************************
void PopLib::Profile::SetIntegerValue(PopString theValueName, int theValue)
{
	if (mIntegerMap.find(theValueName) != mIntegerMap.end())
		mIntegerMap[theValueName] = theValue;
	else
		mIntegerMap.insert(std::pair<PopString, int>(theValueName, theValue));
}

//************************************
// Method:    GetIntegerValue
// FullName:  PopLib::Profile::GetIntegerValue
// Access:    public
// Returns:   int
// Description: Gets the value of the integer associated with the Key or returns
//				'theDefault' value if not loaded!
// Parameter: PopString theValueName
// Parameter: int theDefault
//************************************
int PopLib::Profile::GetIntegerValue(PopString theValueName, int theDefault)
{
	// We will not create a value that doesn't exist.  This means that you can
	// have things like secret values that won't be created in the profile.xml
	// unless you have garnered that prize! (and called SetIntegerValue())
	if (mIntegerMap.find(theValueName) != mIntegerMap.end())
		return mIntegerMap[theValueName];

	return theDefault;
}

Profile::~Profile()
{
}

bool Profile::Save(PopString theFileName)
{
	XMLWriter aWriter;

	if (aWriter.OpenFile(theFileName) && !aWriter.HasFailed())
	{
		// The XML Writer Class works like a Stack.
		// http://en.wikipedia.org/wiki/Stack_%28data_structure%29

		// You Start a Node and Set it's Attributes.  Any Nodes you start
		// afterwards are child Nodes of the currently open node.

		// Stop Node removes the node from the stack and closes all child nodes.

		// Notice the Symmetry of Start/Stop Calls

		aWriter.StartElement("Profile");

		std::map<PopString, int>::iterator map_itr = mIntegerMap.begin();
		for (; map_itr != mIntegerMap.end(); ++map_itr)
		{
			aWriter.StartElement("Integer");
			aWriter.WriteAttribute("id", map_itr->first);
			aWriter.WriteAttribute("value", map_itr->second);
			aWriter.StopElement();
		}

		std::map<PopString, double>::iterator float_itr = mFloatMap.begin();
		for (; float_itr != mFloatMap.end(); ++float_itr)
		{
			aWriter.StartElement("Float");
			aWriter.WriteAttribute("id", float_itr->first);
			aWriter.WriteAttribute("value", (float)float_itr->second);
			aWriter.StopElement();
		}

		std::map<PopString, PopString>::iterator str_itr = mStringMap.begin();
		for (; str_itr != mStringMap.end(); ++str_itr)
		{
			aWriter.StartElement("String");
			aWriter.WriteAttribute("id", str_itr->first);
			aWriter.WriteAttribute("value", str_itr->second);
			aWriter.StopElement();
		}

		std::map<PopString, bool>::iterator bool_itr = mBoolMap.begin();
		for (; bool_itr != mBoolMap.end(); ++bool_itr)
		{
			aWriter.StartElement("Bool");
			aWriter.WriteAttribute("id", bool_itr->first);
			aWriter.WriteAttribute("value", bool_itr->second);
			aWriter.StopElement();
		}

		aWriter.StopElement();

		aWriter.CloseFile();

		return true; // Success
	}

	return false; // FAILURE
}

//************************************
// Method:      Load
// FullName:    PopLib::Profile::Load
// Access:      virtual public
// Returns:     bool
// Parameter:   PopString theFileName
// Description: Loads the '%user_name%.xml' from the '%APP_DATA_FOLDER%/users/' dir
//************************************
bool Profile::Load(PopString theFileName)
{
	mIntegerMap.clear();
	mBoolMap.clear();
	mFloatMap.clear();
	mStringMap.clear();

	XMLParser aParser;

	if (aParser.OpenFile(theFileName) && !aParser.HasFailed())
	{
		XMLElement aNode;

		ParseXML(&aParser);
		return true; // SUCCESS
	}

	// FAILURE
	return false;
}

// This can be done inline with the code, but makes it messy
bool Profile::HasAttribute(PopLib::XMLElement *theNode, PopString theAttrib)
{
	return (theNode && theNode->mAttributes.find(theAttrib) != theNode->mAttributes.end());
}

// I'm only passing the Parser to this class because the Profile is the only thing
// we are storing in this class.  See Notes below.
void Profile::ParseXML(PopLib::XMLParser *theParser)
{
	if (!theParser)
		return; // OOPS

	XMLElement aNode;

	while (theParser->NextElement(&aNode)) // The Node gets fill with the next node data
	{
		switch (aNode.mType)
		{
		case XMLElement::TYPE_START: // the open tag.  eg: <Profile>
		{
			if (aNode.mValue == "Profile") // Corresponds with the SAVE()
			{
			}
			else if (aNode.mValue == "Bool") // Corresponds with the SAVE()
			{
				if (HasAttribute(&aNode, "id") && HasAttribute(&aNode, "value"))
				{
					PopString anId = aNode.mAttributes["id"];
					PopString aValue = aNode.mAttributes["value"];
					bool aBoolean = (aValue == "true" || aValue == "TRUE" || aValue == "1" ||
									 aValue == "yes" || aValue == "YES");

					mBoolMap.insert(std::pair<PopString, bool>(anId, aBoolean));
				}
			}
			else if (aNode.mValue == "String") // Corresponds with the SAVE()
			{
				if (HasAttribute(&aNode, "id") && HasAttribute(&aNode, "value"))
				{
					PopString anId = aNode.mAttributes["id"];
					PopString aValue = aNode.mAttributes["value"];

					mStringMap.insert(std::pair<PopString, PopString>(anId, aValue));
				}
			}
			else if (aNode.mValue == "Float") // Corresponds with the SAVE()
			{
				if (HasAttribute(&aNode, "id") && HasAttribute(&aNode, "value"))
				{
					PopString anId = aNode.mAttributes["id"];
					double aValue = atof(aNode.mAttributes["value"].c_str());

					mFloatMap.insert(std::pair<PopString, double>(anId, aValue));
				}
			}
			else if (aNode.mValue == "Integer")
			{
				if (HasAttribute(&aNode, "id") && HasAttribute(&aNode, "value"))
				{
					PopString anId = aNode.mAttributes["id"];
					int aValue = atoi(aNode.mAttributes["value"].c_str());

					mIntegerMap.insert(std::pair<PopString, int>(anId, aValue));
				}
			}
			break;
		}
		case XMLElement::TYPE_END: // The closing tag. eg: </Profile>
		{
			break;
		}
		}
	}
}

//************************************
// Method:    LoadUser
// FullName:  PopLib::Profile::LoadUser
// Access:    public
// Returns:   bool
// Description: Changes the currently loaded user to theUserName.
//				This is one of the main methods you will be using.
// Parameter: PopString theUserName
//************************************
bool Profile::LoadUser(PopString theUserName)
{
	SetUserName(theUserName);
	if (mUserName != "")
	{
		std::string aFileName = GetUserFileName(mUserName);

		if (PopLib::FileExists(aFileName))
		{
			return Load(aFileName);
		}
	}

	SetUserName("");
	return false;
}

//************************************
// Method:    SaveUser
// FullName:  PopLib::Profile::SaveUser
// Access:    public
// Returns:   bool
// Description: Saves the currently loaded user's profile
//				This is one of the main methods you will be using.
//************************************
bool Profile::SaveUser()
{
	if (mUserName != "")
	{
		std::string aFileName = GetUserFileName(mUserName);
		MkDir(GetFileDir(aFileName));

		return Save(aFileName);
	}
	return false;
}

//************************************
// Method:    NewUser
// FullName:  PopLib::Profile::NewUser
// Access:    public
// Returns:   bool
// Description: Creates a new user from the specified user name
//				This is one of the main methods you will be using.
// Parameter: PopString theUserName
//************************************
bool Profile::NewUser(PopString theUserName)
{
	SetUserName(theUserName);
	gAppBase->RegistryWriteString("LastProfileName", mUserName);
	ResetProfile();
	return SaveUser();
}

//************************************
// Method:    RenameUser
// FullName:  PopLib::Profile::RenameUser
// Access:    public
// Returns:   bool
// Description: Rename the userprofile-file
//				This is one of the main methods you will be using.
//				(caller: maybe remember to rename the scores of the user)
// Parameter: PopString theNewUserName
//************************************
bool Profile::RenameUser(PopString theNewUserName)
{
	if (theNewUserName != "")
	{
		PopString OldUserName = mUserName; // remember old username

		if (SetUserName(theNewUserName) == true) // sets mUserName to theNewUserName if successful
		{
			std::string OldFileName = GetUserFileName(OldUserName);
			std::string NewFileName = GetUserFileName(mUserName);

			rename(OldFileName.c_str(), NewFileName.c_str());

			return true;
		}
		else
		{
			return false;
		}
	}
	return false;
}

//************************************
// Method:    DeleteUser
// FullName:  PopLib::Profile::DeleteUser
// Access:    public
// Returns:   bool
// Description: Delete the profile-file
//				This is one of the main methods you will be using.
// 				(caller: maybe remember to delete the scores of the user)
// Parameter: PopString theUserName
//************************************
bool Profile::DeleteUser(PopString theUserName)
{
	if (theUserName != "")
	{
		std::string aFileName = GetUserFileName(theUserName);

		remove(aFileName.c_str());

		return true;
	}
	return false;
}

//************************************
// Method:    SetUserName
// FullName:  PopLib::Profile::SetUserName
// Access:    public
// Returns:   bool
// Description: internally used method to validate the user name
//				this is primarily because Windows has file name
//				restrictions!
// Parameter: PopString theUserName
//************************************
bool Profile::SetUserName(PopString theUserName)
{
	// don�t allow the following chars in a username
	for (unsigned int i = 0; i < theUserName.length(); i++)
	{
		if (theUserName[i] == '\\' || theUserName[i] == '/' || theUserName[i] == ':' || theUserName[i] == '?' ||
			theUserName[i] == '"' || theUserName[i] == '<' || theUserName[i] == '>' || theUserName[i] == '|')
		{
			// bad User Name
			return false;
		}
	}

	mUserName = theUserName;
	// write registry key if the username was entered in a dialog
	gAppBase->RegistryWriteString("LastProfileName", mUserName);
	return true;
}

//************************************
// Method:    ResetProfile
// FullName:  PopLib::Profile::ResetProfile
// Access:    public
// Returns:   void
// Description: Use this to reset the user to 0!
//************************************
void Profile::ResetProfile()
{
	mFloatMap.clear();
	mIntegerMap.clear();
	mStringMap.clear();
	mBoolMap.clear();
}

//************************************
// Method:    SetBoolValue
// FullName:  PopLib::Profile::SetBoolValue
// Access:    public
// Returns:   void
// Description: Sets the specified Variable to the Value
// Parameter: PopString theValueName
// Parameter: bool theValue
//************************************
void PopLib::Profile::SetBoolValue(PopString theValueName, bool theValue)
{
	if (mBoolMap.find(theValueName) != mBoolMap.end())
		mBoolMap[theValueName] = theValue;
	else
		mBoolMap.insert(std::pair<PopString, bool>(theValueName, theValue));
}

//************************************
// Method:    GetBoolValue
// FullName:  PopLib::Profile::GetBoolValue
// Access:    public
// Returns:   bool
// Description: Gets the Specified variable, and returns theDefault if not found
//				Warning: does not add the variable if not present.  This is useful
//				for unlocking secret things!
// Parameter: PopString theValueName
// Parameter: bool theDefault
//************************************
bool PopLib::Profile::GetBoolValue(PopString theValueName, bool theDefault)
{
	if (mBoolMap.find(theValueName) != mBoolMap.end())
		return mBoolMap[theValueName];

	return theDefault;
}

//************************************
// Method:    SetFloatValue
// FullName:  PopLib::Profile::SetFloatValue
// Access:    public
// Returns:   void
// Description:  Sets the specified Variable to the Value
// Parameter: PopString theValueName
// Parameter: double theValue
//************************************
void PopLib::Profile::SetFloatValue(PopString theValueName, double theValue)
{
	if (mFloatMap.find(theValueName) != mFloatMap.end())
		mFloatMap[theValueName] = theValue;
	else
		mFloatMap.insert(std::pair<PopString, double>(theValueName, theValue));
}

//************************************
// Method:    GetFloatValue
// FullName:  PopLib::Profile::GetFloatValue
// Access:    public
// Returns:   double
// Description: Gets the Specified variable, and returns theDefault if not found
//				Warning: does not add the variable if not present.  This is useful
//				for unlocking secret things!
// Parameter: PopString theValueName
// Parameter: double theDefault
//************************************
double PopLib::Profile::GetFloatValue(PopString theValueName, double theDefault)
{
	if (mFloatMap.find(theValueName) != mFloatMap.end())
		return mFloatMap[theValueName];

	return theDefault;
}

//************************************
// Method:    SetStringValue
// FullName:  PopLib::Profile::SetStringValue
// Access:    public
// Returns:   void
// Description:  Sets the specified Variable to the Value
// Parameter: PopString theValueName
// Parameter: PopString theValue
//************************************
void PopLib::Profile::SetStringValue(PopString theValueName, PopString theValue)
{
	if (mStringMap.find(theValueName) != mStringMap.end())
		mStringMap[theValueName] = theValue;
	else
		mStringMap.insert(std::pair<PopString, PopString>(theValueName, theValue));
}

//************************************
// Method:    GetStringValue
// FullName:  PopLib::Profile::GetStringValue
// Access:    public
// Returns:   PopString
// Description: Gets the Specified variable, and returns theDefault if not found
//				Warning: does not add the variable if not present.  This is useful
//				for unlocking secret things!
// Parameter: PopString theValueName
// Parameter: PopString theDefault
//************************************
PopString PopLib::Profile::GetStringValue(PopString theValueName, PopString theDefault)
{
	if (mStringMap.find(theValueName) != mStringMap.end())
		return mStringMap[theValueName];

	return theDefault;
}

//************************************
// Method:      EraseStateSaves
// FullName:    PopLib::Profile::EraseStateSaves
// Access:      virtual public
// Returns:     void
// Parameter:   PopString theUserName
// Description: To help manage game states, states are saved in a user
//				sub-folder. To delete all the states, just delete the folder.
//************************************
void PopLib::Profile::EraseStateSaves(PopString theUserName)
{
	if (theUserName == "")
	{
		std::string aUserName = mUserName;
		std::string aStatePath = StrFormat("%susers/%s/", GetAppDataFolder().c_str(), aUserName.c_str());

		Deltree(aStatePath);
	}
	else
	{
		std::string aUserName = theUserName;
		std::string aStatePath = StrFormat("%susers/%s/", GetAppDataFolder().c_str(), aUserName.c_str());

		Deltree(aStatePath);
	}
}