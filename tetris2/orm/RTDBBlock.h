#ifndef __RTDBBLOCK_H__
#define __RTDBBLOCK_H__


#include "RTDBBase.h"


class CRTDBBlock : public CRTDBBase
{
public:
	CRTDBBlock();
	CRTDBBlock(const CRTDBBlock &_other);
	~CRTDBBlock();

private:
	int m_ID;
	std::string m_TimeStamp;
	int m_UserID;
	int m_GroupID;
	int m_Dimension;
	int m_Base;
	std::string m_Block;
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

	int GetUserID(void) const;
	void SetUserID(const int _UserID);

	int GetGroupID(void) const;
	void SetGroupID(const int _GroupID);

	int GetDimension(void) const;
	void SetDimension(const int _Dimension);

	int GetBase(void) const;
	void SetBase(const int _Base);

	std::string GetBlock(void) const;
	void SetBlock(const std::string _Block);

	int GetStateID(void) const;
	void SetStateID(const int _StateID);
};


#endif//__RTDBBLOCK_H__

