#include "RTEDB.h"
#include "RTEDBStyle.h"
#include "RTEDBFunctor.h"
#include "RTEDBStatic.h"
#include "../RTNSDB.h"
#include "../RTNSLog.h"
#include "../RTNSTool.h"
#include "../RTDataType.h"
#include "../RTNSStatic.h"


CRTEDB::CRTEDB()
	: CRTEBase(RTES_DB)
{
}


CRTEDB::CRTEDB(const CRTEDB &_other)
	: CRTEBase(RTES_DB)
{
}


CRTEDB::~CRTEDB()
{
}


int CRTEDB::Power(void)
{
	CMMaster Master(this);

	int work = 0;

	work += this->RunLocker();

	return(work);
}


int CRTEDB::DoMail(void)
{
	const auto Ops = GetCurrentOps();
	const auto op = RTNSTool::GetStrOps(Ops);
	auto pDBFunctor = GetRTEDBFunctor(op);
	if (nullptr == pDBFunctor)
	{
		return(0);
	}

	pDBFunctor->operator ()(*this);

	return(1);
}

