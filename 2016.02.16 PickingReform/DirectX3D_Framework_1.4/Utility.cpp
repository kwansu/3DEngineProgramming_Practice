#include "stdafx.h"

bool MYFILELOAD::IsBlank(char c)
{
	return false;
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
