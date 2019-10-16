#include "RTNSNet.h"
#include "ws2tcpip.h"
#include "RTNSTool.h"


namespace RTNSNet
{
	namespace RTNSKeep
	{
		std::string GetIPV4(unsigned char* _pIP)
		{
			std::string ip;
			char chSign = '.';
			const int Length = 4;

			for (int index = 0; index < Length; ++index)
			{
				const auto num = _pIP[index];

				ip += chSign + RTNSTool::int2string(num);
			}

			return(ip.substr(1));
		}


		std::string GetIPV6(unsigned short* _pIP)
		{
			std::string ip;
			char chSign = ':';
			const int Length = 8;

			for (int index = 0; index < Length; ++index)
			{
				const auto num = _pIP[index];

				ip += chSign + RTNSTool::int2hexstring(num);
			}

			return(ip.substr(1));
		}
	}//RTNSKeep


	std::string GetIP(sockaddr* _pAddr)
	{
		const auto family = _pAddr->sa_family;

		if (AF_INET == family)
		{
			auto pAddrIn = (sockaddr_in *)_pAddr;

			return(RTNSKeep::GetIPV4((unsigned char *)&(pAddrIn->sin_addr)));
		}

		auto pAddrIn = (sockaddr_in6 *)_pAddr;

		return(RTNSKeep::GetIPV6((unsigned short *)&(pAddrIn->sin6_addr)));
	}


	std::string GetPort(sockaddr* _pAddr)
	{
		const auto family = _pAddr->sa_family;
		int port = 0;

		if (AF_INET == family)
		{
			auto pAddrIn = (sockaddr_in *)_pAddr;
			port = pAddrIn->sin_port;
		}
		else
		{
			auto pAddrIn = (sockaddr_in6 *)_pAddr;
			port = pAddrIn->sin6_port;
		}

		return(RTNSTool::int2string(port));
	}
}//RTNSNet

