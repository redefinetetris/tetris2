#include "RTNSTool.h"
#include <set>
#include <thread>
#include <random>
#include <sstream>
#include "RTDict.h"
#include "RTMail.h"
#include "RTNSDB.h"
#include "RTBlock.h"
#include "RTETimer.h"
#include "RTNSKeep.h"
#include "RTDBBlock.h"
#include "RTDataType.h"


namespace RTNSTool
{

	long GetMicroSecond(const long _Time)
	{
		return(_Time);
	}


	long GetMilliSecond(const long _Time)
	{
		return(_Time * GetMicroSecond(1000));
	}


	long GetSecond(const long _Time)
	{
		return(_Time * GetMilliSecond(1000));
	}


	long GetMinute(const long _Time)
	{
		return(_Time * GetSecond(60));
	}


	long GetHour(const long _Time)
	{
		return(_Time * GetMinute(60));
	}


	long GetDay(const long _Time)
	{
		return(_Time * GetHour(24));
	}


	int string2int(const std::string _Str)
	{
		std::istringstream iss(_Str);
		int result = 0;

		iss >> result;

		return(result);
	}


	std::string int2string(const int _Val)
	{
		return(std::to_string(_Val));
	}


	std::string int2hexstring(const int _Val)
	{
		char chs[IP_ADDR_SIZE]{ '\0' };

		sprintf(chs, "%X", _Val);

		return(chs);
	}


	unsigned int string2uint(const std::string _Str)
	{
		std::istringstream iss(_Str);
		unsigned int result = 0;

		iss >> result;

		return(result);
	}


	std::string uint2string(const unsigned int _Val)
	{
		return(std::to_string(_Val));
	}


	std::string uint2hexstring(const unsigned int _Val)
	{
		char chs[IP_ADDR_SIZE]{ '\0' };

		sprintf(chs, "%X", _Val);

		return(chs);
	}


	long long string2longlong(const std::string _Str)
	{
		std::istringstream iss(_Str);
		long long result = 0;

		iss >> result;

		return(result);
	}


	std::string longlong2string(const long long _Val)
	{
		return(std::to_string(_Val));
	}


	double string2double(const std::string _Str)
	{
		std::istringstream iss(_Str);
		double result = 0;

		iss >> result;

		return(result);
	}


	std::string double2string(const double _Val)
	{
		return(std::to_string(_Val));
	}


	CRTDict string2dict(const std::string _Str)
	{
		return(RTNSKeep::string2dict(_Str));
	}


	std::string dict2string(const CRTDict& _Dict)
	{
		return(RTNSKeep::dict2string(_Dict));
	}


	std::vector<int> string2vector(const std::string& _Block)
	{
		std::vector<int> Cells;
		Cells.reserve(_Block.size());

		for (auto item = _Block.begin(); item != _Block.end(); ++item)
		{
			const char ch = *item;
			const int cell = ch - '0';

			Cells.push_back(cell);
		}

		return(Cells);
	}


	std::string vector2string(const std::vector<int>& _Vect)
	{
		std::string Cells;
		Cells.reserve(_Vect.size());

		for (auto item = _Vect.begin(); item != _Vect.end(); ++item)
		{
			Cells += int2string(*item);
		}

		return(Cells);
	}


	int GetThreadID(void)
	{
		std::stringstream oss;
		oss << std::this_thread::get_id();

		int tid = 0;
		oss >> tid;

		return(tid);
	}


	std::string GetThreadIDString(void)
	{
		const auto tid = GetThreadID();
		const auto strTid = int2string(tid);

		return(strTid);
	}


	CRTDict MakeDict(const std::string& _Key, const std::string& _Value)
	{
		const std::string strOP("=");
		std::vector<std::string> Condition{ strOP, _Value };
		const CRTDict Dict{
			{ _Key, Condition },
		};

		return(Dict);
	}


	CRTDict MakeDict(const std::vector<std::string>& _Keys, const std::vector<std::string>& _Values)
	{
		const std::string strOP("=");
		const auto Length = (int)_Keys.size();
		CRTDict Dict;

		for (int index = 0; index < Length; ++index)
		{
			std::vector<std::string> Condition{ strOP, _Values[index] };
			Dict[_Keys[index]] = Condition;
		}

		return(Dict);
	}


	CRTDict MakeDict(const std::string& _Key, const std::string& _Value, const std::string& _Key2, const std::string& _Value2)
	{
		const std::string strOP("=");
		std::vector<std::string> Condition{ strOP, _Value };
		std::vector<std::string> Condition2{ strOP, _Value2 };
		const CRTDict Dict{
			{ _Key, Condition },
			{ _Key2, Condition2 },
		};

		return(Dict);
	}


	const std::string& SignHubLoop(void)
	{
		const static std::string _SignHubLoop("__hub__");

		return(_SignHubLoop);
	}


	const std::string& SignSessionLoop(void)
	{
		const static std::string _SignSessionLoop("__session__");

		return(_SignSessionLoop);
	}


	const std::string& SignGameLoop(void)
	{
		const static std::string _SignSessionLoop("__game__");

		return(_SignSessionLoop);
	}


	const std::string& SignHistory(void)
	{
		const static std::string _SignHistory("__history__");

		return(_SignHistory);
	}


	int BackwardValue(void)
	{
		return(-1);
	}


	int NormalValue(void)
	{
		return(0);
	}


	int ForwardValue(void)
	{
		return(1);
	}


	int HubLoopValue(void)
	{
		return(100);
	}


	int SessionLoopValue(void)
	{
		return(200);
	}


	int GameLoopValue(void)
	{
		return(300);
	}


	int RandomM(const int _Min, const int _Max)
	{
		std::random_device dev;
		std::default_random_engine eng(dev());
		std::uniform_int_distribution<> dis(_Min, _Max);
		auto rander(std::bind(dis, eng));

		return(rander());
	}


	std::string RandomString(const int _Length)
	{
		const static std::string _RandomStr("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789`~!@#$%^&*()_=+-*/;:'<>,./?\" \t\r\n");
		const static int _Size = _RandomStr.length() - 1;

		std::string cells;

		for (int i = 0; i < _Length; ++i)
		{
			const auto index = RandomM(0, _Size);
			cells += _RandomStr[index];
		}

		return(cells);
	}


	bool DetectHit(const CRTBlock& _Area, const CRTBlock& _Block)
	{
		const auto pointO = _Block.GetO();

		for (int x = 0; x < _Block.GetLength(); ++x)
		{
			for (int y = 0; y < _Block.GetWidth(); ++y)
			{
				if (_Block.GetValue(x, y))
				{
					if (_Area.GetValue(pointO.GetX() + x, pointO.GetY() + y))
					{
						return(true);
					}
				}
			}
		}//for

		return(false);
	}


	bool DetectFreeze(const CRTDict& _Args)
	{
		const auto x_offset = GetIntValue4Dict(_Args, "x", 0);

		if (0 < x_offset)
		{
			return(true);
		}

		return(false);
	}


	void Merge(CRTBlock& _Area, const CRTBlock& _Block)
	{
		const auto pointO = _Block.GetO();

		for (int x = 0; x < _Block.GetLength(); ++x)
		{
			for (int y = 0; y < _Block.GetWidth(); ++y)
			{
				const auto value = _Block.GetValue(x, y);

				if (value)
				{
					_Area[pointO.GetX() + x][pointO.GetY() + y] = value;
				}
			}
		}//for
	}


	void Merge(CRTBlock& _Area, const CRTBlock& _Block, const int _Cell)
	{
		const auto pointO = _Block.GetO();

		for (int x = 0; x < _Block.GetLength(); ++x)
		{
			for (int y = 0; y < _Block.GetWidth(); ++y)
			{
				const auto value = _Block.GetValue(x, y);

				if (value)
				{
					_Area[pointO.GetX() + x][pointO.GetY() + y] = _Cell;
				}
			}
		}//for
	}


	std::vector<int> DetectTarget(const CRTBlock& _Area, const CRTBlock& _Block)
	{
		std::vector<int> Target;
		Target.reserve(VECTOR_RESERVE_SIZE);
		const auto pointO = _Block.GetO();

		for (int x = pointO.GetX(); x < pointO.GetX() + _Block.GetRealLength(); ++x)
		{
			bool full = true;

			for (int y = 1; y < _Area.GetWidth() - 1; ++y)
			{
				if (!_Area.GetValue(x, y))
				{
					full = false;

					break;
				}
			}

			if (false == full)
			{
				continue;
			}
			Target.push_back(x);
		}//for

		return(Target);
	}


	void InsertLines(const CRTBlock& _SrcArea, const std::vector<int>& _SrcLines, const std::vector<int>& _Cells, CRTBlock& _DestArea)
	{
		int indexCell = 0;

		_DestArea.ClearValue();
		_DestArea.SetBorder();

		for (auto item = _SrcLines.begin(); item != _SrcLines.end(); ++item)
		{
			const auto x = *item;
			++indexCell;

			for (int y = 1; y < _SrcArea.GetWidth() - 1; ++y)
			{
				_DestArea[x][y] = _Cells[indexCell];
				++indexCell;
			}
		}//for

		int cursor = _SrcArea.GetLength() - 2;
		const std::set<int> SrcLines(_SrcLines.begin(), _SrcLines.end());

		for (int x = cursor; 0 < x && 0 < cursor; --x)
		{
			while (0 != SrcLines.count(cursor))
			{
				--cursor;
			}

			for (int y = 1; y < _SrcArea.GetWidth() - 1; ++y)
			{
				_DestArea[cursor][y] = _SrcArea[x][y];
			}

			--cursor;
		}//for
	}


	void RemoveLines(const CRTBlock& _SrcArea, const std::vector<int>& _SrcLines, CRTBlock& _DestArea)
	{
		int cursor = _SrcArea.GetLength() - 2;
		const std::set<int> SrcLines(_SrcLines.begin(), _SrcLines.end());

		_DestArea.ClearValue();
		_DestArea.SetBorder();

		for (int x = cursor; 0 < x; --x)
		{
			if (0 != SrcLines.count(x))
			{
				continue;
			}

			for (int y = 1; y < _SrcArea.GetWidth() - 1; ++y)
			{
				_DestArea[cursor][y] = _SrcArea[x][y];
			}

			--cursor;
		}//for
	}


	void RecoverBlockPoint(CRTBlock& _Block, const CRTDict& _Args)
	{
		const auto Prefix = RTNSTool::SignGameLoop();
		const auto x = _Args[Prefix + "x"].GetInt();
		const auto y = _Args[Prefix + "y"].GetInt();
		const auto z = _Args[Prefix + "z"].GetInt();
		const CRTPoint pointO(x, y, z);

		_Block.SetO(pointO);
	}


	int RecoverBlock(CRTBlock& _Block, const CRTDict& _Args, const std::string _Style)
	{
		RecoverBlockPoint(_Block, _Args);

		const auto Prefix = RTNSTool::SignGameLoop();
		const auto id = _Args[Prefix + _Style].GetInt();

		_Block.SetID(0);
		_Block.ClearValue();

		if (id < 1)
		{
			return(0);
		}

		auto pDBBlock = RTNSDB::GetDBBlock(id);
		if (nullptr == pDBBlock)
		{
			return(0);
		}

		const auto Values = string2vector(pDBBlock->GetBlock());
		_Block.SetValue(Values);
		_Block.SetID(pDBBlock->GetID());

		return(_Block.GetID());
	}


	int RecoverHealthAndMask(CRTEBase* _pRTEBase, const CRTDict& _Args)
	{
		const auto Prefix = SignGameLoop();
		const auto Health = (RTHealthStyle_t)_Args[Prefix + "health"].GetUInt();
		auto AllMask = _Args[Prefix + "allmask"].GetUInt();

		_pRTEBase->SetHealth(Health);
		_pRTEBase->SetAllMask(AllMask);

		return(0);
	}


	int GetBackDictID(void)
	{
		static std::atomic<int> _BackDictID = 0;

		return(++_BackDictID);
	}


	std::shared_ptr<CRTMail> NewMail(void)
	{
		auto pMail = NewSharedPtrObj<CRTMail>(GetCurrentMaster());

		if (nullptr == pMail)
		{
			return(nullptr);
		}

		return(pMail);
	}


	std::shared_ptr<CRTMail> BackMail(const std::shared_ptr<CRTMail> _pSrcMail, const CRTDict& _Dict)
	{
		auto pMail = NewMail();
		if (nullptr == pMail)
		{
			return(nullptr);
		}

		pMail->CopyNetInfo(*_pSrcMail);
		pMail->SetDict(_Dict);

		return(pMail);
	}


	std::shared_ptr<CRTMail> BackMail(const std::string& _Msg)
	{
		auto pMail = NewMail();
		if (nullptr == pMail)
		{
			return(nullptr);
		}

		pMail->SetText(_Msg);

		return(pMail);
	}


	std::shared_ptr<CRTMail> BackMail(const CRTDict& _Dict)
	{
		auto pMail = NewMail();
		if (nullptr == pMail)
		{
			return(nullptr);
		}

		pMail->SetDict(_Dict);

		return(pMail);
	}


	CRTDict BackDict(const std::vector<std::string>& _Ops, const CRTDict& _Args, const std::string _Code, const std::string _Msg, const int _ID)
	{
		auto dict = BackDict(_Ops, _Code, _Msg, _ID);

		dict["args"] = _Args;

		return(dict);
	}


	CRTDict BackDict(const std::vector<std::string>& _Ops, const std::string _Code, const std::string _Msg, const int _ID)
	{
		const CRTDict dict{
			{ "ops", _Ops },
			{ "code", _Code },
			{ "msg", _Msg },
			{ "id", _ID },
		};

		return(dict);
	}


	CRTDict BackDictBy(const std::shared_ptr<CRTMail> _pSrcMail, const CRTDict& _Args, const std::string _Code, const std::string _Msg)
	{
		const auto dict = _pSrcMail->GetDict();
		const auto ops = dict["ops"].GetVectorString();
		auto id = GetIntValue4Dict(dict, "id", 0);
		if (0 == id)
		{
			id = GetBackDictID();
		}

		return(BackDict(ops, _Args, _Code, _Msg, id));
	}


	CRTDict BackDictBy(const std::shared_ptr<CRTMail> _pSrcMail, const std::string _Code, const std::string _Msg)
	{
		const auto dict = _pSrcMail->GetDict();
		const auto ops = dict["ops"].GetVectorString();
		auto id = GetIntValue4Dict(dict, "id", 0);
		if (0 == id)
		{
			id = GetBackDictID();
		}

		return(BackDict(ops, _Code, _Msg, id));
	}


	CRTDict BackDict4Loop(const std::shared_ptr<CRTMail> _pSrcMail, const CRTDict& _Args, const std::string _Code, const std::string _Msg)
	{
		auto back_dict = BackDictBy(_pSrcMail, _Args, _Code, _Msg);
		const auto dict = _pSrcMail->GetDict();
		const auto code = VerifyDict4Loop(back_dict, dict);

		return(back_dict);
	}


	CRTDict BackDict4Loop(const std::shared_ptr<CRTMail> _pSrcMail, const std::string _Code, const std::string _Msg)
	{
		auto back_dict = BackDictBy(_pSrcMail, _Code, _Msg);
		const auto dict = _pSrcMail->GetDict();
		const auto code = VerifyDict4Loop(back_dict, dict);

		return(back_dict);
	}


	int VerifyDict4Loop(CRTDict& _BackDict, const CRTDict& _Dict)
	{
		if (false == _Dict.HasKey(RTNSTool::SignHubLoop()))
		{
			return(0);
		}

		const auto LoopValue = _Dict[RTNSTool::SignHubLoop()].GetString();
		std::vector<std::string> opsNew{ LoopValue };

		const auto ops(_Dict["ops"].GetVectorString());
		opsNew.insert(opsNew.end(), ops.begin(), ops.end());

		_BackDict["ops"] = opsNew;
		_BackDict[RTNSTool::SignHubLoop()] = LoopValue;

		return(1);
	}


	std::shared_ptr<CRTMail> BackMailBy(const std::shared_ptr<CRTMail> _pSrcMail, const CRTDict& _Args, const std::string _Code, const std::string _Msg)
	{
		const auto back_dict = BackDictBy(_pSrcMail, _Args, _Code, _Msg);

		return(BackMail(_pSrcMail, back_dict));
	}


	std::shared_ptr<CRTMail> BackMailBy(const std::shared_ptr<CRTMail> _pSrcMail, const std::string _Code, const std::string _Msg)
	{
		const auto back_dict = BackDictBy(_pSrcMail, _Code, _Msg);

		return(BackMail(_pSrcMail, back_dict));
	}


	std::string ToBase64(const std::string _Str)
	{
		return(RTNSKeep::ToBase64(_Str));
	}


	std::string FromBase64(const std::string _StrBase64)
	{
		return(RTNSKeep::FromBase64(_StrBase64));
	}


	std::string ToEncrypt(const std::string _Str, const std::string _Key)
	{
		return(RTNSKeep::ToEncrypt(_Str, _Key));
	}


	std::string FromEncrypt(const std::string _StrEncrypt, const std::string _Key)
	{
		return(RTNSKeep::FromEncrypt(_StrEncrypt, _Key));
	}


	std::string GetStrOps(const std::vector<std::string>& _Ops, unsigned int _Index)
	{
		std::string strOps;

		for (; _Index < _Ops.size(); ++_Index)
		{
			strOps += _Ops[_Index];
		}

		return(strOps);
	}


	CRTDict WatchDict(const CRTBlock& _Area, const CRTBlock& _Block)
	{
		CRTBlock merge(_Area);

		RTNSTool::Merge(merge, _Block);

		const auto Values = merge.GetValue();
		const CRTDict Args{
			{ "area", RTNSTool::vector2string(Values) },
		};
		const auto Dict = RTNSTool::BackDictBy(GetCurrentMail(), Args);

		return(Dict);
	}


	CRTDict SessionDict(const int _idSession, const int _idGame, const std::string _Op, const int _LoopStyle)
	{
		const std::vector<std::string> Ops{ "session", _Op };
		CRTDict args{
			{ "sessionid", _idSession },
		};
		if (_idGame)
		{
			args["gameid"] = _idGame;
		}

		CRTDict dict{
			{ "ops", Ops },
			{ "args", args },
			{ "code", "ok" },
			{ "msg", "luck" },
			{ "id", GetBackDictID() },
		};
		if (_LoopStyle)
		{
			if (_LoopStyle==HubLoopValue())
			{
				dict[SignHubLoop()] = "session";
			}
			else
			{
				dict[SignSessionLoop()] = "session";
			}
		}//if

		return(dict);
	}


	std::shared_ptr<CRTMail> SessionMail(const int _idSession, const int _idGame, const std::string _Op, const int _LoopStyle)
	{
		const auto dict = SessionDict(_idSession, _idGame, _Op, _LoopStyle);

		return(BackMail(dict));
	}


	std::string GetTimerMsg4RTEGame(const int _idSession, const int _idGame, const std::string _Op)
	{
		const std::vector<std::string> Ops{ "game", _Op };
		const CRTDict args{
			{ "sessionid", _idSession },
			{ "gameid", _idGame },
		};
		const CRTDict dict{
			{ "ops", Ops },
			{ "args", args },
			{ SignHubLoop(), HubLoopValue() },
			{ "id", GetBackDictID() },
		};

		return(dict2string(dict));
	}


	std::string GetTimerMsg4RTESession(const int _idSession, const std::string _Op)
	{
		const std::vector<std::string> Ops{ "session", _Op };
		const CRTDict args{
			{ "sessionid", _idSession },
		};
		const CRTDict dict{
			{ "ops", Ops },
			{ "args", args },
			{ SignHubLoop(), HubLoopValue() },
			{ "id", GetBackDictID() },
		};

		return(dict2string(dict));
	}


	std::string GetTimerMsg4RTEDB(const int _idDB, const std::string _Op)
	{
		const std::vector<std::string> Ops{ "db", _Op };
		const CRTDict args{
			{ "dbid", _idDB },
		};
		const CRTDict dict{
			{ "ops", Ops },
			{ "args", args },
			{ SignHubLoop(), HubLoopValue() },
			{ "id", GetBackDictID() },
		};

		return(dict2string(dict));
	}


	std::string GetTimerMsg4RTERoot(const int _idRoot, const int _idSession, const std::string _Op)
	{
		const std::vector<std::string> Ops{ "root", _Op };
		const CRTDict args{
			{ "rootid", _idRoot },
			{ "sessionid", _idSession },
		};
		const CRTDict dict{
			{ "ops", Ops },
			{ "args", args },
			{ SignHubLoop(), HubLoopValue() },
			{ "id", GetBackDictID() },
		};

		return(dict2string(dict));
	}


	std::vector<std::shared_ptr<CRTMail>> GetDBClockMails(const int _idDB, const std::string _Op, const int _FlushTime, const int _DownTTLTime, const int _WashTTLTime, const int _Circle)
	{
		const auto mailFlush = RTNSTool::TimerMail("db", RTES_DB, _idDB, _Circle, _Op, _FlushTime, "flush", RTNSTool::GetTimerMsg4RTEDB(_idDB, "flush"));
		const auto mailDownTTL = RTNSTool::TimerMail("db", RTES_DB, _idDB, _Circle, _Op, _DownTTLTime, "downttl", RTNSTool::GetTimerMsg4RTEDB(_idDB, "downttl"));
		const auto mailWashTTL = RTNSTool::TimerMail("db", RTES_DB, _idDB, _Circle, _Op, _WashTTLTime, "washttl", RTNSTool::GetTimerMsg4RTEDB(_idDB, "washttl"));

		const std::vector<std::shared_ptr<CRTMail>> Mails{ mailFlush, mailDownTTL, mailWashTTL };

		return(Mails);
	}


	std::shared_ptr<CRTMail> GetSessionTimerMail(const int _idSession, const std::string _Card, const std::string _Op, const int _Time, const std::string _Msg)
	{
		const auto pMail = RTNSTool::TimerMail("session", RTES_Session, _idSession, 1, _Op, _Time, _Card, _Msg);

		return(pMail);
	}


	std::vector<std::shared_ptr<CRTMail>> GetSessionClockMails(const int _idRoot, const int _idSession, const std::string _Op, const int _JumpTime, const int _RaceTime, const int _MoveTime)
	{
		const auto mailJump = GetSessionTimerMail(_idSession, "jump", _Op, _JumpTime, GetTimerMsg4RTESession(_idSession, "jump"));
		const auto mailRace = GetSessionTimerMail(_idSession, "race", _Op, _RaceTime, GetTimerMsg4RTESession(_idSession, "race"));
		const auto mailMove = GetSessionTimerMail(_idSession, "move", _Op, _MoveTime, GetTimerMsg4RTESession(_idSession, "move"));

		const auto DeathTime = GetSecond(19);
		const auto mailDeath = TimerMail("session", RTES_Session, _idSession, 0, "new", DeathTime, "death", GetTimerMsg4RTERoot(_idRoot, _idSession, "deletesession"));

		std::vector<std::shared_ptr<CRTMail>> Mails{ mailJump, mailMove };

		if (_RaceTime)
		{
			Mails.push_back(mailRace);
		}
		if (_idRoot)
		{
			Mails.push_back(mailDeath);
		}

		return(Mails);
	}


	CRTDict TimerDict(const std::string _Src, const int _Style, const int _TimerID, const int _Circle, const std::string _Op, const int _MicroSeconds, const std::string _Card, const std::string _Msg)
	{
		const std::vector<std::string> Ops{ "clock", _Op };
		const CRTDict args{
			{ "style", _Style },
			{ "timerid", _TimerID },
			{ "circle", _Circle },
			{ "microseconds", _MicroSeconds },
			{ "card", _Card },
			{ "msg", _Msg },
		};
		const CRTDict dict{
			{ "ops", Ops },
			{ "args", args },
			{ SignHubLoop(), _Src },
			{ "code", "ok" },
			{ "msg", "luck" },
			{ "id", GetBackDictID() },
		};

		return(dict);
	}


	std::shared_ptr<CRTMail> TimerMail(const std::string _Src, const int _Style, const int _TimerID, const int _Circle, const std::string _Op, const int _MicroSeconds, const std::string _Card, const std::string _Msg)
	{
		const auto dict = TimerDict(_Src, _Style, _TimerID, _Circle, _Op, _MicroSeconds, _Card, _Msg);

		return(BackMail(dict));
	}


	int GetIntValue4Dict(const CRTDict& _Dict, const std::string _Key, const int _Default)
	{
		auto result = _Default;

		if (_Dict.HasKey(_Key))
		{
			result = _Dict[_Key].GetInt();
		}

		return(result);
	}


	std::string GetStringValue4Dict(const CRTDict& _Dict, const std::string _Key, const std::string _Default)
	{
		auto result = _Default;

		if (_Dict.HasKey(_Key))
		{
			result = _Dict[_Key].GetString();
		}

		return(result);
	}


	CRTDict GetDictByTimer(const CRTETimer& _Timer)
	{
		const CRTDict dict{
			{ "style", _Timer.GetRTEStyle() },
			{ "timerid", _Timer.GetSelfID() },
			{ "microseconds", _Timer.GetWaitTime() },
			{ "card", _Timer.GetCard() },
			{ "msg", _Timer.GetMsg() },
		};

		return(dict);
	}


	std::shared_ptr<CRTMail> GetMailByTrail(const int _RootID, const int _ReplayMode)
	{
		auto pMail = NewMail();
		if (nullptr == pMail)
		{
			return(nullptr);
		}

		const std::vector<std::string> Ops{ "trail", "newroot" };
		CRTDict BackArgs{
			{ "rootid", _RootID },
			{ "replaymode", _ReplayMode },
		};
		if (_ReplayMode)
		{
			const auto Args = GetCurrentArgs();
			const auto Token = Args["token"].GetString();

			BackArgs["token"] = Token;
		}
		const CRTDict BackDict{
			{ "ops", Ops },
			{ "args", BackArgs },
			{ "id", RTNSTool::GetBackDictID() },
			{ RTNSTool::SignHubLoop(), RTNSTool::HubLoopValue() },
		};

		pMail->SetDict(BackDict);

		return(pMail);
	}


	bool NewGameSpace(std::unique_ptr<CRTBlock>& _pArea, std::unique_ptr<CRTBlock>& _pAreaBuffer, std::unique_ptr<CRTBlock>& _pBlock, std::unique_ptr<CRTBlock>& _pBlockBuffer, const int _Length, const int _Width, const int _Base)
	{
		std::unique_ptr<CRTBlock> pArea(new (std::nothrow) CRTBlock(_Length, _Width, 0));
		std::unique_ptr<CRTBlock> pAreaBuffer(new (std::nothrow) CRTBlock(_Length, _Width, 0));
		std::unique_ptr<CRTBlock> pBlock(new (std::nothrow) CRTBlock(_Base, _Base, 0));
		std::unique_ptr<CRTBlock> pBlockBuffer(new (std::nothrow) CRTBlock(_Base, _Base, 0));

		if (nullptr == pArea || nullptr == pAreaBuffer || nullptr == pBlock || nullptr == pBlockBuffer)
		{
			return(false);
		}

		_pArea = std::move(pArea);
		_pAreaBuffer = std::move(pAreaBuffer);
		_pBlock = std::move(pBlock);
		_pBlockBuffer = std::move(pBlockBuffer);

		return(true);
	}


	bool DeleteGameSpace(std::unique_ptr<CRTBlock>& _pArea, std::unique_ptr<CRTBlock>& _pAreaBuffer, std::unique_ptr<CRTBlock>& _pBlock, std::unique_ptr<CRTBlock>& _pBlockBuffer)
	{
		auto pArea = std::move(_pArea);
		auto pAreaBuffer = std::move(_pAreaBuffer);
		auto pBlock = std::move(_pBlock);
		auto pBlockBuffer = std::move(_pBlockBuffer);

		return(true);
	}


	int DoHealth(CRTBase* _pHost, const CRTDict& _Args)
	{
		const auto Health = _Args["health"].GetString();

		if ("hungup" == Health)
		{
			_pHost->BackUpHealth();
			_pHost->SetHealth(RTHS_HungUp);

			return(0);
		}

		_pHost->RecoverHealth();

		return(1);
	}

}//RTNSTool

