#include "RTEDBStatic.h"
#include "../RTManager.h"


CDBTimer& GetDBTimer(void)
{
	static CDBTimer _DBTimer;

	return(_DBTimer);
}


CDBFire& GetDBFire(void)
{
	static CDBFire _DBFire;

	return(_DBFire);
}


CDBFlush& GetDBFlush(void)
{
	static CDBFlush _DBFlush;

	return(_DBFlush);
}


CDBDownTTL& GetDBDownTTL(void)
{
	static CDBDownTTL _DBDownTTL;

	return(_DBDownTTL);
}


CDBWashTTL& GetDBWashTTL(void)
{
	static CDBWashTTL _DBWashTTL;

	return(_DBWashTTL);
}


CRTEDBFunctor* GetRTEDBFunctor(const std::string _Name)
{
	static CRTManager<std::string, CRTEDBFunctor*> _RTEDBManager{
		{ "timer",                 &GetDBTimer()                      },
		{ "fire",                  &GetDBFire()                       },
		{ "flush",                 &GetDBFlush()                      },
		{ "downttl",               &GetDBDownTTL()                    },
		{ "washttl",               &GetDBWashTTL()                    },
	};

	return(_RTEDBManager[_Name]);
}

