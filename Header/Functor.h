#pragma once


template<typename T>
void Safe_Delete(T& Temp)
{
	if (Temp)
	{
		delete Temp;
		Temp = nullptr;
	}
}


class CTagFinder
{
private:
	const TCHAR*		m_pStrKey;

public:
	CTagFinder(const TCHAR* pStrKey)
		: m_pStrKey(pStrKey)
	{

	}

public:
	template<typename T>
	bool		operator()(T& Pair)
	{
		return !lstrcmp(m_pStrKey, Pair.first);
	}
};

class CDeleteMap
{
public:
	template<typename T>
	void operator()(T& Pair)
	{
		if (Pair.second)
		{
			delete Pair.second;
			Pair.second = nullptr;
		}
	}
};

class CDeleteObj
{
public:
	template<typename T>
	void operator()(T& Temp)
	{
		if (Temp)
		{
			delete Temp;
			Temp = nullptr;
		}
	}
};

template<typename T>
bool		CompareY(T Dest, T Sour)
{
	return Dest->Get_Info().fY < Sour->Get_Info().fY;
}
