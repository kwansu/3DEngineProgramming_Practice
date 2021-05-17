#include "stdafx.h"
#include "cReferrers.h"


cReferrers::cReferrers()
: m_nRefCount(1)
{
	g_pRefCounter->AddReference(this);
}


cReferrers::~cReferrers()
{
	//assert(m_nRefCount <= 0 && "참조자가 잘못 지워졌습니다.");
	//g_pRefCounter->RemovecReference(this);
}


void cReferrers::AddRef()
{
	++m_nRefCount;
}


void cReferrers::Release()
{
	//--m_nRefCount;
	//if (m_nRefCount <= 0)
	//	delete this;
}
