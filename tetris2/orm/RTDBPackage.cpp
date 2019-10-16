#include "RTDBPackage.h"
#include "../RTNSDB.h"
#include "../RTNSLog.h"
#include "../RTNSTool.h"


CRTDBPackage::CRTDBPackage()
	: CRTDBBase("packages", 2048)
	, m_ID(0)
	, m_TimeStamp("")
	, m_IP("")
	, m_Mail("")
	, m_StateID(RTNSDB::StateGood())
{
}


CRTDBPackage::CRTDBPackage(const CRTDBPackage &_other)
	: CRTDBBase(_other)
	, m_ID(_other.m_ID)
	, m_TimeStamp(_other.m_TimeStamp)
	, m_IP(_other.m_IP)
	, m_Mail(_other.m_Mail)
	, m_StateID(_other.m_StateID)
{
}


CRTDBPackage::~CRTDBPackage()
{
}


int CRTDBPackage::GetIndex(void) const
{
	return(this->GetID());
}


int CRTDBPackage::GetColumnSize(void) const
{
	return(5);
}


CRTDict CRTDBPackage::GetColumnValue(void) const
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


std::vector<std::string> CRTDBPackage::GetAllColumn(void) const
{
	const static std::vector<std::string> _PackageColumns{
		"id",
		"timestamp",
		"ip",
		"mail",
		"stateid",
	};

	return(_PackageColumns);
}


std::vector<std::string> CRTDBPackage::GetAllValue(void) const
{
	const std::vector<std::string> _PackageValues{
		RTNSTool::int2string(m_ID),
		m_TimeStamp,
		m_IP,
		m_Mail,
		RTNSTool::int2string(m_StateID),
	};

	return(_PackageValues);
}


void CRTDBPackage::SetAllValue(const std::vector<std::string>& _Values)
{
	m_ID = RTNSTool::string2int(_Values[0]);
	m_TimeStamp = _Values[1];
	m_IP = _Values[2];
	m_Mail = _Values[3];
	m_StateID = RTNSTool::string2int(_Values[4]);

	if (RTNSDB::StateDelete() == m_StateID)
	{
		this->SetObjStyle(RTDBOS_Delete);
	}
}


int CRTDBPackage::GetID(void) const
{
	return(m_ID);
}


void CRTDBPackage::SetID(const int _ID)
{
	m_ID = _ID;
}


std::string CRTDBPackage::GetTimeStamp(void) const
{
	return(m_TimeStamp);
}


void CRTDBPackage::SetTimeStamp(const std::string _TimeStamp)
{
	m_TimeStamp = _TimeStamp;
}


std::string CRTDBPackage::GetIP(void) const
{
	return(m_IP);
}


void CRTDBPackage::SetIP(const std::string _IP)
{
	m_IP = _IP;
}


std::string CRTDBPackage::GetMail(void) const
{
	return(m_Mail);
}


void CRTDBPackage::SetMail(const std::string _Mail)
{
	m_Mail = _Mail;
}


int CRTDBPackage::GetStateID(void) const
{
	return(m_StateID);
}


void CRTDBPackage::SetStateID(const int _StateID)
{
	m_StateID = _StateID;

	if (RTNSDB::StateDelete() == m_StateID)
	{
		this->SetObjStyle(RTDBOS_Delete);
	}
}

