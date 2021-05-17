#include "stdafx.h"
#include "cUI.h"


cUI::cUI()
{
}


cUI::~cUI()
{
}

void cUI::Update()
{
	UpdateTransform();

	if (m_pParent)
		m_matWorld *= m_pParent->m_matWorld;

	for each(auto pUI in m_apChild)
	{
		pUI->Update();
	}
}

void cUI::SetParent(cUI * pParent)
{
	m_pParent = pParent;
}
