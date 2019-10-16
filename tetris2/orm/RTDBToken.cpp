#include "RTDBToken.h"
#include "../RTNSDB.h"
#include "../RTNSLog.h"
#include "../RTNSTool.h"


CRTDBToken::CRTDBToken()
	: CRTDBBase("tokens", 2048)
	, m_ID(0)
	, m_TimeStamp("")
	, m_UserID(0)
	, m_Token("")
	, m_StateID(RTNSDB::StateGood())
{
}


CRTDBToken::CRTDBToken(const CRTDBToken &_other)
	: CRTDBBase(_other)
	, m_ID(_other.m_ID)
	, m_TimeStamp(_other.m_TimeStamp)
	, m_UserID(_other.m_UserID)
	, m_Token(_other.m_Token)
	, m_StateID(_other.m_StateID)
{
}


CRTDBToken::~CRTDBToken()
{
}


int CRTDBToken::GetIndex(void) const
{
	return(this->GetID());
}


int CRTDBToken::GetColumnSize(void) const
{
	return(5);
}


CRTDict CRTDBToken::GetColumnValue(void) const
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


std::vector<std::string> CRTDBToken::GetAllColumn(void) const
{
	const static std::vector<std::string> _TokenColumns{
		"id",
		"timestamp",
		"userid",
		"token",
		"stateid",
	};

	return(_TokenColumns);
}


std::vector<std::string> CRTDBToken::GetAllValue(void) const
{
	const std::vector<std::string> _TokenValues{
		RTNSTool::int2string(m_ID),
		m_TimeStamp,
		RTNSTool::int2string(m_UserID),
		m_Token,
		RTNSTool::int2string(m_StateID),
	};

	return(_TokenValues);
}


void CRTDBToken::SetAllValue(const std::vector<std::string>& _Values)
{
	m_ID = RTNSTool::string2int(_Values[0]);
	m_TimeStamp = _Values[1];
	m_UserID = RTNSTool::string2int(_Values[2]);
	m_Token = _Values[3];
	m_StateID = RTNSTool::string2int(_Values[4]);

	if (RTNSDB::StateDelete() == m_StateID)
	{
		this->SetObjStyle(RTDBOS_Delete);
	}
}


int CRTDBToken::GetID(void) const
{
	return(m_ID);
}


void CRTDBToken::SetID(const int _ID)
{
	m_ID = _ID;
}


std::string CRTDBToken::GetTimeStamp(void) const
{
	return(m_TimeStamp);
}


void CRTDBToken::SetTimeStamp(const std::string _TimeStamp)
{
	m_TimeStamp = _TimeStamp;
}


int CRTDBToken::GetUserID(void) const
{
	return(m_UserID);
}


void CRTDBToken::SetUserID(const int _UserID)
{
	m_UserID = _UserID;
}


std::string CRTDBToken::GetToken(void) const
{
	return(m_Token);
}


void CRTDBToken::SetToken(const std::string _Token)
{
	m_Token = _Token;
}


int CRTDBToken::GetStateID(void) const
{
	return(m_StateID);
}


void CRTDBToken::SetStateID(const int _StateID)
{
	m_StateID = _StateID;

	if (RTNSDB::StateDelete() == m_StateID)
	{
		this->SetObjStyle(RTDBOS_Delete);
	}
}

