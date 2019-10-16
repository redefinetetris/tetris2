#ifndef __RTEDBSTATIC_H__
#define __RTEDBSTATIC_H__


#include "RTEDBFunctor.h"
#include <string>


CDBTimer& GetDBTimer(void);
CDBFire& GetDBFire(void);
CDBFlush& GetDBFlush(void);
CDBDownTTL& GetDBDownTTL(void);
CDBWashTTL& GetDBWashTTL(void);


CRTEDBFunctor* GetRTEDBFunctor(const std::string _Name);


#endif//__RTEDBSTATIC_H__

