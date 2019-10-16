#include "RTServer.h"
#include <thread>
#include "RTDict.h"
#include "RTMail.h"
#include "RTNSDB.h"
#include "RTNSLog.h"
#include "RTNSTool.h"
#include "RTEStatic.h"
#include "RTCurrent.h"
#include "RTNSStatic.h"
#include "RTDataType.h"


CRTServer::CRTServer(const int _Threads, const char *_Port)
	: CRTBase()
	, m_Port(_Port)
	, m_SocketV4(INVALID_SOCKET)
	, m_SocketV6(INVALID_SOCKET)
	, m_pResultV4(nullptr)
	, m_pResultV6(nullptr)
{
	CMMaster Master(this);

	const auto codeV4 = this->Init(m_SocketV4, m_Port, m_pResultV4);
	const auto codeV6 = this->Init(m_SocketV6, m_Port, m_pResultV6, AF_INET6);

	if (0 != codeV4 || 0 != codeV6)
	{
		LogError("init socket v4 & v6 fail");
		return;
	}

	RTNSStatic::SetServer(this);

	this->Worker(_Threads);

	const auto codeCNDB = this->PowerCNDB();
	if (0 != codeCNDB)
	{
		LogError("power cndb fail");
		return;
	}

	const auto codeTrail = this->PowerTrail();
	if (0 != codeTrail)
	{
		LogError("power trail fail");
		return;
	}

	this->Recv();
}


CRTServer::~CRTServer()
{
}


int CRTServer::Init(SOCKET &_Socket, const char *_Port, addrinfo* &_pResult, const int family, const int socktype, const int protocol, const int flags)
{
	WSADATA wsadata;
	WORD version = MAKEWORD(2, 2);

	const auto codeVersion = WSAStartup(version, &wsadata);
	if (NO_ERROR != codeVersion)
	{
		return(-1);
	}

	addrinfo hint;
	memset(&hint, 0, sizeof(addrinfo));
	hint.ai_family = family;
	hint.ai_socktype = socktype;
	hint.ai_protocol = protocol;
	hint.ai_flags = flags;

	const auto codeAddrInfo = getaddrinfo(nullptr, _Port, &hint, &_pResult);
	if (NO_ERROR != codeAddrInfo)
	{
		return(-2);
	}

	_Socket = socket(_pResult->ai_family, _pResult->ai_socktype, _pResult->ai_protocol);
	if (INVALID_SOCKET == _Socket)
	{
		return(-3);
	}

	const auto codeBind = bind(_Socket, _pResult->ai_addr, _pResult->ai_addrlen);
	if (SOCKET_ERROR == codeBind)
	{
		return(-4);
	}

	return(0);
}


int CRTServer::Worker(const int _Threads)
{
	const int keep = 3;

	RTNSStatic::SetWorkThreaderSize(_Threads - keep);

	for (int id = keep; id < _Threads; ++id)
	{
		std::thread worker(RTNSStatic::ThreadEventFun);

		worker.detach();
	}

	//定时器专用线程
	std::thread clocker(RTNSStatic::ThreadClockFun);
	clocker.detach();

	//邮件路由专用线程
	std::thread huber(RTNSStatic::ThreadHubFun);
	huber.detach();

	return(0);
}


void CRTServer::Recv(void)
{
	static auto& _ServerRTEHub = GetRTEHub();
	const int seconds = 1;
	const int microseconds = 0;
	const struct timeval _timeout {
		seconds, microseconds
	};
	fd_set readfds;

	//网络包接收专用线程
	while (RTNSStatic::Power())
	{
		FD_ZERO(&readfds);
		FD_SET(m_SocketV4, &readfds);
		FD_SET(m_SocketV6, &readfds);

		const auto code = select(0, &readfds, nullptr, nullptr, &_timeout);
		if (code < 1)
		{
			_ServerRTEHub.m_RecvBuffer.FlushWriter();

			continue;
		}

		if (FD_ISSET(m_SocketV4, &readfds))
		{
			this->Reader(m_SocketV4, m_pResultV4, RTIP_V4);
		}
		else// if (FD_ISSET(m_SocketV6, &readfds))
		{
			this->Reader(m_SocketV6, m_pResultV6, RTIP_V6);
		}

		RTNSStatic::WakeHubThreader();
	}//while
}


int CRTServer::Reader(SOCKET _Socket, addrinfo *_pResult, const RTIPStyle_t _IPStyle)
{
	static auto& _ServerRTEHub = GetRTEHub();
	static char _ServerAddrRemote[IP_ADDR_SIZE] = { 0 };
	static char _ServerChsBuffer[SOCKET_BUFFER_SIZE] = { 0 };

	int arLength = _pResult->ai_addrlen;
	memset(_ServerAddrRemote, '\0', IP_ADDR_SIZE);
	memset(_ServerChsBuffer, '\0', SOCKET_BUFFER_SIZE);

	const auto code = recvfrom(_Socket, _ServerChsBuffer, SOCKET_BUFFER_SIZE, 0, (sockaddr *)_ServerAddrRemote, &arLength);

	if (SOCKET_ERROR == code)
	{
		return(-1);
	}

	auto pMail = RTNSTool::NewMail();
	if (nullptr == pMail)
	{
		LogError("server new mail space fail");
		return(-2);
	}

	pMail->SetIPStyle(_IPStyle);
	pMail->SetIPAddr(_ServerAddrRemote);
	pMail->SetText(_ServerChsBuffer);

	_ServerRTEHub.m_RecvBuffer.Writer(pMail);

	return(0);
}


int CRTServer::PowerTrail(void) const
{
	auto pMail = RTNSTool::GetMailByTrail(RTNSDB::DefaultDBRootID());
	if (nullptr == pMail)
	{
		return(-1);
	}

	auto& RTEHub = GetRTEHub();
	RTEHub.m_RecvBuffer.Writer(pMail);

	RTNSStatic::WakeHubThreader();

	return(0);
}


int CRTServer::PowerCNDB(void) const
{
	auto pMail = RTNSTool::NewMail();
	if (nullptr == pMail)
	{
		return(-1);
	}

	const std::vector<std::string> Ops{ "db", "fire" };
	const CRTDict Args{
		{ "op", "new" },
	};
	const CRTDict dict{
		{ "ops", Ops },
		{ "args", Args },
		{ "id", RTNSTool::GetBackDictID() },
	};

	pMail->SetDict(dict);

	auto& RTEHub = GetRTEHub();
	RTEHub.m_RecvBuffer.Writer(pMail);

	RTNSStatic::WakeHubThreader();

	return(0);
}


int CRTServer::Send(void)
{
	int work = 0;
	auto& RTEHub = GetRTEHub();
	std::vector<std::shared_ptr<CRTMail>> Mails;
	Mails.reserve(VECTOR_RESERVE_SIZE);

	const auto ok = RTEHub.m_SendBuffer.Reader(Mails);
	if (!ok)
	{
		return(work);
	}

	for (auto item = Mails.begin(); item != Mails.end(); ++item)
	{
		++work;

		const auto pMail = *item;
		const auto msg = pMail->GetText();
		//PrintLogInfo(msg);
		//LogInfo(msg);
		const auto pChars = msg.c_str();
		const auto chsLength = strlen(pChars);

		const auto remoteSocket = (sockaddr *)pMail->GetIPAddr();

		switch (pMail->GetIPStyle())
		{
		case RTIP_V4: sendto(m_SocketV4, pChars, chsLength, 0, remoteSocket, m_pResultV4->ai_addrlen); break;
		case RTIP_V6: sendto(m_SocketV6, pChars, chsLength, 0, remoteSocket, m_pResultV6->ai_addrlen); break;
		default: break;
		}
	}//for

	return(work);
}

