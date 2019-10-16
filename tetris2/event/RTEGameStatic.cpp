#include "RTEGameStatic.h"
#include "../RTManager.h"


CGameNew& GetGameNew(void)
{
	static CGameNew _GameNew;

	return(_GameNew);
}


CGameDelete& GetGameDelete(void)
{
	static CGameDelete _GameDelete;

	return(_GameDelete);
}


CGameDoctor& GetGameDoctor(void)
{
	static CGameDoctor _GameDoctor;

	return(_GameDoctor);
}


CGameMove& GetGameMove(void)
{
	static CGameMove _GameMove;

	return(_GameMove);
}


CGameTransfer& GetGameTransfer(void)
{
	static CGameTransfer _GameTransfer;

	return(_GameTransfer);
}


CGameHit& GetGameHit(void)
{
	static CGameHit _GameHit;

	return(_GameHit);
}


CGameFreeze& GetGameFreeze(void)
{
	static CGameFreeze _GameFreeze;

	return(_GameFreeze);
}


CGameTarget& GetGameTarget(void)
{
	static CGameTarget _GameTarget;

	return(_GameTarget);
}


CGameCoin& GetGameCoin(void)
{
	static CGameCoin _GameCoin;

	return(_GameCoin);
}


CGameRemove& GetGameRemove(void)
{
	static CGameRemove _GameRemove;

	return(_GameRemove);
}


CGameWatch& GetGameWatch(void)
{
	static CGameWatch _GameWatch;

	return(_GameWatch);
}


CGameOver& GetGameOver(void)
{
	static CGameOver _GameOver;

	return(_GameOver);
}


CGameTimer& GetGameTimer(void)
{
	static CGameTimer _GameTimer;

	return(_GameTimer);
}


CGameHealth& GetGameHealth(void)
{
	static CGameHealth _GameHealth;

	return(_GameHealth);
}


CGameHole& GetGameHole(void)
{
	static CGameHole _GameHole;

	return(_GameHole);
}


CRTEGameFunctor* GetRTEGameFunctor(const std::string _Name)
{
	static CRTManager<std::string, CRTEGameFunctor*> _RTEGameManager{
		{ "new",                   &GetGameNew()                      },
		{ "delete",                &GetGameDelete()                   },
		{ "doctor",                &GetGameDoctor()                   },
		{ "move",                  &GetGameMove()                     },
		{ "transfer",              &GetGameTransfer()                 },
		{ "hit",                   &GetGameHit()                      },
		{ "freeze",                &GetGameFreeze()                   },
		{ "target",                &GetGameTarget()                   },
		{ "coin",                  &GetGameCoin()                     },
		{ "remove",                &GetGameRemove()                   },
		{ "watch",                 &GetGameWatch()                    },
		{ "over",                  &GetGameOver()                     },
		{ "timer",                 &GetGameTimer()                    },
		{ "health",                &GetGameHealth()                   },
		{ "hole",                  &GetGameHole()                     },
	};

	return(_RTEGameManager[_Name]);
}

