#ifndef __RTEGAMESTATIC_H__
#define __RTEGAMESTATIC_H__


#include "RTEGameFunctor.h"
#include <string>


CGameNew& GetGameNew(void);
CGameDelete& GetGameDelete(void);
CGameDoctor& GetGameDoctor(void);
CGameMove& GetGameMove(void);
CGameTransfer& GetGameTransfer(void);
CGameHit& GetGameHit(void);
CGameFreeze& GetGameFreeze(void);
CGameTarget& GetGameTarget(void);
CGameCoin& GetGameCoin(void);
CGameRemove& GetGameRemove(void);
CGameWatch& GetGameWatch(void);
CGameOver& GetGameOver(void);
CGameTimer& GetGameTimer(void);
CGameHealth& GetGameHealth(void);
CGameHole& GetGameHole(void);


CRTEGameFunctor* GetRTEGameFunctor(const std::string _Name);


#endif//__RTEGAMESTATIC_H__

