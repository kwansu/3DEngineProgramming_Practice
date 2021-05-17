#pragma once

class ASELoader;

class cGeometry
{
	friend class ASELoader;
protected:
	cGeometry*			m_pParent;
	vector<Vertex_PNT>	m_aVertex;
	vector<cGeometry*>	m_apChild;
	D3DMATERIAL9		m_mtl;
	LPDIRECT3DTEXTURE9	m_pTexture;

	D3DXMATRIXA16		m_matLocal;
	D3DXMATRIXA16		m_matWorld;
	
public:
	cGeometry();
	~cGeometry();

	virtual void Update();
	virtual void Render(D3DXMATRIXA16* pmatParent);
};

