#pragma once
#include "cReferrers.h"

#define g_pRefCounter cReferenceCounter::GetInstance()

// 프로그램의 직접할당하는 객체의 참조테이블.
class cReferenceCounter
{
	friend class cReferrers;
	SINGLETONE(cReferenceCounter);

private:
	set<cReferrers*>	m_setReferrers;

private:
	void AddReference(cReferrers* pReferrers);
	void RemovecReference(cReferrers* pReferrers);

public:
	void Destroy();
};

