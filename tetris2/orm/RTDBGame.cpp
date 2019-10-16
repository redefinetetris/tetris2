#include "RTDBGame.h"
#include "../RTNSDB.h"
#include "../RTNSLog.h"
#include "../RTNSTool.h"


CRTDBGame::CRTDBGame()
	: CRTDBBase("games", 128)
	, m_ID(0)
	, m_TimeStamp("")
	, m_SessionID(0)
	, m_UserID(0)
	, m_StateID(RTNSDB::StateGood())
{
}


CRTDBGame::CRTDBGame(const CRTDBGame &_other)
	: CRTDBBase(_other)
	, m_ID(_other.m_ID)
	, m_TimeStamp(_other.m_TimeStamp)
	, m_SessionID(_other.m_SessionID)
	, m_UserID(_other.m_UserID)
	, m_StateID(_other.m_StateID)
{
}


CRTDBGame::~CRTDBGame()
{
}


int CRTDBGame::GetIndex(void) const
{
	return(this->GetID());
}


int CRTDBGame::GetColumnSize(void) const
{
	return(5);
}


CRTDict CRTDBGame::GetColumnValue(void) const
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


std::vector<std::string> CRTDBGame::GetAllColumn(void) const
{
	const static std::vector<std::string> _GameColumns{
		"id",
		"timestamp",
		"sessionid",
		"userid",
		"stateid",
	};

	return(_GameColumns);
}


std::vector<std::string> CRTDBGame::GetAllValue(void) const
{
	const std::vector<std::string> _GameValues{
		RTNSTool::int2string(m_ID),
		m_TimeStamp,
		RTNSTool::int2string(m_SessionID),
		RTNSTool::int2string(m_UserID),
		RTNSTool::int2string(m_StateID),
	};

	return(_GameValues);
}


void CRTDBGame::SetAllValue(const std::vector<std::string>& _Values)
{
	m_ID = RTNSTool::string2int(_Values[0]);
	m_TimeStamp = _Values[1];
	m_SessionID = RTNSTool::string2int(_Values[2]);
	m_UserID = RTNSTool::string2int(_Values[3]);
	m_StateID = RTNSTool::string2int(_Values[4]);

	if (RTNSDB::StateDelete() == m_StateID)
	{
		this->SetObjStyle(RTDBOS_Delete);
	}
}


int CRTDBGame::GetID(void) const
{
	return(m_ID);
}


void CRTDBGame::SetID(const int _ID)
{
	m_ID = _ID;
}


std::string CRTDBGame::GetTimeStamp(void) const
{
	return(m_TimeStamp);
}


void CRTDBGame::SetTimeStamp(const std::string _TimeStamp)
{
	m_TimeStamp = _TimeStamp;
}


int CRTDBGame::GetSessionID(void) const
{
	return(m_SessionID);
}


void CRTDBGame::SetSessionID(const int _SessionID)
{
	m_SessionID = _SessionID;
}


int CRTDBGame::GetUserID(void) const
{
	return(m_UserID);
}


void CRTDBGame::SetUserID(const int _UserID)
{
	m_UserID = _UserID;
}


int CRTDBGame::GetStateID(void) const
{
	return(m_StateID);
}


void CRTDBGame::SetStateID(const int _StateID)
{
	m_StateID = _StateID;

	if (RTNSDB::StateDelete() == m_StateID)
	{
		this->SetObjStyle(RTDBOS_Delete);
	}
}

