#include "RTEUser.h"
#include "RTEUserStyle.h"
#include "RTEUserFunctor.h"
#include "RTEUserStatic.h"
#include "../RTNSDB.h"
#include "../RTNSLog.h"
#include "../RTNSTool.h"
#include "../RTDataType.h"
#include "../RTNSStatic.h"


CRTEUser::CRTEUser()
	: CRTEBase(RTES_User)
	, m_PayManager()
{
}


CRTEUser::CRTEUser(const CRTEUser &_other)
	: CRTEBase(_other)
	, m_PayManager(_other.m_PayManager)
{
}


CRTEUser::~CRTEUser()
{
}


int CRTEUser::Power(void)
{
	CMMaster Master(this);

	return(this->RunLocker());
}


int CRTEUser::DoMail(void)
{
	const auto ops = GetCurrentOps();
	const auto& op = RTNSTool::GetStrOps(ops);

	auto pUserFunctor = GetRTEUserFunctor(op);
	if (nullptr == pUserFunctor)
	{
		return(1);
	}

	pUserFunctor->operator ()(*this);

	return(1);
}

