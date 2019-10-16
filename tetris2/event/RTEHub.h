#ifndef __RTEHUB_H__
#define __RTEHUB_H__


#include "RTEBase.h"


class CRTEHub : public CRTEBase
{
public:
	CRTEHub();
	CRTEHub(const CRTEHub &_other);
	~CRTEHub();

public:
	int operator () ();
	virtual int Power(void);

private:
	virtual int SelfRun(void);
	virtual int DoMail(void);

private:
	int Sender(void);
	int Mailer(void);

	int NoGameR(void);
	int GameR(void);

	std::vector<std::shared_ptr<CRTMail>> NoGameM(void);
	std::vector<std::shared_ptr<CRTMail>> GameM(void);
	int GuardM(const std::vector<std::shared_ptr<CRTMail>>& _Mails);

private:
	int FlushWriter(void);
};


#endif//__RTEHUB_H__

