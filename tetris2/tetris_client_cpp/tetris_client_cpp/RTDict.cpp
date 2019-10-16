#include "RTDict.h"


CRTDict::CRTDict()
	: m_Container()
{
}


CRTDict::CRTDict(const std::initializer_list<std::pair<std::string, CRTValue>> &_Values)
	: m_Container(_Values)
{
}


CRTDict::CRTDict(const CRTDict &_other)
	: m_Container(_other.m_Container)
{
}


CRTDict::~CRTDict()
{
}


CRTValue& CRTDict::operator [] (const std::string _Key)
{
	return(m_Container[_Key]);
}


const CRTValue& CRTDict::operator [] (const std::string _Key) const
{
	return(m_Container[_Key]);
}


std::vector<std::string> CRTDict::Keys(void) const
{
	return(m_Container.Keys());
}


bool CRTDict::IsEmpty(void) const
{
	return(m_Container.IsEmpty());
}


bool CRTDict::HasKey(const std::string _Key) const
{
	return(m_Container.HasKey(_Key));
}


void CRTDict::DeleteTarget(const std::string _Key)
{
	m_Container.DeleteTarget(_Key);
}

