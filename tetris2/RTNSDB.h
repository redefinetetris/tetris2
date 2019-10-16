#ifndef __RTNSDB_H__
#define __RTNSDB_H__


#include <string>
#include <vector>
#include <memory>


class CRTDict;
class CRTMail;
class CRTEBase;
class CRTDBGame;
class CRTDBUser;
class CRTDBBlock;
class CRTDBSpeed;
class CRTDBToken;
class CRTDBCursor;
class CRTDBReplay;
class CRTDBSession;
class CRTDBPackage;
class CRTDBTransfer;
class CRTDBPassword;


namespace RTNSDB
{
	std::string DQuot(const std::string _str);


	//当前时间相关
	std::string GetCurrentDateTime(const char _ch = '\0');

	long long GetTimeStamp(void);
	std::string GetTimeStampString(void);


	//角色相关
	int RoleAdmin(void);
	int RoleGod(void);
	int RolePlayer(void);


	//状态相关
	int StateGood(void);
	int StateBad(void);
	int StateFreeze(void);
	int StateDelete(void);


	//方块信息相关
	std::shared_ptr<CRTDBBlock> GetDBBlock(const int _ID);
	std::shared_ptr<CRTDBBlock> GetNextDBBlock(const int _ID);
	int GetNextDBBlockID(const int _ID);
	int GetBase(const int _GroupID);

	int GetRandomDBBlockID(const int _GroupID);
	std::vector<int> GetAllDBBlockID(const int _GroupID);


	//旋转相关
	std::shared_ptr<CRTDBTransfer> GetTransfer(const int _ID);
	std::shared_ptr<CRTDBTransfer> GetTransferByBlockID(const int _BlockID);


	//速度相关
	std::shared_ptr<CRTDBSpeed> GetSpeed(const int _ID);
	int GetSpeedByTime(const int _ID);


	//金币相关
	unsigned int GetCoinsPerLine(void);


	//时间相关
	long long GetNanoSecond(const long long _nanoseconds);
	long long GetNSByMicroSecond(const long long _macroseconds);
	long long GetNSByMilliSecond(const long long _milliseconds);
	long long GetNSBySecond(const long long _seconds);
	long long GetNSByMinute(const long long _minutes);
	long long GetNSByHour(const long long _hours);
	long long GetNSByDay(const long long _days);


	//登录状态相关
	long long UpJWTID(void);
	const std::string& GetJWTKey(void);
	std::string GenerateTokenSimple(const int _idUser);
	std::string GenerateToken(const int _idUser);
	CRTDict DecodeToken(const std::string& _Token);
	CRTDict DecodeTokenByDB(const std::string& _Token);
	bool TokenTimeout(const CRTDict& _DictPayload);
	//校验成功时返回用户的id（大于0）
	int VerifyToken(const std::string& _Token, const bool _VerifyTime);
	std::string RefreshToken(const std::string& _Token);
	int GetUserIDByToken(const std::string& _Token, const bool _Verify = true);


	//令牌相关
	int SaveToken(const int _idUser, const std::string& _Token);
	std::shared_ptr<CRTDBToken> FindToken(const int _idUser);
	std::shared_ptr<CRTDBToken> FindToken(const std::string& _Token);
	int DeleteToken(const int _idUser);
	int DeleteToken(const std::string& _Token);


	//用户相关
	std::shared_ptr<CRTDBUser> FindUser(const int _idUser);
	std::shared_ptr<CRTDBUser> FindUser(const std::string _User);
	int DeleteUser(const int _idUser);
	int VerifyUser(const std::string _User, const std::string _Key);
	//成功时返回用户的id（大于0）
	int NewUser(const std::string _User, const std::string _Key);
	int SaveUser(const std::string _User);
	int SavePassword(const int _idUser, const std::string _Key);
	std::shared_ptr<CRTDBPassword> FindPassword(const int _idUser);
	int VerifyPassword(const int _idUser, const std::string _Key);


	//游戏相关
	int NewDBSessionID(const int _idUser);
	int NewDBGameID(const int _idUser, const int _idSession);

	int DefaultDBRootID(void);
	int UpDBRootID(void);
	int UpDBSessionID(void);
	int UpDBGameID(void);


	//邮件包相关
	int NewDBPackage(std::shared_ptr<CRTMail> _pMail);
	int NewDBPackage(const std::string& _TimeStamp, const std::string& _IP, const std::string& _Mail);
	int UpdateDBPackage(std::shared_ptr<CRTMail> _pMail);
	int UpdateDBPackage(const int _ID, const std::string& _Mail);
	std::shared_ptr<CRTDBPackage> FindDBPackage(const std::string& _TimeStamp);
	std::shared_ptr<CRTDBPackage> GetDBPackage(const int _ID);
	//构造复盘邮件包
	std::shared_ptr<CRTMail> NewReplayMailByCursor(const int _RootID, const int _idPackage, const int _History);


	//指令相关
	int NewDBReplay(CRTEBase* _pHost, std::shared_ptr<CRTMail> _pMail, const int _FunctorStyle);
	int NewDBReplay(CRTEBase* _pHost, std::shared_ptr<CRTMail> _pMail, const int _SlaveStyle, const int _SlaveID, const int _FunctorStyle);
	int NewDBReplay(const std::string& _TimeStamp, const int _PackageID, const int _MasterStyle, const int _MasterID, const int _SlaveStyle, const int _SlaveID, const int _FunctorStyle);
	//所有的会话
	std::vector<std::shared_ptr<CRTDBReplay>> FindAllDBReplayBySession(const int _FunctorStyle);
	std::shared_ptr<CRTDBReplay> FindDBReplayBySession(const int _idSession, const int _FunctorStyle, int _Index);
	//每个会话的game
	//左闭右开
	std::vector<std::shared_ptr<CRTDBReplay>> FindAllDBReplayByGame(const int _idSession, const int _idStart, const int _idEnd, const int _FunctorStyle);
	std::shared_ptr<CRTDBReplay> FindDBReplayByCursor(std::shared_ptr<CRTDBCursor> _pCursor, const int _OpIndex);


	//复盘的进度
	std::shared_ptr<CRTDBCursor> NewDBCursor(const int _idRoot, const int _idSession, const int _idGame, const int _StartReplayID, const int _EndReplayID, const int _Force);
	std::shared_ptr<CRTDBCursor> FindDBCursor(const int _ID);
	std::shared_ptr<CRTDBCursor> LatestDBCursor(void);
}//RTNSDB


#endif

