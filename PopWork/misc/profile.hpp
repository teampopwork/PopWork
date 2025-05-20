#ifndef __PROFILE_HPP__
#define __PROFILE_HPP__
#ifdef _WIN32
#pragma once
#endif

#include "common.hpp"
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
	PopString mUserName;

	std::map<PopString, int> mIntegerMap;
	std::map<PopString, bool> mBoolMap;
	std::map<PopString, PopString> mStringMap;
	std::map<PopString, double> mFloatMap;

	Profile();

  public:
	static Profile *GetProfile();
	virtual ~Profile();

	// Serialization Functions
  public:
	virtual bool Save(PopString theFileName); // Returns 'true' if success
	virtual bool Load(PopString theFileName); // Returns 'true' if success
	virtual void ParseXML(PopWork::XMLParser *theParser);
	virtual bool HasAttribute(PopWork::XMLElement *theNode, PopString theAttrib);

	// Even More Abstract Serialization functions
  public:
	virtual bool LoadUser(PopString theUserName);	   // Load the User from the users dir
	virtual bool SaveUser();							   // Called to Save this User
	virtual bool NewUser(PopString theUserName);	   // Called to start a New User
	virtual bool RenameUser(PopString theNewUserName); // Called to Rename User
	virtual bool DeleteUser(PopString theUserName);	   // Called to Delete User

	// Member Variable Get/Set Methods
  public:
	virtual PopString GetUserName()
	{
		return mUserName;
	};													 // returns the User Name
	virtual bool SetUserName(PopString theUserName); // Returns 'true' if success

	virtual void ResetProfile();

	// A new Feature!  Allows for Multiple State Types!  Story mode, Casual Mode, Mini Game Mode
	virtual std::string GetStateFileName(PopString theStateName, PopString theUserName = _S(""));
	virtual void EraseStateSaves(PopString theUserName = _S(""));
	virtual std::string GetUserFileName(PopString theUserName = _S(""));

	// Another Cool Feature!  Read and Write integers with String Values!
	virtual void SetIntegerValue(PopString theValueName, int theValue);
	virtual int GetIntegerValue(PopString theValueName, int theDefault);

	virtual void SetBoolValue(PopString theValueName, bool theValue);
	virtual bool GetBoolValue(PopString theValueName, bool theDefault);

	virtual void SetFloatValue(PopString theValueName, double theValue);
	virtual double GetFloatValue(PopString theValueName, double theDefault);

	virtual void SetStringValue(PopString theValueName, PopString theValue);
	virtual PopString GetStringValue(PopString theValueName, PopString theDefault);
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