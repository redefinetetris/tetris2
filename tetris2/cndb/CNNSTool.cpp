#include "CNNSTool.h"
#include <regex>


namespace CNNSTool
{
	int GetFileSize(std::fstream& _FileStream)
	{
		_FileStream.seekg(0, std::ios_base::end);

		const int szFile = (int)_FileStream.tellg();

		return(szFile);
	}


	int GetExtendFileSize(const int _Pos)
	{
		//+4KB
		const unsigned int Mask = 0XFFF;
		const auto Up = _Pos + Mask;
		const auto UnMask = ~Mask;
		const auto Total = Up & UnMask;

		return(Total);
	}


	char SignSplit(void)
	{
		return(1);
	}


	char SignFill(void)
	{
		return(' ');
	}


	std::vector<std::string> SplitLine(const std::string& _strLine)
	{
		int start = 0;
		const auto Sign = SignSplit();
		std::vector<std::string> Values;

		while (true)
		{
			const auto end = _strLine.find(Sign, start);
			if (std::string::npos == end)
			{
				break;
			}

			Values.push_back(_strLine.substr(start, end - start));
			start = end + 1;
		}

		return(Values);
	}


	std::string JoinLine(const std::vector<std::string>& _Values)
	{
		const auto Sign = SignSplit();
		std::string strLine;

		for (auto item = _Values.begin(); item != _Values.end(); ++item)
		{
			strLine += *item + Sign;
		}

		return(strLine);
	}


	void ReadFile(std::fstream& _FileStream, char* _pBuffer, const int _Pos, const int _Length)
	{
		_FileStream.clear();

		_FileStream.seekg(_Pos, std::ios_base::beg);
		_FileStream.read(_pBuffer, _Length);

		_FileStream.clear();
	}


	bool RunCondition(const std::vector<std::string>& _Condition, const std::string& _Target)
	{
		const auto& Op = _Condition[0];
		const auto& Value = _Condition[1];

		//等于
		if ("=" == Op)
		{
			if (Value == _Target)
			{
				return(true);
			}
		}
		//不等于
		else if ("!=" == Op)
		{
			if (Value != _Target)
			{
				return(true);
			}
		}
		//正则表达式
		else if ("reg" == Op)
		{
			std::regex re(Value);

			if (true == std::regex_match(_Target, re))
			{
				return(true);
			}
		}

		return(false);
	}

}//CNNSTool

