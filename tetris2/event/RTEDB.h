#ifndef __RTEDB_H__
#define __RTEDB_H__


#include "RTEBase.h"


class CRTEDB : public CRTEBase
{
public:
	CRTEDB();
	CRTEDB(const CRTEDB &_other);
	~CRTEDB();

private:
	friend class CDBTimer;
	friend class CDBFire;
	friend class CDBFlush;
	friend class CDBDownTTL;
	friend class CDBWashTTL;

public:
	virtual int Power(void);
	virtual int DoMail(void);
};


#endif//__RTEDB_H__

