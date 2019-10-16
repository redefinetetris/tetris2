#ifndef __RTEREPLAYSTATIC_H__
#define __RTEREPLAYSTATIC_H__


#include "RTEReplayFunctor.h"
#include <string>


CReplayInit& GetReplayInit(void);
CReplayQuery& GetReplayQuery(void);
CReplayBackward& GetReplayBackward(void);
CReplayForward& GetReplayForward(void);


CRTEReplayFunctor* GetRTEReplayFunctor(const std::string _Name);


#endif//__RTEREPLAYSTATIC_H__

