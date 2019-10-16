#ifndef __RTDBREPLAY_H__
#define __RTDBREPLAY_H__


#include "RTDBBase.h"


class CRTDBReplay : public CRTDBBase
{
public:
	CRTDBReplay();
	CRTDBReplay(const CRTDBReplay &_other);
	~CRTDBReplay();

private:
	int m_ID;
	std::string m_TimeStamp;
	int m_PackageID;
	int m_MasterStyle;
	int m_MasterID;
	int m_SlaveStyle;
	int m_SlaveID;
	int m_FunctorStyle;
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

	int GetPackageID(void) const;
	void SetPackageID(const int _PackageID);

	int GetMasterStyle(void) const;
	void SetMasterStyle(const int _MasterStyle);

	int GetMasterID(void) const;
	void SetMasterID(const int _MasterID);

	int GetSlaveStyle(void) const;
	void SetSlaveStyle(const int _SlaveStyle);

	int GetSlaveID(void) const;
	void SetSlaveID(const int _SlaveID);

	int GetFunctorStyle(void) const;
	void SetFunctorStyle(const int _FunctorStyle);

	int GetStateID(void) const;
	void SetStateID(const int _StateID);
};


#endif//__RTDBREPLAY_H__

