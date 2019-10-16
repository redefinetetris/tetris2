#ifndef __RTEROOTSTATIC_H__
#define __RTEROOTSTATIC_H__


#include "RTERootFunctor.h"
#include <string>


CRootNewSession& GetRootNewSession(void);
CRootDeleteSession& GetRootDeleteSession(void);
CRootQuery& GetRootQuery(void);
CRootHealth& GetRootHealth(void);


CRTERootFunctor* GetRTERootFunctor(const std::string _Name);


#endif//__RTEROOTSTATIC_H__

