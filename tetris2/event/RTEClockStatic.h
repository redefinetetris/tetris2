#ifndef __RTECLOCKSTATIC_H__
#define __RTECLOCKSTATIC_H__


#include "RTEClockFunctor.h"
#include <string>


CClockUpdate& GetClockUpdate(void);
CClockNew& GetClockNew(void);
CClockDelete& GetClockDelete(void);
CClockQuery& GetClockQuery(void);
CClockHealth& GetClockHealth(void);


CRTEClockFunctor* GetRTEClockFunctor(const std::string _Name);


#endif//__RTECLOCKSTATIC_H__

