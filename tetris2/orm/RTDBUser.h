#ifndef __RTDBUSER_H__
#define __RTDBUSER_H__


#include "RTDBBase.h"


class CRTDBUser : public CRTDBBase
{
public:
	CRTDBUser();
	CRTDBUser(const CRTDBUser &_other);
	~CRTDBUser();

private:
	int m_ID;
	std::string m_TimeStamp;
	std::string m_Name;
	std::string m_LangName;
	int m_RoleID;
	int m_StateID;


public:
	virtual int GetIndex(void) const;
	virtual int GetColumnSize(void) const;

	virtual CRTDict GetColumnValue(void) const;
	virtual std::vector<std::string> GetAllColumn(void) const;
	virtual std::vector<std::string> GetAllValue(void) const;
	virtual void SetAllValue(const std::vector<std::string>& _Values);

public:
	int GetID(void) const;
	void SetID(const int _ID);

	std::string GetTimeStamp(void) const;
	void SetTimeStamp(const std::string _TimeStamp);

	std::string GetName(void) const;
	void SetName(const std::string _Name);

	std::string GetLangName(void) const;
	void SetLangName(const std::string _LangName);

	int GetRoleID(void) const;
	void SetRoleID(const int _RoleID);

	int GetStateID(void) const;
	void SetStateID(const int _StateID);
};


#endif//__RTDBUSER_H__

