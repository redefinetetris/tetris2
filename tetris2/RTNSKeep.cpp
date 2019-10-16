#include "RTNSKeep.h"
#include <memory>
#include "json.h"
#include "base64.h"
#include "../RTDict.h"
#include "../RTNSLog.h"
#include "../RTDataType.h"


namespace RTNSTool
{
	namespace RTNSKeep
	{
		void NoSurpport(const std::string _Msg)
		{
			PrintLogInfo(_Msg);
			LogError(_Msg);
		}
	}//RTNSKeep


	namespace RTNSKeep
	{
		extern CRTDict json2dict(const Json::Value& _Json);


		void array2dict(const std::string& _Key, const Json::Value& _Value, CRTDict& _Dict)
		{
			const int sz = _Value.size();
			if (!sz)
			{
				return;
			}

			const auto type = _Value[0].type();

			if (Json::ValueType::intValue == type)
			{
				std::vector<int> Result;
				Result.reserve(sz);

				for (int index = 0; index < sz; ++index)
				{
					Result.push_back(_Value[index].asInt());
				}

				_Dict[_Key] = Result;
			}
			else if (Json::ValueType::uintValue == type)
			{
				std::vector<int> Result;
				Result.reserve(sz);

				for (int index = 0; index < sz; ++index)
				{
					Result.push_back(_Value[index].asUInt());
				}

				_Dict[_Key] = Result;
			}
			else if (Json::ValueType::realValue == type)
			{
				std::vector<double> Result;
				Result.reserve(sz);

				for (int index = 0; index < sz; ++index)
				{
					Result.push_back(_Value[index].asDouble());
				}

				_Dict[_Key] = Result;
			}
			else if (Json::ValueType::stringValue == type)
			{
				std::vector<std::string> Result;
				Result.reserve(sz);

				for (int index = 0; index < sz; ++index)
				{
					Result.push_back(_Value[index].asString());
				}

				_Dict[_Key] = Result;
			}
			else if (Json::ValueType::objectValue == type)
			{
				std::vector<CRTDict> Result;
				Result.reserve(sz);

				for (int index = 0; index < sz; ++index)
				{
					Result.push_back(json2dict(_Value[index]));
				}

				_Dict[_Key] = Result;
			}
			else
			{
				NoSurpport("json datatype error");
			}
		}


		void value2dict(const std::string& _Key, const Json::Value& _Value, CRTDict& _Dict)
		{
			const auto type = _Value.type();

			switch (type)
			{
			case Json::ValueType::intValue:		_Dict[_Key] = _Value.asInt(); break;
			case Json::ValueType::uintValue:	_Dict[_Key] = _Value.asUInt(); break;
			case Json::ValueType::realValue:	_Dict[_Key] = _Value.asDouble(); break;
			case Json::ValueType::stringValue:	_Dict[_Key] = _Value.asString(); break;
			case Json::ValueType::arrayValue:	array2dict(_Key, _Value, _Dict); break;
			case Json::ValueType::objectValue:	_Dict[_Key] = json2dict(_Value); break;
			default:							NoSurpport("json datatype error"); break;
			}//switch
		}


		CRTDict json2dict(const Json::Value& _Json)
		{
			CRTDict dict;
			const auto keys = _Json.getMemberNames();

			for (auto item = keys.begin(); item != keys.end(); ++item)
			{
				const auto key = *item;
				const auto value = _Json[key];

				value2dict(key, value, dict);
			}

			return(dict);
		}


		CRTDict string2dict(const std::string _Str)
		{
			Json::CharReaderBuilder builder;
			std::unique_ptr<Json::CharReader> pRreader(builder.newCharReader());
			Json::Value json;
			auto begin = _Str.c_str();
			auto end = begin + _Str.length();

			const auto code = pRreader->parse(begin, end, &json, nullptr);
			if (true == code)
			{
				return(json2dict(json));
			}

			return(CRTDict());
		}
	}//RTNSKeep


	namespace RTNSKeep
	{
		extern Json::Value dict2json(const CRTDict& _Dict);


		void array2json(const std::string& _Key, const CRTValue& _Value, Json::Value& _Json)
		{
			int index = -1;
			Json::Value json;
			const auto type = _Value.GetValueStyle();

			if (RTVS_vector_int == type)
			{
				const auto Result = _Value.GetVectorInt();

				for (auto item = Result.begin(); item != Result.end(); ++item)
				{
					json[++index] = *item;
				}
			}
			else if (RTVS_vector_unsigned_int == type)
			{
				const auto Result = _Value.GetVectorUInt();

				for (auto item = Result.begin(); item != Result.end(); ++item)
				{
					json[++index] = *item;
				}
			}
			else if (RTVS_vector_double == type)
			{
				const auto Result = _Value.GetVectorDouble();

				for (auto item = Result.begin(); item != Result.end(); ++item)
				{
					json[++index] = *item;
				}
			}
			else if (RTVS_vector_string == type)
			{
				const auto Result = _Value.GetVectorString();

				for (auto item = Result.begin(); item != Result.end(); ++item)
				{
					json[++index] = *item;
				}
			}
			else if (RTVS_vector_dict == type)
			{
				const auto Result = _Value.GetVectorDict();

				for (auto item = Result.begin(); item != Result.end(); ++item)
				{
					json[++index] = dict2json(*item);
				}
			}
			else
			{
				NoSurpport("json datatype error");
			}

			_Json[_Key] = json;
		}


		void dict2value(const std::string& _Key, const CRTValue& _Value, Json::Value &_Json)
		{
			const auto type = _Value.GetValueStyle();

			switch (type)
			{
			case RTVS_int:				_Json[_Key] = _Value.GetInt(); break;
			case RTVS_unsigned_int:		_Json[_Key] = _Value.GetUInt(); break;
			case RTVS_double:			_Json[_Key] = _Value.GetDouble(); break;
			case RTVS_string:			_Json[_Key] = _Value.GetString(); break;
			case RTVS_dict:				_Json[_Key] = dict2json(_Value.GetDict()); break;
			case RTVS_vector_int:
			case RTVS_vector_unsigned_int:
			case RTVS_vector_double:
			case RTVS_vector_string:
			case RTVS_vector_dict:		array2json(_Key, _Value, _Json); break;
			default:					NoSurpport("json datatype error"); break;
			}//switch
		}


		Json::Value dict2json(const CRTDict& _Dict)
		{
			Json::Value json;
			const auto keys = _Dict.Keys();

			for (auto item = keys.begin(); item != keys.end(); ++item)
			{
				const auto key = *item;
				const auto value = _Dict[key];

				dict2value(key, value, json);
			}

			return(json);
		}


		std::string dict2string(const CRTDict& _Dict)
		{
			const auto json = dict2json(_Dict);

			return(json.toStyledString());
		}
	}//RTNSKeep


	namespace RTNSKeep
	{
		std::string ToBase64(const std::string _Str)
		{
			auto pChs = (unsigned char*)_Str.c_str();
			const auto str(base64_encode(pChs, _Str.length()));

			return(str);
		}


		std::string FromBase64(const std::string _StrBase64)
		{
			const auto strBase64 = base64_decode(_StrBase64);

			return(strBase64);
		}
	}//RTNSKeep


	namespace RTNSKeep
	{
		std::string ToEncrypt(const std::string _Str, const std::string _Key)
		{
			return(_Str);
		}


		std::string FromEncrypt(const std::string _StrEncrypt, const std::string _Key)
		{
			return(_StrEncrypt);
		}
	}//RTNSKeep
}//RTNSTool