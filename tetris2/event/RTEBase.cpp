#include "RTEBase.h"
#include "../RTDataType.h"


CRTEBase::CRTEBase(const RTEStyle_t _RTEStyle)
	: CRTRecvSendBuffer()
	, CRTMask()
	, m_pParent(nullptr)
	, m_RTEStyle(_RTEStyle)
{
}


CRTEBase::CRTEBase(const CRTEBase &_other)
	: CRTRecvSendBuffer(_other)
	, CRTMask(_other)
	, m_pParent(_other.m_pParent)
	, m_RTEStyle(_other.m_RTEStyle)
{
}


CRTEBase::~CRTEBase()
{
}


CRTEBase* CRTEBase::GetParent(void) const
{
	return(m_pParent);
}


void CRTEBase::SetParent(CRTEBase* _pParent)
{
	m_pParent = _pParent;
}


RTEStyle_t CRTEBase::GetRTEStyle(void) const
{
	return(m_RTEStyle);
}


int CRTEBase::Power(void)
{
	return(0);
}


int CRTEBase::RunLocker(const bool _OnlyOneMail)
{
	std::unique_lock<std::mutex> locker(m_Mutex, std::defer_lock);

	if (false == locker.try_lock())
	{
		return(0);
	}

	return(this->Run(_OnlyOneMail));
}


int CRTEBase::RunSelfLocker(void)
{
	std::unique_lock<std::mutex> locker(m_Mutex, std::defer_lock);

	if (false == locker.try_lock())
	{
		return(0);
	}

	return(this->SelfRun());
}


int CRTEBase::Run(const bool _OnlyOne)
{
	int work = 0;

	m_SendBuffer.FlushWriter();

	work += this->SelfRun();
	work += this->MailsRun(_OnlyOne);

	return(work);
}


int CRTEBase::SelfRun(void)
{
	int work = 0;

	return(work);
}


int CRTEBase::MailsRun(const bool _OnlyOneMail)
{
	int work = 0;
	std::vector<std::shared_ptr<CRTMail>> Mails;
	Mails.reserve(VECTOR_RESERVE_SIZE);

	if (true == _OnlyOneMail)
	{
		std::shared_ptr<CRTMail> pMail = nullptr;

		const auto okPB = m_PrivateBuffer.Reader(pMail);
		if (false == okPB)
		{
			const auto okRB = m_RecvBuffer.Reader(pMail);
			if (false == okRB)
			{
				return(work);
			}
		}

		Mails.push_back(pMail);
	}//if
	else
	{
		const auto okPB = m_PrivateBuffer.Reader(Mails);
		const auto okRB = m_RecvBuffer.Reader(Mails);

		if (false == okPB && false == okRB)
		{
			return(work);
		}
	}

	work += this->PreMails();

	for (auto item = Mails.begin(); item != Mails.end(); ++item)
	{
		++work;

		auto pMail = *item;
		CMStacker stacker(this, *item);

		const auto codePreDoMail = this->PreDoMail();
		const auto codeDoMail = this->DoMail();
		const auto codePostDoMail = this->PostDoMail();
	}//for

	work += this->PostMails();

	return(work);
}


int CRTEBase::PreMails(void)
{
	int work = 0;

	return(work);
}


int CRTEBase::PostMails(void)
{
	int work = 0;

	return(work);
}


int CRTEBase::PreDoMail(void)
{
	return(0);
}


int CRTEBase::DoMail(void)
{
	return(0);
}


int CRTEBase::PostDoMail(void)
{
	return(0);
}

