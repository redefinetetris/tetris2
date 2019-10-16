#ifndef __RTDICT_H__
#define __RTDICT_H__


#include "RTValue.h"
#include "RTManager.h"


class CRTDict
{
public:
	CRTDict();
	CRTDict(const std::initializer_list<std::pair<std::string, CRTValue>> &_Values);
	CRTDict(const CRTDict &_other);
	~CRTDict();

private:
	CRTManager<std::string, CRTValue> m_Container;

public:
	CRTValue& operator [] (const std::string _Key);
	const CRTValue& operator [] (const std::string _Key) const;

	std::vector<std::string> Keys(void) const;
	bool IsEmpty(void) const;
	bool HasKey(const std::string _Key) const;
	void DeleteTarget(const std::string _Key);
};


#endif//__RTDICT_H__

