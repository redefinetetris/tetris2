#ifndef __RTNSLOG_H__
#define __RTNSLOG_H__


#include <string>


void LogInfo(const std::string _str);
void LogWarning(const std::string _str);
void LogError(const std::string _str);


void PrintLogInfo(const std::string _str);


class CMLoger
{
public:
	CMLoger(const std::string _Msg)
		: m_Msg(_Msg)
	{
		LogInfo("Begin " + m_Msg);
	}

	~CMLoger()
	{
		LogInfo("End " + m_Msg);
	}

private:
	const std::string m_Msg;
};


#endif
