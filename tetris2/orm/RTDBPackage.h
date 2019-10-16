#ifndef __RTDBPACKAGE_H__
#define __RTDBPACKAGE_H__


#include "RTDBBase.h"


class CRTDBPackage : public CRTDBBase
{
public:
	CRTDBPackage();
	CRTDBPackage(const CRTDBPackage &_other);
	~CRTDBPackage();

private:
	int m_ID;
	std::string m_TimeStamp;
	std::string m_IP;
	std::string m_Mail;
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

	std::string GetIP(void) const;
	void SetIP(const std::string _IP);

	std::string GetMail(void) const;
	void SetMail(const std::string _Mail);

	int GetStateID(void) const;
	void SetStateID(const int _StateID);
};


#endif//__RTDBPACKAGE_H__

