#ifndef __RTRECVSENDBUFFER_H__
#define __RTRECVSENDBUFFER_H__


#include <mutex>
#include "RTBase.h"
#include "RTMail.h"
#include "RTBuffer.h"
#include "RTBufferSimple.h"


class CRTRecvSendBuffer : public CRTBase
{
public:
	CRTRecvSendBuffer();
	CRTRecvSendBuffer(const CRTRecvSendBuffer &_other);
	~CRTRecvSendBuffer();

protected:
	std::mutex m_Mutex;

public:
	CRTBuffer<std::shared_ptr<CRTMail>> m_RecvBuffer;
	CRTBuffer<std::shared_ptr<CRTMail>> m_SendBuffer;
protected:
	CRTBufferSimple<std::shared_ptr<CRTMail>> m_PrivateBuffer;

protected:
	void NewPrivateMail(const std::shared_ptr<CRTMail> & _Mail);
	void NewPrivateMail(const std::vector<std::shared_ptr<CRTMail>> & _Mails);
};


#endif//__RTRECVSENDBUFFER_H__

