#include "RTDBSpeed.h"
#include "../RTNSDB.h"
#include "../RTNSLog.h"
#include "../RTNSTool.h"


CRTDBSpeed::CRTDBSpeed()
	: CRTDBBase("speeds", 128)
	, m_ID(0)
	, m_TimeStamp("")
	, m_MicroSecond(0)
	, m_StateID(RTNSDB::StateGood())
{
}


CRTDBSpeed::CRTDBSpeed(const CRTDBSpeed &_other)
	: CRTDBBase(_other)
	, m_ID(_other.m_ID)
	, m_TimeStamp(_other.m_TimeStamp)
	, m_MicroSecond(_other.m_MicroSecond)
	, m_StateID(_other.m_StateID)
{
}


CRTDBSpeed::~CRTDBSpeed()
{
}


int CRTDBSpeed::GetIndex(void) const
{
	return(this->GetID());
}


int CRTDBSpeed::GetColumnSize(void) const
{
	return(4);
}


CRTDict CRTDBSpeed::GetColumnValue(void) const
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


std::vector<std::string> CRTDBSpeed::GetAllColumn(void) const
{
	const static std::vector<std::string> _SpeedColumns{
		"id",
		"timestamp",
		"microsecond",
		"stateid",
	};

	return(_SpeedColumns);
}


std::vector<std::string> CRTDBSpeed::GetAllValue(void) const
{
	const std::vector<std::string> _SpeedValues{
		RTNSTool::int2string(m_ID),
		m_TimeStamp,
		RTNSTool::int2string(m_MicroSecond),
		RTNSTool::int2string(m_StateID),
	};

	return(_SpeedValues);
}


void CRTDBSpeed::SetAllValue(const std::vector<std::string>& _Values)
{
	m_ID = RTNSTool::string2int(_Values[0]);
	m_TimeStamp = _Values[1];
	m_MicroSecond = RTNSTool::string2int(_Values[2]);
	m_StateID = RTNSTool::string2int(_Values[3]);

	if (RTNSDB::StateDelete() == m_StateID)
	{
		this->SetObjStyle(RTDBOS_Delete);
	}
}


int CRTDBSpeed::GetID(void) const
{
	return(m_ID);
}


void CRTDBSpeed::SetID(const int _ID)
{
	m_ID = _ID;
}


std::string CRTDBSpeed::GetTimeStamp(void) const
{
	return(m_TimeStamp);
}


void CRTDBSpeed::SetTimeStamp(const std::string _TimeStamp)
{
	m_TimeStamp = _TimeStamp;
}


int CRTDBSpeed::GetMicroSecond(void) const
{
	return(m_MicroSecond);
}


void CRTDBSpeed::SetMicroSecond(const int _MicroSecond)
{
	m_MicroSecond = _MicroSecond;
}


int CRTDBSpeed::GetStateID(void) const
{
	return(m_StateID);
}


void CRTDBSpeed::SetStateID(const int _StateID)
{
	m_StateID = _StateID;

	if (RTNSDB::StateDelete() == m_StateID)
	{
		this->SetObjStyle(RTDBOS_Delete);
	}
}

