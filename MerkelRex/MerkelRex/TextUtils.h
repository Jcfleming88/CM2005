#pragma once

#include <string>
#include <iostream>

/* A series of functions used to help perform common text tasks */
class TextUtils
{
public:
	/* Clears the console */
	static void clearConsole();

	/* Deletes the last line in the console */
	static void deleteLine();

	/* Checks if the string is in a date format */
	static bool isDate(std::string& str);

	/* Checks if the string is a number */
	static bool isNumber(std::string str);

	/* Prints a break line to the console */
	static void printBreak();

	/* Converts a float to a string with the specified number of decimal places */
	static std::string toRoundedString(float num, int precision);

	/* Trims the whitespace from the string */
	static void trim(std::string& str);
};