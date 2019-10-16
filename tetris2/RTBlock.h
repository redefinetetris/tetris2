#ifndef __RTBLOCK_H__
#define __RTBLOCK_H__


#include <mutex>
#include <vector>
#include "RTPoint.h"


class CRTBlock
{
public:
	CRTBlock(const int _Length, const int _Width, const int _ID);
	CRTBlock(const std::vector<int> &_Values, const int _Length, const int _Width, const int _ID);
	CRTBlock(const CRTBlock &_other);
	~CRTBlock();

public:
	const std::unique_ptr<int[]>& operator [] (const int _Index) const;
	std::unique_ptr<int[]>& operator [] (const int _Index);

private:
	std::unique_ptr<std::unique_ptr<int[]>[]> m_pSpace;
	int m_Length;
	int m_Width;
	int m_ID;
	CRTPoint m_O;
	int m_RealLength;

public:
	int GetLength(void) const;
	void SetLength(const int &_Length);

	int GetWidth(void) const;
	void SetWidth(const int &_Width);

	int GetID(void) const;
	void SetID(const int &_ID);

	CRTPoint GetO(void) const;
	void SetO(const CRTPoint &_O);
	void ClearO(void);

	int GetRealLength(void) const;

public:
	bool IsOK(void) const;
	void CountRealLength(void);

	void ClearValue(const int _Value = 0);
	void SetBorder(const int _Value = 1);

	std::vector<int> GetValue(void) const;
	void SetValue(const std::vector<int>& _Values);

	int GetValue(const CRTPoint _Point) const;
	void SetValue(const CRTPoint _Point, const int _Value);

	int GetValue(const int _X, const int _Y) const;
	void SetValue(const int _X, const int _Y, const int _Value);
};


#endif//__RTBLOCK_H__

