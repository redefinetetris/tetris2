#ifndef __RTFUNCTOR_H__
#define __RTFUNCTOR_H__


#include <memory>


class CRTMail;
class CRTEBase;


class CRTFunctor
{
public:
	CRTFunctor(const int _FunctorStyle);
	CRTFunctor(const CRTFunctor &_other);
	~CRTFunctor();

private:
	const int m_FunctorStyle;

public:
	int GetFunctorStyle(void) const;

	int ReplayCmd2DB(CRTEBase* _pMaster, std::shared_ptr<CRTMail> _pMail) const;
};


#endif//__RTFUNCTOR_H__

