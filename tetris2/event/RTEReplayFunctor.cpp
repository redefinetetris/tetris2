#include "RTEReplayFunctor.h"
#include "../RTDict.h"
#include "../RTMail.h"
#include "../RTNSDB.h"
#include "../RTNSLog.h"
#include "../RTNSTool.h"
#include "../RTDataType.h"
#include "../orm/RTDBReplay.h"
#include "../orm/RTDBCursor.h"
#include "../orm/RTDBStatic.h"
#include "RTEReplay.h"


CRTEReplayFunctor::CRTEReplayFunctor(const int _FunctorStyle)
	: CRTFunctor(_FunctorStyle)
{
}


CRTEReplayFunctor::~CRTEReplayFunctor()
{
}


RTEReplayStyle_t CRTEReplayFunctor::operator () (CRTEReplay & _Replay) const
{
	const auto codeBase = this->ReplayCmd2DB(&_Replay, GetCurrentMail());

	const auto codePreDoFunctor = this->PreDoFunctor(_Replay);
	const auto codeDoFunctor = this->DoFunctor(_Replay);
	const auto codePostDoFunctor = this->PostDoFunctor(_Replay);

	return(codeDoFunctor);
}


RTEReplayStyle_t CRTEReplayFunctor::DoFunctor(CRTEReplay & _Replay) const
{
	const auto code = this->Functor(_Replay);

	return(code);
}


RTEReplayStyle_t CRTEReplayFunctor::Functor(CRTEReplay & _Replay) const
{
	return(RTERS_Unknown);
}


RTEReplayStyle_t CRTEReplayFunctor::PreDoFunctor(CRTEReplay & _Replay) const
{
	return(RTERS_Unknown);
}


RTEReplayStyle_t CRTEReplayFunctor::PostDoFunctor(CRTEReplay & _Replay) const
{
	return(RTERS_Unknown);
}


CReplayInit::CReplayInit()
	: CRTEReplayFunctor(RTERS_Init)
{
}


CReplayInit::~CReplayInit()
{
}


RTEReplayStyle_t CReplayInit::DoFunctor(CRTEReplay & _Replay) const
{
	const auto code = this->Init(_Replay);

	return(code);
}


RTEReplayStyle_t CReplayInit::Init(CRTEReplay & _Replay) const
{
	const auto idRoot = RTNSDB::UpDBRootID();
	auto pMail = RTNSTool::GetMailByTrail(idRoot, 1);

	if (nullptr == pMail)
	{
		const auto back_mail = RTNSTool::BackMailBy(GetCurrentMail(), "bad", "trail out memory");
		_Replay.m_SendBuffer.Writer(back_mail);

		return(RTERS_OutMemory);
	}
	_Replay.m_SendBuffer.Writer(pMail);

	const auto Args(GetCurrentArgs());
	const auto idSession = Args["sessionid"].GetInt();
	const auto StartReplayID(RTNSTool::GetIntValue4Dict(Args, "startreplayid", 1));
	int EndReplayID = 0;
	const auto& pReplayEnd = RTNSDB::FindDBReplayBySession(idSession, 0, StartReplayID + 1);
	if (nullptr != pReplayEnd)
	{
		EndReplayID = pReplayEnd->GetID();
	}

	const auto idGame = Args["gameid"].GetInt();
	const auto Force = RTNSTool::GetIntValue4Dict(Args, "force", 0);

	const auto pCursor = RTNSDB::NewDBCursor(idRoot, idSession, idGame, StartReplayID, EndReplayID, Force);
	if (nullptr == pCursor)
	{
		const auto back_mail = RTNSTool::BackMailBy(GetCurrentMail(), "bad", "cursor out memory");
		_Replay.m_SendBuffer.Writer(back_mail);

		return(RTERS_OutMemory);
	}

	const CRTDict back_args{
		{ "cursorid", pCursor->GetID() },
	};
	const auto back_mail = RTNSTool::BackMailBy(GetCurrentMail(), back_args);
	_Replay.m_SendBuffer.Writer(back_mail);

	return(RTERS_Init);
}


CReplayQuery::CReplayQuery()
	: CRTEReplayFunctor(RTERS_Query)
{
}


CReplayQuery::~CReplayQuery()
{
}


RTEReplayStyle_t CReplayQuery::DoFunctor(CRTEReplay & _Replay) const
{
	const auto code = this->Query(_Replay);

	return(code);
}


RTEReplayStyle_t CReplayQuery::Query(CRTEReplay & _Replay) const
{
	const auto Args(GetCurrentArgs());
	const auto Style(Args["style"].GetString());
	CRTDict back_args;

	if ("id" == Style)
	{
		auto pValue = RTNSDB::LatestDBCursor();
		if (nullptr != pValue)
		{
			back_args["start"] = 1;
			back_args["end"] = pValue->GetID();
		}
	}
	else if ("session" == Style)
	{
		const auto Sessions = RTNSDB::FindAllDBReplayBySession(0);
		std::vector<int> SessionIDs;
		std::vector<int> IDs;
		SessionIDs.reserve(Sessions.size());
		IDs.reserve(Sessions.size());

		for (auto item = Sessions.begin(); item != Sessions.end(); ++item)
		{
			auto pValue = *item;

			SessionIDs.push_back(pValue->GetSlaveID());
			IDs.push_back(pValue->GetID());
		}

		back_args["ids"] = IDs;
		back_args["sessionids"] = SessionIDs;
	}
	else if ("game" == Style)
	{
		const auto idSession(Args["sessionid"].GetInt());
		const auto idStart(RTNSTool::GetIntValue4Dict(Args, "startid", 0));
		const auto idEnd(RTNSTool::GetIntValue4Dict(Args, "endid", 0));

		const auto Games = RTNSDB::FindAllDBReplayByGame(idSession, idStart, idEnd, 0);
		std::vector<int> GameIDs;
		std::vector<int> IDs;
		GameIDs.reserve(Games.size());
		IDs.reserve(Games.size());

		for (auto item = Games.begin(); item != Games.end(); ++item)
		{
			auto pValue = *item;

			GameIDs.push_back(pValue->GetSlaveID());
			IDs.push_back(pValue->GetID());
		}

		back_args["ids"] = IDs;
		back_args["gameids"] = GameIDs;
	}

	const auto back_mail = RTNSTool::BackMailBy(GetCurrentMail(), back_args);
	_Replay.m_SendBuffer.Writer(back_mail);

	return(RTERS_Query);
}


CReplayBackward::CReplayBackward()
	: CRTEReplayFunctor(RTERS_Backward)
{
}


CReplayBackward::~CReplayBackward()
{
}


RTEReplayStyle_t CReplayBackward::DoFunctor(CRTEReplay & _Replay) const
{
	const auto code = this->Backward(_Replay);

	return(code);
}


RTEReplayStyle_t CReplayBackward::Backward(CRTEReplay & _Replay) const
{
	const auto Args(GetCurrentArgs());
	const auto idCursor(Args["cursorid"].GetInt());

	const auto pCursor = RTNSDB::FindDBCursor(idCursor);
	if (nullptr == pCursor)
	{
		return(RTERS_NotFind);
	}

	auto pReplay = RTNSDB::FindDBReplayByCursor(pCursor, -1);
	if (nullptr == pReplay)
	{
		return(RTERS_NotFind);
	}

	const auto idPackage = pReplay->GetPackageID();
	auto pMail = RTNSDB::NewReplayMailByCursor(pCursor->GetRootID(), idPackage, RTNSTool::BackwardValue());
	if (nullptr == pMail)
	{
		return(RTERS_NotFind);
	}

	pMail->CopyNetInfo(*GetCurrentMail());
	_Replay.m_SendBuffer.Writer(pMail);

	return(RTERS_Backward);
}


CReplayForward::CReplayForward()
	: CRTEReplayFunctor(RTERS_Forward)
{
}


CReplayForward::~CReplayForward()
{
}


RTEReplayStyle_t CReplayForward::DoFunctor(CRTEReplay & _Replay) const
{
	const auto code = this->Forward(_Replay);

	return(code);
}


RTEReplayStyle_t CReplayForward::Forward(CRTEReplay & _Replay) const
{
	const auto Args(GetCurrentArgs());
	const auto idCursor(Args["cursorid"].GetInt());

	const auto pCursor = RTNSDB::FindDBCursor(idCursor);
	if (nullptr == pCursor)
	{
		return(RTERS_NotFind);
	}

	if (pCursor->GetForce())
	{
		const auto& pReplayEnd = RTNSDB::FindDBReplayBySession(pCursor->GetSessionID(), 0, pCursor->GetCurrent() + 1);
		if (nullptr != pReplayEnd)
		{
			const auto EndReplayID = pReplayEnd->GetID();
			pCursor->SetEndReplayID(EndReplayID);

			pCursor->SetForce(0);
		}
		else
		{
			const auto& pLatestValue = GetReplayManager().GetLatestRecord();
			if (nullptr == pLatestValue)
			{
				return(RTERS_Error);
			}

			const auto EndReplayID = pLatestValue->GetID();
			pCursor->SetEndReplayID(EndReplayID);
		}//else
	}//if

	auto pReplay = RTNSDB::FindDBReplayByCursor(pCursor, 1);
	if (nullptr == pReplay)
	{
		return(RTERS_NotFind);
	}

	const auto idPackage = pReplay->GetPackageID();
	auto pMail = RTNSDB::NewReplayMailByCursor(pCursor->GetRootID(), idPackage, RTNSTool::ForwardValue());
	if (nullptr == pMail)
	{
		return(RTERS_NotFind);
	}

	pMail->CopyNetInfo(*GetCurrentMail());
	_Replay.m_SendBuffer.Writer(pMail);

	return(RTERS_Forward);
}

