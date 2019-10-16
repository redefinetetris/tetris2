#ifndef __RTDBSTATE_H__
#define __RTDBSTATE_H__


#include "RTDBBase.h"


class CRTDBState : public CRTDBBase
{
public:
	CRTDBState();
	CRTDBState(const CRTDBState &_other);
	~CRTDBState();

private:
	int m_ID;
	std::string m_Name;
	std::string m_LangName;


public:
	virtual int GetIndex(void) const;
	virtual int GetColumnSize(void) const;

	virtual CRTDict GetColumnValue(void) const;
	virtual std::vector<std::string> GetAllColumn(void) const;
	virtual std::vector<std::string> GetAllValue(void) const;
	virtual void SetAllValue(const std::vector<std::string>& _Values);

public:
	int GetID(void) const;
	void SetID(const int _ID);

	std::string GetName(void) const;
	void SetName(const std::string _Name);

	std::string GetLangName(void) const;
	void SetLangName(const std::string _LangName);
};


#endif//__RTDBSTATE_H__

