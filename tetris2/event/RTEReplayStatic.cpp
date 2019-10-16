#include "RTEReplayStatic.h"
#include "../RTManager.h"


CReplayInit& GetReplayInit(void)
{
	static CReplayInit _ReplayInit;

	return(_ReplayInit);
}


CReplayQuery& GetReplayQuery(void)
{
	static CReplayQuery _ReplayQuery;

	return(_ReplayQuery);
}


CReplayBackward& GetReplayBackward(void)
{
	static CReplayBackward _ReplayBackward;

	return(_ReplayBackward);
}


CReplayForward& GetReplayForward(void)
{
	static CReplayForward _ReplayForward;

	return(_ReplayForward);
}


CRTEReplayFunctor* GetRTEReplayFunctor(const std::string _Name)
{
	static CRTManager<std::string, CRTEReplayFunctor*> _RTEReplayManager{
		{ "init",                  &GetReplayInit()                   },
		{ "query",                 &GetReplayQuery()                  },
		{ "backward",              &GetReplayBackward()               },
		{ "forward",               &GetReplayForward()                },
	};

	return(_RTEReplayManager[_Name]);
}

