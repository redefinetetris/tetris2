#include "RTMail.h"
#include "RTNSNet.h"
#include "RTNSTool.h"


CRTMail::CRTMail()
	: CRTMail(RTIP_Unknown)
{
}


CRTMail::CRTMail(CRTBase* _pMaster)
	: CRTBase()
	, m_pMaster(_pMaster)
	, m_IPStyle(RTIP_Unknown)
	, m_IPAddr{ '\0' }
	, m_Text()
{
}


CRTMail::CRTMail(const RTIPStyle_t _IPStyle)
	: CRTBase()
	, m_pMaster(nullptr)
	, m_IPStyle(_IPStyle)
	, m_IPAddr{ '\0' }
	, m_Text()
{
}


CRTMail::CRTMail(const std::string _Text)
	: CRTMail()
{
	this->SetText(_Text);
}


CRTMail::CRTMail(const std::string _IP, const std::string _Text)
	: CRTMail(_Text)
{
	const auto Length = _IP.size();

	if (0 == Length)
	{
		return;
	}

	if (Length < 16)//255.255.255.255
	{
		m_IPStyle = RTIP_V4;
	}
	else
	{
		m_IPStyle = RTIP_V6;
	}

	m_IPAddr;
}


CRTMail::CRTMail(const RTIPStyle_t _IPStyle, const char _IPAddr[], const std::string _Text)
	: CRTMail(_Text)
{
	m_IPStyle = _IPStyle;
	memcpy(m_IPAddr, _IPAddr, IP_ADDR_SIZE);
}


CRTMail::CRTMail(const CRTMail &_other)
	: CRTBase()
	, m_IPStyle(_other.m_IPStyle)
	, m_IPAddr{ '\0' }
	, m_Text(_other.m_Text)
{
	memcpy(m_IPAddr, _other.m_IPAddr, IP_ADDR_SIZE);
}


CRTMail::~CRTMail()
{
}


CRTBase* CRTMail::GetMaster(void) const
{
	return(m_pMaster);
}


RTIPStyle_t CRTMail::GetIPStyle(void) const
{
	return(m_IPStyle);
}


void CRTMail::SetIPStyle(const RTIPStyle_t &_IPStyle)
{
	m_IPStyle = _IPStyle;
}


char* CRTMail::GetIPAddr(void) const
{
	return((char*)m_IPAddr);
}


void CRTMail::SetIPAddr(const char _IPAddr[])
{
	memcpy(m_IPAddr, _IPAddr, IP_ADDR_SIZE);
}


std::string CRTMail::GetIPString(void) const
{
	const auto ip = RTNSNet::GetIP((sockaddr *)m_IPAddr);
	const auto port = RTNSNet::GetPort((sockaddr *)m_IPAddr);

	return(ip + ":" + port);
}


std::string CRTMail::GetText(void) const
{
	return(m_Text);
}


void CRTMail::SetText(const std::string &_Text)
{
	m_Text = _Text;
}


CRTDict CRTMail::GetDict(void) const
{
	return(RTNSTool::string2dict(m_Text));
}


void CRTMail::SetDict(const CRTDict &_Dict)
{
	m_Text = RTNSTool::dict2string(_Dict);
}


bool CRTMail::IPOK(void) const
{
	if (RTIP_Unknown != m_IPStyle)
	{
		return(true);
	}

	return(false);
}


bool CRTMail::IPV4Style(void) const
{
	if (RTIP_V4 == m_IPStyle)
	{
		return(true);
	}

	return(false);
}


void CRTMail::CopyNetInfo(const CRTMail& _other)
{
	m_IPStyle = _other.m_IPStyle;
	memcpy(m_IPAddr, _other.m_IPAddr, IP_ADDR_SIZE);
}

