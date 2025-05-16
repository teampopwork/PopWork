#ifndef __PROFILE_H__
#define __PROFILE_H__
#ifdef _WIN32
#pragma once
#endif

#include "common.h"
#include <map>

namespace PopWork
{
class XMLParser; // Forward Class declaration to avoid Include files
class XMLElement;

class Profile
{
	// 'Protected' Section allows only classes derived from Profile
	// To access it's class members. We will Access these variables
	// through Get/Set functions (which will validate)
  protected:
	PopWorkString mUserName;

	std::map<PopWorkString, int> mIntegerMap;
	std::map<PopWorkString, bool> mBoolMap;
	std::map<PopWorkString, PopWorkString> mStringMap;
	std::map<PopWorkString, double> mFloatMap;

	Profile();

  public:
	static Profile *GetProfile();
	virtual ~Profile();

	// Serialization Functions
  public:
	virtual bool Save(PopWorkString theFileName); // Returns 'true' if success
	virtual bool Load(PopWorkString theFileName); // Returns 'true' if success
	virtual void ParseXML(PopWork::XMLParser *theParser);
	virtual bool HasAttribute(PopWork::XMLElement *theNode, PopWorkString theAttrib);

	// Even More Abstract Serialization functions
  public:
	virtual bool LoadUser(PopWorkString theUserName);	   // Load the User from the users dir
	virtual bool SaveUser();							   // Called to Save this User
	virtual bool NewUser(PopWorkString theUserName);	   // Called to start a New User
	virtual bool RenameUser(PopWorkString theNewUserName); // Called to Rename User
	virtual bool DeleteUser(PopWorkString theUserName);	   // Called to Delete User

	// Member Variable Get/Set Methods
  public:
	virtual PopWorkString GetUserName()
	{
		return mUserName;
	};													 // returns the User Name
	virtual bool SetUserName(PopWorkString theUserName); // Returns 'true' if success

	virtual void ResetProfile();

	// A new Feature!  Allows for Multiple State Types!  Story mode, Casual Mode, Mini Game Mode
	virtual std::string GetStateFileName(PopWorkString theStateName, PopWorkString theUserName = _S(""));
	virtual void EraseStateSaves(PopWorkString theUserName = _S(""));
	virtual std::string GetUserFileName(PopWorkString theUserName = _S(""));

	// Another Cool Feature!  Read and Write integers with String Values!
	virtual void SetIntegerValue(PopWorkString theValueName, int theValue);
	virtual int GetIntegerValue(PopWorkString theValueName, int theDefault);

	virtual void SetBoolValue(PopWorkString theValueName, bool theValue);
	virtual bool GetBoolValue(PopWorkString theValueName, bool theDefault);

	virtual void SetFloatValue(PopWorkString theValueName, double theValue);
	virtual double GetFloatValue(PopWorkString theValueName, double theDefault);

	virtual void SetStringValue(PopWorkString theValueName, PopWorkString theValue);
	virtual PopWorkString GetStringValue(PopWorkString theValueName, PopWorkString theDefault);
};
}; // namespace PopWork

#define GETPROFILEINT(a, b) PopWork::Profile::GetProfile()->GetIntegerValue(a, b)
#define GETPROFILEFLOAT(a, b) PopWork::Profile::GetProfile()->GetFloat(a, b)
#define GETPROFILEBOOL(a, b) PopWork::Profile::GetProfile()->GetBooleanValue(a, b)
#define GETPROFILESTRING(a, b) PopWork::Profile::GetProfile()->GetStringValue(a, b)

#define SETPROFILEINT(a, b) PopWork::Profile::GetProfile()->SetIntegerValue(a, b)
#define SETPROFILEFLOAT(a, b) PopWork::Profile::GetProfile()->SetFloat(a, b)
#define SETPROFILEBOOL(a, b) PopWork::Profile::GetProfile()->SetBooleanValue(a, b)
#define SETPROFILESTRING(a, b) PopWork::Profile::GetProfile()->SetStringValue(a, b)

#endif