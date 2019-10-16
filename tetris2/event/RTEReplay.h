#ifndef __RTEREPLAY_H__
#define __RTEREPLAY_H__


#include "RTEBase.h"


class CRTEReplay : public CRTEBase
{
public:
	CRTEReplay();
	CRTEReplay(const CRTEReplay &_other);
	~CRTEReplay();

private:
	friend class CReplayInit;
	friend class CReplayQuery;
	friend class CReplayBackward;
	friend class CReplayForward;

public:
	virtual int Power(void);

private:
	virtual int DoMail(void);
};


#endif//__RTEREPLAY_H__

