#include "RTEGameFunctor.h"
#include "../RTDict.h"
#include "../RTMail.h"
#include "../RTNSDB.h"
#include "../RTNSLog.h"
#include "../RTNSTool.h"
#include "../RTDataType.h"
#include "../orm/RTDBGame.h"
#include "../orm/RTDBBlock.h"
#include "RTEGame.h"


CRTEGameFunctor::CRTEGameFunctor(const int _FunctorStyle)
	: CRTFunctor(_FunctorStyle)
{
}


CRTEGameFunctor::~CRTEGameFunctor()
{
}


RTEGameStyle_t CRTEGameFunctor::operator () (CRTEGame & _Game) const
{
	const auto codeBase = this->ReplayCmd2DB(&_Game, GetCurrentMail());
	RTEGameStyle_t codeFunctor = RTEGS_Unknown;

	const auto ModeHistory = CurrentHistory();

	if (RTNSTool::BackwardValue() != ModeHistory)
	{
		const auto codePreDoFunctor = this->PreDoFunctor(_Game);
		codeFunctor = this->DoFunctor(_Game);
		const auto codePostDoFunctor = this->PostDoFunctor(_Game);
	}
	else
	{
		const auto codePreUnDoFunctor = this->PreUnDoFunctor(_Game);
		codeFunctor = this->UnDoFunctor(_Game);
		const auto codePostUnDoFunctor = this->PostUnDoFunctor(_Game);
	}

	return(codeFunctor);
}


RTEGameStyle_t CRTEGameFunctor::DoFunctor(CRTEGame & _Game) const
{
	const auto code = this->Functor(_Game);

	return(code);
}


RTEGameStyle_t CRTEGameFunctor::UnDoFunctor(CRTEGame & _Game) const
{
	const auto code = this->UnFunctor(_Game);

	return(code);
}


RTEGameStyle_t CRTEGameFunctor::Functor(CRTEGame & _Game) const
{
	return(RTEGS_Unknown);
}


RTEGameStyle_t CRTEGameFunctor::UnFunctor(CRTEGame & _Game) const
{
	return(RTEGS_Unknown);
}


RTEGameStyle_t CRTEGameFunctor::PreDoFunctor(CRTEGame & _Game) const
{
	return(RTEGS_Unknown);
}


RTEGameStyle_t CRTEGameFunctor::PostDoFunctor(CRTEGame & _Game) const
{
	return(RTEGS_Unknown);
}


RTEGameStyle_t CRTEGameFunctor::PreUnDoFunctor(CRTEGame & _Game) const
{
	return(RTEGS_Unknown);
}


RTEGameStyle_t CRTEGameFunctor::PostUnDoFunctor(CRTEGame & _Game) const
{
	return(RTEGS_Unknown);
}


CGameNew::CGameNew()
	: CRTEGameFunctor(RTEGS_New)
{
}


CGameNew::~CGameNew()
{
}


RTEGameStyle_t CGameNew::DoFunctor(CRTEGame & _Game) const
{
	const auto code = this->New(_Game);

	return(code);
}


RTEGameStyle_t CGameNew::UnDoFunctor(CRTEGame & _Game) const
{
	const auto code = this->UnNew(_Game);

	return(code);
}


RTEGameStyle_t CGameNew::New(CRTEGame & _Game) const
{
	const auto args = GetCurrentArgs();
	const auto base = _Game.GetBaseID();
	const auto length = args["length"].GetInt() + base + 2;
	const auto width = args["width"].GetInt() + 2;

	const auto bSuccess = RTNSTool::NewGameSpace(_Game.m_pArea, _Game.m_pAreaBuffer, _Game.m_pBlock, _Game.m_pBlockBuffer, length, width, base);

	auto code(RTEGS_New);
	auto strCode("ok");
	auto strMsg("luck");

	if (false == bSuccess)
	{
		code = RTEGS_OutMemory;
		strCode = "bad";
		strMsg = "out memoty";

		_Game.SetMask(RTEGS_OutMemory);
	}
	else
	{
		_Game.m_pArea->SetBorder();

		_Game.SetMask(RTEGS_4_Area);
		_Game.NextDoctor();
	}

	_Game.BackMail2PayUser(strCode, strMsg);

	return(code);
}


RTEGameStyle_t CGameNew::UnNew(CRTEGame & _Game) const
{
	_Game.m_pBlock->ClearValue();
	const auto Dict = RTNSTool::WatchDict(*_Game.m_pArea, *_Game.m_pBlock);
	_Game.BackMail2PayUser(_Game.GetSelfID(), Dict);

	const auto bSuccess = RTNSTool::DeleteGameSpace(_Game.m_pArea, _Game.m_pAreaBuffer, _Game.m_pBlock, _Game.m_pBlockBuffer);

	_Game.BackMail2PayUser();

	return(RTEGS_New);
}


CGameDelete::CGameDelete()
	: CRTEGameFunctor(RTEGS_Delete)
{
}


CGameDelete::~CGameDelete()
{
}


RTEGameStyle_t CGameDelete::DoFunctor(CRTEGame & _Game) const
{
	const auto code = this->Delete(_Game);

	return(code);
}


RTEGameStyle_t CGameDelete::UnDoFunctor(CRTEGame & _Game) const
{
	const auto code = this->UnDelete(_Game);

	return(code);
}


RTEGameStyle_t CGameDelete::Delete(CRTEGame & _Game) const
{
	std::unique_ptr<CRTBlock> pArea(std::move(_Game.m_pArea));
	std::unique_ptr<CRTBlock> pAreaBuffer(std::move(_Game.m_pAreaBuffer));
	std::unique_ptr<CRTBlock> pBlock(std::move(_Game.m_pBlock));
	std::unique_ptr<CRTBlock> pBlockBuffer(std::move(_Game.m_pBlockBuffer));

	auto code(RTEGS_Delete);
	auto strCode("ok");
	auto strMsg("luck");

	if (nullptr == pArea || nullptr == pAreaBuffer || nullptr == pBlock || nullptr == pBlockBuffer)
	{
		code = RTEGS_Bad;
		strCode = "bad";
		strMsg = "no new";
	}
	else
	{
		auto args = GetCurrentArgs();
		const auto Prefix = RTNSTool::SignGameLoop();
		args[Prefix + "length"] = pArea->GetLength();
		args[Prefix + "width"] = pArea->GetWidth();
		args[Prefix + "base"] = pBlock->GetLength();

		args[Prefix + "game_cells"] = pArea->GetValue();
		args[Prefix + "game_coins"] = _Game.GetCoins();
		args[Prefix + "block_cells"] = pBlock->GetValue();

		auto dict = GetCurrentDict();
		dict["args"] = args;
		auto pMail = GetCurrentMail();
		pMail->SetDict(dict);
		RTNSDB::UpdateDBPackage(pMail);

		_Game.SetAllMask(RTEGS_DisableAll);
	}//else

	_Game.BackMail2PayUser();

	return(code);
}


RTEGameStyle_t CGameDelete::UnDelete(CRTEGame & _Game) const
{
	const auto args = GetCurrentArgs();
	const auto Prefix = RTNSTool::SignGameLoop();
	const auto length = args[Prefix + "length"].GetInt();
	const auto width = args[Prefix + "width"].GetInt();
	const auto base = args[Prefix + "base"].GetInt();

	const auto bSuccess = RTNSTool::NewGameSpace(_Game.m_pArea, _Game.m_pAreaBuffer, _Game.m_pBlock, _Game.m_pBlockBuffer, length, width, base);

	auto code(RTEGS_Delete);
	auto strCode("ok");
	auto strMsg("luck");

	if (false == bSuccess)
	{
		code = RTEGS_OutMemory;
		strCode = "bad";
		strMsg = "out memoty";

		_Game.SetMask(RTEGS_OutMemory);
	}
	else
	{
		const auto GameCells = args[Prefix + "game_cells"].GetVectorInt();
		const auto Coins = args[Prefix + "game_coins"].GetInt();
		const auto id = args[Prefix + "id"].GetInt();
		const auto x = args[Prefix + "x"].GetInt();
		const auto y = args[Prefix + "y"].GetInt();
		const auto z = args[Prefix + "z"].GetInt();
		const auto BlockCells = args[Prefix + "block_cells"].GetVectorInt();

		_Game.m_pArea->SetValue(GameCells);
		_Game.SetCoins(Coins);

		_Game.m_pBlock->SetID(id);
		CRTPoint pointO(x, y, z);
		_Game.m_pBlock->SetO(pointO);
		_Game.m_pBlock->SetValue(BlockCells);

		_Game.SetMask(RTEGS_4_Area);
	}

	_Game.BackMail2PayUser(strCode, strMsg);

	return(code);
}


CGameDoctor::CGameDoctor()
	: CRTEGameFunctor(RTEGS_Doctor)
{
}


CGameDoctor::~CGameDoctor()
{
}


RTEGameStyle_t CGameDoctor::DoFunctor(CRTEGame & _Game) const
{
	const auto code = this->Doctor(_Game);

	return(code);
}


RTEGameStyle_t CGameDoctor::UnDoFunctor(CRTEGame & _Game) const
{
	const auto code = this->UnDoctor(_Game);

	return(code);
}


RTEGameStyle_t CGameDoctor::Doctor(CRTEGame & _Game) const
{
	const auto args = GetCurrentArgs();
	auto& pArea = _Game.m_pArea;
	auto& pBlock = _Game.m_pBlock;

	RTNSTool::RecoverBlock(*pBlock, args);

	auto code(RTEGS_Doctor);
	const auto codeDetect = RTNSTool::DetectHit(*pArea, *pBlock);

	if (codeDetect)
	{
		pBlock->ClearO();
		pBlock->ClearValue();

		_Game.NextGameOver();

		code = RTEGS_Over;
	}
	else
	{
		_Game.SetMask(RTEGS_4_Doctor);

		_Game.BackMail2PayUser();
	}

	return(code);
}


RTEGameStyle_t CGameDoctor::UnDoctor(CRTEGame & _Game) const
{
	RTNSTool::Merge(*_Game.m_pArea, *_Game.m_pBlock, 0);

	_Game.BackMail2PayUser();

	return(RTEGS_Doctor);
}


CGameMove::CGameMove()
	: CRTEGameFunctor(RTEGS_Move)
{
}


CGameMove::~CGameMove()
{
}


RTEGameStyle_t CGameMove::DoFunctor(CRTEGame & _Game) const
{
	_Game.UpdateCurrentMail4UserCmd();

	const auto code = this->Move(_Game);

	return(code);
}


RTEGameStyle_t CGameMove::UnDoFunctor(CRTEGame & _Game) const
{
	const auto code = this->UnMove(_Game);

	return(code);
}


RTEGameStyle_t CGameMove::Move(CRTEGame & _Game) const
{
	const auto args = GetCurrentArgs();
	const auto x_offset = args["x"].GetInt();
	const auto y_offset = args["y"].GetInt();
	const auto z_offset = args["z"].GetInt();

	auto& pBlock = _Game.m_pBlock;
	auto& pBlockBuffer = _Game.m_pBlockBuffer;

	auto pointO = pBlock->GetO();
	pointO += CRTPoint(x_offset, y_offset, z_offset);

	pBlockBuffer->SetO(pointO);
	pBlockBuffer->SetValue(pBlock->GetValue());
	pBlockBuffer->SetID(pBlock->GetID());

	_Game.NextHit();

	return(RTEGS_Move);
}


RTEGameStyle_t CGameMove::UnMove(CRTEGame & _Game) const
{
	const auto args = GetCurrentArgs();
	const auto idBlock = RTNSTool::RecoverBlock(*_Game.m_pBlock, args);

	_Game.BackMail2PayUser();

	return(RTEGS_Move);
}


CGameTransfer::CGameTransfer()
	: CRTEGameFunctor(RTEGS_Transfer)
{
}


CGameTransfer::~CGameTransfer()
{
}


RTEGameStyle_t CGameTransfer::DoFunctor(CRTEGame & _Game) const
{
	_Game.UpdateCurrentMail4UserCmd();

	const auto code = this->Transfer(_Game);

	return(code);
}


RTEGameStyle_t CGameTransfer::UnDoFunctor(CRTEGame & _Game) const
{
	const auto code = this->UnTransfer(_Game);

	return(code);
}


RTEGameStyle_t CGameTransfer::Transfer(CRTEGame & _Game) const
{
	auto& pBlock = _Game.m_pBlock;
	const auto args = GetCurrentArgs();
	auto nextID = 0;

	if (args.HasKey("style"))
	{
		nextID = args["style"].GetInt();
	}
	else
	{
		nextID = RTNSDB::GetNextDBBlockID(pBlock->GetID());
	}

	auto pDBBlock = RTNSDB::GetDBBlock(nextID);
	const auto Values = RTNSTool::string2vector(pDBBlock->GetBlock());
	auto& pBlockBuffer = _Game.m_pBlockBuffer;

	pBlockBuffer->SetO(pBlock->GetO());
	pBlockBuffer->SetValue(Values);
	pBlockBuffer->SetID(pDBBlock->GetID());

	_Game.NextHit();

	return(RTEGS_Transfer);
}


RTEGameStyle_t CGameTransfer::UnTransfer(CRTEGame & _Game) const
{
	const auto args = GetCurrentArgs();
	RTNSTool::RecoverBlock(*_Game.m_pBlock, args);

	_Game.BackMail2PayUser();

	return(RTEGS_Transfer);
}


CGameHit::CGameHit()
	: CRTEGameFunctor(RTEGS_Hit)
{
}


CGameHit::~CGameHit()
{
}


RTEGameStyle_t CGameHit::DoFunctor(CRTEGame & _Game) const
{
	const auto code = this->Hit(_Game);

	return(code);
}


RTEGameStyle_t CGameHit::UnDoFunctor(CRTEGame & _Game) const
{
	const auto code = this->UnHit(_Game);

	return(code);
}


RTEGameStyle_t CGameHit::Hit(CRTEGame & _Game) const
{
	const auto codeDetectHit = RTNSTool::DetectHit(*_Game.m_pArea, *_Game.m_pBlockBuffer);
	auto strCode("ok");
	auto strMsg("no hit");

	if (codeDetectHit)
	{
		const auto Prefix = RTNSTool::SignGameLoop();
		_Game.UpdateCurrentMail4UserCmd(Prefix + "hit", 1);

		const auto codeDetectFreeze = RTNSTool::DetectFreeze(GetCurrentArgs());
		if (codeDetectFreeze)
		{
			strCode = "bad";
			strMsg = "hit";

			_Game.NextFreeze();
		}
	}
	else
	{
		std::swap(_Game.m_pBlock, _Game.m_pBlockBuffer);
	}

	_Game.BackMail2PayUser(strCode, strMsg);

	return(RTEGS_Hit);
}


RTEGameStyle_t CGameHit::UnHit(CRTEGame & _Game) const
{
	return(RTEGS_Unknown);
}


CGameFreeze::CGameFreeze()
	: CRTEGameFunctor(RTEGS_Freeze)
{
}


CGameFreeze::~CGameFreeze()
{
}


RTEGameStyle_t CGameFreeze::DoFunctor(CRTEGame & _Game) const
{
	const auto code = this->Freeze(_Game);

	return(code);
}


RTEGameStyle_t CGameFreeze::UnDoFunctor(CRTEGame & _Game) const
{
	const auto code = this->UnFreeze(_Game);

	return(code);
}


RTEGameStyle_t CGameFreeze::Freeze(CRTEGame & _Game) const
{
	RTNSTool::Merge(*_Game.m_pArea, *_Game.m_pBlock);

	_Game.NextTarget();

	_Game.BackMail2PayUser();

	return(RTEGS_Freeze);
}


RTEGameStyle_t CGameFreeze::UnFreeze(CRTEGame & _Game) const
{
	const auto args = GetCurrentArgs();
	const auto idBlock = RTNSTool::RecoverBlock(*_Game.m_pBlock, args);

	RTNSTool::Merge(*_Game.m_pArea, *_Game.m_pBlock, 0);

	_Game.BackMail2PayUser();

	return(RTEGS_Freeze);
}


CGameTarget::CGameTarget()
	: CRTEGameFunctor(RTEGS_Target)
{
}


CGameTarget::~CGameTarget()
{
}


RTEGameStyle_t CGameTarget::DoFunctor(CRTEGame & _Game) const
{
	const auto code = this->Target(_Game);

	return(code);
}


RTEGameStyle_t CGameTarget::UnDoFunctor(CRTEGame & _Game) const
{
	const auto code = this->UnTarget(_Game);

	return(code);
}


RTEGameStyle_t CGameTarget::Target(CRTEGame & _Game) const
{
	_Game.m_pBlock->CountRealLength();

	const auto Target = RTNSTool::DetectTarget(*_Game.m_pArea, *_Game.m_pBlock);
	_Game.m_pBlock->ClearValue();

	if (Target.size())
	{
		_Game.NextCoin(Target.size()*RTNSDB::GetCoinsPerLine());
		_Game.NextRemove(Target);
	}
	else
	{
		_Game.BackMail2PayUser();
	}

	_Game.SetMask(RTEGS_4_Target);
	_Game.NextDoctor();

	return(RTEGS_Target);
}


RTEGameStyle_t CGameTarget::UnTarget(CRTEGame & _Game) const
{
	return(RTEGS_Unknown);
}


CGameCoin::CGameCoin()
	: CRTEGameFunctor(RTEGS_Coin)
{
}


CGameCoin::~CGameCoin()
{
}


RTEGameStyle_t CGameCoin::DoFunctor(CRTEGame & _Game) const
{
	const auto code = this->Coin(_Game);

	return(code);
}


RTEGameStyle_t CGameCoin::UnDoFunctor(CRTEGame & _Game) const
{
	const auto code = this->UnCoin(_Game);

	return(code);
}


RTEGameStyle_t CGameCoin::Coin(CRTEGame & _Game) const
{
	const auto args = GetCurrentArgs();
	const auto coin = args["coin"].GetInt();

	if (0 == coin)
	{
		return(RTEGS_OK);
	}

	_Game.UpCoins(coin);

	_Game.BackMail2PayUser();

	return(RTEGS_Coin);
}


RTEGameStyle_t CGameCoin::UnCoin(CRTEGame & _Game) const
{
	const auto args = GetCurrentArgs();
	const auto coin = args["coin"].GetInt();

	if (0 == coin)
	{
		return(RTEGS_OK);
	}

	_Game.DownCoins(coin);

	_Game.BackMail2PayUser();

	return(RTEGS_Coin);
}


CGameRemove::CGameRemove()
	: CRTEGameFunctor(RTEGS_Remove)
{
}


CGameRemove::~CGameRemove()
{
}


RTEGameStyle_t CGameRemove::DoFunctor(CRTEGame & _Game) const
{
	const auto code = this->Remove(_Game);

	return(code);
}


RTEGameStyle_t CGameRemove::UnDoFunctor(CRTEGame & _Game) const
{
	const auto code = this->UnRemove(_Game);

	return(code);
}


RTEGameStyle_t CGameRemove::Remove(CRTEGame & _Game) const
{
	auto args = GetCurrentArgs();
	const auto Target = args["target"].GetVectorInt();

	if (0 == Target.size())
	{
		return(RTEGS_OK);
	}

	auto& pArea = _Game.m_pArea;
	auto& pAreaBuffer = _Game.m_pAreaBuffer;
	auto& Area = *pArea;
	auto& AreaBuffer = *pAreaBuffer;

	std::vector<int> Cells;
	Cells.reserve(Target.size()*Area.GetWidth());

	for (auto item = Target.begin(); item != Target.end(); ++item)
	{
		const auto x = *item;

		for (int y = 0; y < Area.GetWidth(); ++y)
		{
			Cells.push_back(Area[x][y]);
		}
	}//for

	const auto Prefix = RTNSTool::SignGameLoop();
	const auto strCells = RTNSTool::vector2string(Cells);
	args[Prefix + "cells"] = strCells;

	auto dict = GetCurrentDict();
	dict["args"] = args;
	auto pMail = GetCurrentMail();
	pMail->SetDict(dict);
	RTNSDB::UpdateDBPackage(pMail);

	RTNSTool::RemoveLines(Area, Target, AreaBuffer);

	std::swap(pArea, pAreaBuffer);

	_Game.BackMail2PayUser();

	return(RTEGS_Remove);
}


RTEGameStyle_t CGameRemove::UnRemove(CRTEGame & _Game) const
{
	auto args = GetCurrentArgs();
	const auto Target = args["target"].GetVectorInt();

	if (0 == Target.size())
	{
		return(RTEGS_OK);
	}

	const auto Prefix = RTNSTool::SignGameLoop();
	const auto strCells = args[Prefix + "cells"].GetString();
	const auto Cells = RTNSTool::string2vector(strCells);

	auto& pArea = _Game.m_pArea;
	auto& pAreaBuffer = _Game.m_pAreaBuffer;
	auto& Area = *pArea;
	auto& AreaBuffer = *pAreaBuffer;

	RTNSTool::InsertLines(Area, Target, Cells, AreaBuffer);

	std::swap(pArea, pAreaBuffer);

	_Game.BackMail2PayUser();

	return(RTEGS_Remove);
}


CGameWatch::CGameWatch()
	: CRTEGameFunctor(RTEGS_Watch)
{
}


CGameWatch::~CGameWatch()
{
}


RTEGameStyle_t CGameWatch::DoFunctor(CRTEGame & _Game) const
{
	const auto code = this->Watch(_Game);

	return(code);
}


RTEGameStyle_t CGameWatch::UnDoFunctor(CRTEGame & _Game) const
{
	const auto code = this->UnWatch(_Game);

	return(code);
}


RTEGameStyle_t CGameWatch::Watch(CRTEGame & _Game) const
{
	const auto Dict = RTNSTool::WatchDict(*_Game.m_pArea, *_Game.m_pBlock);
	_Game.BackMail2PayUser(_Game.GetSelfID(), Dict);

	return(RTEGS_Watch);
}


RTEGameStyle_t CGameWatch::UnWatch(CRTEGame & _Game) const
{
	return(this->Watch(_Game));
}


CGameOver::CGameOver()
	: CRTEGameFunctor(RTEGS_Over)
{
}


CGameOver::~CGameOver()
{
}


RTEGameStyle_t CGameOver::DoFunctor(CRTEGame & _Game) const
{
	const auto code = this->Over(_Game);

	return(code);
}


RTEGameStyle_t CGameOver::UnDoFunctor(CRTEGame & _Game) const
{
	const auto code = this->UnOver(_Game);

	return(code);
}


RTEGameStyle_t CGameOver::Over(CRTEGame & _Game) const
{
	const auto args = GetCurrentArgs();
	const auto modeReplay = _Game.GetMask(RTEGS_ReplayMode);

	_Game.SetHealth(RTHS_Death);
	_Game.SetAllMask(RTEGS_DisableAll);

	_Game.BackMail2PayUser("bad", "game over");

	if (false == modeReplay)
	{
		_Game.NextSessionOver();
	}

	return(RTEGS_Over);
}


RTEGameStyle_t CGameOver::UnOver(CRTEGame & _Game) const
{
	const auto args = GetCurrentArgs();

	RTNSTool::RecoverHealthAndMask(&_Game, args);

	//_Game.BackMail2PayUser();

	return(RTEGS_Over);
}


CGameTimer::CGameTimer()
	: CRTEGameFunctor(RTEGS_Timer)
{
}


CGameTimer::~CGameTimer()
{
}


RTEGameStyle_t CGameTimer::DoFunctor(CRTEGame & _Game) const
{
	const auto code = this->Timer(_Game);

	return(code);
}


RTEGameStyle_t CGameTimer::UnDoFunctor(CRTEGame & _Game) const
{
	const auto code = this->UnTimer(_Game);

	return(code);
}


RTEGameStyle_t CGameTimer::Timer(CRTEGame & _Game) const
{
	const auto Args = GetCurrentArgs();
	const auto idGame = _Game.GetSelfID();
	const auto Circle = Args["circle"].GetInt();
	const auto MicroSeconds = Args["microseconds"].GetInt();
	const auto Op = Args["op"].GetString();
	const auto Card = Args["card"].GetString();
	const auto Msg = Args["msg"].GetString();

	const auto timer_mail = RTNSTool::TimerMail("game", _Game.GetRTEStyle(), idGame, Circle, Op, MicroSeconds, Card, Msg);
	const auto back_mail = RTNSTool::BackMailBy(GetCurrentMail());

	const std::vector <std::shared_ptr<CRTMail>> Mails{ timer_mail, back_mail };
	_Game.m_SendBuffer.Writer(Mails);

	return(RTEGS_Timer);
}


RTEGameStyle_t CGameTimer::UnTimer(CRTEGame & _Game) const
{
	return(RTEGS_Unknown);
}


CGameHealth::CGameHealth()
	: CRTEGameFunctor(RTEGS_Health)
{
}


CGameHealth::~CGameHealth()
{
}


RTEGameStyle_t CGameHealth::DoFunctor(CRTEGame & _Game) const
{
	const auto modeReplay = _Game.GetMask(RTEGS_ReplayMode);

	if (false == modeReplay)
	{
		auto Args = GetCurrentArgs();
		const auto Prefix = RTNSTool::SignGameLoop();

		Args[Prefix + "health"] = (unsigned int)_Game.GetHealth();
		Args[Prefix + "allmask"] = _Game.GetAllMask();

		_Game.UpdateCurrentMail4UserCmd(Args);
	}

	const auto code = this->Health(_Game);

	return(code);
}


RTEGameStyle_t CGameHealth::UnDoFunctor(CRTEGame & _Game) const
{
	const auto code = this->UnHealth(_Game);

	return(code);
}


RTEGameStyle_t CGameHealth::Health(CRTEGame & _Game) const
{
	auto Args = GetCurrentArgs();

	RTNSTool::DoHealth(&_Game, Args);

	_Game.BackMail2PayUser();

	return(RTEGS_Health);
}


RTEGameStyle_t CGameHealth::UnHealth(CRTEGame & _Game) const
{
	const auto Args = GetCurrentArgs();
	const auto Prefix = RTNSTool::SignGameLoop();
	const auto HealthStyle = (RTHealthStyle_t)Args[Prefix + "health"].GetUInt();

	_Game.SetHealth(HealthStyle);

	_Game.BackMail2PayUser();

	return(RTEGS_Health);
}


CGameHole::CGameHole()
	: CRTEGameFunctor(RTEGS_Hole)
{
}


CGameHole::~CGameHole()
{
}


RTEGameStyle_t CGameHole::DoFunctor(CRTEGame & _Game) const
{
	const auto code = this->Hole(_Game);

	return(code);
}


RTEGameStyle_t CGameHole::Hole(CRTEGame & _Game) const
{
	_Game.BackMail2PayUser("ok", "hole");

	return(RTEGS_Hole);
}

