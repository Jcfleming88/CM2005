#include <vector>
#include <string>
#include <fstream>
#include <iostream>

#include "OrderBookEntry.h"
#include "TextUtils.h"

#pragma once
class CSVParser
{
public:
	CSVParser() = default;
	static std::vector<OrderBookEntry> ReadFile(std::string filename);
	static std::vector<std::string> Tokenise(std::string csvLine, char seperator);
	static OrderBookEntry StringsToOBE(
		std::string timestamp,
		std::string product,
		OrderBookType orderType,
		std::string price,
		std::string amount
	);

private:
	static OrderBookEntry StringsToOBE(std::vector<std::string> tokens, int lineNumber = 0);
};

