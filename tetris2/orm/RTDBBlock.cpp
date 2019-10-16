#include "RTDBBlock.h"
#include "../RTNSDB.h"
#include "../RTNSLog.h"
#include "../RTNSTool.h"


CRTDBBlock::CRTDBBlock()
	: CRTDBBase("blocks", 256)
	, m_ID(0)
	, m_TimeStamp("")
	, m_UserID(0)
	, m_GroupID(0)
	, m_Dimension(2)
	, m_Base(4)
	, m_Block("")
	, m_StateID(RTNSDB::StateGood())
{
}


CRTDBBlock::CRTDBBlock(const CRTDBBlock &_other)
	: CRTDBBase(_other)
	, m_ID(_other.m_ID)
	, m_TimeStamp(_other.m_TimeStamp)
	, m_UserID(_other.m_UserID)
	, m_GroupID(_other.m_GroupID)
	, m_Dimension(_other.m_Dimension)
	, m_Base(_other.m_Base)
	, m_Block(_other.m_Block)
	, m_StateID(_other.m_StateID)
{
}


CRTDBBlock::~CRTDBBlock()
{
}


int CRTDBBlock::GetIndex(void) const
{
	return(this->GetID());
}


int CRTDBBlock::GetColumnSize(void) const
{
	return(8);
}


CRTDict CRTDBBlock::GetColumnValue(void) const
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


std::vector<std::string> CRTDBBlock::GetAllColumn(void) const
{
	const static std::vector<std::string> _BlockColumns{
		"id",
		"timestamp",
		"userid",
		"groupid",
		"dimension",
		"base",
		"block",
		"stateid",
	};

	return(_BlockColumns);
}


std::vector<std::string> CRTDBBlock::GetAllValue(void) const
{
	const std::vector<std::string> _BlockValues{
		RTNSTool::int2string(m_ID),
		m_TimeStamp,
		RTNSTool::int2string(m_UserID),
		RTNSTool::int2string(m_GroupID),
		RTNSTool::int2string(m_Dimension),
		RTNSTool::int2string(m_Base),
		m_Block,
		RTNSTool::int2string(m_StateID),
	};

	return(_BlockValues);
}


void CRTDBBlock::SetAllValue(const std::vector<std::string>& _Values)
{
	m_ID = RTNSTool::string2int(_Values[0]);
	m_TimeStamp = _Values[1];
	m_UserID = RTNSTool::string2int(_Values[2]);
	m_GroupID = RTNSTool::string2int(_Values[3]);
	m_Dimension = RTNSTool::string2int(_Values[4]);
	m_Base = RTNSTool::string2int(_Values[5]);
	m_Block = _Values[6];
	m_StateID = RTNSTool::string2int(_Values[7]);

	if (RTNSDB::StateDelete() == m_StateID)
	{
		this->SetObjStyle(RTDBOS_Delete);
	}
}


int CRTDBBlock::GetID(void) const
{
	return(m_ID);
}


void CRTDBBlock::SetID(const int _ID)
{
	m_ID = _ID;
}


std::string CRTDBBlock::GetTimeStamp(void) const
{
	return(m_TimeStamp);
}


void CRTDBBlock::SetTimeStamp(const std::string _TimeStamp)
{
	m_TimeStamp = _TimeStamp;
}


int CRTDBBlock::GetUserID(void) const
{
	return(m_UserID);
}


void CRTDBBlock::SetUserID(const int _UserID)
{
	m_UserID = _UserID;
}


int CRTDBBlock::GetGroupID(void) const
{
	return(m_GroupID);
}


void CRTDBBlock::SetGroupID(const int _GroupID)
{
	m_GroupID = _GroupID;
}


int CRTDBBlock::GetDimension(void) const
{
	return(m_Dimension);
}


void CRTDBBlock::SetDimension(const int _Dimension)
{
	m_Dimension = _Dimension;
}


int CRTDBBlock::GetBase(void) const
{
	return(m_Base);
}


void CRTDBBlock::SetBase(const int _Base)
{
	m_Base = _Base;
}


std::string CRTDBBlock::GetBlock(void) const
{
	return(m_Block);
}


void CRTDBBlock::SetBlock(const std::string _Block)
{
	m_Block = _Block;
}


int CRTDBBlock::GetStateID(void) const
{
	return(m_StateID);
}


void CRTDBBlock::SetStateID(const int _StateID)
{
	m_StateID = _StateID;

	if (RTNSDB::StateDelete() == m_StateID)
	{
		this->SetObjStyle(RTDBOS_Delete);
	}
}

