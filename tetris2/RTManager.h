#ifndef __RTMANAGER_H__
#define __RTMANAGER_H__


#include <unordered_map>
#include <initializer_list>


template<class T_Key, class T_Value>
class CRTManager
{
public:
	CRTManager()
		: m_Manager()
	{}
	CRTManager(const std::unordered_map<T_Key, T_Value> &_Manager)
		: m_Manager(_Manager)
	{}
	CRTManager(const CRTManager &_other)
		: m_Manager(_other.m_Manager)
	{}
	CRTManager(const std::initializer_list<std::pair<T_Key, T_Value>> &_Values)
		: m_Manager(_Values.begin(), _Values.end())
	{}
	~CRTManager()
	{}

private:
	std::unordered_map<T_Key, T_Value> m_Manager;

public:
	std::unordered_map<T_Key, T_Value> GetManager(void) const
	{
		return(m_Manager);
	}

	void SetManager(const std::unordered_map<T_Key, T_Value> &_Manager)
	{
		m_Manager = _Manager;
	}

public:
	T_Value& operator [] (const T_Key _Key)
	{
		return(m_Manager[_Key]);
	}

	const T_Value& operator [] (const T_Key _Key) const
	{
		return(m_Manager.at(_Key));
	}

	std::vector<T_Key> Keys(void) const
	{
		std::vector<T_Key> keys;
		keys.reserve(m_Manager.size());

		for (auto item = m_Manager.begin(); item != m_Manager.end(); ++item)
		{
			const auto pair = *item;

			keys.push_back(pair.first);
		}

		return(keys);
	}

	std::vector<T_Value> Values(void) const
	{
		std::vector<T_Value> values;
		values.reserve(m_Manager.size());

		for (auto item = m_Manager.begin(); item != m_Manager.end(); ++item)
		{
			const auto pair = *item;

			values.push_back(pair.second);
		}

		return(values);
	}

	bool IsEmpty(void) const
	{
		return(m_Manager.empty());
	}

	bool HasKey(const T_Key _Key) const
	{
		const auto item = m_Manager.find(_Key);

		if (m_Manager.end() == item)
		{
			return(false);
		}

		return(true);
	}

	void DeleteTarget(const T_Key _Key)
	{
		m_Manager.erase(_Key);
	}

	void Clear(void)
	{
		m_Manager.clear();
	}

	int Size(void) const
	{
		return(m_Manager.size());
	}
};


#endif//__RTMANAGER_H__

