#include "RTEHub.h"
#include "../RTNSDB.h"
#include "../RTNSLog.h"
#include "../RTNSTool.h"
#include "../RTServer.h"
#include "../RTDataType.h"
#include "../RTNSStatic.h"
#include "RTEStatic.h"



CRTEHub::CRTEHub()
	: CRTEBase(RTES_Hub)
{
}


CRTEHub::CRTEHub(const CRTEHub &_other)
	: CRTEBase(_other)
{
}


CRTEHub::~CRTEHub()
{
}


int CRTEHub::operator () ()
{
	auto work = this->Mailer();
	work += this->MailsRun();

	if (!work)
	{
		work += this->FlushWriter();
	}

	return(work);
}


int CRTEHub::Power(void)
{
	CMMaster Master(this);

	return(this->RunSelfLocker());
}


int CRTEHub::SelfRun(void)
{
	int work = 0;

	work += this->Sender();

	return(work);
}


int CRTEHub::DoMail(void)
{
	const auto Ops = GetCurrentOps();
	const auto& op = Ops[0];
	int oks = 0;

	if ("session" == op || "game" == op)
	{
		oks += this->GameR();
	}
	else
	{
		oks += this->NoGameR();
	}

	if (oks)
	{
		LogInfo("wake one thread in Recver");
		RTNSStatic::WakeWorkThreader();
	}

	return(oks);
}


int CRTEHub::Sender(void)
{
	int work = 0;

	auto pServer = RTNSStatic::GetServer();
	//if (pServer)
	{
		work += pServer->Send();
	}

	return(work);
}


int CRTEHub::Mailer(void)
{
	int work = 0;

	//集中邮件
	auto Mails = this->NoGameM();
	auto MailsGame = this->GameM();

	Mails.insert(Mails.end(), MailsGame.begin(), MailsGame.end());

	//邮件甄别
	work += this->GuardM(Mails);

	return(work);
}


int CRTEHub::NoGameR(void)
{
	const auto ops = GetCurrentOps();
	const auto& op0 = ops[0];

	if ("root" == op0)
	{
		const auto Args = GetCurrentArgs();
		auto idRoot = RTNSTool::GetIntValue4Dict(Args, "rootid", RTNSDB::DefaultDBRootID());
		auto pRoot = GetRTETrail().m_RootManager[idRoot];

		if (nullptr == pRoot)
		{
			LogError("find root " + RTNSTool::int2string(idRoot) + " fail in NoGameR");
			return(1);
		}

		pRoot->m_RecvBuffer.Writer(GetCurrentMail());
	}
	else
	{
		auto pRTEObj = GetRTE4Recv(op0);
		if (nullptr == pRTEObj)
		{
			LogError("find rte " + op0 + " fail in NoGameR");
			return(1);
		}

		pRTEObj->m_RecvBuffer.Writer(GetCurrentMail());
	}

	return(1);
}


int CRTEHub::GameR(void)
{
	const auto args = GetCurrentArgs();
	const auto idRoot = RTNSTool::GetIntValue4Dict(args, "rootid", RTNSDB::DefaultDBRootID());
	auto pRoot = GetRTETrail().m_RootManager[idRoot];
	if (nullptr == pRoot)
	{
		return(1);
	}

	if (false == pRoot->GetHealth(RTHS_DoMail))
	{
		return(-1);
	}

	const auto idSession = RTNSTool::GetIntValue4Dict(args, "sessionid", 0);
	auto pSession = pRoot->m_SessionManager[idSession];
	if (nullptr == pSession)
	{
		LogWarning("find session " + RTNSTool::int2string(idSession) + " fail in GameR");
		return(1);
	}

	pSession->m_RecvBuffer.Writer(GetCurrentMail());

	return(1);
}


std::vector<std::shared_ptr<CRTMail>> CRTEHub::NoGameM(void)
{
	std::vector<std::shared_ptr<CRTMail>> Mails;
	Mails.reserve(VECTOR_RESERVE_SIZE);
	const static auto _HubValues = GetRTE4SendValues();

	for (auto item = _HubValues.begin(); item != _HubValues.end(); ++item)
	{
		auto pRTEObj = *item;
		if (nullptr == pRTEObj)
		{
			continue;
		}

		const auto ok = pRTEObj->m_SendBuffer.Reader(Mails);
	}//for

	return(Mails);
}


std::vector<std::shared_ptr<CRTMail>> CRTEHub::GameM(void)
{
	std::vector<std::shared_ptr<CRTMail>> Mails;
	Mails.reserve(VECTOR_RESERVE_SIZE);

	auto RTETrail = GetRTETrail();
	const auto okTrail = RTETrail.m_SendBuffer.Reader(Mails);

	const auto Roots = RTETrail.m_RootManager.Values();

	for (auto item = Roots.begin(); item != Roots.end(); ++item)
	{
		auto pRTERoot = *item;
		if (nullptr == pRTERoot)
		{
			continue;
		}

		auto& RTERoot = *pRTERoot;
		const auto okRoot = RTERoot.m_SendBuffer.Reader(Mails);

		const auto Values = RTERoot.m_SessionManager.Values();

		for (auto item = Values.begin(); item != Values.end(); ++item)
		{
			auto pSession = *item;
			if (nullptr == pSession)
			{
				continue;
			}

			const auto okSession = pSession->m_SendBuffer.Reader(Mails);
		}//for
	}

	return(Mails);
}


int CRTEHub::GuardM(const std::vector<std::shared_ptr<CRTMail>>& _Mails)
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

		if (dict.HasKey(RTNSTool::SignHubLoop()))
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

	if (Sends.size())
	{
		LogInfo("wake one thread in GuardM");
		RTNSStatic::WakeWorkThreader();
	}

	return(work);
}


int CRTEHub::FlushWriter(void)
{
	int work = 0;
	const static auto _HubValues = GetRTE4SendValues();

	for (auto item = _HubValues.begin(); item != _HubValues.end(); ++item)
	{
		auto pSMRTEObj = *item;
		if (nullptr == pSMRTEObj)
		{
			continue;
		}

		work += pSMRTEObj->m_RecvBuffer.FlushWriter();
	}//for

	auto RTETrail = GetRTETrail();
	work += RTETrail.FlushWriter();

	work += this->m_SendBuffer.FlushWriter();

	return(work);
}


