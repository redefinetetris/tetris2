#include "RTPoint.h"


CRTPoint::CRTPoint(const int _X, const int _Y, const int _Z)
	: m_X(_X)
	, m_Y(_Y)
	, m_Z(_Z)
{
}


CRTPoint::CRTPoint(const CRTPoint &_other)
	: m_X(_other.m_X)
	, m_Y(_other.m_Y)
	, m_Z(_other.m_Z)
{
}


CRTPoint::~CRTPoint()
{
}


int CRTPoint::GetX(void) const
{
	return(m_X);
}


void CRTPoint::SetX(const int &_X)
{
	m_X = _X;
}


int CRTPoint::GetY(void) const
{
	return(m_Y);
}


void CRTPoint::SetY(const int &_Y)
{
	m_Y = _Y;
}


int CRTPoint::GetZ(void) const
{
	return(m_Z);
}


void CRTPoint::SetZ(const int &_Z)
{
	m_Z = _Z;
}


void CRTPoint::Clear(const int _Value)
{
	m_X = _Value;
	m_Y = _Value;
	m_Z = _Value;
}


CRTPoint& CRTPoint::operator = (const CRTPoint& _other)
{
	m_X = _other.m_X;
	m_Y = _other.m_Y;
	m_Z = _other.m_Z;

	return(*this);
}


CRTPoint& CRTPoint::operator += (const CRTPoint& _other)
{
	m_X += _other.m_X;
	m_Y += _other.m_Y;
	m_Z += _other.m_Z;

	return(*this);
}

