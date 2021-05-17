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
	// ����, �ٳ���, �鿩����� �ܾ��� ������ �Ǵ�
	bool IsBlank(char c);

	void GetToken(std::ifstream& iFile, OUT char* szToken, unsigned uMaxLength = 1024);
	void GetFloat(std::ifstream& iFile, OUT float* fOut);
	void GetInteger(std::ifstream& iFile, OUT int* nOut);
}