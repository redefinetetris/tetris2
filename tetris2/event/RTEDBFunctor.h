#ifndef __RTEDBFUNCTOR_H__
#define __RTEDBFUNCTOR_H__


#include "../RTFunctor.h"
#include "RTEDBStyle.h"


class CRTEDB;


class CRTEDBFunctor : public CRTFunctor
{
public:
	CRTEDBFunctor(const int _FunctorStyle);
	~CRTEDBFunctor();

public:
	virtual RTEDBStyle_t operator () (CRTEDB & _DB) const;

protected:
	virtual RTEDBStyle_t DoFunctor(CRTEDB & _DB) const;

private:
	RTEDBStyle_t Functor(CRTEDB & _DB) const;

protected:
	virtual RTEDBStyle_t PreDoFunctor(CRTEDB & _DB) const;
	virtual RTEDBStyle_t PostDoFunctor(CRTEDB & _DB) const;
};


class CDBTimer : public CRTEDBFunctor
{
public:
	CDBTimer();
	~CDBTimer();

protected:
	virtual RTEDBStyle_t DoFunctor(CRTEDB & _DB) const;

private:
	RTEDBStyle_t Timer(CRTEDB & _DB) const;
};


class CDBFire : public CRTEDBFunctor
{
public:
	CDBFire();
	~CDBFire();

protected:
	virtual RTEDBStyle_t DoFunctor(CRTEDB & _DB) const;

private:
	RTEDBStyle_t Fire(CRTEDB & _DB) const;
};


class CDBFlush : public CRTEDBFunctor
{
public:
	CDBFlush();
	~CDBFlush();

protected:
	virtual RTEDBStyle_t DoFunctor(CRTEDB & _DB) const;

private:
	RTEDBStyle_t Flush(CRTEDB & _DB) const;
};


class CDBDownTTL : public CRTEDBFunctor
{
public:
	CDBDownTTL();
	~CDBDownTTL();

protected:
	virtual RTEDBStyle_t DoFunctor(CRTEDB & _DB) const;

private:
	RTEDBStyle_t DownTTL(CRTEDB & _DB) const;
};


class CDBWashTTL : public CRTEDBFunctor
{
public:
	CDBWashTTL();
	~CDBWashTTL();

protected:
	virtual RTEDBStyle_t DoFunctor(CRTEDB & _DB) const;

private:
	RTEDBStyle_t WashTTL(CRTEDB & _DB) const;
};


#endif//__RTEDBFUNCTOR_H__

