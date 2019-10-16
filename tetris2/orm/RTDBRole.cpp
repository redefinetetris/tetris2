#include "RTDBRole.h"
#include "../RTNSDB.h"
#include "../RTNSLog.h"
#include "../RTNSTool.h"


CRTDBRole::CRTDBRole()
	: CRTDBBase("roles", 256)
	, m_ID(0)
	, m_TimeStamp("")
	, m_Name("")
	, m_LangName("")
	, m_StateID(RTNSDB::StateGood())
{
}


CRTDBRole::CRTDBRole(const CRTDBRole &_other)
	: CRTDBBase(_other)
	, m_ID(_other.m_ID)
	, m_TimeStamp(_other.m_TimeStamp)
	, m_Name(_other.m_Name)
	, m_LangName(_other.m_LangName)
	, m_StateID(_other.m_StateID)
{
}


CRTDBRole::~CRTDBRole()
{
}


int CRTDBRole::GetIndex(void) const
{
	return(this->GetID());
}


int CRTDBRole::GetColumnSize(void) const
{
	return(5);
}


CRTDict CRTDBRole::GetColumnValue(void) const
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


std::vector<std::string> CRTDBRole::GetAllColumn(void) const
{
	const static std::vector<std::string> _RoleColumns{
		"id",
		"timestamp",
		"name",
		"langname",
		"stateid",
	};

	return(_RoleColumns);
}


std::vector<std::string> CRTDBRole::GetAllValue(void) const
{
	const std::vector<std::string> _RoleValues{
		RTNSTool::int2string(m_ID),
		m_TimeStamp,
		m_Name,
		m_LangName,
		RTNSTool::int2string(m_StateID),
	};

	return(_RoleValues);
}


void CRTDBRole::SetAllValue(const std::vector<std::string>& _Values)
{
	m_ID = RTNSTool::string2int(_Values[0]);
	m_TimeStamp = _Values[1];
	m_Name = _Values[2];
	m_LangName = _Values[3];
	m_StateID = RTNSTool::string2int(_Values[4]);

	if (RTNSDB::StateDelete() == m_StateID)
	{
		this->SetObjStyle(RTDBOS_Delete);
	}
}


int CRTDBRole::GetID(void) const
{
	return(m_ID);
}


void CRTDBRole::SetID(const int _ID)
{
	m_ID = _ID;
}


std::string CRTDBRole::GetTimeStamp(void) const
{
	return(m_TimeStamp);
}


void CRTDBRole::SetTimeStamp(const std::string _TimeStamp)
{
	m_TimeStamp = _TimeStamp;
}


std::string CRTDBRole::GetName(void) const
{
	return(m_Name);
}


void CRTDBRole::SetName(const std::string _Name)
{
	m_Name = _Name;
}


std::string CRTDBRole::GetLangName(void) const
{
	return(m_LangName);
}


void CRTDBRole::SetLangName(const std::string _LangName)
{
	m_LangName = _LangName;
}


int CRTDBRole::GetStateID(void) const
{
	return(m_StateID);
}


void CRTDBRole::SetStateID(const int _StateID)
{
	m_StateID = _StateID;

	if (RTNSDB::StateDelete() == m_StateID)
	{
		this->SetObjStyle(RTDBOS_Delete);
	}
}

