#ifndef __RTEUSERFUNCTOR_H__
#define __RTEUSERFUNCTOR_H__


#include "../RTFunctor.h"
#include "RTEUserStyle.h"


class CRTEUser;


class CRTEUserFunctor : public CRTFunctor
{
public:
	CRTEUserFunctor(const int _FunctorStyle);
	~CRTEUserFunctor();

public:
	virtual RTEUserStyle_t operator () (CRTEUser & _User) const;

protected:
	virtual RTEUserStyle_t DoFunctor(CRTEUser & _User) const;

private:
	RTEUserStyle_t Functor(CRTEUser & _User) const;

protected:
	virtual RTEUserStyle_t PreDoFunctor(CRTEUser & _User) const;
	virtual RTEUserStyle_t PostDoFunctor(CRTEUser & _User) const;
};


class CUserLogin : public CRTEUserFunctor
{
public:
	CUserLogin();
	~CUserLogin();

protected:
	virtual RTEUserStyle_t DoFunctor(CRTEUser & _User) const;

private:
	RTEUserStyle_t Login(CRTEUser & _User) const;
};


class CUserLogout : public CRTEUserFunctor
{
public:
	CUserLogout();
	~CUserLogout();

protected:
	virtual RTEUserStyle_t DoFunctor(CRTEUser & _User) const;

private:
	RTEUserStyle_t Logout(CRTEUser & _User) const;
};


class CUserRegin : public CRTEUserFunctor
{
public:
	CUserRegin();
	~CUserRegin();

protected:
	virtual RTEUserStyle_t DoFunctor(CRTEUser & _User) const;

private:
	RTEUserStyle_t Regin(CRTEUser & _User) const;
};


class CUserRegout : public CRTEUserFunctor
{
public:
	CUserRegout();
	~CUserRegout();

protected:
	virtual RTEUserStyle_t DoFunctor(CRTEUser & _User) const;

private:
	RTEUserStyle_t Regout(CRTEUser & _User) const;
};


#endif//__RTEUSERFUNCTOR_H__

