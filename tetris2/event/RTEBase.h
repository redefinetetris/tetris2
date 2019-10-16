#ifndef __RTEBASE_H__
#define __RTEBASE_H__


#include "RTEStyle.h"
#include "../RTMask.h"
#include "../RTCurrent.h"
#include "../RTRecvSendBuffer.h"


class CRTEBase : public CRTRecvSendBuffer, public CRTMask
{
public:
	CRTEBase(const RTEStyle_t _RTEStyle);
	CRTEBase(const CRTEBase &_other);
	~CRTEBase();

private:
	CRTEBase* m_pParent;
	const RTEStyle_t m_RTEStyle;

public:
	CRTEBase* GetParent(void) const;
	void SetParent(CRTEBase* _pParent);

	RTEStyle_t GetRTEStyle(void) const;

public:
	virtual int Power(void);

	virtual int RunLocker(const bool _OnlyOneMail = false);
	virtual int RunSelfLocker(void);

	virtual int Run(const bool _OnlyOneMail = false);
	virtual int SelfRun(void);

protected:
	virtual int MailsRun(const bool _OnlyOneMail = false);
	virtual int PreMails(void);
	virtual int PostMails(void);

	virtual int PreDoMail(void);
	virtual int DoMail(void);
	virtual int PostDoMail(void);
};


#endif//__RTEBASE_H__

