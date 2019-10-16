#ifndef __RTETIMER_H__
#define __RTETIMER_H__


#include "RTEBase.h"


class CRTETimer : public CRTEBase
{
public:
	CRTETimer(const int _Style, const int _SelfID, const int _Circle, const int _WaitTime, const std::string _Card, const std::string _Msg);
	CRTETimer(const int _Style, const int _SelfID, const int _Circle, const int _Counter, const std::chrono::high_resolution_clock::time_point _BasePoint, const int _WaitTime, const std::string _Card, const std::string _Msg);
	CRTETimer(const CRTETimer &_other);
	~CRTETimer();

private:
	int m_Style;
	int m_Circle;
	int m_Counter;
	std::chrono::high_resolution_clock::time_point m_BasePoint;
	int m_WaitTime;
	std::string m_Card;
	std::string m_Msg;

public:
	int GetStyle(void) const;
	void SetStyle(const int &_Style);

	int GetCircle(void) const;
	void SetCircle(const int &_Circle);

	int GetCounter(void);
	void SetCounter(const int &_Counter);

	std::chrono::high_resolution_clock::time_point GetBasePoint(void) const;
	void SetBasePoint(const std::chrono::high_resolution_clock::time_point &_BasePoint);

	int GetWaitTime(void) const;
	void SetWaitTime(const int &_WaitTime);

	std::string GetCard(void) const;
	void SetCard(const std::string &_Card);

	std::string GetMsg(void) const;
	void SetMsg(const std::string &_Msg);

public:
	virtual int SelfRun(void);
};


#endif//__RTETIMER_H__

