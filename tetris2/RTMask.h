#ifndef __RTMASK_H__
#define __RTMASK_H__


class CRTMask
{
public:
	CRTMask();
	CRTMask(const unsigned int _Mask, const unsigned int _MaskBackUp);
	CRTMask(const CRTMask &_other);
	~CRTMask();

private:
	unsigned int m_Mask;
	unsigned int m_MaskBackUp;

public:
	unsigned int GetAllMask(void) const;
	void SetAllMaskSimple(const unsigned int &_Mask);
	void SetAllMask(const unsigned int &_Mask);
	void ClearAllMask(void);

public:
	bool GetMask(const unsigned int &_Mask) const;
	void SetMask(const unsigned int &_Mask);
	void ClearMask(const unsigned int &_Mask);

	unsigned int GetMaskBackUp(void) const;
	void SetMaskBackUp(const unsigned int &_MaskBackUp);

	void BackUpMask(void);
	void RecoverMask(void);
};


#endif//__RTMASK_H__

