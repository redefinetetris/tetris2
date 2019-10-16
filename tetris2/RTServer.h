#ifndef __RTSERVER_H__
#define __RTSERVER_H__


#include "RTBase.h"
#include "RTIPStyle.h"
#include "winsock2.h"
#include "ws2tcpip.h"
#pragma comment(lib, "ws2_32.lib")


class CRTServer : public CRTBase
{
public:
	CRTServer(const int _Threads = 8, const char *_Port = "60000");
	~CRTServer();

private:
	const char* m_Port;
	SOCKET m_SocketV4;
	SOCKET m_SocketV6;
	addrinfo* m_pResultV4;
	addrinfo* m_pResultV6;

private:
	int Init(SOCKET &_Socket, const char *_Port, addrinfo* &_pResult, const int family = AF_INET, const int socktype = SOCK_DGRAM, const int protocol = IPPROTO_UDP, const int flags = AI_PASSIVE);
	int Worker(const int _Threads);

private:
	void Recv(void);
	int Reader(SOCKET _Socket, addrinfo *_pResult, const RTIPStyle_t _IPStyle);

private:
	int PowerTrail(void) const;
	int PowerCNDB(void) const;

public:
	int Send(void);
};


#endif//__RTSERVER_H__

