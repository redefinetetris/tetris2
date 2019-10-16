#include "RTETrail.h"
#include "RTETrailStyle.h"
#include "RTETrailFunctor.h"
#include "RTETrailStatic.h"
#include "../RTNSDB.h"
#include "../RTNSLog.h"
#include "../RTNSTool.h"
#include "../RTDataType.h"
#include "../RTNSStatic.h"


CRTETrail::CRTETrail()
	: CRTEBase(RTES_Trail)
	, m_RootManager()
{
}


CRTETrail::~CRTETrail()
{
}


int CRTETrail::Power(void)
{
	CMMaster Master(this);

	int work = 0;

	work += this->RunLocker(true);

	const auto Values = m_RootManager.Values();

	for (auto item = Values.begin(); item != Values.end(); ++item)
	{
		auto pRoot = *item;
		if (nullptr == pRoot)
		{
			continue;
		}

		work += pRoot->Power();
	}

	return(work);
}


int CRTETrail::DoMail(void)
{
	const auto ops = GetCurrentOps();
	const auto& op1 = ops[1];

	auto pTrailFunctor = GetRTETrailFunctor(op1);
	if (nullptr == pTrailFunctor)
	{
		return(0);
	}

	pTrailFunctor->operator ()(*this);

	return(1);
}


int CRTETrail::FlushWriter(void)
{
	int work = 0;
	const auto Roots = m_RootManager.Values();

	for (auto item = Roots.begin(); item != Roots.end(); ++item)
	{
		auto pRoot = *item;
		if (nullptr == pRoot)
		{
			continue;
		}

		work += pRoot->FlushWriter();
	}

	work += m_RecvBuffer.FlushWriter();

	return(work);
}

