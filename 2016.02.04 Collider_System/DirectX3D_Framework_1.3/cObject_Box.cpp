#include "stdafx.h"
#include "cObject_Box.h"


cObject_Box::cObject_Box()
{
	D3DXCreateBox(g_pDevice, 10, 5, 5, &mesh, NULL);
}


cObject_Box::~cObject_Box()
{
	SafeRelease(mesh);
}


void cObject_Box::Setup()
{
}


void cObject_Box::Update()
{
}


void cObject_Box::Render()
{
	//mesh->DrawSubset(0);
}
