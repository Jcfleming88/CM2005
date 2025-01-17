#include "TextUtils.h"

void TextUtils::PrintBreak()
{
    std::cout << "=================================================" << std::endl;
}

bool TextUtils::IsNumber(std::string str)
{
	int numberOfDecimals = 0;
	for (char c : str)
	{
		if (c < '0' || c > '9')
		{
			if (c == '.' && numberOfDecimals == 0)
			{
				numberOfDecimals++;
			}
			else
			{
				return false;
			}
		}
	}
	return true;
}