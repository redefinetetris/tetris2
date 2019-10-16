#include "RTERootStatic.h"
#include "../RTManager.h"


CRootNewSession& GetRootNewSession(void)
{
	static CRootNewSession _RootNewSession;

	return(_RootNewSession);
}


CRootDeleteSession& GetRootDeleteSession(void)
{
	static CRootDeleteSession _RootDeleteSession;

	return(_RootDeleteSession);
}


CRootQuery& GetRootQuery(void)
{
	static CRootQuery _RootQuery;

	return(_RootQuery);
}


CRootHealth& GetRootHealth(void)
{
	static CRootHealth _RootHealth;

	return(_RootHealth);
}


CRTERootFunctor* GetRTERootFunctor(const std::string _Name)
{
	static CRTManager<std::string, CRTERootFunctor*> _RTERootManager{
		{ "newsession",            &GetRootNewSession()               },
		{ "deletesession",         &GetRootDeleteSession()            },
		{ "query",                 &GetRootQuery()                    },
		{ "health",                &GetRootHealth()                   },
	};

	return(_RTERootManager[_Name]);
}

