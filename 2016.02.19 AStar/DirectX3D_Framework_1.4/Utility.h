#pragma once


template <typename T>
inline void SafeDelete(T& p)
{
	if (p)
	{
		delete p;
		p = NULL;
	}
}


template <typename T>
inline void SafeRelease(T& p)
{
	if (p)
	{
		p->Release();
		p = NULL;
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


namespace MYFILELOAD
{
	// 띄어쓰기, 줄내림, 들여쓰기등 단어의 끝인지 판단
	bool IsBlank(char c);

	void GetToken(std::ifstream& iFile, OUT char* szToken, unsigned uMaxLength = 1024);
	void GetFloat(std::ifstream& iFile, OUT float* fOut);
	void GetInteger(std::ifstream& iFile, OUT int* nOut);
}