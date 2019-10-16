#include "RTRecvSendBuffer.h"
#include "../RTDataType.h"


CRTRecvSendBuffer::CRTRecvSendBuffer()
	: CRTBase()
	, m_Mutex()
	, m_RecvBuffer()
	, m_SendBuffer()
	, m_PrivateBuffer()
{
}


CRTRecvSendBuffer::CRTRecvSendBuffer(const CRTRecvSendBuffer &_other)
	: CRTBase(_other)
	, m_Mutex()
	, m_RecvBuffer()
	, m_SendBuffer()
	, m_PrivateBuffer()
{
}


CRTRecvSendBuffer::~CRTRecvSendBuffer()
{
}


void CRTRecvSendBuffer::NewPrivateMail(const std::shared_ptr<CRTMail> & _Mail)
{
	m_PrivateBuffer.Writer(_Mail);
}


void CRTRecvSendBuffer::NewPrivateMail(const std::vector<std::shared_ptr<CRTMail>> & _Mails)
{
	m_PrivateBuffer.Writer(_Mails);
}

