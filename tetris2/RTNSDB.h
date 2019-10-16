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


	//��ǰʱ�����
	std::string GetCurrentDateTime(const char _ch = '\0');

	long long GetTimeStamp(void);
	std::string GetTimeStampString(void);


	//��ɫ���
	int RoleAdmin(void);
	int RoleGod(void);
	int RolePlayer(void);


	//״̬���
	int StateGood(void);
	int StateBad(void);
	int StateFreeze(void);
	int StateDelete(void);


	//������Ϣ���
	std::shared_ptr<CRTDBBlock> GetDBBlock(const int _ID);
	std::shared_ptr<CRTDBBlock> GetNextDBBlock(const int _ID);
	int GetNextDBBlockID(const int _ID);
	int GetBase(const int _GroupID);

	int GetRandomDBBlockID(const int _GroupID);
	std::vector<int> GetAllDBBlockID(const int _GroupID);


	//��ת���
	std::shared_ptr<CRTDBTransfer> GetTransfer(const int _ID);
	std::shared_ptr<CRTDBTransfer> GetTransferByBlockID(const int _BlockID);


	//�ٶ����
	std::shared_ptr<CRTDBSpeed> GetSpeed(const int _ID);
	int GetSpeedByTime(const int _ID);


	//������
	unsigned int GetCoinsPerLine(void);


	//ʱ�����
	long long GetNanoSecond(const long long _nanoseconds);
	long long GetNSByMicroSecond(const long long _macroseconds);
	long long GetNSByMilliSecond(const long long _milliseconds);
	long long GetNSBySecond(const long long _seconds);
	long long GetNSByMinute(const long long _minutes);
	long long GetNSByHour(const long long _hours);
	long long GetNSByDay(const long long _days);


	//��¼״̬���
	long long UpJWTID(void);
	const std::string& GetJWTKey(void);
	std::string GenerateTokenSimple(const int _idUser);
	std::string GenerateToken(const int _idUser);
	CRTDict DecodeToken(const std::string& _Token);
	CRTDict DecodeTokenByDB(const std::string& _Token);
	bool TokenTimeout(const CRTDict& _DictPayload);
	//У��ɹ�ʱ�����û���id������0��
	int VerifyToken(const std::string& _Token, const bool _VerifyTime);
	std::string RefreshToken(const std::string& _Token);
	int GetUserIDByToken(const std::string& _Token, const bool _Verify = true);


	//�������
	int SaveToken(const int _idUser, const std::string& _Token);
	std::shared_ptr<CRTDBToken> FindToken(const int _idUser);
	std::shared_ptr<CRTDBToken> FindToken(const std::string& _Token);
	int DeleteToken(const int _idUser);
	int DeleteToken(const std::string& _Token);


	//�û����
	std::shared_ptr<CRTDBUser> FindUser(const int _idUser);
	std::shared_ptr<CRTDBUser> FindUser(const std::string _User);
	int DeleteUser(const int _idUser);
	int VerifyUser(const std::string _User, const std::string _Key);
	//�ɹ�ʱ�����û���id������0��
	int NewUser(const std::string _User, const std::string _Key);
	int SaveUser(const std::string _User);
	int SavePassword(const int _idUser, const std::string _Key);
	std::shared_ptr<CRTDBPassword> FindPassword(const int _idUser);
	int VerifyPassword(const int _idUser, const std::string _Key);


	//��Ϸ���
	int NewDBSessionID(const int _idUser);
	int NewDBGameID(const int _idUser, const int _idSession);

	int DefaultDBRootID(void);
	int UpDBRootID(void);
	int UpDBSessionID(void);
	int UpDBGameID(void);


	//�ʼ������
	int NewDBPackage(std::shared_ptr<CRTMail> _pMail);
	int NewDBPackage(const std::string& _TimeStamp, const std::string& _IP, const std::string& _Mail);
	int UpdateDBPackage(std::shared_ptr<CRTMail> _pMail);
	int UpdateDBPackage(const int _ID, const std::string& _Mail);
	std::shared_ptr<CRTDBPackage> FindDBPackage(const std::string& _TimeStamp);
	std::shared_ptr<CRTDBPackage> GetDBPackage(const int _ID);
	//���츴���ʼ���
	std::shared_ptr<CRTMail> NewReplayMailByCursor(const int _RootID, const int _idPackage, const int _History);


	//ָ�����
	int NewDBReplay(CRTEBase* _pHost, std::shared_ptr<CRTMail> _pMail, const int _FunctorStyle);
	int NewDBReplay(CRTEBase* _pHost, std::shared_ptr<CRTMail> _pMail, const int _SlaveStyle, const int _SlaveID, const int _FunctorStyle);
	int NewDBReplay(const std::string& _TimeStamp, const int _PackageID, const int _MasterStyle, const int _MasterID, const int _SlaveStyle, const int _SlaveID, const int _FunctorStyle);
	//���еĻỰ
	std::vector<std::shared_ptr<CRTDBReplay>> FindAllDBReplayBySession(const int _FunctorStyle);
	std::shared_ptr<CRTDBReplay> FindDBReplayBySession(const int _idSession, const int _FunctorStyle, int _Index);
	//ÿ���Ự��game
	//����ҿ�
	std::vector<std::shared_ptr<CRTDBReplay>> FindAllDBReplayByGame(const int _idSession, const int _idStart, const int _idEnd, const int _FunctorStyle);
	std::shared_ptr<CRTDBReplay> FindDBReplayByCursor(std::shared_ptr<CRTDBCursor> _pCursor, const int _OpIndex);


	//���̵Ľ���
	std::shared_ptr<CRTDBCursor> NewDBCursor(const int _idRoot, const int _idSession, const int _idGame, const int _StartReplayID, const int _EndReplayID, const int _Force);
	std::shared_ptr<CRTDBCursor> FindDBCursor(const int _ID);
	std::shared_ptr<CRTDBCursor> LatestDBCursor(void);
}//RTNSDB


#endif

