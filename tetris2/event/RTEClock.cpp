#include "RTEClock.h"
#include "RTEClockStyle.h"
#include "RTEClockFunctor.h"
#include "RTEClockStatic.h"
#include "../RTNSDB.h"
#include "../RTNSLog.h"
#include "../RTNSTool.h"
#include "../RTDataType.h"
#include "../RTNSStatic.h"


CRTEClock::CRTEClock()
	: CRTEBase(RTES_Clock)
	, m_TimerManager()
{
	m_TimerManager.reserve(VECTOR_RESERVE_SIZE);
}


CRTEClock::~CRTEClock()
{
}


int CRTEClock::operator () ()
{
	const auto work = this->Run();

	return(work);
}


int CRTEClock::SelfRun(void)
{
	int work = 0;

	const auto total = m_TimerManager.size();
	if (0 == total)
	{
		return(work);
	}

	const auto bads = this->Guard();

	static int _ClockCounter = 0;
	_ClockCounter += 1;
	if (1000 < _ClockCounter)
	{
		if (19 < bads)
		{
			this->Wash();
		}

		_ClockCounter = 0;
	}

	work += this->Mailer();
	if (work)
	{
		RTNSStatic::WakeHubThreader();
	}

	return(work);
}


int CRTEClock::DoMail(void)
{
	const auto ops = GetCurrentOps();
	const auto op1 = ops[1];

	auto pFunctor = GetRTEClockFunctor(op1);
	if (nullptr == pFunctor)
	{
		return(0);
	}

	pFunctor->operator ()(*this);

	return(1);
}


int CRTEClock::Guard(void)
{
	int oks = 0;

	for (auto item = m_TimerManager.begin(); item != m_TimerManager.end(); ++item)
	{
		auto& timer = *item;

		if (RTHS_Run & timer.GetHealth())
		{
			++oks;
			timer.SelfRun();
		}
	}

	return(m_TimerManager.size() - oks);
}


void CRTEClock::Wash(void)
{
	std::vector<CRTETimer> _ClockCache;
	_ClockCache.reserve(m_TimerManager.size());

	for (auto item = m_TimerManager.begin(); item != m_TimerManager.end(); ++item)
	{
		const auto& timer = *item;

		if (RTHS_Run & timer.GetHealth())
		{
			_ClockCache.push_back(timer);
		}
	}

	_ClockCache.swap(m_TimerManager);
}


void CRTEClock::Clear(void)
{
	m_TimerManager.clear();
}


int CRTEClock::Mailer(void)
{
	int work = 0;
	std::vector<std::shared_ptr<CRTMail>> Mails;
	Mails.reserve(VECTOR_RESERVE_SIZE);

	for (auto item = m_TimerManager.begin(); item != m_TimerManager.end(); ++item)
	{
		auto& timer = *item;
		const auto Counter = timer.GetCounter();
		const auto& Msg = timer.GetMsg();

		//for (int index = 0; index < Counter; ++index)
		if (Counter)
		{
			++work;

			auto pMail = RTNSTool::BackMail(Msg);
			if (nullptr==pMail)
			{
				PrintLogInfo("new space fail in clock");
				LogError("new space fail in clock");
				continue;
			}

			Mails.push_back(pMail);
		}
	}//for

	if (Mails.size())
	{
		m_SendBuffer.Writer(Mails);
	}

	return(work);
}

