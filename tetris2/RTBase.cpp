#include "RTBase.h"


CRTBase::CRTBase()
	: m_Health(RTHS_Run)
	, m_BackUpHealth(RTHS_Run)
	, m_SelfID(0)
{
}


CRTBase::CRTBase(const CRTBase &_other)
	: m_Health(_other.GetHealth())
	, m_BackUpHealth(_other.GetBackUpHealth())
	, m_SelfID(_other.GetSelfID())
{
}


CRTBase::~CRTBase()
{
}


RTHealthStyle_t CRTBase::GetHealth(void) const
{
	return(m_Health);
}


bool CRTBase::GetHealth(const RTHealthStyle_t _Style) const
{
	if (m_Health & _Style)
	{
		return(true);
	}

	return(false);
}


void CRTBase::SetHealth(const RTHealthStyle_t &_Health)
{
	m_Health = _Health;
}


RTHealthStyle_t CRTBase::GetBackUpHealth(void) const
{
	return(m_BackUpHealth);
}


void CRTBase::SetBackUpHealth(const RTHealthStyle_t &_BackUpHealth)
{
	m_BackUpHealth = _BackUpHealth;
}


void CRTBase::BackUpHealth(void)
{
	m_BackUpHealth = (RTHealthStyle_t)m_Health;
}


void CRTBase::RecoverHealth(void)
{
	m_Health = (RTHealthStyle_t)m_BackUpHealth;
}


int CRTBase::GetSelfID(void) const
{
	return(m_SelfID);
}


void CRTBase::SetSelfID(const int &_SelfID)
{
	m_SelfID = _SelfID;
}

