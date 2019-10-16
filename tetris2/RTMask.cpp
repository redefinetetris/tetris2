#include "RTMask.h"


CRTMask::CRTMask()
	: m_Mask(0)
	, m_MaskBackUp(0)
{
}


CRTMask::CRTMask(const unsigned int _Mask, const unsigned int _MaskBackUp)
	: m_Mask(_Mask)
	, m_MaskBackUp(_MaskBackUp)
{
}


CRTMask::CRTMask(const CRTMask &_other)
	: m_Mask(_other.m_Mask)
	, m_MaskBackUp(_other.m_MaskBackUp)
{
}


CRTMask::~CRTMask()
{
}


unsigned int CRTMask::GetAllMask(void) const
{
	return(m_Mask);
}


void CRTMask::SetAllMaskSimple(const unsigned int &_Mask)
{
	m_Mask = _Mask;
}


void CRTMask::SetAllMask(const unsigned int &_Mask)
{
	const unsigned int ReplayMode = 0X80000000;

	if (m_Mask & ReplayMode)
	{
		m_Mask = _Mask | ReplayMode;
	}
	else
	{
		m_Mask = _Mask;
	}
}


void CRTMask::ClearAllMask(void)
{
	m_Mask = 0;
}


bool CRTMask::GetMask(const unsigned int &_Mask) const
{
	if (m_Mask & _Mask)
	{
		return(true);
	}

	return(false);
}


void CRTMask::SetMask(const unsigned int &_Mask)
{
	m_Mask |= _Mask;
}


void CRTMask::ClearMask(const unsigned int &_Mask)
{
	const auto keepMask = ~_Mask;

	m_Mask &= keepMask;
}


unsigned int CRTMask::GetMaskBackUp(void) const
{
	return(m_MaskBackUp);
}


void CRTMask::SetMaskBackUp(const unsigned int &_MaskBackUp)
{
	m_MaskBackUp = _MaskBackUp;
}


void CRTMask::BackUpMask(void)
{
	m_MaskBackUp = m_Mask;
}


void CRTMask::RecoverMask(void)
{
	m_Mask = m_MaskBackUp;
}

