#include "mail.h"


CRTDict LoginMail(const std::string user, const std::string key, const std::string vcode)
{
	CRTDict args;
	args["user"] = user;
	args["key"] = key;
	args["vcode"] = vcode;

	std::vector<std::string> ops{ "user", "login" };

	CRTDict dict;
	dict["ops"] = ops;
	dict["args"] = args;

	return(dict);
}


CRTDict RootMail(const std::string token, const int sessionid, const int length, const int width, const int height, const int number)
{
	CRTDict args;
	args["token"] = token;
	args["sessionid"] = sessionid;
	args["length"] = length;
	args["width"] = width;
	args["height"] = height;
	if (number)
	{
		args["number"] = number;
	}

	std::vector<std::string> ops{ "root", "newsession" };

	CRTDict dict;
	dict["ops"] = ops;
	dict["args"] = args;

	return(dict);
}


CRTDict SessionMail(const std::string token, const int sessionid, const int gameid)
{
	CRTDict args;
	args["token"] = token;
	args["sessionid"] = sessionid;
	args["gameid"] = gameid;

	std::vector<std::string> ops{ "session", "newgame" };

	CRTDict dict;
	dict["ops"] = ops;
	dict["args"] = args;

	return(dict);
}


CRTDict NewMail(const std::string token, const int length, const int width, const int height, const int sessionid, const int gameid)
{
	CRTDict args;
	args["token"] = token;
	args["sessionid"] = sessionid;
	args["gameid"] = gameid;
	args["length"] = length;
	args["width"] = width;
	args["height"] = height;

	std::vector<std::string> ops{ "game", "new" };

	CRTDict dict;
	dict["ops"] = ops;
	dict["args"] = args;

	return(dict);
}


CRTDict FireMail(const std::string token, const int sessionid, const std::string op)
{
	CRTDict args;
	args["token"] = token;
	args["sessionid"] = sessionid;
	args["op"] = op;

	std::vector<std::string> ops{ "session", "fire" };

	CRTDict dict;
	dict["ops"] = ops;
	dict["args"] = args;

	return(dict);
}


CRTDict MoveMail(const std::string token, const int x, const int y, const int z, const int sessionid, const int gameid)
{
	CRTDict args;
	args["token"] = token;
	args["sessionid"] = sessionid;
	args["gameid"] = gameid;
	args["x"] = x;
	args["y"] = y;
	args["z"] = z;

	std::vector<std::string> ops{ "game", "move" };

	CRTDict dict;
	dict["ops"] = ops;
	dict["args"] = args;

	return(dict);
}


CRTDict TransferMail(const std::string token, const int sessionid, const int gameid, const int style)
{
	CRTDict args;
	args["token"] = token;
	args["sessionid"] = sessionid;
	args["gameid"] = gameid;
	if (style)
	{
		args["style"] = style;
	}

	std::vector<std::string> ops{ "game", "transfer" };

	CRTDict dict;
	dict["ops"] = ops;
	dict["args"] = args;

	return(dict);
}


CRTDict WatchMail(const std::string token, const int rootid, const int sessionid, const int gameid)
{
	CRTDict args;
	args["token"] = token;
	args["rootid"] = rootid;
	args["sessionid"] = sessionid;
	args["gameid"] = gameid;

	std::vector<std::string> ops{ "game", "watch" };

	CRTDict dict;
	dict["ops"] = ops;
	dict["args"] = args;

	return(dict);
}


CRTDict HealthMail(const std::string token, const std::string rte, const int id, const std::string health)
{
	CRTDict args;
	args["token"] = token;
	args[rte + "id"] = id;
	args["health"] = health;

	std::vector<std::string> ops{ rte, "health" };

	CRTDict dict;
	dict["ops"] = ops;
	dict["args"] = args;

	return(dict);
}


CRTDict HealthMail(const std::string token, const std::string rte, const int id, const std::string rte2, const int id2, const std::string health)
{
	CRTDict args;
	args["token"] = token;
	args[rte + "id"] = id;
	args[rte2 + "id"] = id2;
	args["health"] = health;

	std::vector<std::string> ops{ rte, "health" };

	CRTDict dict;
	dict["ops"] = ops;
	dict["args"] = args;

	return(dict);
}


CRTDict HealthClockMail(const std::string token, const int style, const int timerid, const std::string health)
{
	CRTDict args;
	args["token"] = token;
	args["style"] = style;
	args["timerid"] = timerid;
	args["health"] = health;

	std::vector<std::string> ops{ "clock", "health" };

	CRTDict dict;
	dict["ops"] = ops;
	dict["args"] = args;

	return(dict);
}


CRTDict QuerySIDMail(const std::string token)
{
	CRTDict args;
	args["token"] = token;
	args["sessionid"] = 1;

	std::vector<std::string> ops{ "root", "query" };

	CRTDict dict;
	dict["ops"] = ops;
	dict["args"] = args;

	return(dict);
}


CRTDict QueryGIDMail(const std::string token)
{
	CRTDict args;
	args["token"] = token;
	args["gameid"] = 1;

	std::vector<std::string> ops{ "root", "query" };

	CRTDict dict;
	dict["ops"] = ops;
	dict["args"] = args;

	return(dict);
}


CRTDict QuerySMail(const std::string token)
{
	CRTDict args;
	args["token"] = token;
	args["style"] = "session";

	std::vector<std::string> ops{ "replay", "query" };

	CRTDict dict;
	dict["ops"] = ops;
	dict["args"] = args;

	return(dict);
}


CRTDict QueryGMail(const std::string token, const int sessionid)
{
	CRTDict args;
	args["token"] = token;
	args["style"] = "game";
	args["sessionid"] = sessionid;

	std::vector<std::string> ops{ "replay", "query" };

	CRTDict dict;
	dict["ops"] = ops;
	dict["args"] = args;

	return(dict);
}


CRTDict InitMail(const std::string token, const int startreplayid, const int sessionid, const int gameid, const int force)
{
	CRTDict args;
	args["token"] = token;
	args["startreplayid"] = startreplayid;
	args["endreplayid"] = 0;
	args["sessionid"] = sessionid;
	args["gameid"] = gameid;
	if (force)
	{
		args["force"] = force;
	}

	std::vector<std::string> ops{ "replay", "init" };

	CRTDict dict;
	dict["ops"] = ops;
	dict["args"] = args;

	return(dict);
}


CRTDict BackwardMail(const std::string token, const int cursorid)
{
	CRTDict args;
	args["token"] = token;
	args["cursorid"] = cursorid;

	std::vector<std::string> ops{ "replay", "backward" };

	CRTDict dict;
	dict["ops"] = ops;
	dict["args"] = args;

	return(dict);
}


CRTDict ForwardMail(const std::string token, const int cursorid)
{
	CRTDict args;
	args["token"] = token;
	args["cursorid"] = cursorid;

	std::vector<std::string> ops{ "replay", "forward" };

	CRTDict dict;
	dict["ops"] = ops;
	dict["args"] = args;

	return(dict);
}


CRTDict QueryRootMail(const std::string token, const std::string style, const int styleid)
{
	CRTDict args;
	args["token"] = token;
	if (0 < style.size())
	{
		args[style] = styleid;
	}

	std::vector<std::string> ops{ "root", "query" };

	CRTDict dict;
	dict["ops"] = ops;
	dict["args"] = args;

	return(dict);
}

