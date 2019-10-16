#ifndef __CNNSTOOL_H__
#define __CNNSTOOL_H__


#include <string>
#include <vector>
#include <memory>
#include <fstream>
#include "../RTDict.h"
#include "../RTNSTool.h"
#include "../RTDataType.h"
#include "../RTManagerLocker.h"
#include "../orm/RTDBObjectStyle.h"


namespace CNNSTool
{
	int GetFileSize(std::fstream& _FileStream);
	int GetExtendFileSize(const int _Pos);


	char SignSplit(void);
	char SignFill(void);


	std::vector<std::string> SplitLine(const std::string& _strLine);
	std::string JoinLine(const std::vector<std::string>& _Values);


	template<class T_Key, class T_Value>
	std::shared_ptr<T_Value> QueryFile(std::fstream& _FileStream, const T_Key _Key)
	{
		auto pValue = RTNSTool::NewSharedPtrObj<T_Value>();
		if (nullptr == pValue)
		{
			return(nullptr);
		}

		pValue->SetID(_Key);
		const auto bCode = QueryFile<T_Key, T_Value>(_FileStream, pValue);
		if (false == bCode)
		{
			return(nullptr);
		}

		return(pValue);
	}


	void ReadFile(std::fstream& _FileStream, char* _pBuffer, const int _Pos, const int _Length);


	template<class T_Key, class T_Value>
	bool QueryFile(std::fstream& _FileStream, std::shared_ptr<T_Value> _pValue)
	{
		const auto Key = _pValue->GetID();
		const auto LengthPerLine = _pValue->GetLengthPerLine();
		const auto Pos = Key * LengthPerLine;
		char chsLine[MAX_LENGTH_PER_LINE]{ 0 };

		ReadFile(_FileStream, chsLine, Pos, LengthPerLine);

		const auto Values = SplitLine(chsLine);
		if (0 == Values.size())
		{
			return(false);
		}

		_pValue->SetAllValue(Values);
		_pValue->SetObjStyle(RTDBOS_Get);

		return(true);
	}


	template<class T_Manager, class T_Key, class T_Value>
	std::shared_ptr<T_Value> QueryMemory(T_Manager& _Manager, const T_Key _Key)
	{
		auto pValue = _Manager[_Key];

		return(pValue);
	}


	template<class T_Manager, class T_Key, class T_Value>
	std::shared_ptr<T_Value> QuerySimple(T_Manager& _Manager, std::fstream& _FileStream, const T_Key _Key)
	{
		auto pValueMemory = QueryMemory<T_Manager, T_Key, T_Value>(_Manager, _Key);
		if (nullptr != pValueMemory)
		{
			return(pValueMemory);
		}

		auto pValueFile = QueryFile<T_Key, T_Value>(_FileStream, _Key);
		if (nullptr != pValueFile)
		{
			return(pValueFile);
		}

		return(nullptr);
	}


	template<class T_Manager, class T_Key, class T_Value>
	std::shared_ptr<T_Value> Query(T_Manager& _Manager, std::fstream& _FileStream, const T_Key _Key)
	{
		auto pValue = QuerySimple<T_Manager, T_Key, T_Value>(_Manager, _FileStream, _Key);
		if (nullptr == pValue)
		{
			return(nullptr);
		}

		if (true == pValue->GetObjStyle(RTDBOS_Delete))
		{
			return(nullptr);
		}

		_Manager[_Key] = pValue;

		return(pValue);
	}


	bool RunCondition(const std::vector<std::string>& _Condition, const std::string& _Target);


	template<class T_Value>
	bool RunCondition(const CRTDict& _Dict, std::shared_ptr<T_Value> _pValue)
	{
		const auto Keys = _Dict.Keys();
		const auto CVs = _pValue->GetColumnValue();

		for (auto item = Keys.begin(); item != Keys.end(); ++item)
		{
			const auto& key = *item;
			const auto& Condition = _Dict[key].GetVectorString();
			const auto& target = CVs[key].GetString();
			const auto bCode = RunCondition(Condition, target);

			if (false == bCode)
			{
				return(false);
			}
		}//for

		return(true);
	}

	//°üº¬_Index
	template<class T_Manager, class T_Key, class T_Value>
	std::vector<std::shared_ptr<T_Value>> QueryAllBySize(T_Manager& _Manager, std::fstream& _FileStream, const CRTDict& _Dict, const int _szObj, int _Index, const int _OpIndex)
	{
		std::vector<std::shared_ptr<T_Value>> Result;
		Result.reserve(VECTOR_RESERVE_SIZE);
		int size = 0;

		while (size < _szObj)
		{
			auto pValue = Query<T_Manager, T_Key, T_Value>(_Manager, _FileStream, _Index);
			if (nullptr == pValue)
			{
				break;
			}

			const auto bOK = RunCondition(_Dict, pValue);
			if (true == bOK)
			{
				Result.push_back(pValue);
				++size;
			}

			_Index += _OpIndex;
		}//while

		return(Result);
	}


	//×ó±ÕÓÒ¿ª
	template<class T_Manager, class T_Key, class T_Value>
	std::vector<std::shared_ptr<T_Value>> QueryAllByRange(T_Manager& _Manager, std::fstream& _FileStream, const CRTDict& _Dict, const int _idStart, int _idEnd = 0)
	{
		std::vector<std::shared_ptr<T_Value>> Result;
		Result.reserve(VECTOR_RESERVE_SIZE);

		if (0 == _idEnd)
		{
			const auto pLatestRecord = GetLatestRecord<T_Key, T_Value>(_FileStream);
			if (nullptr != pLatestRecord)
			{
				_idEnd = pLatestRecord->GetID() + 1;
			}
			else
			{
				_idEnd = 0X7FFFFFFF;
			}
		}

		for (int index = _idStart; index < _idEnd; ++index)
		{
			auto pValue = Query<T_Manager, T_Key, T_Value>(_Manager, _FileStream, index);
			if (nullptr == pValue)
			{
				break;
			}

			const auto bOK = RunCondition(_Dict, pValue);
			if (true == bOK)
			{
				Result.push_back(pValue);
			}
		}//for

		return(Result);
	}


	template<class T_Key, class T_Value>
	void UpdateFile(std::fstream& _FileStream, std::shared_ptr<T_Value> _pValue)
	{
		const auto LengthPerLine = _pValue->GetLengthPerLine();
		const auto Pos = _pValue->GetIndex() * LengthPerLine;
		std::string strPad;

		const auto szFile = GetFileSize(_FileStream);
		if (szFile <= Pos)
		{
			const auto Total = GetExtendFileSize(Pos);
			strPad.resize(Total - szFile, SignFill());
		}

		_FileStream << strPad;
		_FileStream.seekp(Pos);
		const auto Values = _pValue->GetAllValue();
		auto strLine = JoinLine(Values);
		strLine.resize(LengthPerLine - strLine.size(), SignFill());
		_FileStream << strLine;
	}


	template<class T_Key, class T_Value>
	std::shared_ptr<T_Value> GetLatestRecord(std::fstream& _FileStream)
	{
		const auto szFile = CNNSTool::GetFileSize(_FileStream);
		if (0 == szFile)
		{
			return(nullptr);
		}

		auto pValue = RTNSTool::NewSharedPtrObj<T_Value>();
		if (nullptr == pValue)
		{
			return(nullptr);
		}

		const auto PosMax = szFile / pValue->GetLengthPerLine();

		for (int index = PosMax - 1; 0 < index; --index)
		{
			pValue->SetID(index);

			const auto bCode = CNNSTool::QueryFile<T_Key, T_Value>(_FileStream, pValue);
			if (false == bCode)
			{
				continue;
			}

			return(pValue);
		}

		return(nullptr);
	}
}//CNNSTool


#endif//__CNNSTOOL_H__

