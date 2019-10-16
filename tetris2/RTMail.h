#ifndef __RTMAIL_H__
#define __RTMAIL_H__


#include <string>
#include "RTDict.h"
#include "RTBase.h"
#include "RTIPStyle.h"
#include "RTDataType.h"
#include "RTHealthStyle.h"


class CRTBase;


class CRTMail : public CRTBase
{
public:
	CRTMail();
	CRTMail(CRTBase* _pMaster);
	CRTMail(const RTIPStyle_t _IPStyle);
	CRTMail(const std::string _Text);
	CRTMail(const std::string _IP, const std::string _Text);
	CRTMail(const RTIPStyle_t _IPStyle, const char _IPAddr[], const std::string _Text);
	CRTMail(const CRTMail &_other);
	~CRTMail();

private:
	CRTBase* m_pMaster;

public:
	CRTBase* GetMaster(void) const;

private:
	RTIPStyle_t m_IPStyle;
	char m_IPAddr[IP_ADDR_SIZE];
	std::string m_Text;

public:
	RTIPStyle_t GetIPStyle(void) const;
	void SetIPStyle(const RTIPStyle_t &_IPStyle);

	char* GetIPAddr(void) const;
	void SetIPAddr(const char _IPAddr[]);
	std::string GetIPString(void) const;

	std::string GetText(void) const;
	void SetText(const std::string &_Text);

	CRTDict GetDict(void) const;
	void SetDict(const CRTDict &_Dict);

public:
	bool IPOK(void) const;
	bool IPV4Style(void) const;
	void CopyNetInfo(const CRTMail& _other);
};


#endif//__RTMAIL_H__

