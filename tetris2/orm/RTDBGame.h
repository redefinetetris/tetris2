#ifndef __RTDBGAME_H__
#define __RTDBGAME_H__


#include "RTDBBase.h"


class CRTDBGame : public CRTDBBase
{
public:
	CRTDBGame();
	CRTDBGame(const CRTDBGame &_other);
	~CRTDBGame();

private:
	int m_ID;
	std::string m_TimeStamp;
	int m_SessionID;
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

	std::string GetTimeStamp(void) const;
	void SetTimeStamp(const std::string _TimeStamp);

	int GetSessionID(void) const;
	void SetSessionID(const int _SessionID);

	int GetUserID(void) const;
	void SetUserID(const int _UserID);

	int GetStateID(void) const;
	void SetStateID(const int _StateID);
};


#endif//__RTDBGAME_H__

