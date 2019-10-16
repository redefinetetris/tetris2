#include "RTDBSession.h"
#include "../RTNSDB.h"
#include "../RTNSLog.h"
#include "../RTNSTool.h"


CRTDBSession::CRTDBSession()
	: CRTDBBase("sessions", 128)
	, m_ID(0)
	, m_RootID(0)
	, m_TimeStamp("")
	, m_UserID(0)
	, m_StateID(RTNSDB::StateGood())
{
}


CRTDBSession::CRTDBSession(const CRTDBSession &_other)
	: CRTDBBase(_other)
	, m_ID(_other.m_ID)
	, m_RootID(_other.m_RootID)
	, m_TimeStamp(_other.m_TimeStamp)
	, m_UserID(_other.m_UserID)
	, m_StateID(_other.m_StateID)
{
}


CRTDBSession::~CRTDBSession()
{
}


int CRTDBSession::GetIndex(void) const
{
	return(this->GetID());
}


int CRTDBSession::GetColumnSize(void) const
{
	return(5);
}


CRTDict CRTDBSession::GetColumnValue(void) const
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


std::vector<std::string> CRTDBSession::GetAllColumn(void) const
{
	const static std::vector<std::string> _SessionColumns{
		"id",
		"rootid",
		"timestamp",
		"userid",
		"stateid",
	};

	return(_SessionColumns);
}


std::vector<std::string> CRTDBSession::GetAllValue(void) const
{
	const std::vector<std::string> _SessionValues{
		RTNSTool::int2string(m_ID),
		RTNSTool::int2string(m_RootID),
		m_TimeStamp,
		RTNSTool::int2string(m_UserID),
		RTNSTool::int2string(m_StateID),
	};

	return(_SessionValues);
}


void CRTDBSession::SetAllValue(const std::vector<std::string>& _Values)
{
	m_ID = RTNSTool::string2int(_Values[0]);
	m_RootID = RTNSTool::string2int(_Values[1]);
	m_TimeStamp = _Values[2];
	m_UserID = RTNSTool::string2int(_Values[3]);
	m_StateID = RTNSTool::string2int(_Values[4]);

	if (RTNSDB::StateDelete() == m_StateID)
	{
		this->SetObjStyle(RTDBOS_Delete);
	}
}


int CRTDBSession::GetID(void) const
{
	return(m_ID);
}


void CRTDBSession::SetID(const int _ID)
{
	m_ID = _ID;
}


int CRTDBSession::GetRootID(void) const
{
	return(m_RootID);
}


void CRTDBSession::SetRootID(const int _RootID)
{
	m_RootID = _RootID;
}


std::string CRTDBSession::GetTimeStamp(void) const
{
	return(m_TimeStamp);
}


void CRTDBSession::SetTimeStamp(const std::string _TimeStamp)
{
	m_TimeStamp = _TimeStamp;
}


int CRTDBSession::GetUserID(void) const
{
	return(m_UserID);
}


void CRTDBSession::SetUserID(const int _UserID)
{
	m_UserID = _UserID;
}


int CRTDBSession::GetStateID(void) const
{
	return(m_StateID);
}


void CRTDBSession::SetStateID(const int _StateID)
{
	m_StateID = _StateID;

	if (RTNSDB::StateDelete() == m_StateID)
	{
		this->SetObjStyle(RTDBOS_Delete);
	}
}

