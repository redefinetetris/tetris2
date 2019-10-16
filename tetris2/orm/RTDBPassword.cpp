#include "RTDBPassword.h"
#include "../RTNSDB.h"
#include "../RTNSLog.h"
#include "../RTNSTool.h"


CRTDBPassword::CRTDBPassword()
	: CRTDBBase("passwords", 128)
	, m_ID(0)
	, m_TimeStamp("")
	, m_UserID(0)
	, m_Key("")
	, m_StateID(RTNSDB::StateGood())
{
}


CRTDBPassword::CRTDBPassword(const CRTDBPassword &_other)
	: CRTDBBase(_other)
	, m_ID(_other.m_ID)
	, m_TimeStamp(_other.m_TimeStamp)
	, m_UserID(_other.m_UserID)
	, m_Key(_other.m_Key)
	, m_StateID(_other.m_StateID)
{
}


CRTDBPassword::~CRTDBPassword()
{
}


int CRTDBPassword::GetIndex(void) const
{
	return(this->GetID());
}


int CRTDBPassword::GetColumnSize(void) const
{
	return(5);
}


CRTDict CRTDBPassword::GetColumnValue(void) const
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


std::vector<std::string> CRTDBPassword::GetAllColumn(void) const
{
	const static std::vector<std::string> _PasswordColumns{
		"id",
		"timestamp",
		"userid",
		"key",
		"stateid",
	};

	return(_PasswordColumns);
}


std::vector<std::string> CRTDBPassword::GetAllValue(void) const
{
	const std::vector<std::string> _PasswordValues{
		RTNSTool::int2string(m_ID),
		m_TimeStamp,
		RTNSTool::int2string(m_UserID),
		m_Key,
		RTNSTool::int2string(m_StateID),
	};

	return(_PasswordValues);
}


void CRTDBPassword::SetAllValue(const std::vector<std::string>& _Values)
{
	m_ID = RTNSTool::string2int(_Values[0]);
	m_TimeStamp = _Values[1];
	m_UserID = RTNSTool::string2int(_Values[2]);
	m_Key = _Values[3];
	m_StateID = RTNSTool::string2int(_Values[4]);

	if (RTNSDB::StateDelete() == m_StateID)
	{
		this->SetObjStyle(RTDBOS_Delete);
	}
}


int CRTDBPassword::GetID(void) const
{
	return(m_ID);
}


void CRTDBPassword::SetID(const int _ID)
{
	m_ID = _ID;
}


std::string CRTDBPassword::GetTimeStamp(void) const
{
	return(m_TimeStamp);
}


void CRTDBPassword::SetTimeStamp(const std::string _TimeStamp)
{
	m_TimeStamp = _TimeStamp;
}


int CRTDBPassword::GetUserID(void) const
{
	return(m_UserID);
}


void CRTDBPassword::SetUserID(const int _UserID)
{
	m_UserID = _UserID;
}


std::string CRTDBPassword::GetKey(void) const
{
	return(m_Key);
}


void CRTDBPassword::SetKey(const std::string _Key)
{
	m_Key = _Key;
}


int CRTDBPassword::GetStateID(void) const
{
	return(m_StateID);
}


void CRTDBPassword::SetStateID(const int _StateID)
{
	m_StateID = _StateID;

	if (RTNSDB::StateDelete() == m_StateID)
	{
		this->SetObjStyle(RTDBOS_Delete);
	}
}

