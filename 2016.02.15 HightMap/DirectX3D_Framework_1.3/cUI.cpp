#include "stdafx.h"
#include "cUI.h"


cUI::cUI()
	: m_pTexture(NULL)
{
}


cUI::~cUI()
{
	SafeRelease(m_pTexture);
}

void cUI::Setup()
{
}

void cUI::Update()
{
}

void cUI::Render()
{
}

