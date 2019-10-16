#include "RTEUserStatic.h"
#include "../RTManager.h"


CUserLogin& GetUserLogin(void)
{
	static CUserLogin _UserLogin;

	return(_UserLogin);
}


CUserLogout& GetUserLogout(void)
{
	static CUserLogout _UserLogout;

	return(_UserLogout);
}


CUserRegin& GetUserRegin(void)
{
	static CUserRegin _UserRegin;

	return(_UserRegin);
}


CUserRegout& GetUserRegout(void)
{
	static CUserRegout _UserRegout;

	return(_UserRegout);
}


CRTEUserFunctor* GetRTEUserFunctor(const std::string _Name)
{
	static CRTManager<std::string, CRTEUserFunctor*> _RTEUserManager{
		{ "login",                 &GetUserLogin()                    },
		{ "logout",                &GetUserLogout()                   },
		{ "regin",                 &GetUserRegin()                    },
		{ "regout",                &GetUserRegout()                   },
	};

	return(_RTEUserManager[_Name]);
}

