#include "RTDBBase.h"


CRTDBBase::CRTDBBase(const std::string _TableName, const int _LengthPerLine, const int _TTL, const unsigned int _ObjStyle)
	: m_TableName(_TableName)
	, m_LengthPerLine(_LengthPerLine)
	, m_TTL(_TTL)
	, m_ObjStyle(_ObjStyle)
{
}


CRTDBBase::CRTDBBase(const CRTDBBase &_other)
	: m_TableName(_other.m_TableName)
	, m_LengthPerLine(_other.m_LengthPerLine)
	, m_TTL(_other.m_TTL)
	, m_ObjStyle((unsigned int)_other.m_ObjStyle)
{
}


CRTDBBase::~CRTDBBase()
{
}


std::string CRTDBBase::GetTableName(void) const
{
	return(m_TableName);
}


std::string CRTDBBase::GetDBName(void) const
{
	const auto nameDB = "dbs/" + m_TableName + ".cndb";

	return(nameDB);
}


int CRTDBBase::GetLengthPerLine(void) const
{
	return(m_LengthPerLine);
}


int CRTDBBase::GetTTL(void) const
{
	return(m_TTL);
}


void CRTDBBase::UpTTL(const int _TTL)
{
	m_TTL += _TTL;
}


unsigned int CRTDBBase::GetAllObjStyle(void) const
{
	return(m_ObjStyle);
}


void CRTDBBase::SetAllObjStyle(const unsigned int _ObjStyle)
{
	m_ObjStyle = _ObjStyle;
}


void CRTDBBase::ClearAllObjStyle(const unsigned int _ObjStyle)
{
	const auto keepObjStyle = ~_ObjStyle;

	m_ObjStyle &= keepObjStyle;
}


bool CRTDBBase::GetObjStyle(const RTDBObjectStyle_t _ObjStyle) const
{
	if (m_ObjStyle & _ObjStyle)
	{
		return(true);
	}

	return(false);
}


void CRTDBBase::SetObjStyle(const RTDBObjectStyle_t _ObjStyle)
{
	m_ObjStyle |= _ObjStyle;
}


int CRTDBBase::GetIndex(void) const
{
	return(0);
}


int CRTDBBase::GetColumnSize(void) const
{
	return(0);
}


CRTDict CRTDBBase::GetColumnValue(void) const
{
	CRTDict Result;

	return(Result);
}


std::vector<std::string> CRTDBBase::GetAllColumn(void) const
{
	const std::vector<std::string> _BaseColumns;

	return(_BaseColumns);
}


std::vector<std::string> CRTDBBase::GetAllValue(void) const
{
	const std::vector<std::string> _BaseValues;

	return(_BaseValues);
}


void CRTDBBase::SetAllValue(const std::vector<std::string>& _Values)
{
}

