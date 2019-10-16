#include "RTDBStatic.h"
#include "../RTNSDB.h"


CCNDB<int, CRTDBState>& GetStateManager(void)
{
	static CCNDB<int, CRTDBState> _StateManager;

	return(_StateManager);
}


CCNDB<int, CRTDBUser>& GetUserManager(void)
{
	static CCNDB<int, CRTDBUser> _UserManager;

	return(_UserManager);
}


CCNDB<int, CRTDBRole>& GetRoleManager(void)
{
	static CCNDB<int, CRTDBRole> _RoleManager;

	return(_RoleManager);
}


CCNDB<int, CRTDBPassword>& GetPasswordManager(void)
{
	static CCNDB<int, CRTDBPassword> _PasswordManager;

	return(_PasswordManager);
}


CCNDB<int, CRTDBBlock>& GetBlockManager(void)
{
	static CCNDB<int, CRTDBBlock> _BlockManager;

	return(_BlockManager);
}


CCNDB<int, CRTDBTransfer>& GetTransferManager(void)
{
	static CCNDB<int, CRTDBTransfer> _TransferManager;

	return(_TransferManager);
}


CCNDB<int, CRTDBSpeed>& GetSpeedManager(void)
{
	static CCNDB<int, CRTDBSpeed> _SpeedManager;

	return(_SpeedManager);
}


CCNDB<int, CRTDBPackage>& GetPackageManager(void)
{
	static CCNDB<int, CRTDBPackage> _PackageManager;

	return(_PackageManager);
}


CCNDB<int, CRTDBToken>& GetTokenManager(void)
{
	static CCNDB<int, CRTDBToken> _TokenManager;

	return(_TokenManager);
}


CCNDB<int, CRTDBRoot>& GetRootManager(void)
{
	static CCNDB<int, CRTDBRoot> _RootManager(RTNSDB::DefaultDBRootID());

	return(_RootManager);
}


CCNDB<int, CRTDBSession>& GetSessionManager(void)
{
	static CCNDB<int, CRTDBSession> _SessionManager;

	return(_SessionManager);
}


CCNDB<int, CRTDBGame>& GetGameManager(void)
{
	static CCNDB<int, CRTDBGame> _GameManager;

	return(_GameManager);
}


CCNDB<int, CRTDBReplay>& GetReplayManager(void)
{
	static CCNDB<int, CRTDBReplay> _ReplayManager;

	return(_ReplayManager);
}


CCNDB<int, CRTDBCursor>& GetCursorManager(void)
{
	static CCNDB<int, CRTDBCursor> _CursorManager;

	return(_CursorManager);
}


static CRTManager<std::string, Manager_t*> __CNDBManager{
	{ "states",           (Manager_t*)&GetStateManager()          },
	{ "users",            (Manager_t*)&GetUserManager()           },
	{ "roles",            (Manager_t*)&GetRoleManager()           },
	{ "passwords",        (Manager_t*)&GetPasswordManager()       },
	{ "blocks",           (Manager_t*)&GetBlockManager()          },
	{ "transfers",        (Manager_t*)&GetTransferManager()       },
	{ "speeds",           (Manager_t*)&GetSpeedManager()          },
	{ "packages",         (Manager_t*)&GetPackageManager()        },
	{ "tokens",           (Manager_t*)&GetTokenManager()          },
	{ "roots",            (Manager_t*)&GetRootManager()           },
	{ "sessions",         (Manager_t*)&GetSessionManager()        },
	{ "games",            (Manager_t*)&GetGameManager()           },
	{ "replays",          (Manager_t*)&GetReplayManager()         },
	{ "cursors",          (Manager_t*)&GetCursorManager()         },
};


Manager_t* GetCNDB(const std::string _Name)
{
	return(__CNDBManager[_Name]);
}


std::vector<std::string> GetCNDBManagerKeys(void)
{
	return(__CNDBManager.Keys());
}


std::vector<Manager_t*> GetCNDBManagerValues(void)
{
	return(__CNDBManager.Values());
}

