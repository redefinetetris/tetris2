#include "RTESession.h"
#include "RTESessionStyle.h"
#include "RTESessionFunctor.h"
#include "RTESessionStatic.h"
#include "../RTNSDB.h"
#include "../RTNSLog.h"
#include "../RTNSTool.h"
#include "../RTDataType.h"
#include "../RTNSStatic.h"


CRTESession::CRTESession()
	: CRTEPayBase(RTES_Session)
	, CRTEGS()
	, m_SpeedID(0)
	, m_Number(0)
	, m_TTF(5)
	, m_Length(0)
	, m_Width(0)
	, m_Height(0)
	, m_GameManager()
{
}


CRTESession::CRTESession(const int _idGroup, const int _idBase, const int _Number, const int _Length, const int _Width, const int _Height)
	: CRTEPayBase(RTES_Session)
	, CRTEGS(_idGroup, _idBase)
	, m_SpeedID(0)
	, m_Number(_Number)
	, m_TTF(5)
	, m_Length(_Length)
	, m_Width(_Width)
	, m_Height(_Height)
	, m_GameManager()
{
}


CRTESession::~CRTESession()
{
}


int CRTESession::GetSpeedID(void) const
{
	return(m_SpeedID);
}


void CRTESession::SetSpeedID(const int &_SpeedID)
{
	m_SpeedID = _SpeedID;
}


int CRTESession::UpSpeedID(void)
{
	return(++m_SpeedID);
}


int CRTESession::GetNumber(void) const
{
	return(m_Number);
}


void CRTESession::SetNumber(const int &_Number)
{
	m_Number = _Number;
}


int CRTESession::GetTTF(void) const
{
	return(m_TTF);
}


int CRTESession::DownTTF(void)
{
	return(--m_TTF);
}


void CRTESession::SetTTF(const int &_TTF)
{
	m_TTF = _TTF;
}


int CRTESession::GetLength(void) const
{
	return(m_Length);
}


void CRTESession::SetLength(const int &_Length)
{
	m_Length = _Length;
}


int CRTESession::GetWidth(void) const
{
	return(m_Width);
}


void CRTESession::SetWidth(const int &_Width)
{
	m_Width = _Width;
}


int CRTESession::GetHeight(void) const
{
	return(m_Height);
}


void CRTESession::SetHeight(const int &_Height)
{
	m_Height = _Height;
}


void CRTESession::NextTollTimer(const std::string _Op)
{
	const auto Time = RTNSTool::GetSecond(1);
	const auto pMail = RTNSTool::GetSessionTimerMail(this->GetSelfID(), "toll", _Op, Time, RTNSTool::GetTimerMsg4RTESession(this->GetSelfID(), "toll"));

	m_SendBuffer.Writer(pMail);
}


void CRTESession::NextRaceTimer(const std::string _Op)
{
	const auto Time = RTNSTool::GetSecond(1);
	const auto pMail = RTNSTool::GetSessionTimerMail(this->GetSelfID(), "race", _Op, Time, RTNSTool::GetTimerMsg4RTESession(this->GetSelfID(), "race"));

	m_SendBuffer.Writer(pMail);
}


void CRTESession::NextGameNew(void)
{
	const CRTDict Args{
		{ "length", this->GetLength() },
		{ "width", this->GetWidth() },
		{ "height", this->GetHeight() },
		{ "base", this->GetBaseID() },
		{ "sessionid", this->GetSelfID() },
	};
	const std::vector<std::string> Ops{ "game", "new" };
	const CRTDict Dict{
		{ "ops", Ops },
		{ "args", Args },
	};
	auto pMail = RTNSTool::BackMail(Dict);

	m_PrivateBuffer.Writer(pMail);
}


void CRTESession::NextGameOver(void)
{
	const std::vector<std::string> Ops{ "game", "over" };
	const CRTDict Dict{
		{ "ops", Ops },
	};
	auto pMail = RTNSTool::BackMail(Dict);

	m_PrivateBuffer.Writer(pMail);
}


void CRTESession::NextRace(void)
{
	const CRTDict Args{
		{ "op", "new" },
		{ "sessionid", this->GetSelfID() },
		{ "race", RTNSTool::GetMinute(1) },
	};
	const std::vector<std::string> Ops{ "session", "fire" };
	const CRTDict Dict{
		{ "ops", Ops },
		{ "args", Args },
	};
	auto pMail = RTNSTool::BackMail(Dict);

	m_PrivateBuffer.Writer(pMail);
}


void CRTESession::BackMail2PayUser(const CRTDict& _Dict)
{
	const auto Games = m_GameManager.Values();

	for (auto item = Games.begin(); item != Games.end(); ++item)
	{
		auto pGame = *item;
		if (nullptr == pGame)
		{
			continue;
		}

		pGame->BackMail2PayUser(_Dict);
	}//for
}


int CRTESession::Power(void)
{
	CMMaster Master(this);

	int work = 0;

	work += this->RunLocker();

	this->FlushWriter();

	return(work);
}


int CRTESession::SelfRun(void)
{
	int work = 0;

	work += this->Mailer();

	const auto Games = m_GameManager.Values();

	for (auto item = Games.begin(); item != Games.end(); ++item)
	{
		auto pGame = *item;
		if (nullptr == pGame)
		{
			continue;
		}

		work += pGame->Power();
	}

	return(work);
}


int CRTESession::Mailer(void)
{
	int work = 0;

	//集中邮件
	const auto Mails = this->GameM();
	//邮件甄别
	work += this->GuardM(Mails);

	return(work);
}


std::vector<std::shared_ptr<CRTMail>> CRTESession::GameM(void)
{
	std::vector<std::shared_ptr<CRTMail>> Mails;
	Mails.reserve(VECTOR_RESERVE_SIZE);
	const auto Games = m_GameManager.Values();

	for (auto item = Games.begin(); item != Games.end(); ++item)
	{
		auto pGame = *item;
		if (nullptr == pGame)
		{
			continue;
		}

		const auto ok = pGame->m_SendBuffer.Reader(Mails);
	}//for

	return(Mails);
}


int CRTESession::GuardM(const std::vector<std::shared_ptr<CRTMail>>& _Mails)
{
	int work = 0;
	std::vector<std::shared_ptr<CRTMail>> Recvs;
	Recvs.reserve(VECTOR_RESERVE_SIZE);
	std::vector<std::shared_ptr<CRTMail>> Sends;
	Sends.reserve(VECTOR_RESERVE_SIZE);

	for (auto item = _Mails.begin(); item != _Mails.end(); ++item)
	{
		++work;

		const auto& pMail = *item;
		const auto dict = pMail->GetDict();

		if (dict.HasKey(RTNSTool::SignSessionLoop())
			|| dict.HasKey(RTNSTool::SignGameLoop())
			)
		{
			Recvs.push_back(pMail);
		}
		else/* if (mail.IPOK())*/
		{
			Sends.push_back(pMail);
		}
	}//for

	this->NewPrivateMail(Recvs);
	m_SendBuffer.Writer(Sends);

	return(work);
}


int CRTESession::DoMail(void)
{
	CRTESessionFunctor* pSessionFunctor = nullptr;
	const auto Ops = GetCurrentOps();

	if ("session" == Ops[0])
	{
		const auto op1 = Ops[1];
		pSessionFunctor = GetRTESessionFunctor(op1);
		if (nullptr == pSessionFunctor)
		{
			return(0);
		}

		if (RTESS_Health == pSessionFunctor->GetFunctorStyle())
		{
			const auto codeRun = pSessionFunctor->operator ()(*this);

			return(2);
		}
	}

	if (false == this->GetHealth(RTHS_DoMail))
	{
		return(-1);
	}

	if (nullptr == pSessionFunctor)
	{
		return(this->DoMailGame());
	}

	pSessionFunctor->operator ()(*this);

	return(1);
}


int CRTESession::DoMailGame(void)
{
	const auto args = GetCurrentArgs();
	const auto idGame = RTNSTool::GetIntValue4Dict(args, "gameid", 0);

	if (idGame)
	{
		auto pGame = m_GameManager[idGame];

		if (nullptr != pGame)
		{
			pGame->m_RecvBuffer.Writer(GetCurrentMail());
		}
	}
	else
	{
		const auto Games = m_GameManager.Values();

		for (auto item = Games.begin(); item != Games.end(); ++item)
		{
			auto pGame = *item;
			if (nullptr == pGame)
			{
				continue;
			}

			auto Args = GetCurrentArgs();
			if (true == Args.IsEmpty())
			{
				Args = pGame->GetNextArgs();
			}
			else
			{
				Args["gameid"] = pGame->GetSelfID();
			}
			auto Dict = GetCurrentDict();
			Dict["args"] = Args;
			auto pMail = RTNSTool::BackMail(Dict);

			pGame->m_RecvBuffer.Writer(pMail);
		}//for
	}//else

	return(1);
}


int CRTESession::FlushWriter(void)
{
	int work = 0;
	const auto Games = m_GameManager.Values();

	for (auto item = Games.begin(); item != Games.end(); ++item)
	{
		auto pGame = *item;
		if (nullptr == pGame)
		{
			continue;
		}

		work += pGame->m_RecvBuffer.FlushWriter();
	}

	return(work);
}

