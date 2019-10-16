#ifndef __RTBASE_H__
#define __RTBASE_H__


#include <string>
#include <atomic>
#include "RTHealthStyle.h"


class CRTBase
{
public:
	CRTBase();
	CRTBase(const CRTBase &_other);
	~CRTBase();

private:
	std::atomic<RTHealthStyle_t> m_Health;
	std::atomic<RTHealthStyle_t> m_BackUpHealth;
	std::atomic<int> m_SelfID;

public:
	bool GetHealth(const RTHealthStyle_t _Style) const;
	RTHealthStyle_t GetHealth(void) const;
	void SetHealth(const RTHealthStyle_t &_Health);

	RTHealthStyle_t GetBackUpHealth(void) const;
	void SetBackUpHealth(const RTHealthStyle_t &_BackUpHealth);

	void BackUpHealth(void);
	void RecoverHealth(void);

	int GetSelfID(void) const;
	void SetSelfID(const int &_SelfID);
};


#endif//__RTBASE_H__

