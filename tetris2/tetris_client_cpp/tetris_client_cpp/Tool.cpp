#include "Tool.h"
#include "json.h"
#include "RTDict.h"


#define ENCRYPT_BUFFER (4096)


namespace NSTool {
	int string2int(const std::string _str)
	{
		std::istringstream iss(_str);
		int result = 0;

		iss >> result;

		return(result);
	}


	std::string int2string(const int _val)
	{
		return(std::to_string(_val));
	}


	long long string2longlong(const std::string _str)
	{
		std::istringstream iss(_str);
		long long result = 0;

		iss >> result;

		return(result);
	}


	std::string longlong2string(const long long _val)
	{
		return(std::to_string(_val));
	}


	double string2double(const std::string _str)
	{
		std::istringstream iss(_str);
		double result = 0;

		iss >> result;

		return(result);
	}


	std::string double2string(const double _val)
	{
		return(std::to_string(_val));
	}


	void NoSurpport(void)
	{
		;
	}


	void array2dict(const std::string& _key, const Json::Value& _value, CRTDict& _dict)
	{
		const int sz = _value.size();
		if (!sz)
		{
			return;
		}

		const auto type = _value[0].type();

		if (Json::ValueType::intValue == type)
		{
			std::vector<int> result;
			for (int index = 0; index < sz; ++index)
			{
				result.push_back(_value[index].asInt());
			}
			_dict[_key] = result;
		}
		else if (Json::ValueType::realValue == type)
		{
			std::vector<double> result;
			for (int index = 0; index < sz; ++index)
			{
				result.push_back(_value[index].asDouble());
			}
			_dict[_key] = result;
		}
		else if (Json::ValueType::stringValue == type)
		{
			std::vector<std::string> result;
			for (int index = 0; index < sz; ++index)
			{
				result.push_back(_value[index].asString());
			}
			_dict[_key] = result;
		}
	}


	extern CRTDict json2dict(const Json::Value& _json);

	void value2dict(const std::string& _key, const Json::Value& _value, CRTDict& _dict)
	{
		const auto type = _value.type();

		switch (type)
		{
		case Json::ValueType::intValue:		_dict[_key] = _value.asInt(); break;
		case Json::ValueType::realValue:	_dict[_key] = _value.asDouble(); break;
		case Json::ValueType::stringValue:	_dict[_key] = _value.asString(); break;
		case Json::ValueType::arrayValue:	array2dict(_key, _value, _dict); break;
		case Json::ValueType::objectValue:	_dict[_key] = json2dict(_value); break;
		default:							NoSurpport(); break;
		}
	}


	CRTDict json2dict(const Json::Value& _json)
	{
		CRTDict dict;
		const auto keys = _json.getMemberNames();

		for (auto item = keys.begin(); item != keys.end(); ++item)
		{
			const auto key = *item;
			const auto value = _json[key];

			value2dict(key, value, dict);
		}

		return(dict);
	}


	void array2json(const std::string& _key, const CRTValue& _value, Json::Value& _json)
	{
		int index = 0;
		Json::Value result;
		const auto type = _value.GetValueStyle();

		if (RTVS_vector_int == type)
		{
			const auto src = _value.GetVectorInt();

			for (auto item = src.begin(); item != src.end(); ++item)
			{
				result[index++] = *item;
			}
		}
		else if (RTVS_vector_double == type)
		{
			const auto src = _value.GetVectorDouble();

			for (auto item = src.begin(); item != src.end(); ++item)
			{
				result[index++] = *item;
			}
		}
		else if (RTVS_vector_string == type)
		{
			const auto src = _value.GetVectorString();

			for (auto item = src.begin(); item != src.end(); ++item)
			{
				result[index++] = *item;
			}
		}

		_json[_key] = result;
	}


	extern Json::Value dict2json(const CRTDict& _dict);

	void dict2value(const std::string& _key, const CRTValue& _value, Json::Value &_json)
	{
		const auto type = _value.GetValueStyle();

		switch (type)
		{
		case RTVS_int:			_json[_key] = _value.GetInt(); break;
		case RTVS_double:			_json[_key] = _value.GetDouble(); break;
		case RTVS_string:			_json[_key] = _value.GetString(); break;
		case RTVS_vector_int:
		case RTVS_vector_double:
		case RTVS_vector_string:	array2json(_key, _value, _json); break;
		case RTVS_dict:			_json[_key] = dict2json(_value.GetDict()); break;
		default:				NoSurpport(); break;
		}
	}


	Json::Value dict2json(const CRTDict& _dict)
	{
		Json::Value json;
		const auto keys = _dict.Keys();

		for (auto item = keys.begin(); item != keys.end(); ++item)
		{
			const auto key = *item;
			const auto value = _dict[key];

			dict2value(key, value, json);
		}

		return(json);
	}


	CRTDict string2dict(const std::string _str)
	{
		Json::CharReaderBuilder builder;
		std::unique_ptr<Json::CharReader> pRreader(builder.newCharReader());
		Json::Value json;
		auto begin = _str.c_str();
		auto end = begin + _str.length();

		const bool code = pRreader->parse(begin, end, &json, nullptr);

		if (code)
		{
			return(json2dict(json));
		}

		return(CRTDict());
	}


	std::string dict2string(const CRTDict& _dict)
	{
		Json::Value json = dict2json(_dict);

		return(json.toStyledString());
	}


	std::vector<int> string2vector(const std::string& _block)
	{
		std::vector<int> cells;

		for (auto item = _block.begin(); item != _block.end(); ++item)
		{
			const char ch = *item;
			const int cell = ch - '0';

			cells.push_back(cell);
		}

		return(cells);
	}


	std::string vector2string(const std::vector<int>& _vect)
	{
		std::string cells;

		for (auto item = _vect.begin(); item != _vect.end(); ++item)
		{
			cells += int2string(*item);
		}

		return(cells);
	}
}//NSTool

