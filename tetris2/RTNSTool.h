#ifndef __RTNSTOOL_H__
#define __RTNSTOOL_H__


#include <string>
#include <vector>
#include <memory>


class CRTBase;
class CRTDict;
class CRTMail;
class CRTEBase;
class CRTBlock;
class CRTETimer;


namespace RTNSTool
{
	long GetMicroSecond(const long _Time);
	long GetMilliSecond(const long _Time);
	long GetSecond(const long _Time);
	long GetMinute(const long _Time);
	long GetHour(const long _Time);
	long GetDay(const long _Time);


	int string2int(const std::string _Str);
	std::string int2string(const int _Val);
	std::string int2hexstring(const int _Val);


	unsigned int string2uint(const std::string _Str);
	std::string uint2string(const unsigned int _Val);
	std::string uint2hexstring(const unsigned int _Val);


	long long string2longlong(const std::string _Str);
	std::string longlong2string(const long long _Val);


	double string2double(const std::string _Str);
	std::string double2string(const double _Val);


	CRTDict string2dict(const std::string _Str);
	std::string dict2string(const CRTDict& _Dict);


	std::vector<int> string2vector(const std::string& _Block);
	std::string vector2string(const std::vector<int>& _Vect);


	int GetThreadID(void);
	std::string GetThreadIDString(void);


	template<class T>
	std::shared_ptr<T> NewSharedPtrObj(void)
	{
		std::shared_ptr<T> pObj(new (std::nothrow) T());

		return(pObj);
	}


	template<class T, class T_Arg>
	std::shared_ptr<T> NewSharedPtrObj(T_Arg _Arg)
	{
		std::shared_ptr<T> pObj(new (std::nothrow) T(_Arg));

		return(pObj);
	}

	template<class T, class T_Arg, class T_Arg2, class T_Arg3>
	std::shared_ptr<T> NewSharedPtrObj(T_Arg _Arg, T_Arg2 _Arg2, T_Arg3 _Arg3)
	{
		std::shared_ptr<T> pObj(new (std::nothrow) T(_Arg, _Arg2, _Arg3));

		return(pObj);
	}


	CRTDict MakeDict(const std::string& _Key, const std::string& _Value);
	CRTDict MakeDict(const std::vector<std::string>& _Keys, const std::vector<std::string>& _Values);
	CRTDict MakeDict(const std::string& _Key, const std::string& _Value, const std::string& _Key2, const std::string& _Value2);


	const std::string& SignHubLoop(void);
	const std::string& SignSessionLoop(void);
	const std::string& SignGameLoop(void);
	const std::string& SignHistory(void);
	int BackwardValue(void);
	int NormalValue(void);
	int ForwardValue(void);
	int HubLoopValue(void);
	int SessionLoopValue(void);
	int GameLoopValue(void);


	int RandomM(const int _Min, const int _Max);//[_Min, _Max]
	std::string RandomString(const int _Length = 20);


	bool DetectHit(const CRTBlock& _Area, const CRTBlock& _Block);
	bool DetectFreeze(const CRTDict& _Args);
	void Merge(CRTBlock& _Area, const CRTBlock& _Block);
	void Merge(CRTBlock& _Area, const CRTBlock& _Block, const int _Cell);
	std::vector<int> DetectTarget(const CRTBlock& _Area, const CRTBlock& _Block);


	void InsertLines(const CRTBlock& _SrcArea, const std::vector<int>& _SrcLines, const std::vector<int>& _Cells, CRTBlock& _DestArea);
	void RemoveLines(const CRTBlock& _SrcArea, const std::vector<int>& _SrcLines, CRTBlock& _DestArea);


	void RecoverBlockPoint(CRTBlock& _Block, const CRTDict& _Args);
	int RecoverBlock(CRTBlock& _Block, const CRTDict& _Args, const std::string _Style = "id");
	int RecoverHealthAndMask(CRTEBase* _pRTEBase, const CRTDict& _Args);


	int GetBackDictID(void);


	std::shared_ptr<CRTMail> NewMail(void);
	std::shared_ptr<CRTMail> BackMail(const std::string& _Msg);
	std::shared_ptr<CRTMail> BackMail(const CRTDict& _Dict);
	std::shared_ptr<CRTMail> BackMail(const std::shared_ptr<CRTMail> _pSrcMail, const CRTDict& _Dict);

	CRTDict BackDict(const std::vector<std::string>& _Ops, const CRTDict& _Args, const std::string _Code = "ok", const std::string _Msg = "luck", const int _ID = 0);
	CRTDict BackDict(const std::vector<std::string>& _Ops, const std::string _Code = "ok", const std::string _Msg = "luck", const int _ID = 0);

	CRTDict BackDictBy(const std::shared_ptr<CRTMail> _pSrcMail, const CRTDict& _Args, const std::string _Code = "ok", const std::string _Msg = "luck");
	CRTDict BackDictBy(const std::shared_ptr<CRTMail> _pSrcMail, const std::string _Code = "ok", const std::string _Msg = "luck");

	CRTDict BackDict4Loop(const std::shared_ptr<CRTMail> _pSrcMail, const CRTDict& _Args, const std::string _Code = "ok", const std::string _Msg = "luck");
	CRTDict BackDict4Loop(const std::shared_ptr<CRTMail> _pSrcMail, const std::string _Code = "ok", const std::string _Msg = "luck");
	int VerifyDict4Loop(CRTDict& _BackDict, const CRTDict& _Dict);

	std::shared_ptr<CRTMail> BackMailBy(const std::shared_ptr<CRTMail> _pSrcMail, const CRTDict& _Args, const std::string _Code = "ok", const std::string _Msg = "luck");
	std::shared_ptr<CRTMail> BackMailBy(const std::shared_ptr<CRTMail> _pSrcMail, const std::string _Code = "ok", const std::string _Msg = "luck");


	std::string ToBase64(const std::string _Str);
	std::string FromBase64(const std::string _StrBase64);


	std::string ToEncrypt(const std::string _Str, const std::string _Key);
	std::string FromEncrypt(const std::string _StrEncrypt, const std::string _Key);


	std::string GetStrOps(const std::vector<std::string>& _Ops, unsigned int _Index = 1);


	CRTDict WatchDict(const CRTBlock& _Area, const CRTBlock& _Block);
	CRTDict SessionDict(const int _idSession, const int _idGame, const std::string _Op, const int _LoopStyle);
	std::shared_ptr<CRTMail> SessionMail(const int _idSession, const int _idGame, const std::string _Op, const int _LoopStyle);


	std::string GetTimerMsg4RTEGame(const int _idSession, const int _idGame, const std::string _Op);
	std::string GetTimerMsg4RTESession(const int _idSession, const std::string _Op);
	std::string GetTimerMsg4RTEDB(const int _idDB, const std::string _Op);
	std::string GetTimerMsg4RTERoot(const int _idRoot, const int _idSession, const std::string _Op);


	std::vector<std::shared_ptr<CRTMail>> GetDBClockMails(const int _idDB, const std::string _Op, const int _FlushTime, const int _DownTTLTime, const int _WashTTLTime, const int _Circle = 1);
	std::shared_ptr<CRTMail> GetSessionTimerMail(const int _idSession, const std::string _Card, const std::string _Op, const int _TollTime, const std::string _Msg);
	std::vector<std::shared_ptr<CRTMail>> GetSessionClockMails(const int _idRoot, const int _idSession, const std::string _Op, const int _JumpTime, const int _RaceTime, const int _MoveTime);


	CRTDict TimerDict(const std::string _Src, const int _Style, const int _TimerID, const int _Circle, const std::string _Op, const int _MicroSeconds, const std::string _Card, const std::string _Msg);
	std::shared_ptr<CRTMail> TimerMail(const std::string _Src, const int _Style, const int _TimerID, const int _Circle, const std::string _Op, const int _MicroSeconds, const std::string _Card, const std::string _Msg);


	int GetIntValue4Dict(const CRTDict& _Dict, const std::string _Key, const int _Default);
	std::string GetStringValue4Dict(const CRTDict& _Dict, const std::string _Key, const std::string _Default);


	CRTDict GetDictByTimer(const CRTETimer& _Timer);


	std::shared_ptr<CRTMail> GetMailByTrail(const int _RootID, const int _ReplayMode = 0);


	bool NewGameSpace(std::unique_ptr<CRTBlock>& _pArea, std::unique_ptr<CRTBlock>& _pAreaBuffer, std::unique_ptr<CRTBlock>& _pBlock, std::unique_ptr<CRTBlock>& _pBlockBuffer, const int _Length, const int _Width, const int _Base);
	bool DeleteGameSpace(std::unique_ptr<CRTBlock>& _pArea, std::unique_ptr<CRTBlock>& _pAreaBuffer, std::unique_ptr<CRTBlock>& _pBlock, std::unique_ptr<CRTBlock>& _pBlockBuffer);

	int DoHealth(CRTBase* _pHost, const CRTDict& _Args);

}//RTNSTool


#endif

