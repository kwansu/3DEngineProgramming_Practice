#pragma once
#include "cObj_Box.h"

class cObj_Wall :
	public cObj_Box
{
public:
	cObj_Wall();
	~cObj_Wall();

	void Setup();

private:
	// 현재 벽의 각 모서리에 길찾기노드를 추가한다
	// 벽의 위치가 변하면 같이 변하므로, 배치 완료후 한번만 호출
	void AddPathNode();
};

