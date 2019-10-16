#ifndef __RTNSSTATIC_H__
#define __RTNSSTATIC_H__


class CRTServer;


namespace RTNSStatic
{
	bool Power(void);
	void Shutdown(const bool _yes = true);


	CRTServer* GetServer(void);
	void SetServer(CRTServer* _pServer);


	void SetWorkThreaderSize(const int _Size);
	void WakeWorkThreader(void);
	void IdleWorkThreader(const int _work);


	void IdleClockThreader(const int _work);
	int GetClockMicroSeconds(void);
	void SetClockMicroSeconds(const int _MicroSeconds);


	void WakeHubThreader(void);
	void IdleHubThreader(const int _work);
	int GetHubMicroSeconds(void);
	void SetHubMicroSeconds(const int _MicroSeconds);


	void ThreadEventFun(void);
	void ThreadClockFun(void);
	void ThreadHubFun(void);
}//RTNSStatic


#endif

