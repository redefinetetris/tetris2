#ifndef __RTEGAMEFUNCTOR_H__
#define __RTEGAMEFUNCTOR_H__


#include "../RTFunctor.h"
#include "RTEGameStyle.h"


class CRTEGame;


class CRTEGameFunctor : public CRTFunctor
{
public:
	CRTEGameFunctor(const int _FunctorStyle);
	~CRTEGameFunctor();

public:
	virtual RTEGameStyle_t operator () (CRTEGame & _Game) const;

protected:
	virtual RTEGameStyle_t DoFunctor(CRTEGame & _Game) const;
	virtual RTEGameStyle_t UnDoFunctor(CRTEGame & _Game) const;

private:
	RTEGameStyle_t Functor(CRTEGame & _Game) const;
	RTEGameStyle_t UnFunctor(CRTEGame & _Game) const;

protected:
	virtual RTEGameStyle_t PreDoFunctor(CRTEGame & _Game) const;
	virtual RTEGameStyle_t PostDoFunctor(CRTEGame & _Game) const;

	virtual RTEGameStyle_t PreUnDoFunctor(CRTEGame & _Game) const;
	virtual RTEGameStyle_t PostUnDoFunctor(CRTEGame & _Game) const;
};


class CGameNew : public CRTEGameFunctor
{
public:
	CGameNew();
	~CGameNew();

protected:
	virtual RTEGameStyle_t DoFunctor(CRTEGame & _Game) const;
	virtual RTEGameStyle_t UnDoFunctor(CRTEGame & _Game) const;

private:
	RTEGameStyle_t New(CRTEGame & _Game) const;
	RTEGameStyle_t UnNew(CRTEGame & _Game) const;
};


class CGameDelete : public CRTEGameFunctor
{
public:
	CGameDelete();
	~CGameDelete();

protected:
	virtual RTEGameStyle_t DoFunctor(CRTEGame & _Game) const;
	virtual RTEGameStyle_t UnDoFunctor(CRTEGame & _Game) const;

private:
	RTEGameStyle_t Delete(CRTEGame & _Game) const;
	RTEGameStyle_t UnDelete(CRTEGame & _Game) const;
};


class CGameDoctor : public CRTEGameFunctor
{
public:
	CGameDoctor();
	~CGameDoctor();

protected:
	virtual RTEGameStyle_t DoFunctor(CRTEGame & _Game) const;
	virtual RTEGameStyle_t UnDoFunctor(CRTEGame & _Game) const;

private:
	RTEGameStyle_t Doctor(CRTEGame & _Game) const;
	RTEGameStyle_t UnDoctor(CRTEGame & _Game) const;
};


class CGameMove : public CRTEGameFunctor
{
public:
	CGameMove();
	~CGameMove();

protected:
	virtual RTEGameStyle_t DoFunctor(CRTEGame & _Game) const;
	virtual RTEGameStyle_t UnDoFunctor(CRTEGame & _Game) const;

private:
	RTEGameStyle_t Move(CRTEGame & _Game) const;
	RTEGameStyle_t UnMove(CRTEGame & _Game) const;
};


class CGameTransfer : public CRTEGameFunctor
{
public:
	CGameTransfer();
	~CGameTransfer();

protected:
	virtual RTEGameStyle_t DoFunctor(CRTEGame & _Game) const;
	virtual RTEGameStyle_t UnDoFunctor(CRTEGame & _Game) const;

private:
	RTEGameStyle_t Transfer(CRTEGame & _Game) const;
	RTEGameStyle_t UnTransfer(CRTEGame & _Game) const;
};


class CGameHit : public CRTEGameFunctor
{
public:
	CGameHit();
	~CGameHit();

protected:
	virtual RTEGameStyle_t DoFunctor(CRTEGame & _Game) const;
	virtual RTEGameStyle_t UnDoFunctor(CRTEGame & _Game) const;

private:
	RTEGameStyle_t Hit(CRTEGame & _Game) const;
	RTEGameStyle_t UnHit(CRTEGame & _Game) const;
};


class CGameFreeze : public CRTEGameFunctor
{
public:
	CGameFreeze();
	~CGameFreeze();

protected:
	virtual RTEGameStyle_t DoFunctor(CRTEGame & _Game) const;
	virtual RTEGameStyle_t UnDoFunctor(CRTEGame & _Game) const;

private:
	RTEGameStyle_t Freeze(CRTEGame & _Game) const;
	RTEGameStyle_t UnFreeze(CRTEGame & _Game) const;
};


class CGameTarget : public CRTEGameFunctor
{
public:
	CGameTarget();
	~CGameTarget();

protected:
	virtual RTEGameStyle_t DoFunctor(CRTEGame & _Game) const;
	virtual RTEGameStyle_t UnDoFunctor(CRTEGame & _Game) const;

private:
	RTEGameStyle_t Target(CRTEGame & _Game) const;
	RTEGameStyle_t UnTarget(CRTEGame & _Game) const;
};


class CGameCoin : public CRTEGameFunctor
{
public:
	CGameCoin();
	~CGameCoin();

protected:
	virtual RTEGameStyle_t DoFunctor(CRTEGame & _Game) const;
	virtual RTEGameStyle_t UnDoFunctor(CRTEGame & _Game) const;

private:
	RTEGameStyle_t Coin(CRTEGame & _Game) const;
	RTEGameStyle_t UnCoin(CRTEGame & _Game) const;
};


class CGameRemove : public CRTEGameFunctor
{
public:
	CGameRemove();
	~CGameRemove();

protected:
	virtual RTEGameStyle_t DoFunctor(CRTEGame & _Game) const;
	virtual RTEGameStyle_t UnDoFunctor(CRTEGame & _Game) const;

private:
	RTEGameStyle_t Remove(CRTEGame & _Game) const;
	RTEGameStyle_t UnRemove(CRTEGame & _Game) const;
};


class CGameWatch : public CRTEGameFunctor
{
public:
	CGameWatch();
	~CGameWatch();

protected:
	virtual RTEGameStyle_t DoFunctor(CRTEGame & _Game) const;
	virtual RTEGameStyle_t UnDoFunctor(CRTEGame & _Game) const;

private:
	RTEGameStyle_t Watch(CRTEGame & _Game) const;
	RTEGameStyle_t UnWatch(CRTEGame & _Game) const;
};


class CGameOver : public CRTEGameFunctor
{
public:
	CGameOver();
	~CGameOver();

protected:
	virtual RTEGameStyle_t DoFunctor(CRTEGame & _Game) const;
	virtual RTEGameStyle_t UnDoFunctor(CRTEGame & _Game) const;

private:
	RTEGameStyle_t Over(CRTEGame & _Game) const;
	RTEGameStyle_t UnOver(CRTEGame & _Game) const;
};


class CGameTimer : public CRTEGameFunctor
{
public:
	CGameTimer();
	~CGameTimer();

protected:
	virtual RTEGameStyle_t DoFunctor(CRTEGame & _Game) const;
	virtual RTEGameStyle_t UnDoFunctor(CRTEGame & _Game) const;

private:
	RTEGameStyle_t Timer(CRTEGame & _Game) const;
	RTEGameStyle_t UnTimer(CRTEGame & _Game) const;
};


class CGameHealth : public CRTEGameFunctor
{
public:
	CGameHealth();
	~CGameHealth();

protected:
	virtual RTEGameStyle_t DoFunctor(CRTEGame & _Game) const;
	virtual RTEGameStyle_t UnDoFunctor(CRTEGame & _Game) const;

private:
	RTEGameStyle_t Health(CRTEGame & _Game) const;
	RTEGameStyle_t UnHealth(CRTEGame & _Game) const;
};


class CGameHole : public CRTEGameFunctor
{
public:
	CGameHole();
	~CGameHole();

protected:
	virtual RTEGameStyle_t DoFunctor(CRTEGame & _Game) const;

private:
	RTEGameStyle_t Hole(CRTEGame & _Game) const;
};


#endif//__RTEGAMEFUNCTOR_H__

