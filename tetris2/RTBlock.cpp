#include "RTBlock.h"
#include "RTArray.h"


CRTBlock::CRTBlock(const int _Length, const int _Width, const int _ID)
	: m_pSpace(New2DArray<int>(_Length, _Width))
	, m_Length(_Length)
	, m_Width(_Width)
	, m_ID(_ID)
	, m_O(0, 0, 0)
	, m_RealLength(0)
{
	this->ClearValue();
}


CRTBlock::CRTBlock(const std::vector<int> &_Values, const int _Length, const int _Width, const int _ID)
	: CRTBlock(_Length, _Width, _ID)
{
	this->SetValue(_Values);
}


CRTBlock::CRTBlock(const CRTBlock &_other)
	: m_pSpace(New2DArray<int>(_other.m_Length, _other.m_Width))
	, m_Length(_other.m_Length)
	, m_Width(_other.m_Width)
	, m_ID(_other.m_ID)
	, m_O(_other.m_O)
	, m_RealLength(_other.m_RealLength)
{
	this->SetValue(_other.GetValue());
}


CRTBlock::~CRTBlock()
{
}


const std::unique_ptr<int[]>& CRTBlock::operator[](const int _Index) const
{
	return(m_pSpace[_Index]);
}


std::unique_ptr<int[]>& CRTBlock::operator[](const int _Index)
{
	return(m_pSpace[_Index]);
}


int CRTBlock::GetLength(void) const
{
	return(m_Length);
}


void CRTBlock::SetLength(const int &_Length)
{
	m_Length = _Length;
}


int CRTBlock::GetWidth(void) const
{
	return(m_Width);
}


void CRTBlock::SetWidth(const int &_Width)
{
	m_Width = _Width;
}


int CRTBlock::GetID(void) const
{
	return(m_ID);
}


void CRTBlock::SetID(const int &_ID)
{
	m_ID = _ID;
}


CRTPoint CRTBlock::GetO(void) const
{
	return(m_O);
}


void CRTBlock::SetO(const CRTPoint &_O)
{
	m_O = _O;
}


void CRTBlock::ClearO(void)
{
	m_O.Clear();
}


int CRTBlock::GetRealLength(void) const
{
	return(m_RealLength);
}


bool CRTBlock::IsOK(void) const
{
	if (m_O.GetX() || m_O.GetY())
	{
		return(true);
	}

	return(false);
}


void CRTBlock::CountRealLength(void)
{
	for (int x = m_Length - 1; 0 <= x; --x)
	{
		for (int y = 0; y < m_Width; ++y)
		{
			if (m_pSpace[x][y])
			{
				m_RealLength = x + 1;

				return;
			}
		}
	}//for
}


void CRTBlock::ClearValue(const int _Value)
{
	const std::vector<int> Values(m_Length*m_Width, _Value);

	this->SetValue(Values);
}


void CRTBlock::SetBorder(const int _Value)
{
	for (int y = 0; y < m_Width; ++y)
	{
		m_pSpace[0][y] = _Value;
		m_pSpace[m_Length - 4][y] = _Value;
		m_pSpace[m_Length - 3][y] = _Value;
		m_pSpace[m_Length - 2][y] = _Value;
		m_pSpace[m_Length - 1][y] = _Value;
	}

	const auto halfY = m_Width / 2;
	m_pSpace[m_Length - 4][halfY] = 0;
	m_pSpace[m_Length - 3][halfY] = 0;
	m_pSpace[m_Length - 2][halfY] = 0;

	for (int x = 0; x < m_Length; ++x)
	{
		m_pSpace[x][0] = _Value;
		m_pSpace[x][m_Width - 1] = _Value;
	}
}


std::vector<int> CRTBlock::GetValue(void) const
{
	std::vector<int> Values;
	Values.reserve(m_Length*m_Width);

	for (int x = 0; x < m_Length; ++x)
	{
		for (int y = 0; y < m_Width; ++y)
		{
			Values.push_back(m_pSpace[x][y]);
		}
	}

	return(Values);
}


void CRTBlock::SetValue(const std::vector<int>& _Values)
{
	for (int x = 0; x < m_Length; ++x)
	{
		const auto x_pos = x*m_Width;

		for (int y = 0; y < m_Width; ++y)
		{
			m_pSpace[x][y] = _Values[x_pos + y];
		}
	}
}


int CRTBlock::GetValue(const CRTPoint _Point) const
{
	return(this->GetValue(_Point.GetX(), _Point.GetY()));
}


void CRTBlock::SetValue(const CRTPoint _Point, const int _Value)
{
	return(this->SetValue(_Point.GetX(), _Point.GetY(), _Value));
}


int CRTBlock::GetValue(const int _X, const int _Y) const
{
	return(m_pSpace[_X][_Y]);
}


void CRTBlock::SetValue(const int _X, const int _Y, const int _Value)
{
	m_pSpace[_X][_Y] = _Value;
}

