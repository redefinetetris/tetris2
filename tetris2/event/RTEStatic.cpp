#include "RTEStatic.h"
#include "../RTManagerLocker.h"


CRTEGame& GetRTEGame(void)
{
	static CRTEGame _RTEGame;

	return(_RTEGame);
}


CRTESession& GetRTESession(void)
{
	static CRTESession _RTESession;

	return(_RTESession);
}


CRTERoot& GetRTERoot(void)
{
	static CRTERoot _RTERoot;

	return(_RTERoot);
}


CRTETrail& GetRTETrail(void)
{
	static CRTETrail _RTETrail;

	return(_RTETrail);
}


CRTEDB& GetRTEDB(void)
{
	static CRTEDB _RTEDB;

	return(_RTEDB);
}


CRTEClock& GetRTEClock(void)
{
	static CRTEClock _RTEClock;

	return(_RTEClock);
}


CRTEEvent& GetRTEEvent(void)
{
	static CRTEEvent _RTEEvent;

	return(_RTEEvent);
}


CRTEHub& GetRTEHub(void)
{
	static CRTEHub _RTEHub;

	return(_RTEHub);
}


CRTEUser& GetRTEUser(void)
{
	static CRTEUser _RTEUser;

	return(_RTEUser);
}


CRTEReplay& GetRTEReplay(void)
{
	static CRTEReplay _RTEReplay;

	return(_RTEReplay);
}


CRTEBase* GetRTE(const std::string _Name)
{
	static CRTManagerLocker<std::string, CRTEBase*> _RTManager{
		{ "game",           &GetRTEGame()            },
		{ "session",        &GetRTESession()         },
		{ "root",           &GetRTERoot()            },
		{ "trail",          &GetRTETrail()           },
		{ "db",             &GetRTEDB()              },
		{ "clock",          &GetRTEClock()           },
		{ "event",          &GetRTEEvent()           },
		{ "hub",            &GetRTEHub()             },
		{ "user",           &GetRTEUser()            },
		{ "replay",         &GetRTEReplay()          },
	};

	return(_RTManager[_Name]);
}


static CRTManagerLocker<std::string, CRTEBase*> __RTManager4Recv{
	{ "trail",          &GetRTETrail()           },
	{ "db",             &GetRTEDB()              },
	{ "clock",          &GetRTEClock()           },
	{ "user",           &GetRTEUser()            },
	{ "replay",         &GetRTEReplay()          },
};


CRTEBase* GetRTE4Recv(const std::string _Name)
{
	return(__RTManager4Recv[_Name]);
}


CRTEBase* GetRTE4Send(const std::string _Name)
{
	return(GetRTE4Recv(_Name));
}


static CRTManagerLocker<std::string, CRTEBase*> __RTManager4Event{
	{ "trail",          &GetRTETrail()           },
	{ "db",             &GetRTEDB()              },
	{ "hub",            &GetRTEHub()             },
	{ "user",           &GetRTEUser()            },
	{ "replay",         &GetRTEReplay()          },
};

	
CRTEBase* GetRTE4Event(const std::string _Name)
{
	return(__RTManager4Event[_Name]);
}


std::vector<CRTEBase*> GetRTE4SendValues(void)
{
	return(__RTManager4Recv.Values());
}


std::vector<CRTEBase*> GetRTE4EventValues(void)
{
	return(__RTManager4Event.Values());
}

