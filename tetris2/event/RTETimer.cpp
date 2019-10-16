#include "RTETimer.h"


CRTETimer::CRTETimer(const int _Style, const int _SelfID, const int _Circle, const int _WaitTime, const std::string _Card, const std::string _Msg)
	: CRTEBase(RTES_Unknown)
	, m_Style(_Style)
	, m_Circle(_Circle)
	, m_Counter(0)
	, m_BasePoint(std::chrono::high_resolution_clock::now())
	, m_WaitTime(_WaitTime)
	, m_Card(_Card)
	, m_Msg(_Msg)
{
	this->SetSelfID(_SelfID);
}


CRTETimer::CRTETimer(const int _Style, const int _SelfID, const int _Circle, const int _Counter, const std::chrono::high_resolution_clock::time_point _BasePoint, const int _WaitTime, const std::string _Card, const std::string _Msg)
	: CRTEBase(RTES_Unknown)
	, m_Style(_Style)
	, m_Circle(_Circle)
	, m_Counter(_Counter)
	, m_BasePoint(_BasePoint)
	, m_WaitTime(_WaitTime)
	, m_Card(_Card)
	, m_Msg(_Msg)
{
	this->SetSelfID(_SelfID);
}


CRTETimer::CRTETimer(const CRTETimer &_other)
	: CRTEBase(_other)
	, m_Style(_other.m_Style)
	, m_Circle(_other.m_Circle)
	, m_Counter(_other.m_Counter)
	, m_BasePoint(_other.m_BasePoint)
	, m_WaitTime(_other.m_WaitTime)
	, m_Card(_other.m_Card)
	, m_Msg(_other.m_Msg)
{
}


CRTETimer::~CRTETimer()
{
}


int CRTETimer::GetStyle(void) const
{
	return(m_Style);
}


void CRTETimer::SetStyle(const int &_Style)
{
	m_Style = _Style;
}


int CRTETimer::GetCircle(void) const
{
	return(m_Circle);
}


void CRTETimer::SetCircle(const int &_Circle)
{
	m_Circle = _Circle;
}


int CRTETimer::GetCounter(void)
{
	const auto counter = m_Counter;
	m_Counter = 0;

	if (counter && 0 == this->GetCircle())
	{
		this->SetHealth(RTHS_Death);

		return(1);
	}

	return(counter);
}


void CRTETimer::SetCounter(const int &_Counter)
{
	m_Counter = _Counter;
}


std::chrono::high_resolution_clock::time_point CRTETimer::GetBasePoint(void) const
{
	return(m_BasePoint);
}


void CRTETimer::SetBasePoint(const std::chrono::high_resolution_clock::time_point &_BasePoint)
{
	m_BasePoint = _BasePoint;
}


int CRTETimer::GetWaitTime(void) const
{
	return(m_WaitTime);
}


void CRTETimer::SetWaitTime(const int &_WaitTime)
{
	m_WaitTime = _WaitTime;
}


std::string CRTETimer::GetCard(void) const
{
	return(m_Card);
}


void CRTETimer::SetCard(const std::string &_Card)
{
	m_Card = _Card;
}


std::string CRTETimer::GetMsg(void) const
{
	return(m_Msg);
}


void CRTETimer::SetMsg(const std::string &_Msg)
{
	m_Msg = _Msg;
}


int CRTETimer::SelfRun(void)
{
	const auto ms = std::chrono::microseconds(m_WaitTime);
	const auto now = std::chrono::high_resolution_clock::now();

	while ((m_BasePoint + ms) < now)
	{
		++m_Counter;

		m_BasePoint += ms;
	}

	return(m_Counter);
}

