#include "stdafx.h"
#include "cReferenceCounter.h"


cReferenceCounter::cReferenceCounter()
{
}


cReferenceCounter::~cReferenceCounter()
{
}


void cReferenceCounter::AddReference(cReferrers* pReferrers)
{
	m_setReferrers.insert(pReferrers);
}


void cReferenceCounter::RemovecReference(cReferrers* pReferrers)
{
	m_setReferrers.erase(pReferrers);
}


void cReferenceCounter::Destroy()
{
	//assert(m_setReferrers.empty() && "안지워진 객체가 있습니다.");
}
