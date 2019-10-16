#ifndef __RTESESSION_H__
#define __RTESESSION_H__


#include "RTEGS.h"
#include "RTEGame.h"
#include "RTEPayBase.h"


class CRTESession : public CRTEPayBase, public CRTEGS
{
public:
	CRTESession();
	CRTESession(const int _idGroup, const int _idBase, const int _Number, const int _Length, const int _Width, const int _Height);
	~CRTESession();

public:
	CRTManager<int, std::shared_ptr<CRTEGame>> m_GameManager;

private:
	int m_SpeedID;
	int m_Number;
	int m_TTF;
	int m_Length;
	int m_Width;
	int m_Height;

public:
	int GetSpeedID(void) const;
	void SetSpeedID(const int &_SpeedID);
	int UpSpeedID(void);

	int GetNumber(void) const;
	void SetNumber(const int &_Number);

	int GetTTF(void) const;
	int DownTTF(void);
	void SetTTF(const int &_TTF);

	int GetLength(void) const;
	void SetLength(const int &_Length);

	int GetWidth(void) const;
	void SetWidth(const int &_Width);

	int GetHeight(void) const;
	void SetHeight(const int &_Height);

private:
	friend class CSessionNewGame;
	friend class CSessionDeleteGame;
	friend class CSessionTimer;
	friend class CSessionJump;
	friend class CSessionMove;
	friend class CSessionRace;
	friend class CSessionFire;
	friend class CSessionWin;
	friend class CSessionOver;
	friend class CSessionHealth;
	friend class CSessionToll;

public:
	void NextTollTimer(const std::string _Op = "new");
	void NextRaceTimer(const std::string _Op = "delete");

private:
	void NextGameNew(void);
	void NextGameOver(void);
	void NextRace(void);

private:
	void BackMail2PayUser(const CRTDict& _Dict);

public:
	virtual int Power(void);

private:
	virtual int SelfRun(void);
	int Mailer(void);

	std::vector<std::shared_ptr<CRTMail>> GameM(void);
	int GuardM(const std::vector<std::shared_ptr<CRTMail>>& _Mails);

	virtual int DoMail(void);
	int DoMailGame(void);

private:
	int FlushWriter(void);
};


#endif//__RTESESSION_H__

