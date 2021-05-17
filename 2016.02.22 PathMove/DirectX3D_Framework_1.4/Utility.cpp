#include "stdafx.h"

bool MYFILELOAD::IsBlank(char c)
{
	return c < 33;
}

void MYFILELOAD::GetToken(std::ifstream & iFile, OUT char * szToken, unsigned uMaxLength)
{
	unsigned uTokenLen = 0;

	while (uTokenLen < uMaxLength)
	{
		char c = iFile.get();

		if (iFile.eof())
			break;

		if (IsBlank(c))
		{
			if (uTokenLen == 0)
				continue;

			break;
		}

		szToken[uTokenLen++] = c;
	}

	szToken[uTokenLen] = '\0';
}

void MYFILELOAD::GetFloat(std::ifstream & iFile, OUT float* fOut)
{
	char szToken[1024];
	GetToken(iFile, szToken);

	*fOut = atof(szToken);
}

void MYFILELOAD::GetInteger(std::ifstream & iFile, OUT int * nOut)
{
	char szToken[1024];
	GetToken(iFile, szToken);

	*nOut = atoi(szToken);
}
