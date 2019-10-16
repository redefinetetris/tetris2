#ifndef __RTDBSTATIC_H__
#define __RTDBSTATIC_H__


#include <string>
#include <vector>
#include <memory>
#include "../cndb/CNDB.h"
#include "../RTManager.h"
#include "../RTManagerLocker.h"
#include "RTDBState.h"
#include "RTDBUser.h"
#include "RTDBRole.h"
#include "RTDBPassword.h"
#include "RTDBBlock.h"
#include "RTDBTransfer.h"
#include "RTDBSpeed.h"
#include "RTDBPackage.h"
#include "RTDBToken.h"
#include "RTDBRoot.h"
#include "RTDBSession.h"
#include "RTDBGame.h"
#include "RTDBReplay.h"
#include "RTDBCursor.h"


CCNDB<int, CRTDBState>& GetStateManager(void);
CCNDB<int, CRTDBUser>& GetUserManager(void);
CCNDB<int, CRTDBRole>& GetRoleManager(void);
CCNDB<int, CRTDBPassword>& GetPasswordManager(void);
CCNDB<int, CRTDBBlock>& GetBlockManager(void);
CCNDB<int, CRTDBTransfer>& GetTransferManager(void);
CCNDB<int, CRTDBSpeed>& GetSpeedManager(void);
CCNDB<int, CRTDBPackage>& GetPackageManager(void);
CCNDB<int, CRTDBToken>& GetTokenManager(void);
CCNDB<int, CRTDBRoot>& GetRootManager(void);
CCNDB<int, CRTDBSession>& GetSessionManager(void);
CCNDB<int, CRTDBGame>& GetGameManager(void);
CCNDB<int, CRTDBReplay>& GetReplayManager(void);
CCNDB<int, CRTDBCursor>& GetCursorManager(void);


typedef CCNDB<int, CRTDBBase> Manager_t;

Manager_t* GetCNDB(const std::string _Name);


std::vector<std::string> GetCNDBManagerKeys(void);
std::vector<Manager_t*> GetCNDBManagerValues(void);


#endif//__RTDBSTATIC_H__

