#include "CSVParser.h"
#include <regex>

std::vector<OrderBookEntry> CSVParser::ReadFile(std::string filename)
{
	// Create a new set of order book entries
	std::vector<OrderBookEntry> output = std::vector<OrderBookEntry>{};

	// Open the file
	std::cout << "Opening file" << std::endl;
	TextUtils::printBreak();

	std::ifstream file = std::ifstream{ filename };
	if (!file.is_open())
	{
		std::cout << "Unable to open file. Check the filepath in MerkelMain.h and try again." << std::endl;
		return output;
	};

	// Read each line and convert it to an entry
	std::cout << "Reading file and checking for errors, please wait..." << std::endl;
	std::cout << std::endl;

	// Create a vector to store error data
	std::vector<std::string> errors;

	// Set out error reporting
	int lineNumber = 1;
	int errorCount = 0;

	// Output the number of lines read
	std::cout << "Lines read: " << lineNumber << std::endl;

	// Start by setting up the dictionary and getting the headings from the csv
	std::string line;

	while (std::getline(file, line))
	{
		// Split the line into tokens
		std::vector<std::string> tokens = Tokenise(line, ',');

		try 
		{
			// Output the tokens
			output.push_back(StringsToOBE(tokens));
		}
		catch (const std::exception& e)
		{
			// Output the error
			std::string errorMsg = "Line: " + lineNumber;
			errorMsg += " - ";
			errorMsg += e.what();
			errors.push_back(errorMsg);

			errorCount++;
		}

		lineNumber++;

		if (lineNumber % 1000 == 0)
		{
			TextUtils::deleteLine();
			std::cout << "Lines read: " << lineNumber << std::endl;
		}
	}

	// Correction for getting the total number of lines
	lineNumber--;

	TextUtils::deleteLine();
	std::cout << "Lines read: " << lineNumber << std::endl;

	// Close error report
	if (errorCount == 0)
	{
		std::cout << "No errors found." << std::endl;
	}
	else
	{
		std::cout << "Errors found: " << errorCount << std::endl;
		std::cout << "Error report:" << std::endl;
		for (std::string& error : errors)
		{
			std::cout << error << std::endl;
		}
	}
	std::cout << std::endl;

	std::cout << "Reading complete" << std::endl;
	TextUtils::printBreak();
	std::cout << "Output Report" << std::endl;
	std::cout << "Total lines read and converted: " << lineNumber - errorCount << " of " << lineNumber << std::endl;
	TextUtils::printBreak();

	// Example output - For debugging to ensure the correct info is coming out
	// -----------------------------------------------------------------------
	/*std::cout << std::endl;
	std::cout << "Example output from dataset" << std::endl;
	for (int i = 0; i < 5; i++)
	{
		TextUtils::printBreak();
		output[i].printEntry();
	}
	TextUtils::printBreak();
	std::cout << std::endl;*/
	// -----------------------------------------------------------------------

	// Close the file when finished
	std::cout << "Closing file" << std::endl;

	// Close the file
	file.close();

	// Check if the file closed
	if (file.is_open())
	{
		std::cout << "Could not close file" << std::endl;
	}

	std::cout << std::endl;

	// Complete the process
	return output;
}

OrderBookEntry CSVParser::StringsToOBE(std::vector<std::string> tokens, int lineNumber)
{
	// Check what was outputted by the tokeniser
	if (tokens.size() == 0)
	{
		// If there is no line
		throw std::exception{"Empty Line"};
	}
	else if (tokens.size() != 5)
	{
		// If the line is not in the correct format
		throw std::exception{ "Line is not in the correct format" };
	}

	// Check the Order Book Type
	if (tokens[2] != "bid" && tokens[2] != "ask")
	{
		throw std::exception{ "Incorrect order book type" };
	}

	// Check the numbers are actually numbers
	if (!TextUtils::isNumber(tokens[3]) || !TextUtils::isNumber(tokens[4]))
	{
		throw std::exception{ "Price or amount is not a number" };
	}

	// Convert to an order book entry
	OrderBookEntry obe{
		tokens[0],
		tokens[1],
	 	OrderBookEntry::stringToOrderBookType(tokens[2]),
		std::stod(tokens[3]),
		std::stod(tokens[4])
	};

	return obe;
}

std::vector<std::string> CSVParser::Tokenise(std::string csvLine, char separator)
{
	// string vector tokens ## stores the tokens
	std::vector<std::string> tokens;

	// int start, end ## used to delineate the position of the tokens
	int start = csvLine.find_first_not_of(separator);
	int end = 0;

	// start the loop
	do 
	{
		// end = next 'separator' after start
		end = csvLine.find(separator, start);

		if (start == csvLine.size() || start == end)
		{
			// nothing more to find
			break;
		}

		std::string token;
		if (end >= 0)
		{
			// We found the separator
			token = csvLine.substr(start, end - start); // start, substring length
		}
		else
		{
			// end is invalid
			token = csvLine.substr(start, csvLine.size() - start);
		}
		
		// add token to the end of the tokens vector
		tokens.push_back(token);
		
		// move past this token
		start = end + 1;
	} 
	while (end > 0); // continue loop condition

	return tokens;
}

OrderBookEntry CSVParser::StringsToOBE(
	std::string timestamp,
	std::string product,
	OrderBookType orderType,
	std::string price,
	std::string amount
)
{
	std::regex timeStampRegex{ R"(\d{4}\/\d{2}\/\d{2} \d{2}:\d{2}:\d{2}.\d{0,6})" };
	std::regex productRegex{ R"(\w+/\w+)" };

	// Check the timestamp
	if (!std::regex_match(timestamp, timeStampRegex))
	{
		throw std::exception{ "CSVReader::stringToOBE - Incorrect timestamp" };
	}

	// Check the product
	if (!std::regex_match(product, productRegex))
	{
		throw std::exception{ "CSVReader::stringToOBE - Incorrect product" };
	}

	// Check the order type
	if (orderType != OrderBookType::bid && orderType != OrderBookType::ask)
	{
		throw std::exception{ "CSVReader::stringToOBE - Incorrect order book type" };
	}

	double numPrice, numAmount;

	// Convert the numbers
	try {
		numPrice = std::stod(price);
		numAmount = std::stod(amount);
	}
	catch (const std::exception& e) {
		throw  std::exception{ "CSVReader::stringToOBE - Price or amount is not a number" };
	}

	// Check the numbers are about zero
	if (numAmount <= 0)
	{
		throw std::exception{ "CSVReader::stringToOBE - Amount is less than or equal to zero" };
	}

	if (numPrice <= 0)
	{
		throw std::exception{ "CSVReader::stringToOBE - Price is less than or equal to zero" };
	}
	
	// Convert to an order book entry
	OrderBookEntry obe{
		timestamp,
		product,
		orderType,
		numPrice,
		numAmount
	};

	return obe;
}