#ifndef __RTESESSIONFUNCTOR_H__
#define __RTESESSIONFUNCTOR_H__


#include "../RTFunctor.h"
#include "RTESessionStyle.h"


class CRTESession;


class CRTESessionFunctor : public CRTFunctor
{
public:
	CRTESessionFunctor(const int _FunctorStyle);
	~CRTESessionFunctor();

public:
	virtual RTESessionStyle_t operator () (CRTESession & _Session) const;

protected:
	virtual RTESessionStyle_t DoFunctor(CRTESession & _Session) const;

private:
	RTESessionStyle_t Functor(CRTESession & _Session) const;

protected:
	virtual RTESessionStyle_t PreDoFunctor(CRTESession & _Session) const;
	virtual RTESessionStyle_t PostDoFunctor(CRTESession & _Session) const;
};


class CSessionNewGame : public CRTESessionFunctor
{
public:
	CSessionNewGame();
	~CSessionNewGame();

protected:
	virtual RTESessionStyle_t DoFunctor(CRTESession & _Session) const;

private:
	RTESessionStyle_t NewGame(CRTESession & _Session) const;
};


class CSessionDeleteGame : public CRTESessionFunctor
{
public:
	CSessionDeleteGame();
	~CSessionDeleteGame();

protected:
	virtual RTESessionStyle_t DoFunctor(CRTESession & _Session) const;

private:
	RTESessionStyle_t DeleteGame(CRTESession & _Session) const;
};


class CSessionTimer : public CRTESessionFunctor
{
public:
	CSessionTimer();
	~CSessionTimer();

protected:
	virtual RTESessionStyle_t DoFunctor(CRTESession & _Session) const;

private:
	RTESessionStyle_t Timer(CRTESession & _Session) const;
};


class CSessionJump : public CRTESessionFunctor
{
public:
	CSessionJump();
	~CSessionJump();

protected:
	virtual RTESessionStyle_t DoFunctor(CRTESession & _Session) const;

private:
	RTESessionStyle_t Jump(CRTESession & _Session) const;
};


class CSessionMove : public CRTESessionFunctor
{
public:
	CSessionMove();
	~CSessionMove();

protected:
	virtual RTESessionStyle_t DoFunctor(CRTESession & _Session) const;

private:
	RTESessionStyle_t Move(CRTESession & _Session) const;
};


class CSessionRace : public CRTESessionFunctor
{
public:
	CSessionRace();
	~CSessionRace();

protected:
	virtual RTESessionStyle_t DoFunctor(CRTESession & _Session) const;

private:
	RTESessionStyle_t Race(CRTESession & _Session) const;
};


class CSessionFire : public CRTESessionFunctor
{
public:
	CSessionFire();
	~CSessionFire();

protected:
	virtual RTESessionStyle_t DoFunctor(CRTESession & _Session) const;

private:
	RTESessionStyle_t Fire(CRTESession & _Session) const;
};


class CSessionWin : public CRTESessionFunctor
{
public:
	CSessionWin();
	~CSessionWin();

protected:
	virtual RTESessionStyle_t DoFunctor(CRTESession & _Session) const;

private:
	RTESessionStyle_t Win(CRTESession & _Session) const;
};


class CSessionOver : public CRTESessionFunctor
{
public:
	CSessionOver();
	~CSessionOver();

protected:
	virtual RTESessionStyle_t DoFunctor(CRTESession & _Session) const;

private:
	RTESessionStyle_t Over(CRTESession & _Session) const;
};


class CSessionHealth : public CRTESessionFunctor
{
public:
	CSessionHealth();
	~CSessionHealth();

protected:
	virtual RTESessionStyle_t DoFunctor(CRTESession & _Session) const;

private:
	RTESessionStyle_t Health(CRTESession & _Session) const;
};


class CSessionToll : public CRTESessionFunctor
{
public:
	CSessionToll();
	~CSessionToll();

protected:
	virtual RTESessionStyle_t DoFunctor(CRTESession & _Session) const;

private:
	RTESessionStyle_t Toll(CRTESession & _Session) const;
};


#endif//__RTESESSIONFUNCTOR_H__

