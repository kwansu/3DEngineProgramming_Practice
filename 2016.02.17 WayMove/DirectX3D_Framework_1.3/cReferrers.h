#pragma once

// 객체 할당마다 생성되는 참조카운터
// 자원의 할당뒤, 제대로 해제되는지 확인하는 용도.

class cReferrers
{
private:
	int m_nRefCount;

public:
	cReferrers();
	~cReferrers();
	void AddRef();
	void Release();
};

