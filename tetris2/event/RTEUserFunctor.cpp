#include "RTEUserFunctor.h"
#include "../RTDict.h"
#include "../RTMail.h"
#include "../RTNSDB.h"
#include "../RTNSLog.h"
#include "../RTNSTool.h"
#include "../RTDataType.h"
#include "../orm/RTDBUser.h"
#include "RTEUser.h"


CRTEUserFunctor::CRTEUserFunctor(const int _FunctorStyle)
	: CRTFunctor(_FunctorStyle)
{
}


CRTEUserFunctor::~CRTEUserFunctor()
{
}


RTEUserStyle_t CRTEUserFunctor::operator () (CRTEUser & _User) const
{
	const auto codeBase = this->ReplayCmd2DB(&_User, GetCurrentMail());

	const auto codePreDoFunctor = this->PreDoFunctor(_User);
	const auto codeDoFunctor = this->DoFunctor(_User);
	const auto codePostDoFunctor = this->PostDoFunctor(_User);

	return(codeDoFunctor);
}


RTEUserStyle_t CRTEUserFunctor::DoFunctor(CRTEUser & _User) const
{
	const auto code = this->Functor(_User);

	return(code);
}


RTEUserStyle_t CRTEUserFunctor::Functor(CRTEUser & _User) const
{
	return(RTEUS_Unknown);
}


RTEUserStyle_t CRTEUserFunctor::PreDoFunctor(CRTEUser & _User) const
{
	return(RTEUS_Unknown);
}


RTEUserStyle_t CRTEUserFunctor::PostDoFunctor(CRTEUser & _User) const
{
	return(RTEUS_Unknown);
}


CUserLogin::CUserLogin()
	: CRTEUserFunctor(RTEUS_Login)
{
}


CUserLogin::~CUserLogin()
{
}


RTEUserStyle_t CUserLogin::DoFunctor(CRTEUser & _User) const
{
	const auto code = this->Login(_User);

	return(code);
}


RTEUserStyle_t CUserLogin::Login(CRTEUser & _User) const
{
	const auto args = GetCurrentArgs();
	const auto user = args["user"].GetString();
	const auto key = args["key"].GetString();
	const auto vcode = args["vcode"].GetString();
	const auto idUser = RTNSDB::VerifyUser(user, key);
	auto code(RTEUS_Login);
	auto strCode("ok");
	auto strMsg("luck");
	CRTDict back_args;

	if (idUser < 1)
	{
		code = RTEUS_NotFind;
		strCode = "bad";
		strMsg = "not find";
	}
	else
	{
		std::shared_ptr<CRTMail> pPayMail(new (std::nothrow) CRTMail());
		if (pPayMail)
		{
			pPayMail->CopyNetInfo(*GetCurrentMail());
			_User.m_PayManager[idUser] = pPayMail;

			const auto token = RTNSDB::GenerateToken(idUser);
			back_args["token"] = token;

			const auto Msg = "login ok, user id: " + RTNSTool::int2string(idUser);
			PrintLogInfo(Msg);
		}
		else
		{
			code = RTEUS_OutMemory;
			strCode = "bad";
			strMsg = "out memory";
		}
	}//else

	const auto back_mail = RTNSTool::BackMailBy(GetCurrentMail(), back_args, strCode, strMsg);
	_User.m_SendBuffer.Writer(back_mail);

	return(code);
}


CUserLogout::CUserLogout()
	: CRTEUserFunctor(RTEUS_Logout)
{
}


CUserLogout::~CUserLogout()
{
}


RTEUserStyle_t CUserLogout::DoFunctor(CRTEUser & _User) const
{
	const auto code = this->Logout(_User);

	return(code);
}


RTEUserStyle_t CUserLogout::Logout(CRTEUser & _User) const
{
	const auto idUser = GetCurrentUserID();
	auto code(RTEUS_Logout);
	auto strCode("ok");
	auto strMsg("luck");

	if (idUser < 1)
	{
		code = RTEUS_NotFind;
		strCode = "bad";
		strMsg = "not find";
	}
	else
	{
		_User.m_PayManager.DeleteTarget(idUser);

		const auto Msg = "logout ok, user id: " + RTNSTool::int2string(idUser);
		PrintLogInfo(Msg);
	}

	const auto back_mail = RTNSTool::BackMailBy(GetCurrentMail(), strCode, strMsg);
	_User.m_SendBuffer.Writer(back_mail);

	return(code);
}


CUserRegin::CUserRegin()
	: CRTEUserFunctor(RTEUS_Regin)
{
}


CUserRegin::~CUserRegin()
{
}


RTEUserStyle_t CUserRegin::DoFunctor(CRTEUser & _User) const
{
	const auto code = this->Regin(_User);

	return(code);
}


RTEUserStyle_t CUserRegin::Regin(CRTEUser & _User) const
{
	const auto args = GetCurrentArgs();
	const auto user = args["user"].GetString();
	const auto key = args["key"].GetString();
	const auto vcode = args["vcode"].GetString();
	auto pObjUser = RTNSDB::FindUser(user);
	auto code(RTEUS_Regin);
	auto strCode("ok");
	auto strMsg("luck");
	CRTDict back_args;

	if (nullptr== pObjUser)
	{
		code = RTEUS_Regined;
		strCode = "bad";
		strMsg = "repeat regin";
	}
	else
	{
		const auto idUser = RTNSDB::NewUser(user, key);
		if (idUser < 1)
		{
			code = RTEUS_Bad;
			strCode = "bad";
			strMsg = "db fail";
		}
		else
		{
			std::shared_ptr<CRTMail> pPayMail(new (std::nothrow) CRTMail());
			if (pPayMail)
			{
				pPayMail->CopyNetInfo(*GetCurrentMail());
				_User.m_PayManager[idUser] = pPayMail;

				const auto token = RTNSDB::GenerateToken(idUser);
				back_args["token"] = token;

				const auto Msg = "regin ok, user id: " + RTNSTool::int2string(idUser);
				PrintLogInfo(Msg);
			}
			else
			{
				code = RTEUS_OutMemory;
				strCode = "bad";
				strMsg = "out memory";
			}
		}//else
	}//else

	const auto back_mail = RTNSTool::BackMailBy(GetCurrentMail(), back_args, strCode, strMsg);
	_User.m_SendBuffer.Writer(back_mail);

	return(code);
}


CUserRegout::CUserRegout()
	: CRTEUserFunctor(RTEUS_Regout)
{
}


CUserRegout::~CUserRegout()
{
}


RTEUserStyle_t CUserRegout::DoFunctor(CRTEUser & _User) const
{
	const auto code = this->Regout(_User);

	return(code);
}


RTEUserStyle_t CUserRegout::Regout(CRTEUser & _User) const
{
	const auto args = GetCurrentArgs();
	const auto key = args["key"].GetString();
	const auto idUser = GetCurrentUserID();
	const auto ok = RTNSDB::VerifyPassword(idUser, key);
	auto code(RTEUS_Regout);
	auto strCode("ok");
	auto strMsg("luck");

	if (false == ok)
	{
		code = RTEUS_NotFind;
		strCode = "bad";
		strMsg = "not find";
	}
	else
	{
		RTNSDB::DeleteUser(idUser);

		const auto Msg = "regout ok, user id: " + RTNSTool::int2string(idUser);
		PrintLogInfo(Msg);
	}

	const auto back_mail = RTNSTool::BackMailBy(GetCurrentMail(), strCode, strMsg);
	_User.m_SendBuffer.Writer(back_mail);

	return(code);
}

