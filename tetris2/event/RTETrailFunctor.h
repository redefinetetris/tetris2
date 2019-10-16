#ifndef __RTETRAILFUNCTOR_H__
#define __RTETRAILFUNCTOR_H__


#include "../RTFunctor.h"
#include "RTETrailStyle.h"


class CRTETrail;


class CRTETrailFunctor : public CRTFunctor
{
public:
	CRTETrailFunctor(const int _FunctorStyle);
	~CRTETrailFunctor();

public:
	virtual RTETrailStyle_t operator () (CRTETrail & _Trail) const;

protected:
	virtual RTETrailStyle_t DoFunctor(CRTETrail & _Trail) const;

private:
	RTETrailStyle_t Functor(CRTETrail & _Trail) const;

protected:
	virtual RTETrailStyle_t PreDoFunctor(CRTETrail & _Trail) const;
	virtual RTETrailStyle_t PostDoFunctor(CRTETrail & _Trail) const;
};


class CTrailNewRoot : public CRTETrailFunctor
{
public:
	CTrailNewRoot();
	~CTrailNewRoot();

protected:
	virtual RTETrailStyle_t DoFunctor(CRTETrail & _Trail) const;

private:
	RTETrailStyle_t NewRoot(CRTETrail & _Trail) const;
};


class CTrailDeleteRoot : public CRTETrailFunctor
{
public:
	CTrailDeleteRoot();
	~CTrailDeleteRoot();

protected:
	virtual RTETrailStyle_t DoFunctor(CRTETrail & _Trail) const;

private:
	RTETrailStyle_t DeleteRoot(CRTETrail & _Trail) const;
};


class CTrailQuery : public CRTETrailFunctor
{
public:
	CTrailQuery();
	~CTrailQuery();

protected:
	virtual RTETrailStyle_t DoFunctor(CRTETrail & _Trail) const;

private:
	RTETrailStyle_t Query(CRTETrail & _Trail) const;
};


#endif//__RTETRAILFUNCTOR_H__

