#include "RTERootFunctor.h"
#include "../RTDict.h"
#include "../RTMail.h"
#include "../RTNSDB.h"
#include "../RTNSLog.h"
#include "../RTNSTool.h"
#include "../RTDataType.h"
#include "RTERoot.h"
#include "RTESessionStyle.h"


CRTERootFunctor::CRTERootFunctor(const int _FunctorStyle)
	: CRTFunctor(_FunctorStyle)
{
}


CRTERootFunctor::~CRTERootFunctor()
{
}


RTERootStyle_t CRTERootFunctor::operator () (CRTERoot & _Root) const
{
	const auto codeBase = this->ReplayCmd2DB(&_Root, GetCurrentMail());

	const auto codePreDoFunctor = this->PreDoFunctor(_Root);
	const auto codeDoFunctor = this->DoFunctor(_Root);
	const auto codePostDoFunctor = this->PostDoFunctor(_Root);

	return(codeDoFunctor);
}


RTERootStyle_t CRTERootFunctor::DoFunctor(CRTERoot & _Root) const
{
	const auto code = this->Functor(_Root);

	return(code);
}


RTERootStyle_t CRTERootFunctor::Functor(CRTERoot & _Root) const
{
	return(RTERS_Unknown);
}


RTERootStyle_t CRTERootFunctor::PreDoFunctor(CRTERoot & _Root) const
{
	return(RTERS_Unknown);
}


RTERootStyle_t CRTERootFunctor::PostDoFunctor(CRTERoot & _Root) const
{
	return(RTERS_Unknown);
}


CRootNewSession::CRootNewSession()
	: CRTERootFunctor(RTERS_NewSession)
{
}


CRootNewSession::~CRootNewSession()
{
}


RTERootStyle_t CRootNewSession::DoFunctor(CRTERoot & _Root) const
{
	const auto code = this->NewSession(_Root);

	return(code);
}


RTERootStyle_t CRootNewSession::NewSession(CRTERoot & _Root) const
{
	auto pPayMail = GetCurrentPayMail();
	if (nullptr == pPayMail)
	{
		pPayMail = _Root.GetHostPay();
	}
	auto code(RTERS_NewSession);
	CRTDict back_dict;

	if (nullptr == pPayMail)
	{
		code = RTERS_BadToken;

		back_dict = RTNSTool::BackDictBy(GetCurrentMail(), "bad", "bad token");
	}
	else
	{
		const auto args = GetCurrentArgs();
		const auto idGroup = RTNSTool::GetIntValue4Dict(args, "groupid", 1);
		const auto idBase = RTNSDB::GetBase(idGroup);
		const auto Number = RTNSTool::GetIntValue4Dict(args, "number", 0);
		const auto Length = args["length"].GetInt();
		const auto Width = args["width"].GetInt();
		const auto Height = args["height"].GetInt();

		std::shared_ptr<CRTESession> pSession(new (std::nothrow) CRTESession(idGroup, idBase, Number, Length, Width, Height));

		if (nullptr == pSession)
		{
			code = RTERS_OutMemory;

			back_dict = RTNSTool::BackDictBy(GetCurrentMail(), "bad", "out memory");
		}
		else
		{
			if (true == _Root.GetMask(RTERS_ReplayMode))
			{
				pSession->SetMask(RTESS_ReplayMode);
			}

			const auto pMail = GetCurrentMail();
			const auto idSession = args["sessionid"].GetInt();

			pSession->SetSelfID(idSession);
			pSession->SetParent(&_Root);
			_Root.m_SessionManager[idSession] = pSession;

			pSession->m_PayManager[GetCurrentUserID()] = pPayMail;

			const CRTDict back_args{
				{ "sessionid", idSession },
			};
			back_dict = RTNSTool::BackDictBy(GetCurrentMail(), back_args);

			RTNSDB::NewDBReplay(&_Root, GetCurrentMail(), RTES_Session, idSession, 0);

			if (Number)
			{
				pSession->NextTollTimer();
			}
		}//else
	}//else

	const auto back_mail = RTNSTool::BackMail(GetCurrentMail(), back_dict);
	_Root.m_SendBuffer.Writer(back_mail);

	return(code);
}


CRootDeleteSession::CRootDeleteSession()
	: CRTERootFunctor(RTERS_DeleteSession)
{
}


CRootDeleteSession::~CRootDeleteSession()
{
}


RTERootStyle_t CRootDeleteSession::DoFunctor(CRTERoot & _Root) const
{
	const auto code = this->DeleteSession(_Root);

	return(code);
}


RTERootStyle_t CRootDeleteSession::DeleteSession(CRTERoot & _Root) const
{
	const auto args = GetCurrentArgs();
	const auto idSession = args["sessionid"].GetInt();

	auto code(RTERS_DeleteSession);
	auto strCode("ok");
	auto strMsg("luck");
	auto pSession = _Root.m_SessionManager[idSession];

	if (nullptr == pSession)
	{
		code = RTERS_NotFind;
		strCode = "bad";
		strMsg = "not find";
	}
	else
	{
		_Root.m_SessionManager.DeleteTarget(idSession);

		if (nullptr != _Root.m_SessionManager[idSession])
		{
			PrintLogInfo("delete session fail");
		}
	}

	RTNSDB::NewDBReplay(&_Root, GetCurrentMail(), RTES_Session, idSession, 0);

	const auto back_dict = RTNSTool::BackDictBy(GetCurrentMail(), strCode, strMsg);
	const auto back_mail = RTNSTool::BackMail(GetCurrentMail(), back_dict);
	_Root.m_SendBuffer.Writer(back_mail);

	return(code);
}


CRootQuery::CRootQuery()
	: CRTERootFunctor(RTERS_Query)
{
}


CRootQuery::~CRootQuery()
{
}


RTERootStyle_t CRootQuery::DoFunctor(CRTERoot & _Root) const
{
	const auto code = this->Query(_Root);

	return(code);
}


RTERootStyle_t CRootQuery::Query(CRTERoot & _Root) const
{
	const auto args = GetCurrentArgs();
	CRTDict back_args;

	if (true == args.HasKey("session"))
	{
		const auto IDs = _Root.m_SessionManager.Keys();
		back_args["ids"] = IDs;
	}
	else if (true == args.HasKey("game"))
	{
		const auto args = GetCurrentArgs();
		const auto idSession = args["sessionid"].GetInt();
		auto pSession = _Root.m_SessionManager[idSession];

		if (nullptr != pSession)
		{
			const auto IDs = pSession->m_GameManager.Keys();

			back_args["ids"] = IDs;
		}
	}
	else if (true == args.HasKey("sessionid"))
	{
		const auto idSession = RTNSDB::UpDBSessionID();

		back_args["id"] = idSession;
	}
	else if (true == args.HasKey("gameid"))
	{
		const auto idGame = RTNSDB::UpDBGameID();

		back_args["id"] = idGame;
	}

	const auto back_dict = RTNSTool::BackDictBy(GetCurrentMail(), back_args);
	const auto back_mail = RTNSTool::BackMail(GetCurrentMail(), back_dict);
	_Root.m_SendBuffer.Writer(back_mail);

	return(RTERS_Query);
}


CRootHealth::CRootHealth()
	: CRTERootFunctor(RTERS_Health)
{
}


CRootHealth::~CRootHealth()
{
}


RTERootStyle_t CRootHealth::DoFunctor(CRTERoot & _Root) const
{
	const auto code = this->Health(_Root);

	return(code);
}


RTERootStyle_t CRootHealth::Health(CRTERoot & _Root) const
{
	const auto Args = GetCurrentArgs();

	RTNSTool::DoHealth(&_Root, Args);

	return(RTERS_Health);
}

