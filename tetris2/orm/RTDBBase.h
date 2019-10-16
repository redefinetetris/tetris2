#ifndef __RTDBBASE_H__
#define __RTDBBASE_H__


#include <string>
#include <vector>
#include <atomic>
#include "../RTDict.h"
#include "RTDBObjectStyle.h"


class CRTDBBase
{
public:
	CRTDBBase(const std::string _TableName, const int _LengthPerLine, const int _TTL = 1, const unsigned int _ObjStyle = 0);
	CRTDBBase(const CRTDBBase &_other);
	~CRTDBBase();

private:
	const std::string m_TableName;
	const int m_LengthPerLine;
	int m_TTL;
	std::atomic<unsigned int> m_ObjStyle;

public:
	std::string GetTableName(void) const;
	std::string GetDBName(void) const;
	
	int GetLengthPerLine(void) const;

	int GetTTL(void) const;
	void UpTTL(const int _TTL = 1);

	unsigned int GetAllObjStyle(void) const;
	void SetAllObjStyle(const unsigned int _ObjStyle);
	void ClearAllObjStyle(const unsigned int _ObjStyle);
	bool GetObjStyle(const RTDBObjectStyle_t _ObjStyle) const;
	void SetObjStyle(const RTDBObjectStyle_t _ObjStyle);

public:
	virtual int GetIndex(void) const;
	virtual int GetColumnSize(void) const;

	virtual CRTDict GetColumnValue(void) const;
	virtual std::vector<std::string> GetAllColumn(void) const;
	virtual std::vector<std::string> GetAllValue(void) const;
	virtual void SetAllValue(const std::vector<std::string>& _Values);
};


#endif//__RTDBBASE_H__

