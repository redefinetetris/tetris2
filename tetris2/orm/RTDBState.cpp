#include "RTDBState.h"
#include "../RTNSDB.h"
#include "../RTNSLog.h"
#include "../RTNSTool.h"


CRTDBState::CRTDBState()
	: CRTDBBase("states", 128)
	, m_ID(0)
	, m_Name("")
	, m_LangName("")
{
}


CRTDBState::CRTDBState(const CRTDBState &_other)
	: CRTDBBase(_other)
	, m_ID(_other.m_ID)
	, m_Name(_other.m_Name)
	, m_LangName(_other.m_LangName)
{
}


CRTDBState::~CRTDBState()
{
}


int CRTDBState::GetIndex(void) const
{
	return(this->GetID());
}


int CRTDBState::GetColumnSize(void) const
{
	return(3);
}


CRTDict CRTDBState::GetColumnValue(void) const
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


std::vector<std::string> CRTDBState::GetAllColumn(void) const
{
	const static std::vector<std::string> _StateColumns{
		"id",
		"name",
		"langname",
	};

	return(_StateColumns);
}


std::vector<std::string> CRTDBState::GetAllValue(void) const
{
	const std::vector<std::string> _StateValues{
		RTNSTool::int2string(m_ID),
		m_Name,
		m_LangName,
	};

	return(_StateValues);
}


void CRTDBState::SetAllValue(const std::vector<std::string>& _Values)
{
	m_ID = RTNSTool::string2int(_Values[0]);
	m_Name = _Values[1];
	m_LangName = _Values[2];
}


int CRTDBState::GetID(void) const
{
	return(m_ID);
}


void CRTDBState::SetID(const int _ID)
{
	m_ID = _ID;
}


std::string CRTDBState::GetName(void) const
{
	return(m_Name);
}


void CRTDBState::SetName(const std::string _Name)
{
	m_Name = _Name;
}


std::string CRTDBState::GetLangName(void) const
{
	return(m_LangName);
}


void CRTDBState::SetLangName(const std::string _LangName)
{
	m_LangName = _LangName;
}

