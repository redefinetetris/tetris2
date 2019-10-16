#ifndef __RTCURRENT_H__
#define __RTCURRENT_H__


#include <string>
#include <vector>
#include <memory>


class CRTDict;
class CRTMail;
class CRTBase;
class CRTEBase;


CRTBase* GetCurrentMaster(void);


const int CurrentHistory(void);
const std::shared_ptr<CRTMail> GetCurrentMail(void);
const CRTDict& GetCurrentDict(void);
const CRTDict& GetCurrentArgs(void);
const std::vector<std::string>& GetCurrentOps(void);
int GetCurrentUserID(void);
std::shared_ptr<CRTMail>& GetCurrentPayMail(void);


class CMMaster
{
public:
	CMMaster(CRTBase* _pMaster);
	~CMMaster();

private:
	void InitTopElement(void);
};


class CMStacker
{
public:
	CMStacker(CRTEBase* _pMaster, std::shared_ptr<CRTMail> _pMail);
	~CMStacker();

private:
	CRTEBase* m_pMaster;

private:
	void InitTopElement(void);
	void InitElementBy(std::shared_ptr<CRTMail> _pMail);

	int Mail2DB(void);
};



#endif

