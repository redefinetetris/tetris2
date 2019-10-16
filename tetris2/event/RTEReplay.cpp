#include "RTEReplay.h"
#include "RTEReplayStyle.h"
#include "RTEReplayFunctor.h"
#include "RTEReplayStatic.h"
#include "../RTNSDB.h"
#include "../RTNSLog.h"
#include "../RTNSTool.h"
#include "../RTDataType.h"
#include "../RTNSStatic.h"


CRTEReplay::CRTEReplay()
	: CRTEBase(RTES_Replay)
{
}


CRTEReplay::CRTEReplay(const CRTEReplay &_other)
	: CRTEBase(_other)
{
}


CRTEReplay::~CRTEReplay()
{
}


int CRTEReplay::Power(void)
{
	CMMaster Master(this);

	return(this->RunLocker());
}


int CRTEReplay::DoMail(void)
{
	const auto ops = GetCurrentOps();
	const auto& op = RTNSTool::GetStrOps(ops);

	auto pReplayFunctor = GetRTEReplayFunctor(op);
	if (nullptr == pReplayFunctor)
	{
		return(1);
	}

	pReplayFunctor->operator ()(*this);

	//RTNSStatic::WakeHubThreader();

	return(1);
}

