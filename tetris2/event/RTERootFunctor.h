#ifndef __RTEROOTFUNCTOR_H__
#define __RTEROOTFUNCTOR_H__


#include "../RTFunctor.h"
#include "RTERootStyle.h"


class CRTERoot;


class CRTERootFunctor : public CRTFunctor
{
public:
	CRTERootFunctor(const int _FunctorStyle);
	~CRTERootFunctor();

public:
	virtual RTERootStyle_t operator () (CRTERoot & _Root) const;

protected:
	virtual RTERootStyle_t DoFunctor(CRTERoot & _Root) const;

private:
	RTERootStyle_t Functor(CRTERoot & _Root) const;

protected:
	virtual RTERootStyle_t PreDoFunctor(CRTERoot & _Root) const;
	virtual RTERootStyle_t PostDoFunctor(CRTERoot & _Root) const;
};


class CRootNewSession : public CRTERootFunctor
{
public:
	CRootNewSession();
	~CRootNewSession();

protected:
	virtual RTERootStyle_t DoFunctor(CRTERoot & _Root) const;

private:
	RTERootStyle_t NewSession(CRTERoot & _Root) const;
};


class CRootDeleteSession : public CRTERootFunctor
{
public:
	CRootDeleteSession();
	~CRootDeleteSession();

protected:
	virtual RTERootStyle_t DoFunctor(CRTERoot & _Root) const;

private:
	RTERootStyle_t DeleteSession(CRTERoot & _Root) const;
};


class CRootQuery : public CRTERootFunctor
{
public:
	CRootQuery();
	~CRootQuery();

protected:
	virtual RTERootStyle_t DoFunctor(CRTERoot & _Root) const;

private:
	RTERootStyle_t Query(CRTERoot & _Root) const;
};


class CRootHealth : public CRTERootFunctor
{
public:
	CRootHealth();
	~CRootHealth();

protected:
	virtual RTERootStyle_t DoFunctor(CRTERoot & _Root) const;

private:
	RTERootStyle_t Health(CRTERoot & _Root) const;
};


#endif//__RTEROOTFUNCTOR_H__

