#ifndef __RTEUSERSTATIC_H__
#define __RTEUSERSTATIC_H__


#include "RTEUserFunctor.h"
#include <string>


CUserLogin& GetUserLogin(void);
CUserLogout& GetUserLogout(void);
CUserRegin& GetUserRegin(void);
CUserRegout& GetUserRegout(void);


CRTEUserFunctor* GetRTEUserFunctor(const std::string _Name);


#endif//__RTEUSERSTATIC_H__

