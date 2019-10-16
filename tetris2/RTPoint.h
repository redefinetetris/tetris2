#ifndef __RTPOINT_H__
#define __RTPOINT_H__


class CRTPoint
{
public:
	CRTPoint(const int _X, const int _Y, const int _Z);
	CRTPoint(const CRTPoint &_other);
	~CRTPoint();

private:
	int m_X;
	int m_Y;
	int m_Z;

public:
	int GetX(void) const;
	void SetX(const int &_X);

	int GetY(void) const;
	void SetY(const int &_Y);

	int GetZ(void) const;
	void SetZ(const int &_Z);

public:
	void Clear(const int _Value = 0);

public:
	CRTPoint& operator = (const CRTPoint& _other);
	CRTPoint& operator += (const CRTPoint& _other);
};


#endif//__RTPOINT_H__

