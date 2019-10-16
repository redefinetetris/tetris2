#ifndef __RTDBSESSION_H__
#define __RTDBSESSION_H__


#include "RTDBBase.h"


class CRTDBSession : public CRTDBBase
{
public:
	CRTDBSession();
	CRTDBSession(const CRTDBSession &_other);
	~CRTDBSession();

private:
	int m_ID;
	int m_RootID;
	std::string m_TimeStamp;
	int m_UserID;
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

	int GetRootID(void) const;
	void SetRootID(const int _RootID);

	std::string GetTimeStamp(void) const;
	void SetTimeStamp(const std::string _TimeStamp);

	int GetUserID(void) const;
	void SetUserID(const int _UserID);

	int GetStateID(void) const;
	void SetStateID(const int _StateID);
};


#endif//__RTDBSESSION_H__

