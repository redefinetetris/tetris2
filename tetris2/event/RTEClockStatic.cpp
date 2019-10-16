#include "RTEClockStatic.h"
#include "../RTManager.h"


CClockUpdate& GetClockUpdate(void)
{
	static CClockUpdate _ClockUpdate;

	return(_ClockUpdate);
}


CClockNew& GetClockNew(void)
{
	static CClockNew _ClockNew;

	return(_ClockNew);
}


CClockDelete& GetClockDelete(void)
{
	static CClockDelete _ClockDelete;

	return(_ClockDelete);
}


CClockQuery& GetClockQuery(void)
{
	static CClockQuery _ClockQuery;

	return(_ClockQuery);
}


CClockHealth& GetClockHealth(void)
{
	static CClockHealth _ClockHealth;

	return(_ClockHealth);
}


CRTEClockFunctor* GetRTEClockFunctor(const std::string _Name)
{
	static CRTManager<std::string, CRTEClockFunctor*> _RTEClockManager{
		{ "update",                &GetClockUpdate()                  },
		{ "new",                   &GetClockNew()                     },
		{ "delete",                &GetClockDelete()                  },
		{ "query",                 &GetClockQuery()                   },
		{ "health",                &GetClockHealth()                  },
	};

	return(_RTEClockManager[_Name]);
}

