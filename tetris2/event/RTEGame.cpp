#include "RTEGame.h"
#include "RTEGameStyle.h"
#include "RTEGameFunctor.h"
#include "RTEGameStatic.h"
#include "../RTNSDB.h"
#include "../RTNSLog.h"
#include "../RTNSTool.h"
#include "../RTCurrent.h"
#include "../RTDataType.h"
#include "../RTNSStatic.h"


CRTEGame::CRTEGame()
	: CRTEPayBase(RTES_Game)
	, CRTEGS()
	, m_pArea(nullptr)
	, m_pAreaBuffer(nullptr)
	, m_pBlock(nullptr)
	, m_pBlockBuffer(nullptr)
{
	this->SetMask(RTEGS_New);
}


CRTEGame::CRTEGame(const int _idGroup, const int _idBase)
	: CRTEPayBase(RTES_Game)
	, CRTEGS(_idGroup, _idBase)
	, m_pArea(nullptr)
	, m_pAreaBuffer(nullptr)
	, m_pBlock(nullptr)
	, m_pBlockBuffer(nullptr)
{
	this->SetMask(RTEGS_New);

	const auto msg = "\tconstructor game ptr : " + RTNSTool::uint2hexstring((unsigned int)this);
	PrintLogInfo(msg);
}


CRTEGame::CRTEGame(const CRTEGame &_other)
	: CRTEPayBase(_other)
	, CRTEGS(_other)
	, m_pArea(nullptr)
	, m_pAreaBuffer(nullptr)
	, m_pBlock(nullptr)
	, m_pBlockBuffer(nullptr)
{
	this->SetMask(RTEGS_New);
}


CRTEGame::~CRTEGame()
{
	const auto msg = "\tdestructor game ptr : " + RTNSTool::uint2hexstring((unsigned int)this);
	PrintLogInfo(msg);
}


bool CRTEGame::CanDoNext(void) const
{
	if (true == this->GetMask(RTEGS_ReplayMode))
	{
		return(false);
	}

	return(true);
}


CRTDict CRTEGame::GetNextArgs(void) const
{
	const auto Args = GetCurrentArgs();
	CRTDict BackArgs{
		{ "sessionid", this->GetParent()->GetSelfID() },
		{ "gameid", this->GetSelfID() },
	};

	if (Args.HasKey("x"))
	{
		BackArgs["x"] = Args["x"];
		BackArgs["y"] = Args["y"];
		BackArgs["z"] = Args["z"];
	}

	const auto Prefix = RTNSTool::SignGameLoop();
	BackArgs[Prefix + "id"] = m_pBlock->GetID();

	const auto pointO = m_pBlock->GetO();
	BackArgs[Prefix + "x"] = pointO.GetX();
	BackArgs[Prefix + "y"] = pointO.GetY();
	BackArgs[Prefix + "z"] = pointO.GetZ();

	BackArgs[Prefix + "health"] = (unsigned int)this->GetHealth();
	BackArgs[Prefix + "allmask"] = this->GetAllMask();

	return(BackArgs);
}


int CRTEGame::UpdateCurrentMail4UserCmd(void) const
{
	const auto Args = this->GetNextArgs();

	return(this->UpdateCurrentMail4UserCmd(Args));
}


int CRTEGame::UpdateCurrentMail4UserCmd(const std::string _Key, const int _Value) const
{
	auto Args = this->GetNextArgs();
	Args[_Key] = _Value;

	return(this->UpdateCurrentMail4UserCmd(Args));
}


int CRTEGame::UpdateCurrentMail4UserCmd(const CRTDict& _Args) const
{
	auto Dict = GetCurrentDict();
	Dict["args"] = _Args;

	const auto Mail = RTNSTool::dict2string(Dict);
	auto pMail = GetCurrentMail();

	return(RTNSDB::UpdateDBPackage(pMail->GetSelfID(), Mail));
}


void CRTEGame::NextDoctor(void)
{
	if (false == this->CanDoNext())
	{
		return;
	}

	const std::vector<std::string> ops{ "game", "doctor" };
	auto args = this->GetNextArgs();
	const auto Prefix = RTNSTool::SignGameLoop();
	args[Prefix + "id"] = RTNSDB::GetRandomDBBlockID(this->GetGroupID());
	args[Prefix + "x"] = 1;
	args[Prefix + "y"] = (m_pArea->GetWidth() - m_pBlock->GetWidth() + 2) / 2;
	args[Prefix + "z"] = 0;

	auto next_dict(GetCurrentDict());
	next_dict["ops"] = ops;
	next_dict["args"] = args;
	next_dict[RTNSTool::SignGameLoop()] = RTNSTool::GameLoopValue();

	const auto next_Mail = RTNSTool::BackMail(GetCurrentMail(), next_dict);
	m_SendBuffer.Writer(next_Mail);
}


void CRTEGame::NextHit(void)
{
	if (false == this->CanDoNext())
	{
		return;
	}

	const std::vector<std::string> ops{ "game", "hit" };
	const auto args = this->GetNextArgs();

	auto next_dict(GetCurrentDict());
	next_dict["ops"] = ops;
	next_dict["args"] = args;

	const auto next_Mail = RTNSTool::BackMail(GetCurrentMail(), next_dict);
	m_PrivateBuffer.Writer(next_Mail);
}


void CRTEGame::NextFreeze(void)
{
	if (false == this->CanDoNext())
	{
		return;
	}

	const std::vector<std::string> ops{ "game", "freeze" };
	const auto args = this->GetNextArgs();

	auto next_dict(GetCurrentDict());
	next_dict["ops"] = ops;
	next_dict["args"] = args;

	const auto next_Mail = RTNSTool::BackMail(GetCurrentMail(), next_dict);
	m_PrivateBuffer.Writer(next_Mail);
}


void CRTEGame::NextTarget(void)
{
	if (false == this->CanDoNext())
	{
		return;
	}

	const std::vector<std::string> ops{ "game", "target" };
	const auto args = this->GetNextArgs();

	auto next_dict(GetCurrentDict());
	next_dict["ops"] = ops;
	next_dict["args"] = args;

	const auto next_Mail = RTNSTool::BackMail(GetCurrentMail(), next_dict);
	m_PrivateBuffer.Writer(next_Mail);
}


void CRTEGame::NextCoin(const int _Coins)
{
	if (false == this->CanDoNext())
	{
		return;
	}

	const std::vector<std::string> ops{ "game", "coin" };
	auto args = this->GetNextArgs();
	args["coin"] = _Coins;

	auto next_dict(GetCurrentDict());
	next_dict["ops"] = ops;
	next_dict["args"] = args;

	const auto next_Mail = RTNSTool::BackMail(GetCurrentMail(), next_dict);
	m_PrivateBuffer.Writer(next_Mail);
}


void CRTEGame::NextRemove(const std::vector<int>& _Targets)
{
	if (false == this->CanDoNext())
	{
		return;
	}

	const std::vector<std::string> ops{ "game", "remove" };
	auto args = this->GetNextArgs();
	args["target"] = _Targets;

	auto next_dict(GetCurrentDict());
	next_dict["ops"] = ops;
	next_dict["args"] = args;

	const auto next_Mail = RTNSTool::BackMail(GetCurrentMail(), next_dict);

	m_PrivateBuffer.Writer(next_Mail);
}


void CRTEGame::NextDelete(void)
{
	if (false == this->CanDoNext())
	{
		return;
	}

	const std::vector<std::string> ops{ "game", "delete" };
	const auto args = this->GetNextArgs();

	auto next_dict(GetCurrentDict());
	next_dict["ops"] = ops;
	next_dict["args"] = args;

	const auto next_Mail = RTNSTool::BackMail(GetCurrentMail(), next_dict);

	m_PrivateBuffer.Writer(next_Mail);
}


void CRTEGame::NextGameOver(void)
{
	if (false == this->CanDoNext())
	{
		return;
	}

	const std::vector<std::string> ops{ "game", "over" };
	const auto args = this->GetNextArgs();

	auto next_dict(GetCurrentDict());
	next_dict["ops"] = ops;
	next_dict["args"] = args;

	const auto next_Mail = RTNSTool::BackMail(GetCurrentMail(), next_dict);
	m_PrivateBuffer.Writer(next_Mail);
}


void CRTEGame::NextGameWin(void)
{
	if (false == this->CanDoNext())
	{
		return;
	}

	const std::vector<std::string> ops{ "game", "win" };
	const auto args = this->GetNextArgs();

	auto next_dict(GetCurrentDict());
	next_dict["ops"] = ops;
	next_dict["args"] = args;

	const auto next_Mail = RTNSTool::BackMail(GetCurrentMail(), next_dict);
	m_PrivateBuffer.Writer(next_Mail);
}


void CRTEGame::NextSessionOver(void)
{
	if (false == this->CanDoNext())
	{
		return;
	}

	const std::vector<std::string> ops{ "session", "over" };
	const auto args = this->GetNextArgs();

	auto next_dict(GetCurrentDict());
	next_dict["ops"] = ops;
	next_dict["args"] = args;
	next_dict[RTNSTool::SignGameLoop()] = RTNSTool::GameLoopValue();

	const auto next_Mail = RTNSTool::BackMail(GetCurrentMail(), next_dict);
	m_SendBuffer.Writer(next_Mail);
}


int CRTEGame::Power(void)
{
	CMMaster Master(this);

	return(this->Run(true));
}


int CRTEGame::DoMail(void)
{
	const auto Ops = GetCurrentOps();
	const auto op1 = Ops[1];

	auto pGameFunctor = GetRTEGameFunctor(op1);
	if (nullptr == pGameFunctor)
	{
		auto pHoleFunctor = GetRTEGameFunctor("hole");
		if (nullptr != pHoleFunctor)
		{
			const auto codeRun = pHoleFunctor->operator ()(*this);
		}

		return(0);
	}

	if (RTEGS_Health == pGameFunctor->GetFunctorStyle()
		|| RTEGS_Over == pGameFunctor->GetFunctorStyle()
		)
	{
		const auto codeRun = pGameFunctor->operator ()(*this);

		return(2);
	}

	if (false == this->GetHealth(RTHS_DoMail))
	{
		return(-1);
	}

	if (false == this->GetMask(RTEGS_ReplayMode) || RTEGS_Watch == pGameFunctor->GetFunctorStyle())
	{
		const auto ok = this->GetMask(pGameFunctor->GetFunctorStyle());
		if (false == ok)
		{
			return(0);
		}
	}

	const auto codeRun = pGameFunctor->operator ()(*this);

	return(1);
}

