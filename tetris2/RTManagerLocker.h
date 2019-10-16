#ifndef __RTMANAGERLOCKER_H__
#define __RTMANAGERLOCKER_H__


#include <mutex>
#include <unordered_map>
#include <initializer_list>


template<class T_Key, class T_Value>
class CRTManagerLocker
{
public:
	CRTManagerLocker()
		: m_Manager()
	{}
	CRTManagerLocker(const std::unordered_map<T_Key, T_Value> &_Manager)
		: m_Manager(_Manager)
	{}
	CRTManagerLocker(const CRTManagerLocker &_other)
		: m_Manager(_other.m_Manager)
	{}
	CRTManagerLocker(const std::initializer_list<std::pair<T_Key, T_Value>> &_Values)
		: m_Manager(_Values.begin(), _Values.end())
	{}
	~CRTManagerLocker()
	{}

private:
	std::unordered_map<T_Key, T_Value> m_Manager;
	std::mutex m_Mutex;

public:
	std::unordered_map<T_Key, T_Value> GetManager(void) const
	{
		std::unique_lock<std::mutex> locker(m_Mutex);

		return(m_Manager);
	}

	void SetManager(const std::unordered_map<T_Key, T_Value> &_Manager)
	{
		std::unique_lock<std::mutex> locker(m_Mutex);

		m_Manager = _Manager;
	}

public:
	T_Value& operator [] (const T_Key _Key)
	{
		std::unique_lock<std::mutex> locker(m_Mutex);

		return(m_Manager[_Key]);
	}

	const T_Value& operator [] (const T_Key _Key) const
	{
		std::unique_lock<std::mutex> locker(m_Mutex);

		return(m_Manager.at(_Key));
	}

	std::vector<T_Key> Keys(void)
	{
		std::unique_lock<std::mutex> locker(m_Mutex);

		std::vector<T_Key> keys;
		keys.reserve(m_Manager.size());

		for (auto item = m_Manager.begin(); item != m_Manager.end(); ++item)
		{
			const auto pair = *item;

			keys.push_back(pair.first);
		}

		return(keys);
	}

	std::vector<T_Value> Values(void)
	{
		std::unique_lock<std::mutex> locker(m_Mutex);

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
		std::unique_lock<std::mutex> locker(m_Mutex);

		return(m_Manager.empty());
	}

	bool HasKey(const T_Key _Key) const
	{
		std::unique_lock<std::mutex> locker(m_Mutex);

		const auto item = m_Manager.find(_Key);

		if (m_Manager.end() == item)
		{
			return(false);
		}

		return(true);
	}

	void DeleteTarget(const T_Key _Key)
	{
		std::unique_lock<std::mutex> locker(m_Mutex);

		m_Manager.erase(_Key);
	}

	void Clear(void)
	{
		std::unique_lock<std::mutex> locker(m_Mutex);

		m_Manager.clear();
	}

	int Size(void)
	{
		std::unique_lock<std::mutex> locker(m_Mutex);

		return(m_Manager.size());
	}

public:
	void Lock(void)
	{
		m_Mutex.lock();
	}

	bool TryLock(void)
	{
		return(m_Mutex.try_lock());
	}

	void UnLock(void)
	{
		m_Mutex.unlock();
	}
};


#endif//__RTMANAGERLOCKER_H__

