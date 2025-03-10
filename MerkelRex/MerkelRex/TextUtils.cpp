#include "TextUtils.h"

#include <iostream>
#include <iomanip>
#include <sstream>
#include <cstdlib>
#include <algorithm>
#include <cctype>
#include <regex>

void TextUtils::printBreak()
{
	std::string breakLine = "";

	for (int i = 0; i < 100; i++)
	{
		breakLine += "=";
	}

	std::cout << breakLine << std::endl;
}

bool TextUtils::isNumber(std::string str)
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

bool TextUtils::isDate(std::string& str)
{
	trim(str);
	std::regex dateRegex{ "^[0-9]{4}(-[0-9]{2}(-[0-9]{2}){0,1}){0,1}$" };
	return std::regex_match(str, dateRegex);
}

std::string TextUtils::toRoundedString(float num, int precision)
{
	std::stringstream ss;
	ss << std::fixed << std::setprecision(precision) << num;
	return ss.str();
}

void TextUtils::clearConsole()
{
	std::system("cls");
}

void TextUtils::deleteLine()
{
	std::cout << "\033[A\33[2K\r";
}

void TextUtils::trim(std::string& s) {
	s.erase(s.begin(), std::find_if_not(s.begin(), s.end(), [](unsigned char ch) {
		return std::isspace(ch);
		}));
	s.erase(std::find_if_not(s.rbegin(), s.rend(), [](unsigned char ch) {
		return std::isspace(ch);
		}).base(), s.end());
}