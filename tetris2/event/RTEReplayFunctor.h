#ifndef __RTEREPLAYFUNCTOR_H__
#define __RTEREPLAYFUNCTOR_H__


#include "../RTFunctor.h"
#include "RTEReplayStyle.h"


class CRTEReplay;


class CRTEReplayFunctor : public CRTFunctor
{
public:
	CRTEReplayFunctor(const int _FunctorStyle);
	~CRTEReplayFunctor();

public:
	virtual RTEReplayStyle_t operator () (CRTEReplay & _Replay) const;

protected:
	virtual RTEReplayStyle_t DoFunctor(CRTEReplay & _Replay) const;

private:
	RTEReplayStyle_t Functor(CRTEReplay & _Replay) const;

protected:
	virtual RTEReplayStyle_t PreDoFunctor(CRTEReplay & _Replay) const;
	virtual RTEReplayStyle_t PostDoFunctor(CRTEReplay & _Replay) const;
};


class CReplayInit : public CRTEReplayFunctor
{
public:
	CReplayInit();
	~CReplayInit();

protected:
	virtual RTEReplayStyle_t DoFunctor(CRTEReplay & _Replay) const;

private:
	RTEReplayStyle_t Init(CRTEReplay & _Replay) const;
};


class CReplayQuery : public CRTEReplayFunctor
{
public:
	CReplayQuery();
	~CReplayQuery();

protected:
	virtual RTEReplayStyle_t DoFunctor(CRTEReplay & _Replay) const;

private:
	RTEReplayStyle_t Query(CRTEReplay & _Replay) const;
};


class CReplayBackward : public CRTEReplayFunctor
{
public:
	CReplayBackward();
	~CReplayBackward();

protected:
	virtual RTEReplayStyle_t DoFunctor(CRTEReplay & _Replay) const;

private:
	RTEReplayStyle_t Backward(CRTEReplay & _Replay) const;
};


class CReplayForward : public CRTEReplayFunctor
{
public:
	CReplayForward();
	~CReplayForward();

protected:
	virtual RTEReplayStyle_t DoFunctor(CRTEReplay & _Replay) const;

private:
	RTEReplayStyle_t Forward(CRTEReplay & _Replay) const;
};



#endif//__RTEREPLAYFUNCTOR_H__

