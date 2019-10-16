#include "RTEPayBase.h"
#include <vector>
#include "../RTNSDB.h"
#include "../RTNSLog.h"
#include "../RTNSTool.h"
#include "../RTDataType.h"
#include "../RTNSStatic.h"


CRTEPayBase::CRTEPayBase(const RTEStyle_t _RTEStyle)
	: CRTEBase(_RTEStyle)
	, m_PayManager()
{
}


CRTEPayBase::CRTEPayBase(const CRTEPayBase &_other)
	: CRTEBase(_other)
	, m_PayManager(_other.m_PayManager)
{
}


CRTEPayBase::~CRTEPayBase()
{
}


std::shared_ptr<CRTMail> CRTEPayBase::GetHostPay(void) const
{
	const auto PayMails = m_PayManager.Values();

	return(PayMails[0]);
}


void CRTEPayBase::BackMail2PayUser(const CRTDict& _Dict)
{
	std::vector<std::shared_ptr<CRTMail>> Mails;
	Mails.reserve(VECTOR_RESERVE_SIZE);
	const auto Pays = m_PayManager.Values();

	for (auto item = Pays.begin(); item != Pays.end(); ++item)
	{
		const auto pSrcMail = *item;
		const auto pDestMail = RTNSTool::BackMail(pSrcMail, _Dict);

		Mails.push_back(pDestMail);
	}

	m_SendBuffer.Writer(Mails);
}


void CRTEPayBase::BackMail2PayUser(const std::string _Code, const std::string _Msg)
{
	const auto dict = RTNSTool::BackDictBy(GetCurrentMail(), _Code, _Msg);

	this->BackMail2PayUser(dict);
}


void CRTEPayBase::BackMail2PayUser(const int _idGame, const CRTDict& _Dict)
{
	const auto pSrcMail = m_PayManager[_idGame];
	const auto pDestMail = RTNSTool::BackMail(pSrcMail, _Dict);

	m_SendBuffer.Writer(pDestMail);
}

