#pragma once
#include "stVertex.h"

class cGrid
{
private:
	vector<stVertex_PC>	m_aVertex;
	D3DXMATRIXA16		m_matInterval;
	int					m_nLine;

public:
	cGrid();
	~cGrid();
	void Setup();
	void Render();
	// 격자 사이 간격
	void SetInterval(float fInterval);
};

