#ifndef __RTEEVENT_H__
#define __RTEEVENT_H__


#include "RTEBase.h"


class CRTEEvent : public CRTEBase
{
public:
	CRTEEvent();
	CRTEEvent(const CRTEEvent &_other);
	~CRTEEvent();

public:
	int operator () ();
};


#endif//__RTEEVENT_H__

