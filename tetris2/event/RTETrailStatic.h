#ifndef __RTETRAILSTATIC_H__
#define __RTETRAILSTATIC_H__


#include "RTETrailFunctor.h"
#include <string>


CTrailNewRoot& GetTrailNewRoot(void);
CTrailDeleteRoot& GetTrailDeleteRoot(void);
CTrailQuery& GetTrailQuery(void);


CRTETrailFunctor* GetRTETrailFunctor(const std::string _Name);


#endif//__RTETRAILSTATIC_H__

