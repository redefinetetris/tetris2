#ifndef __RTECLOCKFUNCTOR_H__
#define __RTECLOCKFUNCTOR_H__


#include "../RTFunctor.h"
#include "RTEClockStyle.h"


class CRTEClock;


class CRTEClockFunctor : public CRTFunctor
{
public:
	CRTEClockFunctor(const int _FunctorStyle);
	~CRTEClockFunctor();

public:
	virtual RTEClockStyle_t operator () (CRTEClock & _Clock) const;

protected:
	virtual RTEClockStyle_t DoFunctor(CRTEClock & _Clock) const;

private:
	RTEClockStyle_t Functor(CRTEClock & _Clock) const;

protected:
	virtual RTEClockStyle_t PreDoFunctor(CRTEClock & _Clock) const;
	virtual RTEClockStyle_t PostDoFunctor(CRTEClock & _Clock) const;
};


class CClockUpdate : public CRTEClockFunctor
{
public:
	CClockUpdate();
	~CClockUpdate();

protected:
	virtual RTEClockStyle_t DoFunctor(CRTEClock & _Clock) const;

private:
	RTEClockStyle_t Update(CRTEClock & _Clock) const;
};


class CClockNew : public CRTEClockFunctor
{
public:
	CClockNew();
	~CClockNew();

protected:
	virtual RTEClockStyle_t DoFunctor(CRTEClock & _Clock) const;

private:
	RTEClockStyle_t New(CRTEClock & _Clock) const;
};


class CClockDelete : public CRTEClockFunctor
{
public:
	CClockDelete();
	~CClockDelete();

protected:
	virtual RTEClockStyle_t DoFunctor(CRTEClock & _Clock) const;

private:
	RTEClockStyle_t Delete(CRTEClock & _Clock) const;
};


class CClockQuery : public CRTEClockFunctor
{
public:
	CClockQuery();
	~CClockQuery();

protected:
	virtual RTEClockStyle_t DoFunctor(CRTEClock & _Clock) const;

private:
	RTEClockStyle_t Query(CRTEClock & _Clock) const;
};


class CClockHealth : public CRTEClockFunctor
{
public:
	CClockHealth();
	~CClockHealth();

protected:
	virtual RTEClockStyle_t DoFunctor(CRTEClock & _Clock) const;

private:
	RTEClockStyle_t Health(CRTEClock & _Clock) const;
};


#endif//__RTECLOCKFUNCTOR_H__

