#ifndef __RTNSKEEP_H__
#define __RTNSKEEP_H__


#include <string>


class CRTDict;


namespace RTNSTool
{
	namespace RTNSKeep
	{
		CRTDict string2dict(const std::string _Str);
		std::string dict2string(const CRTDict& _Dict);


		std::string ToBase64(const std::string _Str);
		std::string FromBase64(const std::string _StrBase64);


		std::string ToEncrypt(const std::string _Str, const std::string _Key);
		std::string FromEncrypt(const std::string _StrEncrypt, const std::string _Key);
	}//RTNSKeep
}//RTNSTool


#endif//__RTNSKEEP_H__

