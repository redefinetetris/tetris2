#ifndef __RTDBTOKEN_H__
#define __RTDBTOKEN_H__


#include "RTDBBase.h"


class CRTDBToken : public CRTDBBase
{
public:
	CRTDBToken();
	CRTDBToken(const CRTDBToken &_other);
	~CRTDBToken();

private:
	int m_ID;
	std::string m_TimeStamp;
	int m_UserID;
	std::string m_Token;
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

	int GetUserID(void) const;
	void SetUserID(const int _UserID);

	std::string GetToken(void) const;
	void SetToken(const std::string _Token);

	int GetStateID(void) const;
	void SetStateID(const int _StateID);
};


#endif//__RTDBTOKEN_H__

