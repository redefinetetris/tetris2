#include "RTDBCursor.h"
#include "../RTNSDB.h"
#include "../RTNSLog.h"
#include "../RTNSTool.h"


CRTDBCursor::CRTDBCursor()
	: CRTDBBase("cursors", 128)
	, m_ID(0)
	, m_RootID(0)
	, m_SessionID(0)
	, m_GameID(0)
	, m_StartReplayID(0)
	, m_EndReplayID(0)
	, m_Current(0)
	, m_Force(0)
	, m_StateID(RTNSDB::StateGood())
{
}


CRTDBCursor::CRTDBCursor(const CRTDBCursor &_other)
	: CRTDBBase(_other)
	, m_ID(_other.m_ID)
	, m_RootID(_other.m_RootID)
	, m_SessionID(_other.m_SessionID)
	, m_GameID(_other.m_GameID)
	, m_StartReplayID(_other.m_StartReplayID)
	, m_EndReplayID(_other.m_EndReplayID)
	, m_Current(_other.m_Current)
	, m_Force(_other.m_Force)
	, m_StateID(_other.m_StateID)
{
}


CRTDBCursor::~CRTDBCursor()
{
}


int CRTDBCursor::GetIndex(void) const
{
	return(this->GetID());
}


int CRTDBCursor::GetColumnSize(void) const
{
	return(9);
}


CRTDict CRTDBCursor::GetColumnValue(void) const
{
	CRTDict Result;
	const auto Columns = this->GetAllColumn();
	const auto Values = this->GetAllValue();
	const auto Length = this->GetColumnSize();

	for (int index = 0; index < Length; ++index)
	{
		const auto key   = Columns[index];
		const auto value = Values[index];

		Result[key] = value;
	}

	return(Result);
}


std::vector<std::string> CRTDBCursor::GetAllColumn(void) const
{
	const static std::vector<std::string> _CursorColumns{
		"id",
		"rootid",
		"sessionid",
		"gameid",
		"startreplayid",
		"endreplayid",
		"current",
		"force",
		"stateid",
	};

	return(_CursorColumns);
}


std::vector<std::string> CRTDBCursor::GetAllValue(void) const
{
	const std::vector<std::string> _CursorValues{
		RTNSTool::int2string(m_ID),
		RTNSTool::int2string(m_RootID),
		RTNSTool::int2string(m_SessionID),
		RTNSTool::int2string(m_GameID),
		RTNSTool::int2string(m_StartReplayID),
		RTNSTool::int2string(m_EndReplayID),
		RTNSTool::int2string(m_Current),
		RTNSTool::int2string(m_Force),
		RTNSTool::int2string(m_StateID),
	};

	return(_CursorValues);
}


void CRTDBCursor::SetAllValue(const std::vector<std::string>& _Values)
{
	m_ID = RTNSTool::string2int(_Values[0]);
	m_RootID = RTNSTool::string2int(_Values[1]);
	m_SessionID = RTNSTool::string2int(_Values[2]);
	m_GameID = RTNSTool::string2int(_Values[3]);
	m_StartReplayID = RTNSTool::string2int(_Values[4]);
	m_EndReplayID = RTNSTool::string2int(_Values[5]);
	m_Current = RTNSTool::string2int(_Values[6]);
	m_Force = RTNSTool::string2int(_Values[7]);
	m_StateID = RTNSTool::string2int(_Values[8]);

	if (RTNSDB::StateDelete() == m_StateID)
	{
		this->SetObjStyle(RTDBOS_Delete);
	}
}


int CRTDBCursor::GetID(void) const
{
	return(m_ID);
}


void CRTDBCursor::SetID(const int _ID)
{
	m_ID = _ID;
}


int CRTDBCursor::GetRootID(void) const
{
	return(m_RootID);
}


void CRTDBCursor::SetRootID(const int _RootID)
{
	m_RootID = _RootID;
}


int CRTDBCursor::GetSessionID(void) const
{
	return(m_SessionID);
}


void CRTDBCursor::SetSessionID(const int _SessionID)
{
	m_SessionID = _SessionID;
}


int CRTDBCursor::GetGameID(void) const
{
	return(m_GameID);
}


void CRTDBCursor::SetGameID(const int _GameID)
{
	m_GameID = _GameID;
}


int CRTDBCursor::GetStartReplayID(void) const
{
	return(m_StartReplayID);
}


void CRTDBCursor::SetStartReplayID(const int _StartReplayID)
{
	m_StartReplayID = _StartReplayID;
}


int CRTDBCursor::GetEndReplayID(void) const
{
	return(m_EndReplayID);
}


void CRTDBCursor::SetEndReplayID(const int _EndReplayID)
{
	m_EndReplayID = _EndReplayID;
}


int CRTDBCursor::GetCurrent(void) const
{
	return(m_Current);
}


int CRTDBCursor::GetCurrent(const int _OpIndex)
{
	const auto Old = m_Current;

	m_Current += _OpIndex;

	return(Old);
}


void CRTDBCursor::SetCurrent(const int _Current)
{
	m_Current = _Current;
}


int CRTDBCursor::GetForce(void) const
{
	return(m_Force);
}


void CRTDBCursor::SetForce(const int _Force)
{
	m_Force = _Force;
}


int CRTDBCursor::GetStateID(void) const
{
	return(m_StateID);
}


void CRTDBCursor::SetStateID(const int _StateID)
{
	m_StateID = _StateID;

	if (RTNSDB::StateDelete() == m_StateID)
	{
		this->SetObjStyle(RTDBOS_Delete);
	}
}

