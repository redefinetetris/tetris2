#ifndef __RTESESSIONSTATIC_H__
#define __RTESESSIONSTATIC_H__


#include "RTESessionFunctor.h"
#include <string>


CSessionNewGame& GetSessionNewGame(void);
CSessionDeleteGame& GetSessionDeleteGame(void);
CSessionTimer& GetSessionTimer(void);
CSessionJump& GetSessionJump(void);
CSessionMove& GetSessionMove(void);
CSessionRace& GetSessionRace(void);
CSessionFire& GetSessionFire(void);
CSessionWin& GetSessionWin(void);
CSessionOver& GetSessionOver(void);
CSessionHealth& GetSessionHealth(void);
CSessionToll& GetSessionToll(void);


CRTESessionFunctor* GetRTESessionFunctor(const std::string _Name);


#endif//__RTESESSIONSTATIC_H__

