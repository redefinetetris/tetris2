#include "RTERoot.h"
#include "RTERootStyle.h"
#include "RTERootFunctor.h"
#include "RTERootStatic.h"
#include "../RTNSDB.h"
#include "../RTNSLog.h"
#include "../RTNSTool.h"
#include "../RTDataType.h"
#include "../RTNSStatic.h"


CRTERoot::CRTERoot()
	: CRTEPayBase(RTES_Root)
	, m_SessionManager()
{
}


CRTERoot::~CRTERoot()
{
}


int CRTERoot::Power(void)
{
	CMMaster Master(this);

	int work = 0;

	work += this->RunLocker(true);

	const auto Values = m_SessionManager.Values();

	for (auto item = Values.begin(); item != Values.end(); ++item)
	{
		auto pSession = *item;
		if (nullptr == pSession)
		{
			continue;
		}

		work += pSession->Power();
	}

	return(work);
}


int CRTERoot::DoMail(void)
{
	const auto ops = GetCurrentOps();
	const auto& op1 = ops[1];

	auto pRootFunctor = GetRTERootFunctor(op1);
	if (nullptr == pRootFunctor)
	{
		return(0);
	}

	if (RTERS_Health == pRootFunctor->GetFunctorStyle())
	{
		const auto codeRun = pRootFunctor->operator ()(*this);

		return(2);
	}

	if (false == this->GetHealth(RTHS_DoMail))
	{
		return(-1);
	}

	pRootFunctor->operator ()(*this);

	return(1);
}


int CRTERoot::FlushWriter(void)
{
	int work = 0;
	const auto Sessions = m_SessionManager.Values();

	for (auto item = Sessions.begin(); item != Sessions.end(); ++item)
	{
		auto pSession = *item;
		if (nullptr == pSession)
		{
			continue;
		}

		work += pSession->m_RecvBuffer.FlushWriter();
	}

	work += m_RecvBuffer.FlushWriter();

	return(work);
}

