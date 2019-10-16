#ifndef __CNDB_H__
#define __CNDB_H__


#include <atomic>
#include <memory>
#include <fstream>
#include "CNNSTool.h"
#include "../RTDict.h"
#include "../RTManagerLocker.h"


template<class T_Key, class T_Value>
class CCNDB
{
public:
	CCNDB(const int _StartID = 0)
		: m_Manager()
		, m_ID(_StartID)
		, m_Obj()
	{
		m_FileStream.open(m_Obj.GetDBName());

		if (true == m_FileStream.is_open())
		{
			auto pValue = this->GetLatestRecord();
			if (nullptr != pValue)
			{
				m_ID = pValue->GetID();
			}
		}
	}

	~CCNDB()
	{
		this->Flush();

		m_FileStream.close();
	}


	typedef CRTManagerLocker<T_Key, std::shared_ptr<T_Value>> ManagerLocker_t;


private:
	ManagerLocker_t m_Manager;
	std::fstream m_FileStream;
	std::atomic<int> m_ID;
	T_Value m_Obj;

public:
	int GetID(void) const
	{
		return(m_ID);
	}

	int UpID(void)
	{
		return(++m_ID);
	}

public:
	std::shared_ptr<T_Value> Get(const T_Key _Key)
	{
		auto pValue = this->Query(_Key);

		return(pValue);
	}

	void Post(std::shared_ptr<T_Value> _pValue)
	{
		if (0 == _pValue->GetID())
		{
			_pValue->SetID(this->UpID());
		}
		_pValue->SetAllObjStyle(RTDBOS_Post);

		this->Update(_pValue);
	}

	void Put(std::shared_ptr<T_Value> _pValue)
	{
		_pValue->SetAllObjStyle(RTDBOS_Put);

		this->Update(_pValue);
	}

	void Delete(std::shared_ptr<T_Value> _pValue)
	{
		_pValue->SetAllObjStyle(RTDBOS_Delete);

		this->Update(_pValue);
	}

	std::shared_ptr<T_Value> GetLatestRecord(void)
	{
		const auto idMax = this->GetID();
		if (0 < idMax)
		{
			auto pValue = this->Get(idMax);
			if (nullptr != pValue)
			{
				return(pValue);
			}
		}

		const auto pValue = CNNSTool::GetLatestRecord<T_Key, T_Value>(m_FileStream);
		if (nullptr == pValue)
		{
			return(nullptr);
		}

		return(pValue);
	}

public:
	std::shared_ptr<T_Value> GetOnlyOne(const CRTDict& _Dict, const int _Index = 1, const int _OpIndex = 1)
	{
		const auto Result = this->GetAllBySize(_Dict, 1, _Index, _OpIndex);

		if (0 == Result.size())
		{
			return(nullptr);
		}

		return(Result[0]);
	}

	std::vector<std::shared_ptr<T_Value>> GetAllBySize(const CRTDict& _Dict, const int _szObj = 0X7FFFFFFF, const int _Index = 1, const int _OpIndex = 1)
	{
		const auto Result = CNNSTool::QueryAllBySize<ManagerLocker_t, T_Key, T_Value>(m_Manager, m_FileStream, _Dict, _szObj, _Index, _OpIndex);

		return(Result);
	}

	//×ó±ÕÓÒ¿ª
	std::vector<std::shared_ptr<T_Value>> GetAllByRange(const CRTDict& _Dict, const int _idStart, const int _idEnd = 0)
	{
		const auto Result = CNNSTool::QueryAllByRange<ManagerLocker_t, T_Key, T_Value>(m_Manager, m_FileStream, _Dict, _idStart, _idEnd);

		return(Result);
	}

	int GetID(const CRTDict& _Dict)
	{
		auto pValue = this->GetOnlyOne(_Dict);

		if (nullptr == pValue)
		{
			return(0);
		}

		return(pValue->GetIndex());
	}

public:
	int Flush(void)
	{
		int work = 0;
		const auto Values = m_Manager.Values();

		for (auto item = Values.begin(); item != Values.end(); ++item)
		{
			auto pValue = *item;
			if (nullptr == pValue)
			{
				continue;
			}
			if (true == pValue->GetObjStyle(RTDBOS_Get))
			{
				continue;
			}

			++work;
			CNNSTool::UpdateFile<T_Key, T_Value>(m_FileStream, pValue);

			const auto bDelete = pValue->GetObjStyle(RTDBOS_Delete);
			pValue->SetAllObjStyle(RTDBOS_Get);
			if (true == bDelete)
			{
				pValue->SetObjStyle(RTDBOS_Delete);
			}
		}//for

		m_FileStream.flush();

		return(work);
	}

	void DownTTL(void)
	{
		const auto Values = m_Manager.Values();

		for (auto item = Values.begin(); item != Values.end(); ++item)
		{
			auto pValue = *item;
			if (nullptr == pValue)
			{
				continue;
			}

			pValue->UpTTL(-1);
		}//for
	}

	bool Wash(const int _Max = 1000)
	{
		const auto Size = m_Manager.Size();

		if (Size < _Max)
		{
			return(false);
		}

		return(true);
	}

	int WashTTL(void)
	{
		if (false == this->Wash())
		{
			return(0);
		}

		int work = 0;
		const auto Values = m_Manager.Values();

		for (auto item = Values.begin(); item != Values.end(); ++item)
		{
			auto pValue = *item;
			if (nullptr == pValue)
			{
				continue;
			}

			if (0 < pValue->GetTTL())
			{
				continue;
			}
			if (false != pValue->GetObjStyle(RTDBOS_Get))
			{
				continue;
			}

			++work;
			m_Manager.DeleteTarget(pValue->GetIndex());
		}//for

		return(work);
	}

private:
	std::shared_ptr<T_Value> Query(const T_Key _Key)
	{
		auto pValue = CNNSTool::Query<ManagerLocker_t, T_Key, T_Value>(m_Manager, m_FileStream, _Key);
		if (nullptr == pValue)
		{
			return(nullptr);
		}

		pValue->UpTTL();

		return(pValue);
	}

public:
	void Update(const std::shared_ptr<T_Value> _pValue, const RTDBObjectStyle_t _Style = RTDBOS_Put)
	{
		_pValue->UpTTL();
		_pValue->SetAllObjStyle(_Style);

		m_Manager[_pValue->GetID()] = _pValue;

		//this->Flush();
	}
};


#endif//__CNDB_H__

