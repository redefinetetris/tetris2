#ifndef __TOOL_H__
#define __TOOL_H__


#include <string>
#include <vector>
#include <memory>


class CRTDict;


namespace NSTool {
	int string2int(const std::string _str);
	std::string int2string(const int _val);


	long long string2longlong(const std::string _str);
	std::string longlong2string(const long long _val);


	double string2double(const std::string _str);
	std::string double2string(const double _val);


	CRTDict string2dict(const std::string _str);
	std::string dict2string(const CRTDict& _dict);


	std::vector<int> string2vector(const std::string& _block);
	std::string vector2string(const std::vector<int>& _vect);

}//NSTool


#endif

