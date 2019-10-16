#ifndef __RTVALUE_H__
#define __RTVALUE_H__


#include <string>
#include <vector>
#include "RTValueStyle.h"


class CRTDict;


class CRTValue
{
public:
	CRTValue();
	CRTValue(const CRTValue &_other);
	~CRTValue();

public:
	template<class T>
	CRTValue(const T _other)
		: CRTValue()
	{
		*this = _other;
	}

private:
	void* m_pTarget;
	RTValueStyle_t m_ValueStyle;

public:
	RTValueStyle_t GetValueStyle(void) const;
private:
	void SetValueStyle(const RTValueStyle_t &_ValueStyle);

	void NoSurpport(const std::string _Msg);

public:
	void DeleteTargetPointer(void);

	CRTValue& operator = (const CRTValue& _other);

	CRTValue& operator = (const int _other);
	CRTValue& operator = (const unsigned int _other);
	CRTValue& operator = (const double _other);
	CRTValue& operator = (const char* _other);
	CRTValue& operator = (const std::string _other);
	CRTValue& operator = (const CRTDict& _other);

	CRTValue& operator = (const std::vector<int>& _other);
	CRTValue& operator = (const std::vector<unsigned int>& _other);
	CRTValue& operator = (const std::vector<double>& _other);
	CRTValue& operator = (const std::vector<std::string>& _other);
	CRTValue& operator = (const std::vector<CRTDict>& _other);

public:
	int GetInt(void) const;
	unsigned int GetUInt(void) const;
	double GetDouble(void) const;
	std::string GetString(void) const;
	CRTDict GetDict(void) const;

	std::vector<int> GetVectorInt(void) const;
	std::vector<unsigned int> GetVectorUInt(void) const;
	std::vector<double> GetVectorDouble(void) const;
	std::vector<std::string> GetVectorString(void) const;
	std::vector<CRTDict> GetVectorDict(void) const;
};


#endif//__RTVALUE_H__

