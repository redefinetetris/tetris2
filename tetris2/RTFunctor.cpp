#include "RTFunctor.h"
#include "RTMail.h"
#include "RTNSDB.h"
#include "RTFunctor.h"


CRTFunctor::CRTFunctor(const int _FunctorStyle)
	: m_FunctorStyle(_FunctorStyle)
{
}


CRTFunctor::CRTFunctor(const CRTFunctor &_other)
	: m_FunctorStyle(_other.m_FunctorStyle)
{
}


CRTFunctor::~CRTFunctor()
{
}


int CRTFunctor::GetFunctorStyle(void) const
{
	return(m_FunctorStyle);
}


int CRTFunctor::ReplayCmd2DB(CRTEBase* _pMaster, std::shared_ptr<CRTMail> _pMail) const
{
	RTNSDB::NewDBReplay(_pMaster, _pMail, m_FunctorStyle);

	return(0);
}

