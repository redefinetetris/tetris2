#include "RTDBRoot.h"
#include "../RTNSDB.h"
#include "../RTNSLog.h"
#include "../RTNSTool.h"


CRTDBRoot::CRTDBRoot()
	: CRTDBBase("roots", 128)
	, m_ID(0)
	, m_TimeStamp("")
	, m_UserID(0)
	, m_StateID(RTNSDB::StateGood())
{
}


CRTDBRoot::CRTDBRoot(const CRTDBRoot &_other)
	: CRTDBBase(_other)
	, m_ID(_other.m_ID)
	, m_TimeStamp(_other.m_TimeStamp)
	, m_UserID(_other.m_UserID)
	, m_StateID(_other.m_StateID)
{
}


CRTDBRoot::~CRTDBRoot()
{
}


int CRTDBRoot::GetIndex(void) const
{
	return(this->GetID());
}


int CRTDBRoot::GetColumnSize(void) const
{
	return(4);
}


CRTDict CRTDBRoot::GetColumnValue(void) const
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


std::vector<std::string> CRTDBRoot::GetAllColumn(void) const
{
	const static std::vector<std::string> _RootColumns{
		"id",
		"timestamp",
		"userid",
		"stateid",
	};

	return(_RootColumns);
}


std::vector<std::string> CRTDBRoot::GetAllValue(void) const
{
	const std::vector<std::string> _RootValues{
		RTNSTool::int2string(m_ID),
		m_TimeStamp,
		RTNSTool::int2string(m_UserID),
		RTNSTool::int2string(m_StateID),
	};

	return(_RootValues);
}


void CRTDBRoot::SetAllValue(const std::vector<std::string>& _Values)
{
	m_ID = RTNSTool::string2int(_Values[0]);
	m_TimeStamp = _Values[1];
	m_UserID = RTNSTool::string2int(_Values[2]);
	m_StateID = RTNSTool::string2int(_Values[3]);

	if (RTNSDB::StateDelete() == m_StateID)
	{
		this->SetObjStyle(RTDBOS_Delete);
	}
}


int CRTDBRoot::GetID(void) const
{
	return(m_ID);
}


void CRTDBRoot::SetID(const int _ID)
{
	m_ID = _ID;
}


std::string CRTDBRoot::GetTimeStamp(void) const
{
	return(m_TimeStamp);
}


void CRTDBRoot::SetTimeStamp(const std::string _TimeStamp)
{
	m_TimeStamp = _TimeStamp;
}


int CRTDBRoot::GetUserID(void) const
{
	return(m_UserID);
}


void CRTDBRoot::SetUserID(const int _UserID)
{
	m_UserID = _UserID;
}


int CRTDBRoot::GetStateID(void) const
{
	return(m_StateID);
}


void CRTDBRoot::SetStateID(const int _StateID)
{
	m_StateID = _StateID;

	if (RTNSDB::StateDelete() == m_StateID)
	{
		this->SetObjStyle(RTDBOS_Delete);
	}
}

