#include "RTEGS.h"


CRTEGS::CRTEGS()
	: m_idGroup(0)
	, m_idBase(0)
	, m_Coins(0)
{
}


CRTEGS::CRTEGS(const int _idGroup, const int _idBase, const int _Coins)
	: CRTEGS()
{
	m_idGroup = _idGroup;
	m_idBase = _idBase;
	m_Coins = _Coins;
}


CRTEGS::CRTEGS(const CRTEGS &_other)
	: m_idGroup(_other.m_idGroup)
	, m_idBase(_other.m_idBase)
	, m_Coins(_other.m_Coins)
{
}


CRTEGS::~CRTEGS()
{
}


const int CRTEGS::GetGroupID(void) const
{
	return(m_idGroup);
}


int CRTEGS::GetBaseID(void) const
{
	return(m_idBase);
}


int CRTEGS::GetCoins(void) const
{
	return(m_Coins);
}


void CRTEGS::SetCoins(const int &_Coins)
{
	m_Coins = _Coins;
}


void CRTEGS::UpCoins(const int &_Coins)
{
	m_Coins += _Coins;
}


void CRTEGS::DownCoins(const int &_Coins)
{
	m_Coins -= _Coins;
}

