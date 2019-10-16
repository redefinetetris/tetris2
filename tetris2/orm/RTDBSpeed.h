#ifndef __RTDBSPEED_H__
#define __RTDBSPEED_H__


#include "RTDBBase.h"


class CRTDBSpeed : public CRTDBBase
{
public:
	CRTDBSpeed();
	CRTDBSpeed(const CRTDBSpeed &_other);
	~CRTDBSpeed();

private:
	int m_ID;
	std::string m_TimeStamp;
	int m_MicroSecond;
	int m_StateID;


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

	std::string GetTimeStamp(void) const;
	void SetTimeStamp(const std::string _TimeStamp);

	int GetMicroSecond(void) const;
	void SetMicroSecond(const int _MicroSecond);

	int GetStateID(void) const;
	void SetStateID(const int _StateID);
};


#endif//__RTDBSPEED_H__

