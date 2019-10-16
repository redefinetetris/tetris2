#include "RTLog.h"
#include "RTNSDB.h"
#include "RTNSTool.h"


CRTLog::CRTLog(const std::string _FileName)
	: m_Mutex()
	, m_FileName(_FileName)
	, m_FileStream()
{
	m_FileStream.open(m_FileName, std::ios_base::app);
}


CRTLog::~CRTLog()
{
	m_FileStream.close();
}


void CRTLog::WriteMessage(const std::string& _Message)
{
	//std::unique_lock<std::mutex> locker(m_Mutex);

	const auto msg = RTNSDB::GetCurrentDateTime() + " tid=" + RTNSTool::GetThreadIDString() + " " + _Message + '\n';

	m_FileStream << msg;
}

