#ifndef __RTEROOT_H__
#define __RTEROOT_H__


#include "RTESession.h"
#include "RTEPayBase.h"
#include "../RTManagerLocker.h"


class CRTERoot : public CRTEPayBase
{
public:
	CRTERoot();
	~CRTERoot();

public:
	CRTManagerLocker<int, std::shared_ptr<CRTESession>> m_SessionManager;

private:
	friend class CRootNewSession;
	friend class CRootDeleteSession;
	friend class CRootQuery;
	friend class CRootHealth;

public:
	virtual int Power(void);

private:
	virtual int DoMail(void);

public:
	int FlushWriter(void);
};


#endif//__RTEROOT_H__

