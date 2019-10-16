#include "RTNSLog.h"
#include "RTLog.h"
#include "RTNSDB.h"
#include <iostream>


CRTLog __Loger("redefine_tetris_" + RTNSDB::GetCurrentDateTime('_') + ".log");


void LogInfo(const std::string _str)
{
	const static std::string _strInfo = "Info ";

	__Loger.WriteMessage(_strInfo + _str);
}


void LogWarning(const std::string _str)
{
	const static std::string _strWarning = "Warning ";

	__Loger.WriteMessage(_strWarning + _str);
}


void LogError(const std::string _str)
{
	const static std::string _strError = "Error ";

	__Loger.WriteMessage(_strError + _str);
}


void PrintLogInfo(const std::string _str)
{
	std::cout << _str << std::endl;
}

