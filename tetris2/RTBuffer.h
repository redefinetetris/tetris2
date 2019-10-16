#ifndef __RTBUFFER_H__
#define __RTBUFFER_H__


#include <vector>
#include <atomic>


template<class T>
class CRTBuffer
{
public:
	CRTBuffer()
		: m_Switch(true)
		, m_Index(0)
		, m_ReaderBuffer()
		, m_WriterBuffer()
	{
		m_ReaderBuffer.reserve(VECTOR_RESERVE_SIZE);
		m_WriterBuffer.reserve(VECTOR_RESERVE_SIZE);
	}
	~CRTBuffer()
	{}

private:
	std::atomic<bool> m_Switch;
	size_t m_Index;
	std::vector<T> m_ReaderBuffer;
	std::vector<T> m_WriterBuffer;

private:
	bool SwitchBuffer(void)
	{
		if (false == m_Switch)
		{
			return(false);
		}

		if (0 == m_WriterBuffer.size())
		{
			return(false);
		}

		m_ReaderBuffer.clear();
		m_ReaderBuffer.swap(m_WriterBuffer);

		m_Index = 0;
		m_Switch = false;

		return(true);
	}

	bool CanRead(void)
	{
		if (m_Switch)
		{
			return(false);
		}

		if (m_ReaderBuffer.size() <= m_Index)
		{
			m_Switch = true;

			return(false);
		}

		return(true);
	}

	void TryResetSwitch(void)
	{
		if (m_ReaderBuffer.size() <= m_Index)
		{
			m_Switch = true;
		}
	}

public:
	void Clear(void)
	{
		m_Switch = true;
		m_Index = 0;

		m_ReaderBuffer.clear();
		m_WriterBuffer.clear();
	}

	int FlushWriter(void)
	{
		const auto code = SwitchBuffer();
		if (code)
		{
			return(1);
		}

		if (m_WriterBuffer.size())
		{
			return(1);
		}

		return(0);
	}

public:
	bool Reader(T& _Data)
	{
		if (false == this->CanRead())
		{
			return(false);
		}

		_Data = m_ReaderBuffer[m_Index];
		++m_Index;

		this->TryResetSwitch();

		return(true);
	}

	void Writer(const T _Data)
	{
		m_WriterBuffer.push_back(_Data);

		this->SwitchBuffer();
	}

	bool Reader(std::vector<T>& _Datas)
	{
		if (false == CanRead())
		{
			return(false);
		}

		_Datas.insert(_Datas.end(), m_ReaderBuffer.begin() + m_Index, m_ReaderBuffer.end());
		m_Index = m_ReaderBuffer.size();

		this->TryResetSwitch();

		return(true);
	}

	void Writer(const std::vector<T>& _Datas)
	{
		m_WriterBuffer.insert(m_WriterBuffer.end(), _Datas.begin(), _Datas.end());

		this->SwitchBuffer();
	}
};


#endif//__RTBUFFER_H__

