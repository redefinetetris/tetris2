#include "RTDBReplay.h"
#include "../RTNSDB.h"
#include "../RTNSLog.h"
#include "../RTNSTool.h"


CRTDBReplay::CRTDBReplay()
	: CRTDBBase("replays", 128)
	, m_ID(0)
	, m_TimeStamp("")
	, m_PackageID(0)
	, m_MasterStyle(0)
	, m_MasterID(0)
	, m_SlaveStyle(0)
	, m_SlaveID(0)
	, m_FunctorStyle(0)
	, m_StateID(RTNSDB::StateGood())
{
}


CRTDBReplay::CRTDBReplay(const CRTDBReplay &_other)
	: CRTDBBase(_other)
	, m_ID(_other.m_ID)
	, m_TimeStamp(_other.m_TimeStamp)
	, m_PackageID(_other.m_PackageID)
	, m_MasterStyle(_other.m_MasterStyle)
	, m_MasterID(_other.m_MasterID)
	, m_SlaveStyle(_other.m_SlaveStyle)
	, m_SlaveID(_other.m_SlaveID)
	, m_FunctorStyle(_other.m_FunctorStyle)
	, m_StateID(_other.m_StateID)
{
}


CRTDBReplay::~CRTDBReplay()
{
}


int CRTDBReplay::GetIndex(void) const
{
	return(this->GetID());
}


int CRTDBReplay::GetColumnSize(void) const
{
	return(9);
}


CRTDict CRTDBReplay::GetColumnValue(void) const
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


std::vector<std::string> CRTDBReplay::GetAllColumn(void) const
{
	const static std::vector<std::string> _ReplayColumns{
		"id",
		"timestamp",
		"packageid",
		"masterstyle",
		"masterid",
		"slavestyle",
		"slaveid",
		"functorstyle",
		"stateid",
	};

	return(_ReplayColumns);
}


std::vector<std::string> CRTDBReplay::GetAllValue(void) const
{
	const std::vector<std::string> _ReplayValues{
		RTNSTool::int2string(m_ID),
		m_TimeStamp,
		RTNSTool::int2string(m_PackageID),
		RTNSTool::int2string(m_MasterStyle),
		RTNSTool::int2string(m_MasterID),
		RTNSTool::int2string(m_SlaveStyle),
		RTNSTool::int2string(m_SlaveID),
		RTNSTool::int2string(m_FunctorStyle),
		RTNSTool::int2string(m_StateID),
	};

	return(_ReplayValues);
}


void CRTDBReplay::SetAllValue(const std::vector<std::string>& _Values)
{
	m_ID = RTNSTool::string2int(_Values[0]);
	m_TimeStamp = _Values[1];
	m_PackageID = RTNSTool::string2int(_Values[2]);
	m_MasterStyle = RTNSTool::string2int(_Values[3]);
	m_MasterID = RTNSTool::string2int(_Values[4]);
	m_SlaveStyle = RTNSTool::string2int(_Values[5]);
	m_SlaveID = RTNSTool::string2int(_Values[6]);
	m_FunctorStyle = RTNSTool::string2int(_Values[7]);
	m_StateID = RTNSTool::string2int(_Values[8]);

	if (RTNSDB::StateDelete() == m_StateID)
	{
		this->SetObjStyle(RTDBOS_Delete);
	}
}


int CRTDBReplay::GetID(void) const
{
	return(m_ID);
}


void CRTDBReplay::SetID(const int _ID)
{
	m_ID = _ID;
}


std::string CRTDBReplay::GetTimeStamp(void) const
{
	return(m_TimeStamp);
}


void CRTDBReplay::SetTimeStamp(const std::string _TimeStamp)
{
	m_TimeStamp = _TimeStamp;
}


int CRTDBReplay::GetPackageID(void) const
{
	return(m_PackageID);
}


void CRTDBReplay::SetPackageID(const int _PackageID)
{
	m_PackageID = _PackageID;
}


int CRTDBReplay::GetMasterStyle(void) const
{
	return(m_MasterStyle);
}


void CRTDBReplay::SetMasterStyle(const int _MasterStyle)
{
	m_MasterStyle = _MasterStyle;
}


int CRTDBReplay::GetMasterID(void) const
{
	return(m_MasterID);
}


void CRTDBReplay::SetMasterID(const int _MasterID)
{
	m_MasterID = _MasterID;
}


int CRTDBReplay::GetSlaveStyle(void) const
{
	return(m_SlaveStyle);
}


void CRTDBReplay::SetSlaveStyle(const int _SlaveStyle)
{
	m_SlaveStyle = _SlaveStyle;
}


int CRTDBReplay::GetSlaveID(void) const
{
	return(m_SlaveID);
}


void CRTDBReplay::SetSlaveID(const int _SlaveID)
{
	m_SlaveID = _SlaveID;
}


int CRTDBReplay::GetFunctorStyle(void) const
{
	return(m_FunctorStyle);
}


void CRTDBReplay::SetFunctorStyle(const int _FunctorStyle)
{
	m_FunctorStyle = _FunctorStyle;
}


int CRTDBReplay::GetStateID(void) const
{
	return(m_StateID);
}


void CRTDBReplay::SetStateID(const int _StateID)
{
	m_StateID = _StateID;

	if (RTNSDB::StateDelete() == m_StateID)
	{
		this->SetObjStyle(RTDBOS_Delete);
	}
}

