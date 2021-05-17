#pragma once

class cObjFileLoader
{
private:
	map<string, stMeshAttribute>	m_mapAttribute;

public:
	cObjFileLoader();
	~cObjFileLoader();

	void LoadObj();
};

