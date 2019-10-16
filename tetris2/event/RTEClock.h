#ifndef __RTECLOCK_H__
#define __RTECLOCK_H__


#include "RTEBase.h"
#include "RTETimer.h"


class CRTEClock : public CRTEBase
{
public:
	CRTEClock();
	~CRTEClock();

private:
	std::vector<CRTETimer> m_TimerManager;

private:
	friend class CClockUpdate;
	friend class CClockNew;
	friend class CClockDelete;
	friend class CClockQuery;
	friend class CClockHealth;

public:
	int operator () ();

private:
	virtual int SelfRun(void);
	virtual int DoMail(void);

private:
	int Guard(void);
	void Wash(void);
	void Clear(void);
	int Mailer(void);
};


#endif//__RTECLOCK_H__

