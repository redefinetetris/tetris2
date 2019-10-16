#include "RTValue.h"
#include "RTDict.h"
#include <new>


CRTValue::CRTValue()
	: m_pTarget(nullptr)
	, m_ValueStyle(RTVS_unknown)
{
}


CRTValue::CRTValue(const CRTValue &_other)
	: CRTValue()
{
	*this = _other;
}


CRTValue::~CRTValue()
{
	this->DeleteTargetPointer();
}


RTValueStyle_t CRTValue::GetValueStyle(void) const
{
	return(m_ValueStyle);
}


void CRTValue::SetValueStyle(const RTValueStyle_t &_ValueStyle)
{
	m_ValueStyle = _ValueStyle;
}


void CRTValue::NoSurpport(const std::string _Msg)
{
}


void CRTValue::DeleteTargetPointer(void)
{
	if (nullptr == m_pTarget)
	{
		return;
	}

	if (RTVS_int == m_ValueStyle)
	{
		auto pTarget = (int*)m_pTarget;
		delete pTarget;
	}
	else if (RTVS_unsigned_int == m_ValueStyle)
	{
		auto pTarget = (unsigned int*)m_pTarget;
		delete pTarget;
	}
	else if (RTVS_double == m_ValueStyle)
	{
		auto pTarget = (double*)m_pTarget;
		delete pTarget;
	}
	else if (RTVS_string == m_ValueStyle)
	{
		auto pTarget = (std::string*)m_pTarget;
		delete pTarget;
	}

	else if (RTVS_vector_int == m_ValueStyle)
	{
		auto pTarget = (std::vector<int>*)m_pTarget;
		delete pTarget;
	}
	else if (RTVS_vector_unsigned_int == m_ValueStyle)
	{
		auto pTarget = (std::vector<unsigned int>*)m_pTarget;
		delete pTarget;
	}
	else if (RTVS_vector_double == m_ValueStyle)
	{
		auto pTarget = (std::vector<double>*)m_pTarget;
		delete pTarget;
	}
	else if (RTVS_vector_string == m_ValueStyle)
	{
		auto pTarget = (std::vector<std::string>*)m_pTarget;
		delete pTarget;
	}

	else if (RTVS_dict == m_ValueStyle)
	{
		auto pTarget = (CRTDict*)m_pTarget;
		delete pTarget;
	}
	else
	{
		this->NoSurpport("value type error");
	}

	m_pTarget = nullptr;
	m_ValueStyle = RTVS_unknown;
}


CRTValue& CRTValue::operator = (const CRTValue& _other)
{
	//数据类型不一致时，直接覆盖
	switch (_other.m_ValueStyle)
	{
	case RTVS_int:					*this = *(int*)_other.m_pTarget; break;
	case RTVS_unsigned_int:			*this = *(unsigned int*)_other.m_pTarget; break;
	case RTVS_double:				*this = *(double*)_other.m_pTarget; break;
	case RTVS_string:				*this = *(std::string*)_other.m_pTarget; break;
	case RTVS_dict:					*this = *(CRTDict*)_other.m_pTarget; break;
	case RTVS_vector_int:			*this = *(std::vector<int>*)_other.m_pTarget; break;
	case RTVS_vector_unsigned_int:	*this = *(std::vector<unsigned int>*)_other.m_pTarget; break;
	case RTVS_vector_double:		*this = *(std::vector<double>*)_other.m_pTarget; break;
	case RTVS_vector_string:		*this = *(std::vector<std::string>*)_other.m_pTarget; break;
	case RTVS_vector_dict:			*this = *(std::vector<CRTDict>*)_other.m_pTarget; break;

	default:						this->NoSurpport("value type error"); break;
	}//switch

	return(*this);
}


CRTValue& CRTValue::operator = (const int _other)
{
	this->DeleteTargetPointer();

	m_pTarget = new int(_other);
	m_ValueStyle = RTVS_int;

	return(*this);
}


CRTValue& CRTValue::operator=(const unsigned int _other)
{
	this->DeleteTargetPointer();

	m_pTarget = new unsigned int(_other);
	m_ValueStyle = RTVS_unsigned_int;

	return(*this);
}


CRTValue& CRTValue::operator = (const double _other)
{
	this->DeleteTargetPointer();

	m_pTarget = new double(_other);
	m_ValueStyle = RTVS_double;

	return(*this);
}


CRTValue& CRTValue::operator = (const char* _other)
{
	const std::string str(_other);

	*this = str;

	return(*this);
}


CRTValue& CRTValue::operator = (const std::string _other)
{
	this->DeleteTargetPointer();

	m_pTarget = new std::string(_other);
	m_ValueStyle = RTVS_string;

	return(*this);
}


CRTValue& CRTValue::operator = (const CRTDict& _other)
{
	this->DeleteTargetPointer();

	m_pTarget = new CRTDict(_other);
	m_ValueStyle = RTVS_dict;

	return(*this);
}


CRTValue& CRTValue::operator = (const std::vector<int>& _other)
{
	this->DeleteTargetPointer();

	m_pTarget = new std::vector<int>(_other);
	m_ValueStyle = RTVS_vector_int;

	return(*this);
}


CRTValue& CRTValue::operator=(const std::vector<unsigned int>& _other)
{
	this->DeleteTargetPointer();

	m_pTarget = new std::vector<unsigned int>(_other);
	m_ValueStyle = RTVS_vector_unsigned_int;

	return(*this);
}


CRTValue& CRTValue::operator = (const std::vector<double>& _other)
{
	this->DeleteTargetPointer();

	m_pTarget = new std::vector<double>(_other);
	m_ValueStyle = RTVS_vector_double;

	return(*this);
}


CRTValue& CRTValue::operator = (const std::vector<std::string>& _other)
{
	this->DeleteTargetPointer();

	m_pTarget = new std::vector<std::string>(_other);
	m_ValueStyle = RTVS_vector_string;

	return(*this);
}


CRTValue& CRTValue::operator = (const std::vector<CRTDict>& _other)
{
	this->DeleteTargetPointer();

	m_pTarget = new std::vector<CRTDict>(_other);
	m_ValueStyle = RTVS_vector_dict;

	return(*this);
}


int CRTValue::GetInt(void) const
{
	const auto result = *(int*)m_pTarget;

	return(result);
}


unsigned int CRTValue::GetUInt(void) const
{
	const auto result = *(unsigned int*)m_pTarget;

	return(result);
}


double CRTValue::GetDouble(void) const
{
	const auto result = *(double*)m_pTarget;

	return(result);
}


std::string CRTValue::GetString(void) const
{
	const auto result = *(std::string*)m_pTarget;

	return(result);
}


CRTDict CRTValue::GetDict(void) const
{
	const auto result = *(CRTDict*)m_pTarget;

	return(result);
}


std::vector<int> CRTValue::GetVectorInt(void) const
{
	const auto result = *(std::vector<int>*)m_pTarget;

	return(result);
}


std::vector<unsigned int> CRTValue::GetVectorUInt(void) const
{
	const auto result = *(std::vector<unsigned int>*)m_pTarget;

	return(result);
}


std::vector<double> CRTValue::GetVectorDouble(void) const
{
	const auto result = *(std::vector<double>*)m_pTarget;

	return(result);
}


std::vector<std::string> CRTValue::GetVectorString(void) const
{
	const auto result = *(std::vector<std::string>*)m_pTarget;

	return(result);
}


std::vector<CRTDict> CRTValue::GetVectorDict(void) const
{
	const auto result = *(std::vector<CRTDict>*)m_pTarget;

	return(result);
}

