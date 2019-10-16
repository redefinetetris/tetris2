#include "RTEClockFunctor.h"
#include "../RTDict.h"
#include "../RTMail.h"
#include "../RTNSDB.h"
#include "../RTNSLog.h"
#include "../RTNSTool.h"
#include "../RTDataType.h"
#include "RTEClock.h"


CRTEClockFunctor::CRTEClockFunctor(const int _FunctorStyle)
	: CRTFunctor(_FunctorStyle)
{
}


CRTEClockFunctor::~CRTEClockFunctor()
{
}


RTEClockStyle_t CRTEClockFunctor::operator () (CRTEClock & _Clock) const
{
	const auto codeBase = this->ReplayCmd2DB(&_Clock, GetCurrentMail());

	const auto codePreDoFunctor = this->PreDoFunctor(_Clock);
	const auto codeDoFunctor = this->DoFunctor(_Clock);
	const auto codePostDoFunctor = this->PostDoFunctor(_Clock);

	return(codeDoFunctor);
}


RTEClockStyle_t CRTEClockFunctor::DoFunctor(CRTEClock & _Clock) const
{
	const auto code = this->Functor(_Clock);

	return(code);
}


RTEClockStyle_t CRTEClockFunctor::Functor(CRTEClock & _Clock) const
{
	return(RTECS_Unknown);
}


RTEClockStyle_t CRTEClockFunctor::PreDoFunctor(CRTEClock & _Clock) const
{
	return(RTECS_Unknown);
}


RTEClockStyle_t CRTEClockFunctor::PostDoFunctor(CRTEClock & _Clock) const
{
	return(RTECS_Unknown);
}


CClockUpdate::CClockUpdate()
	: CRTEClockFunctor(RTECS_Update)
{
}


CClockUpdate::~CClockUpdate()
{
}


RTEClockStyle_t CClockUpdate::DoFunctor(CRTEClock & _Clock) const
{
	const auto code = this->Update(_Clock);

	return(code);
}


RTEClockStyle_t CClockUpdate::Update(CRTEClock & _Clock) const
{
	const auto args = GetCurrentArgs();
	const auto Style(args["style"].GetInt());
	const auto idTimer(args["timerid"].GetInt());
	const auto Card(args["card"].GetString());
	const auto microseconds(args["microseconds"].GetInt());
	CRTDict back_args;

	for (auto item = _Clock.m_TimerManager.begin(); item != _Clock.m_TimerManager.end(); ++item)
	{
		auto& timer = *item;
		if (RTHS_Death == timer.GetHealth())
		{
			continue;
		}

		if (Style == timer.GetStyle()
			&& idTimer == timer.GetSelfID()
			&& Card == timer.GetCard()
			)
		{
			back_args["microseconds"] = timer.GetWaitTime();
			timer.SetWaitTime(microseconds);
			break;
		}
	}//for

	return(RTECS_Update);
}


CClockNew::CClockNew()
	: CRTEClockFunctor(RTECS_New)
{
}


CClockNew::~CClockNew()
{
}


RTEClockStyle_t CClockNew::DoFunctor(CRTEClock & _Clock) const
{
	const auto code = this->New(_Clock);

	return(code);
}


RTEClockStyle_t CClockNew::New(CRTEClock & _Clock) const
{
	const auto args = GetCurrentArgs();
	const auto Style(args["style"].GetInt());
	const auto idTimer(args["timerid"].GetInt());
	const auto Circle(args["circle"].GetInt());
	const auto microseconds(args["microseconds"].GetInt());
	const auto Card(args["card"].GetString());
	const auto Msg(args["msg"].GetString());
	const CRTETimer timer(Style, idTimer, Circle, microseconds, Card, Msg);

	_Clock.m_TimerManager.push_back(timer);

	return(RTECS_New);
}


CClockDelete::CClockDelete()
	: CRTEClockFunctor(RTECS_Delete)
{
}


CClockDelete::~CClockDelete()
{
}


RTEClockStyle_t CClockDelete::DoFunctor(CRTEClock & _Clock) const
{
	const auto code = this->Delete(_Clock);

	return(code);
}


RTEClockStyle_t CClockDelete::Delete(CRTEClock & _Clock) const
{
	const auto args = GetCurrentArgs();
	const auto Style(args["style"].GetInt());
	const auto idTimer(args["timerid"].GetInt());
	const auto Card(args["card"].GetString());
	int size = 0;

	for (auto item = _Clock.m_TimerManager.begin(); item != _Clock.m_TimerManager.end(); ++item)
	{
		auto& timer = *item;
		if (RTHS_Death == timer.GetHealth())
		{
			continue;
		}

		if (Style == timer.GetStyle()
			&& idTimer == timer.GetSelfID()
			)
		{
			if (0 == Card.size())
			{
				++size;

				timer.GetCounter();
				timer.SetHealth(RTHS_Death);
			}
			else if (Card == timer.GetCard())
			{
				++size;

				timer.GetCounter();
				timer.SetHealth(RTHS_Death);
			}
		}
	}//for

	return(RTECS_Delete);
}


CClockQuery::CClockQuery()
	: CRTEClockFunctor(RTECS_Query)
{
}


CClockQuery::~CClockQuery()
{
}


RTEClockStyle_t CClockQuery::DoFunctor(CRTEClock & _Clock) const
{
	const auto code = this->Query(_Clock);

	return(code);
}


RTEClockStyle_t CClockQuery::Query(CRTEClock & _Clock) const
{
	const auto args = GetCurrentArgs();
	std::vector<CRTDict> Clocks;
	Clocks.reserve(VECTOR_RESERVE_SIZE);

	if (true == args.IsEmpty())
	{
		for (auto item = _Clock.m_TimerManager.begin(); item != _Clock.m_TimerManager.end(); ++item)
		{
			const auto& timer = *item;
			if (RTHS_Death == timer.GetHealth())
			{
				continue;
			}

			const auto clock = RTNSTool::GetDictByTimer(timer);
			Clocks.push_back(clock);
		}//for
	}//if
	else
	{
		const auto args = GetCurrentArgs();
		const auto Style(args["style"].GetInt());
		const auto idTimer(args["timerid"].GetInt());

		for (auto item = _Clock.m_TimerManager.begin(); item != _Clock.m_TimerManager.end(); ++item)
		{
			const auto& timer = *item;
			if (RTHS_Death == timer.GetHealth())
			{
				continue;
			}

			if (Style == timer.GetStyle() && idTimer == timer.GetSelfID())
			{
				const auto clock = RTNSTool::GetDictByTimer(timer);
				Clocks.push_back(clock);
			}
		}//for
	}//else

	const CRTDict back_args{
		{"clocks", Clocks},
	};
	const auto back_dict = RTNSTool::BackDict4Loop(GetCurrentMail(), back_args);
	const auto back_mail = RTNSTool::BackMailBy(GetCurrentMail(), back_dict);
	_Clock.m_SendBuffer.Writer(back_mail);

	return(RTECS_Query);
}


CClockHealth::CClockHealth()
	: CRTEClockFunctor(RTECS_Health)
{
}


CClockHealth::~CClockHealth()
{
}


RTEClockStyle_t CClockHealth::DoFunctor(CRTEClock & _Clock) const
{
	const auto code = this->Health(_Clock);

	return(code);
}


RTEClockStyle_t CClockHealth::Health(CRTEClock & _Clock) const
{
	const auto Args = GetCurrentArgs();
	const auto Style(Args["style"].GetInt());
	const auto idTimer(Args["timerid"].GetInt());

	for (auto item = _Clock.m_TimerManager.begin(); item != _Clock.m_TimerManager.end(); ++item)
	{
		auto& timer = *item;
		if (RTHS_Death == timer.GetHealth())
		{
			continue;
		}

		if (Style != timer.GetStyle() || idTimer != timer.GetSelfID())
		{
			continue;
		}

		RTNSTool::DoHealth(&timer, Args);
	}//for

	return(RTECS_Health);
}

