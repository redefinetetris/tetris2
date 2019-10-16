#ifndef __RTEGS_H__
#define __RTEGS_H__


class CRTEGS
{
public:
	CRTEGS();
	CRTEGS(const int _idGroup, const int _idBase, const int _Coins = 0);
	CRTEGS(const CRTEGS &_other);
	~CRTEGS();

private:
	int m_idGroup;
	int m_idBase;
	int m_Coins;

public:
	const int GetGroupID(void) const;
	int GetBaseID(void) const;

	int GetCoins(void) const;
	void SetCoins(const int &_Coins);
	void UpCoins(const int &_Coins);
	void DownCoins(const int &_Coins);
};


#endif//__RTEGS_H__

