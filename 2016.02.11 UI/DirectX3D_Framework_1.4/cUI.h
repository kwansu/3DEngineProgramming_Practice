#pragma once

class cUI :
	public cTransform
{
protected:
	cUI*			m_pParent;
	vector<cUI*>	m_apChild;

public:
	cUI();
	~cUI();

	virtual void Setup()	{}
	virtual void Update();
	virtual void Render()	{}
	virtual void Event(cUI* pGenerator)	{}

	void SetParent(cUI* pParent);
};


class iUI_Messenger
{
public:
	virtual void DisableUI(cUI* pSender) = 0;
};
