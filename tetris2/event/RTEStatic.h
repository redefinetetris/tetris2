#include "RTEBase.h"
#include "RTEPayBase.h"
#include "RTEGame.h"
#include "RTESession.h"
#include "RTERoot.h"
#include "RTETrail.h"
#include "RTEDB.h"
#include "RTEClock.h"
#include "RTEEvent.h"
#include "RTEHub.h"
#include "RTEUser.h"
#include "RTEReplay.h"


CRTEGame& GetRTEGame(void);
CRTESession& GetRTESession(void);
CRTERoot& GetRTERoot(void);
CRTETrail& GetRTETrail(void);
CRTEDB& GetRTEDB(void);
CRTEClock& GetRTEClock(void);
CRTEEvent& GetRTEEvent(void);
CRTEHub& GetRTEHub(void);
CRTEUser& GetRTEUser(void);
CRTEReplay& GetRTEReplay(void);

CRTEBase* GetRTE(const std::string _Name);
CRTEBase* GetRTE4Recv(const std::string _Name);
CRTEBase* GetRTE4Send(const std::string _Name);
CRTEBase* GetRTE4Event(const std::string _Name);

std::vector<CRTEBase*> GetRTE4SendValues(void);
std::vector<CRTEBase*> GetRTE4EventValues(void);

