#include "main.h"


#define BUFFER_SIZE (4096)


SOCKET __Socket = INVALID_SOCKET;
addrinfo* __pResult = nullptr;
const char* __Port = "60000";
char __buffer[BUFFER_SIZE] = { '\0' };
const int __family = AF_INET;


std::string __user = "red";
std::string __key = "army";
std::string __vcode = "0a8k";
std::string __token;
int __host = 1;
int __number = 1;
int __replaymode = 0;
int __rootid = 1;
int __sessionid = 1;
int __gameid = 1;
int __repalyid = 0;
int __cursorid = 0;
const int __length = 20;
const int __width = 19;
const int __height = 18;
int __run = 1;


void InitData(void)
{
	__user = "red";
	__key = "army";
	__vcode = "0a8k";
	__token = "";
	__host = 0;
	__number = 0;
	__replaymode = 0;
	__rootid = 1;
	__sessionid = 0;
	__gameid = 0;
	__repalyid = 0;
	__cursorid = 1;
	__run = 1;
}


void InitReplayData(void)
{
	__user = "god";
	__key = "god";
	__vcode = "0a8k";
	__token = "";
	__host = 0;
	__number = 0;
	__replaymode = 1;
	__rootid = 1;
	__sessionid = 1;
	__gameid = 1;
	__repalyid = 0;
	__cursorid = 1;
	__run = 1;
}


void InitRedData(void)
{
	__user = "red";
	__key = "army";
	__vcode = "0a8k";
	__token = "";
	__host = 1;
	__number = 2;
	__replaymode = 0;
	__rootid = 1;
	__sessionid = 1;
	__gameid = 1;
	__repalyid = 0;
	__cursorid = 1;
	__run = 1;
}


void InitBlueData(void)
{
	__user = "blue";
	__key = "army";
	__vcode = "0a8k";
	__token = "";
	__host = 0;
	__number = 0;
	__replaymode = 0;
	__rootid = 1;
	__sessionid = 1;
	__gameid = 2;
	__repalyid = 0;
	__cursorid = 1;
	__run = 1;
}


int InitSocket(void)
{
	WSADATA wsadata;
	WORD version = MAKEWORD(2, 2);

	const auto codeVersion = WSAStartup(version, &wsadata);
	if (NO_ERROR != codeVersion)
	{
		return(-1);
	}

	addrinfo hint;
	memset(&hint, 0, sizeof(addrinfo));
	hint.ai_family = __family;
	hint.ai_socktype = SOCK_DGRAM;
	hint.ai_protocol = IPPROTO_UDP;

	const auto codeAddrInfo = getaddrinfo(nullptr, __Port, &hint, &__pResult);
	if (NO_ERROR != codeAddrInfo)
	{
		return(-2);
	}

	__Socket = socket(__pResult->ai_family, __pResult->ai_socktype, __pResult->ai_protocol);
	if (INVALID_SOCKET == __Socket)
	{
		return(-3);
	}

	return(0);
}


int __id = 0;


void Send2Server(CRTDict& dict)
{
	dict["id"] = ++__id;

	auto str = NSTool::dict2string(dict);
	auto pchs = str.c_str();
	auto chsLength = strlen(pchs);
	auto arLength = __pResult->ai_addrlen;

	sendto(__Socket, pchs, chsLength, 0, __pResult->ai_addr, arLength);
}


CRTDict Recv4Server(void)
{
	memset(__buffer, '\0', BUFFER_SIZE);

	const auto length = recv(__Socket, __buffer, BUFFER_SIZE, 0);
	CRTDict dict;

	if (length)
	{
		std::string str(__buffer);

		dict = NSTool::string2dict(str);
	}

	return(dict);
}


CRTDict SendRecv2Server(CRTDict& dict)
{
	Send2Server(dict);

	return(Recv4Server());
}


void SetTo(const int _X = 0, const int _Y = 0)
{
	const COORD pos{ _X,_Y };
	auto handle = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleCursorPosition(handle, pos);
}


void ClearScreenLine(const int _X, const int _Y, const int _Length = 80, const char _Sign = ' ')
{
	SetTo(_X, _Y);

	for (int index = 0; index < _Length; ++index)
	{
		std::cout << _Sign;
	}
}


void Show(const CRTDict& args)
{
	SetTo(0, 15);

	auto area = args["area"].GetString();
	int index = 0;
	char ch = 2;

	for (int x = 0; x < __length + 4 + 2; ++x)
	{
		for (int y = 0; y < __width + 2; ++y)
		{
			if ('0' == area[index])
			{
				std::cout << ' ';
			}
			else
			{
				std::cout << ch;
			}

			++index;
		}

		std::cout << std::endl;
	}
}


void Fire(const CRTDict& args)
{
	ClearScreenLine(0, 10);
	SetTo(0, 10);

	const auto ttf = args["ttf"].GetInt();
	std::cout << " time to fire: " << ttf;
}


void Win(void)
{
	ClearScreenLine(0, 10);
	SetTo(0, 10);

	std::cout << " *** win !!! *** ";
}


void Wait(const CRTDict& args)
{
	ClearScreenLine(0, 10);
	SetTo(0, 10);

	const auto total = args["total"].GetInt();
	const auto size = args["size"].GetInt();
	std::cout << " total: " << total << "\tcurrent: " << size;
}


bool Game(const CRTDict& dict)
{
	const auto ops = dict["ops"].GetVectorString();
	const auto op = ops[1];

	if ("over" == op)
	{
		std::cout << "***** game over *****" << std::endl;
		if (__replaymode)
		{
			__run += 1;
		}
		else
		{
			__run = 0;
		}

		return(false);
	}
	if ("win" == op)
	{
		Win();

		return(true);
	}

	if (dict.HasKey("args"))
	{
		auto args = dict["args"].GetDict();

		if (args.HasKey("area"))
		{
			Show(args);
		}
		else if (args.HasKey("ttf"))
		{
			Fire(args);
		}
		else if ("wait" == op)
		{
			Wait(args);
		}
	}

	return(true);
}


int UserKey(void)
{
	std::cout << "user: ";
	std::cin >> __user;

	std::cout << "key: ";
	std::cin >> __key;

	std::cout << "host: ";
	std::cin >> __host;

	if (__host)
	{
		std::cout << "number: ";
		std::cin >> __number;
	}

	std::cout << "session id: ";
	std::cin >> __sessionid;

	std::cout << "game id: ";
	std::cin >> __gameid;

	return(0);
}


void InitGame(void)
{
	auto login = LoginMail(__user, __key, __vcode);
	auto login_dict = SendRecv2Server(login);

	auto login_args = login_dict["args"].GetDict();
	__token = login_args["token"].GetString();

	auto qsid = QuerySIDMail(__token);
	auto qsid_dict = SendRecv2Server(qsid);

	auto qsid_args = qsid_dict["args"].GetDict();
	__sessionid = qsid_args["id"].GetInt();

	auto qgid = QueryGIDMail(__token);
	auto qgid_dict = SendRecv2Server(qgid);

	auto qgid_args = qgid_dict["args"].GetDict();
	__gameid = qgid_args["id"].GetInt();

	auto root = RootMail(__token, __sessionid, __length, __width, __height, __number);
	auto root_dict = SendRecv2Server(root);

	auto session = SessionMail(__token, __sessionid, __gameid);
	auto session_dict = SendRecv2Server(session);

	auto area = NewMail(__token, __length, __width, 0, __sessionid, __gameid);
	auto area_dict = SendRecv2Server(area);

	std::cout << "Press any key to run ..." << std::endl;
	const auto ch = getch();

	auto fire = FireMail(__token, __sessionid, "new");
	auto fire_dict = SendRecv2Server(fire);
}


void InitReplay(void)
{
	auto login = LoginMail(__user, __key, __vcode);
	auto login_dict = SendRecv2Server(login);

	auto login_args = login_dict["args"].GetDict();
	__token = login_args["token"].GetString();

	auto query = QuerySMail(__token);
	auto query_dict = SendRecv2Server(query);

	auto query_args = query_dict["args"].GetDict();
	auto SIDs = query_args["ids"].GetVectorInt();
	__repalyid = SIDs[0];

	auto init = InitMail(__token, __repalyid, __sessionid, __gameid);
	auto init_dict = SendRecv2Server(init);

	auto init_args = init_dict["args"].GetDict();
	__cursorid = init_args["cursorid"].GetInt();
}


void InitRace(void)
{
	auto login = LoginMail(__user, __key, __vcode);
	auto login_dict = SendRecv2Server(login);

	auto login_args = login_dict["args"].GetDict();
	__token = login_args["token"].GetString();

	if (__host)
	{
		auto root = RootMail(__token, __sessionid, __length, __width, __height, __number);
		auto root_dict = SendRecv2Server(root);
	}

	auto session = SessionMail(__token, __sessionid, __gameid);
	auto session_dict = SendRecv2Server(session);
}


int Run(void)
{
	fd_set readfds;
	const static int ms = 50;
	const static struct timeval _to { 0, ms };

	while (1)
	{
		FD_ZERO(&readfds);
		FD_SET(__Socket, &readfds);

		const int code = select(0, &readfds, nullptr, nullptr, &_to);

		if (code < 1)
		{
			Sleep(ms * 5);

			auto watch = WatchMail(__token, __rootid, __sessionid, __gameid);
			Send2Server(watch);

			continue;
		}

		if (FD_ISSET(__Socket, &readfds))
		{
			if (!Game(Recv4Server()))
			{
				if (0 == __replaymode)
				{
					break;
				}
			}
		}

		Sleep(ms);
	}//while

	return(0);
}


void FunThread(void)
{
	Run();
}


int Key(const char ch)
{
	if ('*' == ch)
	{
		return(0);
	}

	CRTDict dict;
	std::string health = "hungup";

	if ('r' == ch)
	{
		static int __healthRoot = 0;
		if (__healthRoot)
		{
			health = "run";
			__healthRoot = 0;
		}
		else
		{
			__healthRoot = 1;
		}
		dict = HealthMail(__token, "root", __rootid, health);
	}
	else if ('s' == ch)
	{
		static int __healthSession = 0;
		if (__healthSession)
		{
			health = "run";
			__healthSession = 0;
		}
		else
		{
			__healthSession = 1;
		}
		dict = HealthMail(__token, "session", __sessionid, health);
	}
	else if ('g' == ch)
	{
		static int __healthGame = 0;
		if (__healthGame)
		{
			health = "run";
			__healthGame = 0;
		}
		else
		{
			__healthGame = 1;
		}
		dict = HealthMail(__token, "game", __gameid, "session", __sessionid, health);
	}
	else if ('c' == ch)
	{
		static int __healthClock = 0;
		if (__healthClock)
		{
			health = "run";
			__healthClock = 0;
		}
		else
		{
			__healthClock = 1;
		}
		dict = HealthClockMail(__token, 2, __sessionid, health);
	}
	else if ('4' == ch)
	{
		dict = MoveMail(__token, 0, -1, 0, __sessionid, __gameid);
	}
	else if ('6' == ch)
	{
		dict = MoveMail(__token, 0, 1, 0, __sessionid, __gameid);
	}
	else if ('2' == ch)
	{
		dict = MoveMail(__token, 1, 0, 0, __sessionid, __gameid);
	}
	else if ('8' == ch)
	{
		dict = MoveMail(__token, -1, 0, 0, __sessionid, __gameid);
	}
	else if ('5' == ch)
	{
		dict = TransferMail(__token, __sessionid, __gameid);
	}
	//else if ('w' == ch)
	//{
	//	std::thread worker(FunThread);

	//	worker.detach();

	//	return(1);
	//}
	else if ('b' == ch)
	{
		dict = BackwardMail(__token, __cursorid);
	}
	else if ('f' == ch)
	{
		dict = ForwardMail(__token, __cursorid);
	}
	else
	{
		return(0);
	}

	Send2Server(dict);

	return(1);
}


void InitRaceData(const int replaymode)
{
	int style = 0;
	std::cout << "style: 1 -- red army, 2 -- blue army." << std::endl;
	std::cout << "Select: ";
	std::cin >> style;

	if (1 == style)
	{
		InitRedData();
	}
	else if (2 == style)
	{
		InitBlueData();
	}
	else
	{
		UserKey();
	}
}


void InitRaceReplayData(void)
{
	InitReplayData();

	std::cout << "style: 1 -- red army, 2 -- blue army." << std::endl;
	std::cout << "Select: ";
	std::cin >> __gameid;
}


int RunGame(void)
{
	int choice = 0;
	std::cout << "Mode : 1 -- Normal, 0 -- Replay, 2 -- Race." << std::endl;
	std::cout << "Select: ";
	std::cin >> choice;

	InitSocket();

	if (0 == choice)
	{
		InitRaceReplayData();
		InitReplay();

		std::cout << "Press key to forward ..." << std::endl;
		auto ch = getch();

		std::thread worker(FunThread);
		worker.detach();

		__rootid += 1;

		while (__run < 2)
		{
			Key('f');

			Sleep(100);
		}

		std::cout << "Press any key to backward ..." << std::endl;
		ch = getch();
		__run = 1;

		while (__run)
		{
			Key('b');

			Sleep(100);
		}
	}
	else if (1 == choice)
	{
		InitData();

		__replaymode = 0;

		InitGame();

		std::thread worker(FunThread);
		worker.detach();

		while (__run)
		{
			const auto ch = getch();

			Key(ch);
		}
	}
	else
	{
		InitRaceData(0);
		InitRace();

		std::thread worker(FunThread);
		worker.detach();

		while (__run)
		{
			const auto ch = getch();

			Key(ch);
		}
	}

	return(choice);
}


int main(int argc, char *argv[])
{
	while (true)
	{
		RunGame();
	}

	return(0);
}

