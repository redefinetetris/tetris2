#ifndef __RTDBTRANSFER_H__
#define __RTDBTRANSFER_H__


#include "RTDBBase.h"


class CRTDBTransfer : public CRTDBBase
{
public:
	CRTDBTransfer();
	CRTDBTransfer(const CRTDBTransfer &_other);
	~CRTDBTransfer();

private:
	int m_ID;
	std::string m_TimeStamp;
	int m_BlockID;
	int m_NextID;
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

	int GetBlockID(void) const;
	void SetBlockID(const int _BlockID);

	int GetNextID(void) const;
	void SetNextID(const int _NextID);

	int GetStateID(void) const;
	void SetStateID(const int _StateID);
};


#endif//__RTDBTRANSFER_H__

