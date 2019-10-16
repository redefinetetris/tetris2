#ifndef __RTLOG_H__
#define __RTLOG_H__


#include <mutex>
#include <string>
#include <fstream>


class CRTLog
{
public:
	CRTLog(const std::string _FileName);
	~CRTLog();

private:
	std::mutex m_Mutex;
	const std::string m_FileName;
	std::fstream m_FileStream;

public:
	void WriteMessage(const std::string& _Message);
};


#endif//__RTLOG_H__

