#ifndef __RTEGAME_H__
#define __RTEGAME_H__


#include "RTEGS.h"
#include "RTEPayBase.h"
#include "../RTBlock.h"


class CRTEGame : public CRTEPayBase, public CRTEGS
{
public:
	CRTEGame();
	CRTEGame(const int _idGroup, const int _idBase);
	CRTEGame(const CRTEGame &_other);
	~CRTEGame();

private:
	std::unique_ptr<CRTBlock> m_pArea;
	std::unique_ptr<CRTBlock> m_pAreaBuffer;
	std::unique_ptr<CRTBlock> m_pBlock;
	std::unique_ptr<CRTBlock> m_pBlockBuffer;

private:
	friend class CGameNew;
	friend class CGameDelete;
	friend class CGameDoctor;
	friend class CGameMove;
	friend class CGameTransfer;
	friend class CGameHit;
	friend class CGameFreeze;
	friend class CGameTarget;
	friend class CGameCoin;
	friend class CGameRemove;
	friend class CGameWatch;
	friend class CGameOver;
	friend class CGameTimer;
	friend class CGameHealth;
	friend class CGameHole;

private:
	bool CanDoNext(void) const;

public:
	CRTDict GetNextArgs(void) const;

private:
	int UpdateCurrentMail4UserCmd(void) const;
	int UpdateCurrentMail4UserCmd(const std::string _Key, const int _Value) const;
	int UpdateCurrentMail4UserCmd(const CRTDict& _Args) const;

private:
	void NextDoctor(void);
	void NextHit(void);
	void NextFreeze(void);
	void NextTarget(void);
	void NextCoin(const int _Coins);
	void NextRemove(const std::vector<int>& _Targets);
	void NextDelete(void);
public:
	void NextGameOver(void);
	void NextGameWin(void);
	void NextSessionOver(void);

public:
	virtual int Power(void);

private:
	virtual int DoMail(void);
};


#endif//__RTEGAME_H__

