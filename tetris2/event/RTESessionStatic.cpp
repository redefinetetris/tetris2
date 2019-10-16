#include "RTESessionStatic.h"
#include "../RTManager.h"


CSessionNewGame& GetSessionNewGame(void)
{
	static CSessionNewGame _SessionNewGame;

	return(_SessionNewGame);
}


CSessionDeleteGame& GetSessionDeleteGame(void)
{
	static CSessionDeleteGame _SessionDeleteGame;

	return(_SessionDeleteGame);
}


CSessionTimer& GetSessionTimer(void)
{
	static CSessionTimer _SessionTimer;

	return(_SessionTimer);
}


CSessionJump& GetSessionJump(void)
{
	static CSessionJump _SessionJump;

	return(_SessionJump);
}


CSessionMove& GetSessionMove(void)
{
	static CSessionMove _SessionMove;

	return(_SessionMove);
}


CSessionRace& GetSessionRace(void)
{
	static CSessionRace _SessionRace;

	return(_SessionRace);
}


CSessionFire& GetSessionFire(void)
{
	static CSessionFire _SessionFire;

	return(_SessionFire);
}


CSessionWin& GetSessionWin(void)
{
	static CSessionWin _SessionWin;

	return(_SessionWin);
}


CSessionOver& GetSessionOver(void)
{
	static CSessionOver _SessionOver;

	return(_SessionOver);
}


CSessionHealth& GetSessionHealth(void)
{
	static CSessionHealth _SessionHealth;

	return(_SessionHealth);
}


CSessionToll& GetSessionToll(void)
{
	static CSessionToll _SessionToll;

	return(_SessionToll);
}


CRTESessionFunctor* GetRTESessionFunctor(const std::string _Name)
{
	static CRTManager<std::string, CRTESessionFunctor*> _RTESessionManager{
		{ "newgame",               &GetSessionNewGame()               },
		{ "deletegame",            &GetSessionDeleteGame()            },
		{ "timer",                 &GetSessionTimer()                 },
		{ "jump",                  &GetSessionJump()                  },
		{ "move",                  &GetSessionMove()                  },
		{ "race",                  &GetSessionRace()                  },
		{ "fire",                  &GetSessionFire()                  },
		{ "win",                   &GetSessionWin()                   },
		{ "over",                  &GetSessionOver()                  },
		{ "health",                &GetSessionHealth()                },
		{ "toll",                  &GetSessionToll()                  },
	};

	return(_RTESessionManager[_Name]);
}

