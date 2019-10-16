#ifndef __RTEUSER_H__
#define __RTEUSER_H__


#include "RTEBase.h"


class CRTEUser : public CRTEBase
{
public:
	CRTEUser();
	CRTEUser(const CRTEUser &_other);
	~CRTEUser();

public:
	CRTManager<int, std::shared_ptr<CRTMail>> m_PayManager;

private:
	friend class CUserLogin;
	friend class CUserLogout;
	friend class CUserRegin;
	friend class CUserRegout;

public:
	virtual int Power(void);

private:
	virtual int DoMail(void);
};


#endif//__RTEUSER_H__

