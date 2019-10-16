#ifndef __RTEPAYBASE_H__
#define __RTEPAYBASE_H__


#include "RTEBase.h"
#include "../RTDict.h"
#include "../RTMail.h"
#include "../RTManager.h"


class CRTEPayBase : public CRTEBase
{
public:
	CRTEPayBase(const RTEStyle_t _RTEStyle);
	CRTEPayBase(const CRTEPayBase &_other);
	~CRTEPayBase();

public:
	CRTManager<int, std::shared_ptr<CRTMail>> m_PayManager;

public:
	std::shared_ptr<CRTMail> GetHostPay(void) const;

public:
	void BackMail2PayUser(const CRTDict& _Dict);
	void BackMail2PayUser(const std::string _Code = "ok", const std::string _Msg = "luck");
	void BackMail2PayUser(const int _idGame, const CRTDict& _Dict);
};


#endif//__RTEPAYBASE_H__

