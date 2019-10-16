#include "RTCurrent.h"
#include "RTDict.h"
#include "RTMail.h"
#include "RTNSDB.h"
#include "RTNSTool.h"
#include "event/RTEStatic.h"


thread_local CRTBase* __pMaster = nullptr;
thread_local int __CurrentHistory = 0;
thread_local std::shared_ptr<CRTMail> __pCurrentMail = nullptr;
thread_local CRTDict __CurrentDict;
thread_local CRTDict __CurrentArgs;
thread_local std::vector<std::string> __CurrentOps;
thread_local int __CurrentUserID = 0;
thread_local std::shared_ptr<CRTMail> __CurrentPayMail = nullptr;


CRTBase* GetCurrentMaster(void)
{
	return(__pMaster);
}


void SetCurrentMaster(CRTBase* _pMaster)
{
	__pMaster = _pMaster;
}


const int CurrentHistory(void)
{
	return(__CurrentHistory);
}


void SetCurrentHistory(const int _CurrentHistory)
{
	__CurrentHistory = _CurrentHistory;
}


const std::shared_ptr<CRTMail> GetCurrentMail(void)
{
	return(__pCurrentMail);
}


const std::shared_ptr<CRTMail> GetCurrentBadMail(void)
{
	static std::shared_ptr<CRTMail> _pCurrentBadMail = nullptr;

	if (nullptr != _pCurrentBadMail)
	{
		return(_pCurrentBadMail);
	}

	_pCurrentBadMail = RTNSTool::NewMail();
	_pCurrentBadMail->SetSelfID(-1);

	return(_pCurrentBadMail);
}


void SetCurrentMail(const std::shared_ptr<CRTMail>& _pMail)
{
	__pCurrentMail = _pMail;
}


const CRTDict& GetCurrentDict(void)
{
	return(__CurrentDict);
}


void SetCurrentDict(const CRTDict& _Dict)
{
	__CurrentDict = _Dict;
}


const CRTDict& GetCurrentArgs(void)
{
	return(__CurrentArgs);
}


void SetCurrentArgs(const CRTDict& _Args)
{
	__CurrentArgs = _Args;
}


const std::vector<std::string>& GetCurrentOps(void)
{
	return(__CurrentOps);
}


int GetCurrentUserID(void)
{
	return(__CurrentUserID);
}


void SetCurrentUserID(const int _idUser)
{
	__CurrentUserID = _idUser;
}


void SetCurrentOps(const std::vector<std::string>& _Ops)
{
	__CurrentOps = _Ops;
}


std::shared_ptr<CRTMail>& GetCurrentPayMail(void)
{
	return(__CurrentPayMail);
}


void SetCurrentPayMail(const std::shared_ptr<CRTMail> _pPayMail)
{
	__CurrentPayMail = _pPayMail;
}


thread_local std::vector<CRTBase*> __StackMaster;
thread_local std::vector<std::shared_ptr<CRTMail>> __StackMail;


CMMaster::CMMaster(CRTBase* _pMaster)
{
	__StackMaster.push_back(_pMaster);

	this->InitTopElement();
}


CMMaster::~CMMaster()
{
	__StackMaster.pop_back();

	this->InitTopElement();
}


void CMMaster::InitTopElement(void)
{
	if (false == __StackMaster.empty())
	{
		SetCurrentMaster(__StackMaster.back());
	}
	else
	{
		SetCurrentMaster(nullptr);
	}
}


CMStacker::CMStacker(CRTEBase* _pMaster, std::shared_ptr<CRTMail> _pMail)
	: m_pMaster(_pMaster)
{
	__StackMail.push_back(_pMail);

	this->InitTopElement();
	this->Mail2DB();
}


CMStacker::~CMStacker()
{
	__StackMail.pop_back();

	this->InitTopElement();
}


void CMStacker::InitTopElement(void)
{
	if (false == __StackMail.empty())
	{
		this->InitElementBy(__StackMail.back());
	}
	else
	{
		this->InitElementBy(GetCurrentBadMail());
	}
}


void CMStacker::InitElementBy(std::shared_ptr<CRTMail> _pMail)
{
	SetCurrentMail(_pMail);

	const auto Dict(_pMail->GetDict());
	SetCurrentDict(Dict);

	SetCurrentHistory(RTNSTool::NormalValue());

	if ((true == m_pMaster->GetMask(0X80000000) || 0X0 == m_pMaster->GetAllMask())
		&& true == Dict.HasKey(RTNSTool::SignHistory())
		)
	{
		const auto ModeHistory = Dict[RTNSTool::SignHistory()].GetInt();

		SetCurrentHistory(ModeHistory);
	}

	SetCurrentUserID(0);
	SetCurrentPayMail(nullptr);

	if (true == Dict.HasKey("args"))
	{
		const auto args(Dict["args"].GetDict());
		SetCurrentArgs(args);

		if (true == args.HasKey("token"))
		{
			const auto token(args["token"].GetString());
			const auto idUser = RTNSDB::GetUserIDByToken(token, false);

			SetCurrentUserID(idUser);

			auto RTEUser = GetRTEUser();
			auto pPayMail = RTEUser.m_PayManager[idUser];

			SetCurrentPayMail(pPayMail);
		}
	}//if
	else
	{
		SetCurrentArgs(CRTDict());
	}

	if (true == Dict.HasKey("ops"))
	{
		SetCurrentOps(Dict["ops"].GetVectorString());
	}
	else
	{
		SetCurrentOps(std::vector<std::string>());
	}
}


int CMStacker::Mail2DB(void)
{
	const auto pMail = GetCurrentMail();

	if (0 == pMail->GetSelfID())
	{
		RTNSDB::NewDBPackage(pMail);
	}

	return(pMail->GetSelfID());
}

