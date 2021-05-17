#include "stdafx.h"
#include "cObject_Woman.h"


cObject_Woman::cObject_Woman()
{
	//m_fAngleX = -90;
	SetScale(5, 5, 5);
	UpdateWorld();
}


cObject_Woman::~cObject_Woman()
{
}


void cObject_Woman::Setup()
{
}


void cObject_Woman::Update()
{
}


void cObject_Woman::Render()
{
	m_pRoot->Render(&m_matWolrd);
}
