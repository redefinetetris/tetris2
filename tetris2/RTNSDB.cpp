#include "RTNSDB.h"
#include <ctime>
#include <chrono>
#include <atomic>
#include "RTDict.h"
#include "RTMail.h"
#include "RTEBase.h"
#include "RTNSLog.h"
#include "RTNSTool.h"
#include "RTDBGame.h"
#include "RTDBUser.h"
#include "RTDBRole.h"
#include "RTDBBlock.h"
#include "RTDBSpeed.h"
#include "RTDBState.h"
#include "RTDBToken.h"
#include "RTDBCursor.h"
#include "RTDBReplay.h"
#include "RTDBSession.h"
#include "RTDBPackage.h"
#include "RTDBTransfer.h"
#include "RTDBPassword.h"
#include "../RTDataType.h"
#include "orm/RTDBStatic.h"
#include "event/RTERootStyle.h"
#include "event/RTESessionStyle.h"


namespace RTNSDB
{
	std::string GetCurrentDateTime(const char _ch)
	{
		const auto now = std::chrono::system_clock::now();
		const auto time_t_now = std::chrono::system_clock::to_time_t(now);
		const auto local_now = std::localtime(&time_t_now);
		char dt[DT_BUFFER_SIZE] = { '\0' };

		if ('\0' == _ch)
		{
			const char* fmt = "%Y-%m-%d %H:%M:%S";
			strftime(dt, DT_BUFFER_SIZE, fmt, local_now);
		}
		else
		{
			char fmt[DT_BUFFER_SIZE] = { '\0' };
			sprintf(fmt, "%%Y%c%%m%c%%d%c%%H%c%%M%c%%S", _ch, _ch, _ch, _ch, _ch);

			strftime(dt, DT_BUFFER_SIZE, fmt, local_now);
		}

		return(dt);
	}


	long long GetTimeStamp(void)
	{
		const auto now = std::chrono::high_resolution_clock::now();

		return(now.time_since_epoch().count());
	}


	std::string GetTimeStampString(void)
	{
		const auto ts = GetTimeStamp();

		return(RTNSTool::longlong2string(ts));
	}


	int RoleAdmin(void)
	{
		static int idAdmin = 0;

		if (idAdmin)
		{
			return(idAdmin);
		}

		const auto Dict = RTNSTool::MakeDict("name", "admin");
		idAdmin = GetRoleManager().GetID(Dict);

		return(idAdmin);
	}


	int RoleGod(void)
	{
		static int idGod = 0;

		if (idGod)
		{
			return(idGod);
		}

		const auto Dict = RTNSTool::MakeDict("name", "god");
		idGod = GetRoleManager().GetID(Dict);

		return(idGod);
	}


	int RolePlayer(void)
	{
		static int idPlayer = 0;

		if (idPlayer)
		{
			return(idPlayer);
		}

		const auto Dict = RTNSTool::MakeDict("name", "player");
		idPlayer = GetRoleManager().GetID(Dict);

		return(idPlayer);
	}


	int StateGood(void)
	{
		static int idGood = 0;

		if (idGood)
		{
			return(idGood);
		}

		const auto Dict = RTNSTool::MakeDict("name", "good");
		idGood = GetStateManager().GetID(Dict);

		return(idGood);
	}


	int StateBad(void)
	{
		static int idBad = 0;

		if (idBad)
		{
			return(idBad);
		}

		const auto Dict = RTNSTool::MakeDict("name", "bad");
		idBad = GetStateManager().GetID(Dict);

		return(idBad);
	}


	int StateFreeze(void)
	{
		static int idFreeze = 0;

		if (idFreeze)
		{
			return(idFreeze);
		}

		const auto Dict = RTNSTool::MakeDict("name", "freeze");
		idFreeze = GetStateManager().GetID(Dict);

		return(idFreeze);
	}


	int StateDelete(void)
	{
		static int idDelete = 0;

		if (idDelete)
		{
			return(idDelete);
		}

		const auto Dict = RTNSTool::MakeDict("name", "delete");
		idDelete = GetStateManager().GetID(Dict);

		return(idDelete);
	}


	std::shared_ptr<CRTDBBlock> GetDBBlock(const int _ID)
	{
		auto pObj = GetBlockManager().Get(_ID);

		return(pObj);
	}


	std::shared_ptr<CRTDBBlock> GetNextDBBlock(const int _ID)
	{
		const auto NextID = GetNextDBBlockID(_ID);

		return(GetDBBlock(NextID));
	}


	int GetNextDBBlockID(const int _ID)
	{
		const auto pTransfer = GetTransferByBlockID(_ID);
		if (nullptr == pTransfer)
		{
			return(_ID);
		}

		const auto NextID = pTransfer->GetNextID();

		return(NextID);
	}


	int GetBase(const int _GroupID)
	{
		const auto strID = RTNSTool::int2string(_GroupID);
		const auto Dict = RTNSTool::MakeDict("groupid", strID);
		auto pObjBlock = GetBlockManager().GetOnlyOne(Dict);

		if (pObjBlock)
		{
			return(pObjBlock->GetBase());
		}

		return(4);
	}


	int GetRandomDBBlockID(const int _GroupID)
	{
		const auto IDs = GetAllDBBlockID(_GroupID);
		const auto index = RTNSTool::RandomM(0, IDs.size() - 1);

		return(IDs[index]);
	}


	std::vector<int> GetAllDBBlockID(const int _GroupID)
	{
		const auto strID = RTNSTool::int2string(_GroupID);
		const auto Dict = RTNSTool::MakeDict("groupid", strID);
		const auto Objs = GetBlockManager().GetAllBySize(Dict);
		std::vector<int> IDs;
		IDs.reserve(VECTOR_RESERVE_SIZE);

		for (auto item = Objs.begin(); item != Objs.end(); ++item)
		{
			auto& pBlock = *item;

			IDs.push_back(pBlock->GetID());
		}

		return(IDs);
	}


	std::shared_ptr<CRTDBTransfer> GetTransfer(const int _ID)
	{
		auto pObj = GetTransferManager().Get(_ID);

		return(pObj);
	}


	std::shared_ptr<CRTDBTransfer> GetTransferByBlockID(const int _BlockID)
	{
		const auto strID = RTNSTool::int2string(_BlockID);
		const auto Dict = RTNSTool::MakeDict("blockid", strID);
		auto pObj = GetTransferManager().GetOnlyOne(Dict);

		return(pObj);
	}


	std::shared_ptr<CRTDBSpeed> GetSpeed(const int _ID)
	{
		auto pObj = GetSpeedManager().Get(_ID);

		return(pObj);
	}


	int GetSpeedByTime(const int _ID)
	{
		const auto pSpeed = GetSpeed(_ID);
		if (nullptr == pSpeed)
		{
			return(1000000);
		}

		return(pSpeed->GetMicroSecond());
	}


	unsigned int GetCoinsPerLine(void)
	{
		return(10);
	}


	long long GetNanoSecond(const long long _nanoseconds)
	{
		const auto ns = std::chrono::nanoseconds(_nanoseconds);

		return(ns.count());
	}


	long long GetNSByMicroSecond(const long long _macroseconds)
	{
		return(GetNanoSecond(_macroseconds * 1000));
	}


	long long GetNSByMilliSecond(const long long _milliseconds)
	{
		return(GetNSByMicroSecond(_milliseconds * 1000));
	}


	long long GetNSBySecond(const long long _seconds)
	{
		return(GetNSByMilliSecond(_seconds * 1000));
	}


	long long GetNSByMinute(const long long _minutes)
	{
		return(GetNSBySecond(_minutes * 60));
	}


	long long GetNSByHour(const long long _hours)
	{
		return(GetNSByMinute(_hours * 60));
	}


	long long GetNSByDay(const long long _days)
	{
		return(GetNSByHour(_days * 24));
	}


	long long UpJWTID(void)
	{
		std::atomic<long long> _JWTID = 0;

		return(++_JWTID);
	}


	const std::string& GetJWTKey(void)
	{
		const static auto strJWTKey(RTNSTool::RandomString());

		return(strJWTKey);
	}


	const CRTDict& GetTokenHeader()
	{
		const static CRTDict _dict_header{
			//算法
			{ "typ", "JWT" },
			{ "alg", "none" },
		};

		return(_dict_header);
	}


	CRTDict GetTokenPayload(const int _idUser)
	{
		const CRTDict dict_payload{
			//发行者
			{ "iss", "China" },
			//主题
			{ "sub", "redefine tetris" },
			//观众
			{ "aud", _idUser },
			//过期时间
			{ "exp", RTNSTool::longlong2string(GetNSByDay(1)) },
			//缓冲时间
			{ "nbf", RTNSTool::longlong2string(GetNSByMinute(10)) },
			//发行时间
			{ "iat", GetTimeStampString() },
			//JWT ID
			{ "jti", RTNSTool::longlong2string(UpJWTID()) },
		};

		return(dict_payload);
	}


	std::string GenerateTokenSimple(const int _idUser)
	{
		const auto dict_header = GetTokenHeader();
		const auto dict_payload = GetTokenPayload(_idUser);

		const auto header = RTNSTool::dict2string(dict_header);
		const auto payload = RTNSTool::dict2string(dict_payload);

		const auto base64Header = RTNSTool::ToBase64(header);
		const auto base64Payload = RTNSTool::ToBase64(payload);
		const auto base64HP = base64Header + "." + base64Payload;

		const auto encryptSignature = RTNSTool::ToEncrypt(base64HP, GetJWTKey());
		const auto base64Signature = RTNSTool::ToBase64(encryptSignature);

		const auto token = base64HP + "." + base64Signature;

		return(token);
	}


	std::string GenerateToken(const int _idUser)
	{
		const auto token = GenerateTokenSimple(_idUser);

		SaveToken(_idUser, token);

		return(token);
	}


	CRTDict DecodeToken(const std::string& _Token)
	{
		const auto dot1 = _Token.find_first_of('.');
		const auto dot2 = _Token.find_last_of('.');

		if (std::string::npos == dot1 || std::string::npos == dot2 || dot2 <= dot1)
		{
			return(CRTDict());
		}

		const auto base64Signature = _Token.substr(dot2 + 1);
		const auto encryptSignature = RTNSTool::FromBase64(base64Signature);
		const auto signature = RTNSTool::FromEncrypt(encryptSignature, GetJWTKey());
		if (!signature.length())
		{
			return(CRTDict());
		}

		const auto dot3 = signature.find_first_of('.');

		const auto base64Header = _Token.substr(0, dot1);
		const auto base64HeaderSignature = signature.substr(0, dot3);
		if (base64Header != base64HeaderSignature)
		{
			return(CRTDict());
		}

		const auto start = dot1 + 1;
		const auto base64Payload = _Token.substr(start, dot2 - start);
		const auto base64PayloadSignature = signature.substr(dot3 + 1);
		if (base64Payload != base64PayloadSignature)
		{
			return(CRTDict());
		}

		const auto payload = RTNSTool::FromBase64(base64Payload);
		const auto dict_payload = RTNSTool::string2dict(payload);

		return(dict_payload);
	}


	CRTDict DecodeTokenByDB(const std::string& _Token)
	{
		auto pObj = FindToken(_Token);
		if (nullptr == pObj)
		{
			return(CRTDict());
		}

		const auto dot1 = _Token.find_first_of('.');
		const auto dot2 = _Token.find_last_of('.');

		const auto base64Payload = _Token.substr(dot1 + 1, dot2);
		const auto payload = RTNSTool::FromBase64(base64Payload);
		const auto dict_payload = RTNSTool::string2dict(payload);

		return(dict_payload);
	}


	bool TokenTimeout(const CRTDict& _DictPayload)
	{
		if (_DictPayload.IsEmpty())
		{
			return(true);
		}

		const auto strIat = _DictPayload["iat"].GetString();
		const auto strExp = _DictPayload["exp"].GetString();
		const auto strNbf = _DictPayload["nbf"].GetString();

		const auto jwtTimeStamp = RTNSTool::string2longlong(strIat)
			+ RTNSTool::string2longlong(strExp)
			+ RTNSTool::string2longlong(strNbf);
		const auto currentTimeStamp = GetTimeStamp();

		if (jwtTimeStamp < currentTimeStamp)
		{
			return(true);
		}

		return(false);
	}


	int VerifyToken(const std::string& _Token, const bool _VerifyTime)
	{
		//const auto dict_payload = DecodeToken(_Token);
		const auto dict_payload = DecodeTokenByDB(_Token);

		if (dict_payload.IsEmpty())
		{
			return(0);
		}

		if (_VerifyTime)
		{
			if (TokenTimeout(dict_payload))
			{
				return(0);
			}
		}

		const auto aud = dict_payload["aud"].GetInt();

		return(aud);
	}


	std::string RefreshToken(const std::string& _Token)
	{
		const auto idUser = GetUserIDByToken(_Token);
		const auto codeDelete = DeleteToken(_Token);
		const auto new_token = GenerateToken(idUser);

		return(new_token);
	}


	int GetUserIDByToken(const std::string& _Token, const bool _Verify)
	{
		return(VerifyToken(_Token, _Verify));
	}


	int SaveToken(const int _idUser, const std::string& _Token)
	{
		auto pObj = RTNSTool::NewSharedPtrObj<CRTDBToken>();
		if (nullptr == pObj)
		{
			return(0);
		}

		pObj->SetUserID(_idUser);
		pObj->SetToken(_Token);

		GetTokenManager().Post(pObj);

		return(pObj->GetID());
	}


	std::shared_ptr<CRTDBToken> FindToken(const int _idUser)
	{
		const auto strID = RTNSTool::int2string(_idUser);
		const auto Dict = RTNSTool::MakeDict("userid", strID);
		auto pObj = GetTokenManager().GetOnlyOne(Dict);

		return(pObj);
	}


	std::shared_ptr<CRTDBToken> FindToken(const std::string& _Token)
	{
		const auto Dict = RTNSTool::MakeDict("token", _Token);
		auto pObj = GetTokenManager().GetOnlyOne(Dict);

		return(pObj);
	}


	int DeleteToken(const int _idUser)
	{
		auto pObj = FindToken(_idUser);
		if (nullptr == pObj)
		{
			return(0);
		}

		GetTokenManager().Delete(pObj);

		return(1);
	}


	int DeleteToken(const std::string& _Token)
	{
		auto pObj = FindToken(_Token);
		if (nullptr == pObj)
		{
			return(0);
		}

		GetTokenManager().Delete(pObj);

		return(1);
	}


	std::shared_ptr<CRTDBUser> FindUser(const int _idUser)
	{
		const auto strID = RTNSTool::int2string(_idUser);
		const auto Dict = RTNSTool::MakeDict("id", strID);
		auto pObj = GetUserManager().GetOnlyOne(Dict);

		return(pObj);
	}


	std::shared_ptr<CRTDBUser> FindUser(const std::string _User)
	{
		const auto Dict = RTNSTool::MakeDict("name", _User);
		auto pObj = GetUserManager().GetOnlyOne(Dict);

		return(pObj);
	}


	int DeleteUser(const int _idUser)
	{
		auto pObj = FindUser(_idUser);
		if (nullptr == pObj)
		{
			return(0);
		}

		GetUserManager().Delete(pObj);

		return(1);
	}


	int VerifyUser(const std::string _User, const std::string _Key)
	{
		const auto pObjUser = FindUser(_User);
		if (nullptr == pObjUser)
		{
			return(-1);
		}

		const auto idPassword = VerifyPassword(pObjUser->GetID(), _Key);
		if (idPassword < 1)
		{
			return(-2);
		}

		return(pObjUser->GetID());
	}


	int NewUser(const std::string _User, const std::string _Key)
	{
		SaveUser(_User);

		auto pObj = FindUser(_User);
		if (nullptr == pObj)
		{
			return(0);
		}

		SavePassword(pObj->GetID(), _Key);

		return(pObj->GetID());
	}


	int SaveUser(const std::string _User)
	{
		auto pObj = RTNSTool::NewSharedPtrObj<CRTDBUser>();
		if (nullptr == pObj)
		{
			return(0);
		}

		pObj->SetTimeStamp(GetCurrentDateTime());
		pObj->SetName(_User);
		pObj->SetRoleID(RolePlayer());

		GetUserManager().Post(pObj);

		return(pObj->GetID());
	}


	int SavePassword(const int _idUser, const std::string _Key)
	{
		auto pObj = RTNSTool::NewSharedPtrObj<CRTDBPassword>();
		if (nullptr == pObj)
		{
			return(0);
		}

		pObj->SetTimeStamp(GetCurrentDateTime());
		pObj->SetUserID(_idUser);
		pObj->SetKey(_Key);

		GetPasswordManager().Post(pObj);

		return(pObj->GetID());
	}


	std::shared_ptr<CRTDBPassword> FindPassword(const int _idUser)
	{
		const auto strID = RTNSTool::int2string(_idUser);
		const auto Dict = RTNSTool::MakeDict("userid", strID);
		auto pObj = GetPasswordManager().GetOnlyOne(Dict);

		return(pObj);
	}


	int VerifyPassword(const int _idUser, const std::string _Key)
	{
		const auto pObjPassword = FindPassword(_idUser);
		if (nullptr == pObjPassword)
		{
			return(-1);
		}

		if (_Key != pObjPassword->GetKey())
		{
			return(-2);
		}

		return(pObjPassword->GetID());
	}


	int NewDBSessionID(const int _idUser)
	{
		auto pObj = RTNSTool::NewSharedPtrObj<CRTDBSession>();
		if (nullptr == pObj)
		{
			return(0);
		}

		pObj->SetTimeStamp(GetTimeStampString());
		pObj->SetUserID(_idUser);

		GetSessionManager().Post(pObj);

		return(pObj->GetID());
	}


	int NewDBGameID(const int _idUser, const int _idSession)
	{
		auto pObj = RTNSTool::NewSharedPtrObj<CRTDBGame>();
		if (nullptr == pObj)
		{
			return(0);
		}

		pObj->SetTimeStamp(GetTimeStampString());
		pObj->SetSessionID(_idSession);
		pObj->SetUserID(_idUser);

		GetGameManager().Post(pObj);

		return(pObj->GetID());
	}


	int DefaultDBRootID(void)
	{
		return(1);
	}


	int UpDBRootID(void)
	{
		return(GetRootManager().UpID());
	}


	int UpDBSessionID(void)
	{
		return(GetSessionManager().UpID());
	}


	int UpDBGameID(void)
	{
		return(GetGameManager().UpID());
	}


	int NewDBPackage(std::shared_ptr<CRTMail> _pMail)
	{
		const auto timestamp = GetTimeStampString();
		const auto ip = _pMail->GetIPString();
		const auto mail = _pMail->GetText();

		const auto ID = NewDBPackage(timestamp, ip, mail);
		_pMail->SetSelfID(ID);

		return(ID);
	}


	int NewDBPackage(const std::string& _TimeStamp, const std::string& _IP, const std::string& _Mail)
	{
		auto pObj = RTNSTool::NewSharedPtrObj<CRTDBPackage>();
		if (nullptr == pObj)
		{
			return(0);
		}

		pObj->SetTimeStamp(_TimeStamp);
		pObj->SetIP(_IP);
		pObj->SetMail(_Mail);

		GetPackageManager().Post(pObj);

		return(pObj->GetID());
	}


	int UpdateDBPackage(std::shared_ptr<CRTMail> _pMail)
	{
		const auto ID = _pMail->GetSelfID();
		const auto Mail = _pMail->GetText();

		return(UpdateDBPackage(ID, Mail));
	}


	int UpdateDBPackage(const int _ID, const std::string& _Mail)
	{
		auto pObj = GetDBPackage(_ID);
		if (nullptr == pObj)
		{
			return(0);
		}

		pObj->SetMail(_Mail);

		GetPackageManager().Update(pObj);

		return(pObj->GetID());
	}


	std::shared_ptr<CRTDBPackage> FindDBPackage(const std::string& _TimeStamp)
	{
		const auto Dict = RTNSTool::MakeDict("timestamp", _TimeStamp);
		auto pObj = GetPackageManager().GetOnlyOne(Dict);

		return(pObj);
	}


	std::shared_ptr<CRTDBPackage> GetDBPackage(const int _ID)
	{
		auto pObj = GetPackageManager().Get(_ID);

		return(pObj);
	}


	std::shared_ptr<CRTMail> NewReplayMailByCursor(const int _RootID, const int _idPackage, const int _History)
	{
		const auto pPackage = GetDBPackage(_idPackage);
		if (nullptr == pPackage)
		{
			return(nullptr);
		}

		auto pMail = RTNSTool::NewMail();
		if (nullptr == pMail)
		{
			return(nullptr);
		}
		pMail->SetSelfID(pPackage->GetID());

		const auto Mail = pPackage->GetMail();
		auto Dict = RTNSTool::string2dict(Mail);
		auto Args = Dict["args"].GetDict();
		Args["rootid"] = _RootID;
		Dict["args"] = Args;
		Dict[RTNSTool::SignHubLoop()] = RTNSTool::HubLoopValue();
		Dict[RTNSTool::SignHistory()] = _History;

		pMail->SetDict(Dict);
		//PrintLogInfo(pMail->GetText());

		return(pMail);
	}


	int NewDBReplay(CRTEBase* _pHost, std::shared_ptr<CRTMail> _pMail, const int _FunctorStyle)
	{
		const auto timestamp = GetTimeStampString();
		const auto idPackage = _pMail->GetSelfID();
		int styleMaster(0);
		int idMaster(0);
		const auto styleSlave(_pHost->GetRTEStyle());
		const int idSlave(_pHost->GetSelfID());

		auto pParent = _pHost->GetParent();
		if (nullptr != pParent)
		{
			styleMaster = pParent->GetRTEStyle();
			idMaster = pParent->GetSelfID();
		}

		return(NewDBReplay(timestamp, idPackage, styleMaster, idMaster, styleSlave, idSlave, _FunctorStyle));
	}


	int NewDBReplay(CRTEBase* _pHost, std::shared_ptr<CRTMail> _pMail, const int _SlaveStyle, const int _SlaveID, const int _FunctorStyle)
	{
		const auto timestamp = GetTimeStampString();
		const auto idPackage = _pMail->GetSelfID();
		const auto styleMaster = _pHost->GetRTEStyle();
		const auto idMaster = _pHost->GetSelfID();

		return(NewDBReplay(timestamp, idPackage, styleMaster, idMaster, _SlaveStyle, _SlaveID, _FunctorStyle));
	}


	int NewDBReplay(const std::string& _TimeStamp, const int _PackageID, const int _MasterStyle, const int _MasterID, const int _SlaveStyle, const int _SlaveID, const int _FunctorStyle)
	{
		const auto ModeHistory = CurrentHistory();
		if (RTNSTool::NormalValue() != ModeHistory)
		{
			return(-1);
		}

		auto pObj = RTNSTool::NewSharedPtrObj<CRTDBReplay>();
		if (nullptr == pObj)
		{
			return(0);
		}

		pObj->SetTimeStamp(_TimeStamp);
		pObj->SetPackageID(_PackageID);
		pObj->SetMasterStyle(_MasterStyle);
		pObj->SetMasterID(_MasterID);
		pObj->SetSlaveStyle(_SlaveStyle);
		pObj->SetSlaveID(_SlaveID);
		pObj->SetFunctorStyle(_FunctorStyle);

		GetReplayManager().Post(pObj);

		return(pObj->GetID());
	}


	std::vector<std::shared_ptr<CRTDBReplay>> FindAllDBReplayBySession(const int _FunctorStyle)
	{
		std::vector<std::shared_ptr<CRTDBReplay>> Result;
		Result.reserve(VECTOR_RESERVE_SIZE);
		int start = 0;
		auto& Manager = GetReplayManager();
		const auto pLatestValue = Manager.GetLatestRecord();
		const std::vector<std::string> Keys{ "slavestyle", "slaveid", "functorstyle" };
		std::vector<std::string> Values{ RTNSTool::int2string(RTES_Session), "", RTNSTool::int2hexstring(_FunctorStyle) };

		for (int index = 1; index < pLatestValue->GetID(); ++index)
		{
			Values[1] = RTNSTool::int2string(index);

			const auto dict = RTNSTool::MakeDict(Keys, Values);

			auto pValue = Manager.GetOnlyOne(dict, start);
			if (nullptr == pValue)
			{
				break;
			}

			Result.push_back(pValue);
			start = pValue->GetIndex();
		}//for

		return(Result);
	}


	std::shared_ptr<CRTDBReplay> FindDBReplayBySession(const int _idSession, const int _FunctorStyle, const int _Index)
	{
		const static std::vector<std::string> _FindDBReplayBySessionKeys{ "slavestyle", "slaveid", "functorstyle" };
		std::vector<std::string> Values{ RTNSTool::int2string(RTES_Session), RTNSTool::int2string(_idSession), RTNSTool::int2hexstring(_FunctorStyle) };
		const auto dict = RTNSTool::MakeDict(_FindDBReplayBySessionKeys, Values);

		auto pObj = GetReplayManager().GetOnlyOne(dict, _Index);

		return(pObj);
	}


	std::vector<std::shared_ptr<CRTDBReplay>> FindAllDBReplayByGame(const int _idSession, const int _idStart, const int _idEnd, const int _FunctorStyle)
	{
		const std::vector<std::string> Keys{ "masterstyle", "masterid", "slavestyle", "functorstyle" };
		const std::vector<std::string> Values{ RTNSTool::int2string(RTES_Session), RTNSTool::int2string(_idSession), RTNSTool::int2string(RTES_Game), RTNSTool::int2string(_FunctorStyle) };
		const auto dict = RTNSTool::MakeDict(Keys, Values);

		const auto Result = GetReplayManager().GetAllByRange(dict, _idStart, _idEnd);

		return(Result);
	}


	std::shared_ptr<CRTDBReplay> FindDBReplayByCursor(std::shared_ptr<CRTDBCursor> _pCursor, const int _OpIndex)
	{
		const auto Start = _pCursor->GetStartReplayID();
		const auto End = _pCursor->GetEndReplayID();
		const auto Cur = _pCursor->GetCurrent();
		const auto Index = _pCursor->GetCurrent() + _OpIndex;
		if (Index < Start || End <= Index)
		{
			return(nullptr);
		}

		std::vector<std::string> Keys{};
		std::vector<std::string> Values{};
		if (Start == Cur)
		{
			Keys = { "slavestyle", "slaveid" };
			Values = { RTNSTool::int2string(RTES_Session), RTNSTool::int2string(_pCursor->GetSessionID()) };

		}
		else
		{
			Keys = { "masterstyle", "masterid" , "slavestyle", "slaveid" };
			Values = { RTNSTool::int2string(RTES_Session), RTNSTool::int2string(_pCursor->GetSessionID()), RTNSTool::int2string(RTES_Game), RTNSTool::int2string(_pCursor->GetGameID()) };
		}

		const auto dict = RTNSTool::MakeDict(Keys, Values);

		const auto pReplay = GetReplayManager().GetOnlyOne(dict, Cur, _OpIndex);
		if (nullptr != pReplay)
		{
			const auto NewCur = pReplay->GetID() + _OpIndex;
			if (NewCur < End)
			{
				_pCursor->SetCurrent(NewCur);
			}
			else
			{
				return(nullptr);
			}
		}//if

		return(pReplay);
	}


	std::shared_ptr<CRTDBCursor> NewDBCursor(const int _idRoot, const int _idSession, const int _idGame, const int _StartReplayID, const int _EndReplayID, const int _Force)
	{
		auto pObj = RTNSTool::NewSharedPtrObj<CRTDBCursor>();
		if (nullptr == pObj)
		{
			return(0);
		}

		pObj->SetRootID(_idRoot);
		pObj->SetSessionID(_idSession);
		pObj->SetGameID(_idGame);
		pObj->SetStartReplayID(_StartReplayID);
		pObj->SetEndReplayID(_EndReplayID);
		pObj->SetCurrent(_StartReplayID);
		pObj->SetForce(_Force);

		GetCursorManager().Post(pObj);

		return(pObj);
	}


	std::shared_ptr<CRTDBCursor> FindDBCursor(const int _ID)
	{
		auto pObj = GetCursorManager().Get(_ID);

		return(pObj);
	}


	std::shared_ptr<CRTDBCursor> LatestDBCursor(void)
	{
		auto pValue = GetCursorManager().GetLatestRecord();

		return(pValue);
	}

}//RTNSDB

