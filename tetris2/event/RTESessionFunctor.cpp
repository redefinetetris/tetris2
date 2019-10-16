#include "RTESessionFunctor.h"
#include "../RTDict.h"
#include "../RTMail.h"
#include "../RTNSDB.h"
#include "../RTNSLog.h"
#include "../RTNSTool.h"
#include "../RTDataType.h"
#include "../orm/RTDBSession.h"
#include "RTEStyle.h"
#include "RTEStatic.h"
#include "RTESession.h"
#include "RTEGameStyle.h"


CRTESessionFunctor::CRTESessionFunctor(const int _FunctorStyle)
	: CRTFunctor(_FunctorStyle)
{
}


CRTESessionFunctor::~CRTESessionFunctor()
{
}


RTESessionStyle_t CRTESessionFunctor::operator () (CRTESession & _Session) const
{
	const auto codeBase = this->ReplayCmd2DB(&_Session, GetCurrentMail());

	const auto codePreDoFunctor = this->PreDoFunctor(_Session);
	const auto codeDoFunctor = this->DoFunctor(_Session);
	const auto codePostDoFunctor = this->PostDoFunctor(_Session);

	return(codeDoFunctor);
}


RTESessionStyle_t CRTESessionFunctor::DoFunctor(CRTESession & _Session) const
{
	const auto code = this->Functor(_Session);

	return(code);
}


RTESessionStyle_t CRTESessionFunctor::Functor(CRTESession & _Session) const
{
	return(RTESS_Unknown);
}


RTESessionStyle_t CRTESessionFunctor::PreDoFunctor(CRTESession & _Session) const
{
	return(RTESS_Unknown);
}


RTESessionStyle_t CRTESessionFunctor::PostDoFunctor(CRTESession & _Session) const
{
	return(RTESS_Unknown);
}


CSessionNewGame::CSessionNewGame()
	: CRTESessionFunctor(RTESS_NewGame)
{
}


CSessionNewGame::~CSessionNewGame()
{
}


RTESessionStyle_t CSessionNewGame::DoFunctor(CRTESession & _Session) const
{
	const auto code = this->NewGame(_Session);

	return(code);
}


RTESessionStyle_t CSessionNewGame::NewGame(CRTESession & _Session) const
{
	auto pPayMail = GetCurrentPayMail();
	if (nullptr == pPayMail)
	{
		pPayMail = _Session.GetHostPay();
	}
	auto code(RTESS_NewGame);
	CRTDict back_dict;

	if (nullptr == pPayMail)
	{
		code = RTESS_BadToken;

		back_dict = RTNSTool::BackDictBy(GetCurrentMail(), "bad", "bad token");
	}
	else
	{
		std::shared_ptr<CRTEGame> pGame(new (std::nothrow) CRTEGame(_Session.GetGroupID(), _Session.GetBaseID()));
		if (nullptr == pGame)
		{
			code = RTESS_OutMemory;

			back_dict = RTNSTool::BackDictBy(GetCurrentMail(), "bad", "out memory");
		}
		else
		{
			if (true == _Session.GetMask(RTESS_ReplayMode))
			{
				const auto msg = "replay game ptr : " + RTNSTool::uint2hexstring((unsigned int)&*pGame);
				PrintLogInfo(msg);

				pGame->SetMask(RTEGS_ReplayMode);
			}

			const auto args = GetCurrentArgs();
			const auto idSession = _Session.GetSelfID();
			const auto idUser = GetCurrentUserID();
			const auto pMail = GetCurrentMail();
			const auto idGame = args["gameid"].GetInt();

			pGame->SetSelfID(idGame);

			_Session.m_GameManager[idGame] = pGame;
			pGame->SetParent(&_Session);

			pGame->m_PayManager[idGame] = pPayMail;

			const CRTDict back_args{
				{ "gameid", idGame },
			};
			back_dict = RTNSTool::BackDictBy(GetCurrentMail(), back_args);

			RTNSDB::NewDBReplay(&_Session, GetCurrentMail(), RTES_Game, idGame, 0);
		}//else
	}//else

	const auto back_mail = RTNSTool::BackMail(GetCurrentMail(), back_dict);
	_Session.m_SendBuffer.Writer(back_mail);

	return(code);
}


CSessionDeleteGame::CSessionDeleteGame()
	: CRTESessionFunctor(RTESS_DeleteGame)
{
}


CSessionDeleteGame::~CSessionDeleteGame()
{
}


RTESessionStyle_t CSessionDeleteGame::DoFunctor(CRTESession & _Session) const
{
	const auto code = this->DeleteGame(_Session);

	return(code);
}


RTESessionStyle_t CSessionDeleteGame::DeleteGame(CRTESession & _Session) const
{
	const auto args = GetCurrentArgs();
	const auto idGame = args["gameid"].GetInt();

	auto code(RTESS_DeleteGame);
	auto strCode("ok");
	auto strMsg("luck");
	auto pGame = _Session.m_GameManager[idGame];

	if (nullptr == pGame)
	{
		code = RTESS_NotFind;
		strCode = "bad";
		strMsg = "not find";
	}
	else
	{
		RTNSDB::NewDBReplay(&_Session, GetCurrentMail(), RTES_Game, idGame, 0);

		_Session.m_GameManager.DeleteTarget(idGame);
	}

	const auto back_dict = RTNSTool::BackDictBy(GetCurrentMail(), strCode, strMsg);
	const auto back_mail = RTNSTool::BackMail(GetCurrentMail(), back_dict);
	_Session.m_SendBuffer.Writer(back_mail);

	return(code);
}


CSessionTimer::CSessionTimer()
	: CRTESessionFunctor(RTESS_Timer)
{
}


CSessionTimer::~CSessionTimer()
{
}


RTESessionStyle_t CSessionTimer::DoFunctor(CRTESession & _Session) const
{
	const auto code = this->Timer(_Session);

	return(code);
}


RTESessionStyle_t CSessionTimer::Timer(CRTESession & _Session) const
{
	const auto args = GetCurrentArgs();
	const auto idSession = _Session.GetSelfID();
	const auto Circle = args["circle"].GetInt();
	const auto Microseconds = args["microseconds"].GetInt();
	const auto Op = args["op"].GetString();
	const auto Card = args["card"].GetString();
	const auto Msg = args["msg"].GetString();

	const auto timer_mail = RTNSTool::TimerMail("session", _Session.GetRTEStyle(), idSession, Circle, Op, Microseconds, Card, Msg);
	const auto back_mail = RTNSTool::BackMailBy(GetCurrentMail());

	const std::vector <std::shared_ptr<CRTMail>> Mails{ timer_mail, back_mail };
	_Session.m_SendBuffer.Writer(Mails);

	return(RTESS_Timer);
}


CSessionJump::CSessionJump()
	: CRTESessionFunctor(RTESS_Jump)
{
}


CSessionJump::~CSessionJump()
{
}


RTESessionStyle_t CSessionJump::DoFunctor(CRTESession & _Session) const
{
	const auto code = this->Jump(_Session);

	return(code);
}


RTESessionStyle_t CSessionJump::Jump(CRTESession & _Session) const
{
	const auto Msg = "jump: " + RTNSTool::int2string(_Session.GetSelfID());
	PrintLogInfo(Msg);

	const auto idSession = _Session.GetSelfID();
	const auto op("update");
	const auto microseconds = RTNSDB::GetSpeedByTime(_Session.UpSpeedID());
	const auto msg = RTNSTool::GetTimerMsg4RTESession(idSession, "move");

	const auto timer_mail = RTNSTool::TimerMail("session", _Session.GetRTEStyle(), idSession, 1, op, microseconds, "move", msg);
	const auto back_mail = RTNSTool::BackMailBy(GetCurrentMail());
	std::vector<std::shared_ptr<CRTMail>> Mails{ timer_mail, back_mail };

	_Session.m_SendBuffer.Writer(Mails);

	return(RTESS_Jump);
}


CSessionMove::CSessionMove()
	: CRTESessionFunctor(RTESS_Move)
{
}


CSessionMove::~CSessionMove()
{
}


RTESessionStyle_t CSessionMove::DoFunctor(CRTESession & _Session) const
{
	const auto code = this->Move(_Session);

	return(code);
}


RTESessionStyle_t CSessionMove::Move(CRTESession & _Session) const
{
	const static std::vector<std::string> _SessionMoveOps{ "game", "move" };
	const CRTDict MoveArgs{
		{ "x", 1 },
		{ "y", 0 },
		{ "z", 0 },
		{ "sessionid", _Session.GetSelfID() },
	};
	const CRTDict MoveDict{
		{ "ops", _SessionMoveOps },
		{ "args", MoveArgs },
		{ "id", RTNSTool::GetBackDictID() },
		{ RTNSTool::SignGameLoop(), RTNSTool::GameLoopValue() },
	};

	const auto MoveMail = RTNSTool::BackMail(MoveDict);
	_Session.m_PrivateBuffer.Writer(MoveMail);

	return(RTESS_Move);
}


CSessionRace::CSessionRace()
	: CRTESessionFunctor(RTESS_Race)
{
}


CSessionRace::~CSessionRace()
{
}


RTESessionStyle_t CSessionRace::DoFunctor(CRTESession & _Session) const
{
	const auto code = this->Race(_Session);

	return(code);
}


RTESessionStyle_t CSessionRace::Race(CRTESession & _Session) const
{
	const auto Msg = "race: " + RTNSTool::int2string(_Session.GetSelfID());
	PrintLogInfo(Msg);

	int player = 0;
	bool more = false;
	int min_coin = 0X7FFFFFFF;
	std::shared_ptr<CRTEGame> pTarget = nullptr;
	const auto Values = _Session.m_GameManager.Values();

	for (auto item = Values.begin(); item != Values.end(); ++item)
	{
		auto pGame = *item;
		if (nullptr == pGame || false == pGame->GetHealth(RTHS_DoMail))
		{
			continue;
		}

		++player;
		const auto coins = pGame->GetCoins();

		if (coins < min_coin)
		{
			min_coin = coins;
			pTarget = pGame;
			more = false;
		}
		//Æì¹ÄÏàµ±
		else if (coins == min_coin)
		{
			more = true;
			pTarget = nullptr;
		}
	}//for

	if (1 == player)
	{
		_Session.NextRaceTimer();

		const auto mailWin = RTNSTool::SessionMail(_Session.GetSelfID(), pTarget->GetSelfID(), "win", 0);
		_Session.m_PrivateBuffer.Writer(mailWin);
	}
	else if (nullptr != pTarget)
	{
		pTarget->NextGameOver();

		if (false == more && 2 == player)
		{
			const auto mailRace = RTNSTool::SessionMail(_Session.GetSelfID(), 0, "race", RTNSTool::HubLoopValue());

			_Session.m_SendBuffer.Writer(mailRace);
		}
	}//else

	return(RTESS_Race);
}


CSessionFire::CSessionFire()
	: CRTESessionFunctor(RTESS_Fire)
{
}


CSessionFire::~CSessionFire()
{
}


RTESessionStyle_t CSessionFire::DoFunctor(CRTESession & _Session) const
{
	const auto code = this->Fire(_Session);

	return(code);
}


RTESessionStyle_t CSessionFire::Fire(CRTESession & _Session) const
{
	const auto args = GetCurrentArgs();
	const auto op = args["op"].GetString();
	const auto idSession = _Session.GetSelfID();

	const auto DefaultTime = RTNSTool::GetMinute(1);
	const auto microseconds4Jump = RTNSTool::GetIntValue4Dict(args, "jump", DefaultTime);
	auto microseconds4Race = RTNSTool::GetIntValue4Dict(args, "race", DefaultTime);
	const auto microseconds4Move = RTNSTool::GetIntValue4Dict(args, "move", RTNSDB::GetSpeedByTime(_Session.UpSpeedID()));//Ä¬ÈÏ1Ãë

	if (false == args.HasKey("race"))
	{
		microseconds4Race = 0;
	}

	auto Mails = RTNSTool::GetSessionClockMails(0, idSession, op, microseconds4Jump, microseconds4Race, microseconds4Move);
	const auto mailBack = RTNSTool::BackMailBy(GetCurrentMail());
	Mails.push_back(mailBack);

	_Session.m_SendBuffer.Writer(Mails);

	return(RTESS_Fire);
}


CSessionWin::CSessionWin()
	: CRTESessionFunctor(RTESS_Win)
{
}


CSessionWin::~CSessionWin()
{
}


RTESessionStyle_t CSessionWin::DoFunctor(CRTESession & _Session) const
{
	const auto code = this->Win(_Session);

	return(code);
}


RTESessionStyle_t CSessionWin::Win(CRTESession & _Session) const
{
	_Session.NextGameOver();

	const auto args = GetCurrentArgs();
	const auto GameID = args["gameid"].GetInt();

	const auto Msg = "win session: " + RTNSTool::int2string(_Session.GetSelfID()) + "\tgame: " + RTNSTool::int2string(GameID);
	PrintLogInfo(Msg);

	auto pGame = _Session.m_GameManager[GameID];
	if (nullptr == pGame)
	{
		return(RTESS_NotFind);
	}

	pGame->NextGameWin();

	return(RTESS_Win);
}


CSessionOver::CSessionOver()
	: CRTESessionFunctor(RTESS_Over)
{
}


CSessionOver::~CSessionOver()
{
}


RTESessionStyle_t CSessionOver::DoFunctor(CRTESession & _Session) const
{
	const auto code = this->Over(_Session);

	return(code);
}


RTESessionStyle_t CSessionOver::Over(CRTESession & _Session) const
{
	bool AllDeath = true;
	const auto Games = _Session.m_GameManager.Values();

	for (auto item = Games.begin(); item != Games.end(); ++item)
	{
		auto pGame = *item;
		if (nullptr == pGame)
		{
			continue;
		}

		if (true == pGame->GetHealth(RTHS_DoMail))
		{
			AllDeath = false;
			break;
		}
	}//for

	if (false == AllDeath)
	{
		return(RTESS_Over);
	}

	const auto pRoot = _Session.GetParent();
	auto Mails = RTNSTool::GetSessionClockMails(pRoot->GetSelfID(), _Session.GetSelfID(), "delete", 1, 1, 1);

	const auto DBTime = RTNSTool::GetSecond(23);
	const auto DBMails = RTNSTool::GetDBClockMails(0, "new", DBTime, DBTime, DBTime, 0);

	Mails.insert(Mails.end(), DBMails.begin(), DBMails.end());

	_Session.m_SendBuffer.Writer(Mails);

	return(RTESS_Over);
}


CSessionHealth::CSessionHealth()
	: CRTESessionFunctor(RTESS_Health)
{
}


CSessionHealth::~CSessionHealth()
{
}


RTESessionStyle_t CSessionHealth::DoFunctor(CRTESession & _Session) const
{
	const auto code = this->Health(_Session);

	return(code);
}


RTESessionStyle_t CSessionHealth::Health(CRTESession & _Session) const
{
	const auto Args = GetCurrentArgs();

	RTNSTool::DoHealth(&_Session, Args);

	return(RTESS_Health);
}


CSessionToll::CSessionToll()
	: CRTESessionFunctor(RTESS_Toll)
{
}


CSessionToll::~CSessionToll()
{
}


RTESessionStyle_t CSessionToll::DoFunctor(CRTESession & _Session) const
{
	const auto code = this->Toll(_Session);

	return(code);
}


RTESessionStyle_t CSessionToll::Toll(CRTESession & _Session) const
{
	const auto Total = _Session.GetNumber();
	const auto Size = _Session.m_GameManager.Size();
	if (Size < Total)
	{
		const CRTDict Args{
			{ "total", Total },
			{ "size", Size },
			{ "sessionid", _Session.GetSelfID() },
		};
		const std::vector<std::string> Ops{ "session", "wait" };
		const CRTDict Dict{
			{ "ops", Ops },
			{ "args", Args },
		};

		_Session.BackMail2PayUser(Dict);

		return(RTESS_Toll);
	}

	const auto TTF = _Session.DownTTF();
	if (TTF)
	{
		const CRTDict Args{
			{ "ttf", TTF },
			{ "sessionid", _Session.GetSelfID() },
		};
		const std::vector<std::string> Ops{ "session", "toll" };
		const CRTDict Dict{
			{ "ops", Ops },
			{ "args", Args },
		};

		_Session.BackMail2PayUser(Dict);

		return(RTESS_Toll);
	}

	_Session.NextTollTimer("delete");
	_Session.NextGameNew();
	_Session.NextRace();

	return(RTESS_Toll);
}

