#ifndef __RTBUFFERSIMPLE_H__
#define __RTBUFFERSIMPLE_H__


#include <vector>


template<class T>
class CRTBufferSimple
{
public:
	CRTBufferSimple()
		: m_Index(0)
		, m_Buffer()
	{
		m_Buffer.reserve(VECTOR_RESERVE_SIZE);
	}
	~CRTBufferSimple()
	{}

private:
	size_t m_Index;
	std::vector<T> m_Buffer;

public:
	void Clear(void)
	{
		m_Index = 0;
		m_Buffer.clear();
	}

	bool Reader(T& _Data)
	{
		if (m_Buffer.size() <= m_Index)
		{
			return(false);
		}

		_Data = m_Buffer[m_Index];
		++m_Index;

		return(true);
	}

	void Writer(const T _Data)
	{
		m_Buffer.push_back(_Data);
	}

	bool Reader(std::vector<T>& _Datas)
	{
		if (m_Buffer.size() <= m_Index)
		{
			return(false);
		}

		_Datas.insert(_Datas.end(), m_Buffer.begin() + m_Index, m_Buffer.end());

		this->Clear();

		return(true);
	}

	void Writer(const std::vector<T>& _Datas)
	{
		m_Buffer.insert(m_Buffer.end(), _Datas.begin(), _Datas.end());
	}
};


#endif//__RTBUFFERSIMPLE_H__

