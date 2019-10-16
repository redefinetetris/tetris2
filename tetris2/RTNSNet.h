#ifndef __RTNSNET_H__
#define __RTNSNET_H__


#include <string>


struct sockaddr;


namespace RTNSNet
{
	std::string GetIP(sockaddr* _pAddr);
	std::string GetPort(sockaddr* _pAddr);
}//RTNSNet


#endif

