#include "RTNSStatic.h"
#include <mutex>
#include <atomic>
#include <condition_variable>
#include "RTNSLog.h"
#include "RTEStatic.h"


namespace RTNSStatic
{
	bool __Power = true;


	bool Power(void)
	{
		return(__Power);
	}


	void Shutdown(const bool _yes)
	{
		__Power = _yes;
	}


	CRTServer *__pServer = nullptr;


	CRTServer* GetServer(void)
	{
		return(__pServer);
	}


	void SetServer(CRTServer* _pServer)
	{
		__pServer = _pServer;
	}


	std::mutex __MailMutex;
	std::condition_variable __MailCV;
	std::atomic<int> __RunWorkerThreader = 0;


	void SetWorkThreaderSize(const int _Size)
	{
		__RunWorkerThreader = _Size;
	}


	void WakeWorkThreader(void)
	{
		__MailCV.notify_one();
	}


	void IdleWorkThreader(const int _work)
	{
		std::unique_lock<std::mutex> locker(__MailMutex);

		if (0 == _work)
		{
			LogInfo("worker idle");

			--__RunWorkerThreader;
			__MailCV.wait(locker);
			++__RunWorkerThreader;

			LogInfo("worker wake");
		}
		else
		{
			LogInfo("worker continue working");
		}
	}


	std::mutex __ClockMutex;
	std::condition_variable __ClockCV;
	static int __ClockMicroSeconds = 50 * 1000;


	void IdleClockThreader(const int _work)
	{
		std::unique_lock<std::mutex> locker(__ClockMutex);

		if (0 == _work)
		{
			const auto ms = std::chrono::microseconds(GetClockMicroSeconds());

			LogInfo("clock idle");

			const auto vc_status = __ClockCV.wait_for(locker, ms);

			LogInfo("clock wake");
		}
		else
		{
			LogInfo("clock continue working");
		}
	}


	int GetClockMicroSeconds(void)
	{
		return(__ClockMicroSeconds);
	}


	void SetClockMicroSeconds(const int _MicroSeconds)
	{
		__ClockMicroSeconds = _MicroSeconds;
	}


	std::mutex __HubMutex;
	std::condition_variable __HubCV;
	static int __HubMicroSeconds = 50 * 1000;


	void WakeHubThreader(void)
	{
		__HubCV.notify_one();
	}


	void IdleHubThreader(const int _work)
	{
		std::unique_lock<std::mutex> locker(__HubMutex);

		if (0 == _work)
		{
			if (0 == __RunWorkerThreader)
			{
				LogInfo("hub hung up");

				__HubCV.wait(locker);

				LogInfo("hub wake up");
			}
			else
			{
				const auto ms = std::chrono::microseconds(GetHubMicroSeconds());

				LogInfo("hub idle");

				const auto vc_status = __HubCV.wait_for(locker, ms);

				LogInfo("hub wake");
			}
		}
		else
		{
			LogInfo("hub continue working");
		}
	}


	int GetHubMicroSeconds(void)
	{
		return(__HubMicroSeconds);
	}


	void SetHubMicroSeconds(const int _MicroSeconds)
	{
		__HubMicroSeconds = _MicroSeconds;
	}


	void ThreadEventFun(void)
	{
		int work = 0;
		auto& RTEEventer(GetRTEEvent());

		while (true)
		{
			IdleWorkThreader(work);

			CMMaster Master(&RTEEventer);

			work = RTEEventer();
		}
	}


	void ThreadClockFun(void)
	{
		int work = 0;
		auto& RTEClocker(GetRTEClock());

		while (true)
		{
			IdleClockThreader(work);

			CMMaster Master(&RTEClocker);

			work = RTEClocker();
		}
	}


	void ThreadHubFun(void)
	{
		int work = 0;
		auto& RTEHuber(GetRTEHub());

		while (true)
		{
			IdleHubThreader(work);

			CMMaster Master(&RTEHuber);

			work = RTEHuber();
		}
	}

}//RTNSStatic

