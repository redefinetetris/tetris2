#ifndef __RTDBCURSOR_H__
#define __RTDBCURSOR_H__


#include "RTDBBase.h"


class CRTDBCursor : public CRTDBBase
{
public:
	CRTDBCursor();
	CRTDBCursor(const CRTDBCursor &_other);
	~CRTDBCursor();

private:
	int m_ID;
	int m_RootID;
	int m_SessionID;
	int m_GameID;
	int m_StartReplayID;
	int m_EndReplayID;
	int m_Current;
	int m_Force;
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

	int GetSessionID(void) const;
	void SetSessionID(const int _SessionID);

	int GetGameID(void) const;
	void SetGameID(const int _GameID);

	int GetStartReplayID(void) const;
	void SetStartReplayID(const int _StartReplayID);

	int GetEndReplayID(void) const;
	void SetEndReplayID(const int _EndReplayID);

	int GetCurrent(void) const;
	int GetCurrent(const int _OpIndex);
	void SetCurrent(const int _Current);

	int GetForce(void) const;
	void SetForce(const int _Force);

	int GetStateID(void) const;
	void SetStateID(const int _StateID);
};


#endif//__RTDBCURSOR_H__

