#ifndef __MAIL_H__
#define __MAIL_H__


#include <string>
#include <vector>
#include "RTDict.h"


CRTDict LoginMail(const std::string user, const std::string key, const std::string vcode);
CRTDict RootMail(const std::string token, const int sessionid, const int length, const int width, const int height, const int number = 0);
CRTDict SessionMail(const std::string token, const int sessionid, const int gameid);
CRTDict NewMail(const std::string token, const int length, const int width, const int height, const int sessionid, const int gameid);
CRTDict FireMail(const std::string token, const int sessionid, const std::string op);
CRTDict MoveMail(const std::string token, const int x, const int y, const int z, const int sessionid, const int gameid);
CRTDict TransferMail(const std::string token, const int sessionid, const int gameid, const int style = 0);
CRTDict WatchMail(const std::string token, const int rootid, const int sessionid, const int gameid);

CRTDict HealthMail(const std::string token, const std::string rte, const int id, const std::string health);
CRTDict HealthMail(const std::string token, const std::string rte, const int id, const std::string rte2, const int id2, const std::string health);
CRTDict HealthClockMail(const std::string token, const int style, const int timerid, const std::string health);

CRTDict QuerySIDMail(const std::string token);
CRTDict QueryGIDMail(const std::string token);


CRTDict QuerySMail(const std::string token);
CRTDict QueryGMail(const std::string token, const int sessionid);
CRTDict InitMail(const std::string token, const int startreplayid, const int sessionid, const int gameid, const int force = 1);
CRTDict BackwardMail(const std::string token, const int cursorid);
CRTDict ForwardMail(const std::string token, const int cursorid);


CRTDict QueryRootMail(const std::string token, const std::string style = "", const int styleid = 0);


#endif

