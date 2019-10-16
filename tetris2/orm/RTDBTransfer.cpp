#include "RTDBTransfer.h"
#include "../RTNSDB.h"
#include "../RTNSLog.h"
#include "../RTNSTool.h"


CRTDBTransfer::CRTDBTransfer()
	: CRTDBBase("transfers", 128)
	, m_ID(0)
	, m_TimeStamp("")
	, m_BlockID(0)
	, m_NextID(0)
	, m_StateID(RTNSDB::StateGood())
{
}


CRTDBTransfer::CRTDBTransfer(const CRTDBTransfer &_other)
	: CRTDBBase(_other)
	, m_ID(_other.m_ID)
	, m_TimeStamp(_other.m_TimeStamp)
	, m_BlockID(_other.m_BlockID)
	, m_NextID(_other.m_NextID)
	, m_StateID(_other.m_StateID)
{
}


CRTDBTransfer::~CRTDBTransfer()
{
}


int CRTDBTransfer::GetIndex(void) const
{
	return(this->GetID());
}


int CRTDBTransfer::GetColumnSize(void) const
{
	return(5);
}


CRTDict CRTDBTransfer::GetColumnValue(void) const
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


std::vector<std::string> CRTDBTransfer::GetAllColumn(void) const
{
	const static std::vector<std::string> _TransferColumns{
		"id",
		"timestamp",
		"blockid",
		"nextid",
		"stateid",
	};

	return(_TransferColumns);
}


std::vector<std::string> CRTDBTransfer::GetAllValue(void) const
{
	const std::vector<std::string> _TransferValues{
		RTNSTool::int2string(m_ID),
		m_TimeStamp,
		RTNSTool::int2string(m_BlockID),
		RTNSTool::int2string(m_NextID),
		RTNSTool::int2string(m_StateID),
	};

	return(_TransferValues);
}


void CRTDBTransfer::SetAllValue(const std::vector<std::string>& _Values)
{
	m_ID = RTNSTool::string2int(_Values[0]);
	m_TimeStamp = _Values[1];
	m_BlockID = RTNSTool::string2int(_Values[2]);
	m_NextID = RTNSTool::string2int(_Values[3]);
	m_StateID = RTNSTool::string2int(_Values[4]);

	if (RTNSDB::StateDelete() == m_StateID)
	{
		this->SetObjStyle(RTDBOS_Delete);
	}
}


int CRTDBTransfer::GetID(void) const
{
	return(m_ID);
}


void CRTDBTransfer::SetID(const int _ID)
{
	m_ID = _ID;
}


std::string CRTDBTransfer::GetTimeStamp(void) const
{
	return(m_TimeStamp);
}


void CRTDBTransfer::SetTimeStamp(const std::string _TimeStamp)
{
	m_TimeStamp = _TimeStamp;
}


int CRTDBTransfer::GetBlockID(void) const
{
	return(m_BlockID);
}


void CRTDBTransfer::SetBlockID(const int _BlockID)
{
	m_BlockID = _BlockID;
}


int CRTDBTransfer::GetNextID(void) const
{
	return(m_NextID);
}


void CRTDBTransfer::SetNextID(const int _NextID)
{
	m_NextID = _NextID;
}


int CRTDBTransfer::GetStateID(void) const
{
	return(m_StateID);
}


void CRTDBTransfer::SetStateID(const int _StateID)
{
	m_StateID = _StateID;

	if (RTNSDB::StateDelete() == m_StateID)
	{
		this->SetObjStyle(RTDBOS_Delete);
	}
}

