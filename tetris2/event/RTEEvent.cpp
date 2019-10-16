#include "RTEEvent.h"
#include "RTEStatic.h"


CRTEEvent::CRTEEvent()
	: CRTEBase(RTES_Event)
{
}


CRTEEvent::CRTEEvent(const CRTEEvent &_other)
	: CRTEBase(RTES_Event)
{
}


CRTEEvent::~CRTEEvent()
{
}


int CRTEEvent::operator () ()
{
	int work = 0;
	const auto Values = GetRTE4EventValues();

	for (auto item = Values.begin(); item != Values.end(); ++item)
	{
		auto pRTEObj = *item;
		if (nullptr == pRTEObj)
		{
			continue;
		}

		work += pRTEObj->Power();
	}

	return(work);
}

