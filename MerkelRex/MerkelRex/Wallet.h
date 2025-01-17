#pragma once

#include <string>
#include <map>
#include <ostream>

class Wallet
{

public:
	Wallet();

	friend std::ostream& operator<<(std::ostream& os, Wallet& wallet);

	/** insert currency to the wallet */
	void insertCurrency(std::string type, double amount);

	/** remove currency from the wallet */
	bool removeCurrency(std::string type, double amount);

	/** check if the wallet contains this much currency or more */
	bool containsCurrency(std::string type, double amount);

	/** generate a string representation of the wallet */
	std::string toString();

private:
	std::map<std::string, double> currencies;
};