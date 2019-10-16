#include "RTETrailFunctor.h"
#include "../RTDict.h"
#include "../RTMail.h"
#include "../RTNSDB.h"
#include "../RTNSLog.h"
#include "../RTNSTool.h"
#include "../RTDataType.h"
#include "RTETrail.h"
#include "RTERootStyle.h"


CRTETrailFunctor::CRTETrailFunctor(const int _FunctorStyle)
	: CRTFunctor(_FunctorStyle)
{
}


CRTETrailFunctor::~CRTETrailFunctor()
{
}


RTETrailStyle_t CRTETrailFunctor::operator () (CRTETrail & _Trail) const
{
	const auto codeBase = this->ReplayCmd2DB(&_Trail, GetCurrentMail());

	const auto codePreDoFunctor = this->PreDoFunctor(_Trail);
	const auto codeDoFunctor = this->DoFunctor(_Trail);
	const auto codePostDoFunctor = this->PostDoFunctor(_Trail);

	return(codeDoFunctor);
}


RTETrailStyle_t CRTETrailFunctor::DoFunctor(CRTETrail & _Trail) const
{
	const auto code = this->Functor(_Trail);

	return(code);
}


RTETrailStyle_t CRTETrailFunctor::Functor(CRTETrail & _Trail) const
{
	return(RTETS_Unknown);
}


RTETrailStyle_t CRTETrailFunctor::PreDoFunctor(CRTETrail & _Trail) const
{
	return(RTETS_Unknown);
}


RTETrailStyle_t CRTETrailFunctor::PostDoFunctor(CRTETrail & _Trail) const
{
	return(RTETS_Unknown);
}


CTrailNewRoot::CTrailNewRoot()
	: CRTETrailFunctor(RTETS_NewRoot)
{
}


CTrailNewRoot::~CTrailNewRoot()
{
}


RTETrailStyle_t CTrailNewRoot::DoFunctor(CRTETrail & _Trail) const
{
	const auto code = this->NewRoot(_Trail);

	return(code);
}


RTETrailStyle_t CTrailNewRoot::NewRoot(CRTETrail & _Trail) const
{
	const auto args = GetCurrentArgs();
	const auto idRoot(args["rootid"].GetInt());
	const auto ReplayMode = RTNSTool::GetIntValue4Dict(args, "replaymode", 0);
	auto code(RTETS_NewRoot);
	std::string strCode("ok");
	std::string strMsg("luck");
	CRTDict back_args;

	std::shared_ptr<CRTERoot> pRoot(new (std::nothrow) CRTERoot());

	if (nullptr == pRoot)
	{
		code = RTETS_OutMemory;
		strCode = "bad";
		strMsg = "out memory";
	}
	else
	{
		if (ReplayMode)
		{
			pRoot->SetMask(RTERS_ReplayMode);
		}

		pRoot->SetSelfID(idRoot);
		pRoot->SetParent(&_Trail);
		_Trail.m_RootManager[idRoot] = pRoot;

		pRoot->m_PayManager[GetCurrentUserID()] = GetCurrentPayMail();

		back_args["rootid"] = idRoot;
	}

	return(code);
}


CTrailDeleteRoot::CTrailDeleteRoot()
	: CRTETrailFunctor(RTETS_DeleteRoot)
{
}


CTrailDeleteRoot::~CTrailDeleteRoot()
{
}


RTETrailStyle_t CTrailDeleteRoot::DoFunctor(CRTETrail & _Trail) const
{
	const auto code = this->DeleteRoot(_Trail);

	return(code);
}


RTETrailStyle_t CTrailDeleteRoot::DeleteRoot(CRTETrail & _Trail) const
{
	return(RTETS_Unknown);
}


CTrailQuery::CTrailQuery()
	: CRTETrailFunctor(RTETS_Query)
{
}


CTrailQuery::~CTrailQuery()
{
}


RTETrailStyle_t CTrailQuery::DoFunctor(CRTETrail & _Trail) const
{
	const auto code = this->Query(_Trail);

	return(code);
}


RTETrailStyle_t CTrailQuery::Query(CRTETrail & _Trail) const
{
	return(RTETS_Unknown);
}

