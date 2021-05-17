#pragma once

// 매크로를 대체할 템플릿 인라인 함수들 :

template <typename T>
inline void SafeDelete(T &ptr)
{
	if (ptr)
	{
		delete ptr;
		ptr = NULL;
	}
}


template <typename T>
inline void SafeRelease(T &ptr)
{
	if (ptr)
	{
		ptr->Release();
		ptr = NULL;
	}
}


#define SINGLETONE(class_name) private:\
	class_name(void);\
public:\
	~class_name(void);\
	static class_name* GetInstance()\
{\
	static class_name instance;\
	return &instance;\
}

