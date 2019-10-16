#ifndef __RTETRAIL_H__
#define __RTETRAIL_H__


#include "RTEBase.h"
#include "RTERoot.h"
#include "../RTManagerLocker.h"


class CRTETrail : public CRTEBase
{
public:
	CRTETrail();
	~CRTETrail();

public:
	CRTManagerLocker<int, std::shared_ptr<CRTERoot>> m_RootManager;

private:
	friend class CTrailNewRoot;
	friend class CTrailDeleteRoot;
	friend class CTrailQueryRoot;

public:
	virtual int Power(void);

private:
	virtual int DoMail(void);

public:
	int FlushWriter(void);
};


#endif//__RTETRAIL_H__

