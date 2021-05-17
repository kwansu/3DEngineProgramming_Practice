#include "stdafx.h"
#include "cObj_Player.h"


cObj_Player::cObj_Player()
{
}


cObj_Player::~cObj_Player()
{
}

void cObj_Player::Setup()
{
	m_mtl.Diffuse = D3DXCOLOR(0.2f, 0.5f, 0.8f, 1);
}

void cObj_Player::Update()
{
	cObj_Human::Update();
}
