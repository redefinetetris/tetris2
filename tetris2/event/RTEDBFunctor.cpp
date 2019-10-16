#include "RTEDBFunctor.h"
#include "../RTDict.h"
#include "../RTMail.h"
#include "../RTNSDB.h"
#include "../RTNSLog.h"
#include "../RTNSTool.h"
#include "../RTDataType.h"
#include "../orm/RTDBStatic.h"
#include "RTEDB.h"
#include "RTEStyle.h"


CRTEDBFunctor::CRTEDBFunctor(const int _FunctorStyle)
	: CRTFunctor(_FunctorStyle)
{
}


CRTEDBFunctor::~CRTEDBFunctor()
{
}


RTEDBStyle_t CRTEDBFunctor::operator () (CRTEDB & _DB) const
{
	const auto codeBase = this->ReplayCmd2DB(&_DB, GetCurrentMail());

	const auto codePreDoFunctor = this->PreDoFunctor(_DB);
	const auto codeDoFunctor = this->DoFunctor(_DB);
	const auto codePostDoFunctor = this->PostDoFunctor(_DB);

	return(codeDoFunctor);
}


RTEDBStyle_t CRTEDBFunctor::DoFunctor(CRTEDB & _DB) const
{
	const auto code = this->Functor(_DB);

	return(code);
}


RTEDBStyle_t CRTEDBFunctor::Functor(CRTEDB & _DB) const
{
	return(RTEDBS_Unknown);
}


RTEDBStyle_t CRTEDBFunctor::PreDoFunctor(CRTEDB & _DB) const
{
	return(RTEDBS_Unknown);
}


RTEDBStyle_t CRTEDBFunctor::PostDoFunctor(CRTEDB & _DB) const
{
	return(RTEDBS_Unknown);
}


CDBTimer::CDBTimer()
	: CRTEDBFunctor(RTEDBS_Timer)
{
}


CDBTimer::~CDBTimer()
{
}


RTEDBStyle_t CDBTimer::DoFunctor(CRTEDB & _DB) const
{
	const auto code = this->Timer(_DB);

	return(code);
}


RTEDBStyle_t CDBTimer::Timer(CRTEDB & _DB) const
{
	const auto Args = GetCurrentArgs();
	const auto idDB = _DB.GetSelfID();
	const auto Circle = Args["circle"].GetInt();
	const auto MicroSeconds = Args["microseconds"].GetInt();
	const auto Op = Args["op"].GetString();
	const auto Card = Args["card"].GetString();
	const auto Msg = Args["msg"].GetString();

	const auto timer_mail = RTNSTool::TimerMail("db", _DB.GetRTEStyle(), idDB, Circle, Op, MicroSeconds, Card, Msg);
	const auto back_mail = RTNSTool::BackMailBy(GetCurrentMail());

	const std::vector <std::shared_ptr<CRTMail>> Mails{ timer_mail, back_mail };
	_DB.m_SendBuffer.Writer(Mails);

	return(RTEDBS_Timer);
}


CDBFire::CDBFire()
	: CRTEDBFunctor(RTEDBS_Fire)
{
}


CDBFire::~CDBFire()
{
}


RTEDBStyle_t CDBFire::DoFunctor(CRTEDB & _DB) const
{
	const auto code = this->Fire(_DB);

	return(code);
}


RTEDBStyle_t CDBFire::Fire(CRTEDB & _DB) const
{
	const auto Args = GetCurrentArgs();
	const auto Op = Args["op"].GetString();
	const auto idDB = _DB.GetSelfID();

	const auto Minute1 = RTNSTool::GetMinute(1);
	const auto Minute3 = RTNSTool::GetMinute(3);
	const auto Minute5 = RTNSTool::GetMinute(5);
	const auto microseconds4Flush = RTNSTool::GetIntValue4Dict(Args, "flush", Minute5);
	const auto microseconds4DownTTL = RTNSTool::GetIntValue4Dict(Args, "downttl", Minute1);
	const auto microseconds4WashTTL = RTNSTool::GetIntValue4Dict(Args, "washttl", Minute3);

	const auto Mails = RTNSTool::GetDBClockMails(idDB, Op, microseconds4Flush, microseconds4DownTTL, microseconds4WashTTL);
	_DB.m_SendBuffer.Writer(Mails);

	return(RTEDBS_Fire);
}


CDBFlush::CDBFlush()
	: CRTEDBFunctor(RTEDBS_Flush)
{
}


CDBFlush::~CDBFlush()
{
}


RTEDBStyle_t CDBFlush::DoFunctor(CRTEDB & _DB) const
{
	const auto code = this->Flush(_DB);

	return(code);
}


RTEDBStyle_t CDBFlush::Flush(CRTEDB & _DB) const
{
	PrintLogInfo("db flush");

	const auto Args = GetCurrentArgs();
	const auto NameDB = RTNSTool::GetStringValue4Dict(Args, "db", "");
	std::vector<Manager_t*> DBs;

	if (0 < NameDB.size())
	{
		auto pDB = GetCNDB(NameDB);

		if (nullptr != pDB)
		{
			DBs.push_back(pDB);
		}
	}
	else
	{
		DBs = GetCNDBManagerValues();
	}

	for (auto item = DBs.begin(); item != DBs.end(); ++item)
	{
		auto pDB = *item;

		pDB->Flush();
	}

	return(RTEDBS_Flush);
}


CDBDownTTL::CDBDownTTL()
	: CRTEDBFunctor(RTEDBS_DownTTL)
{
}


CDBDownTTL::~CDBDownTTL()
{
}


RTEDBStyle_t CDBDownTTL::DoFunctor(CRTEDB & _DB) const
{
	const auto code = this->DownTTL(_DB);

	return(code);
}


RTEDBStyle_t CDBDownTTL::DownTTL(CRTEDB & _DB) const
{
	PrintLogInfo("db down ttl");

	const auto Args = GetCurrentArgs();
	const auto NameDB = RTNSTool::GetStringValue4Dict(Args, "db", "");
	std::vector<Manager_t*> DBs;

	if (0 < NameDB.size())
	{
		auto pDB = GetCNDB(NameDB);

		if (nullptr != pDB)
		{
			DBs.push_back(pDB);
		}
	}
	else
	{
		DBs = GetCNDBManagerValues();
	}

	for (auto item = DBs.begin(); item != DBs.end(); ++item)
	{
		auto pDB = *item;

		pDB->DownTTL();
	}

	return(RTEDBS_DownTTL);
}


CDBWashTTL::CDBWashTTL()
	: CRTEDBFunctor(RTEDBS_WashTTL)
{
}


CDBWashTTL::~CDBWashTTL()
{
}


RTEDBStyle_t CDBWashTTL::DoFunctor(CRTEDB & _DB) const
{
	const auto code = this->WashTTL(_DB);

	return(code);
}


RTEDBStyle_t CDBWashTTL::WashTTL(CRTEDB & _DB) const
{
	PrintLogInfo("db wash ttl");

	const auto Args = GetCurrentArgs();
	const auto NameDB = RTNSTool::GetStringValue4Dict(Args, "db", "");
	std::vector<Manager_t*> DBs;

	if (0 < NameDB.size())
	{
		auto pDB = GetCNDB(NameDB);

		if (nullptr != pDB)
		{
			DBs.push_back(pDB);
		}
	}
	else
	{
		DBs = GetCNDBManagerValues();
	}

	for (auto item = DBs.begin(); item != DBs.end(); ++item)
	{
		auto pDB = *item;

		pDB->WashTTL();
	}

	return(RTEDBS_WashTTL);
}

