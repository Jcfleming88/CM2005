#include "Wallet.h"

Wallet::Wallet()
{

}

std::ostream& operator<<(std::ostream& os, Wallet& wallet)
{
	os << wallet.toString();
	return os;
}

void Wallet::insertCurrency(std::string type, double amount)
{
	if (amount < 0)
	{
		throw std::exception("Amount cannot be negative");
	}

	if (currencies.count(type) == 0)
	{
		currencies[type] = 0;
	}

	currencies[type] += amount;
}

bool Wallet::removeCurrency(std::string type, double amount)
{
	return true;
}

bool Wallet::containsCurrency(std::string type, double amount)
{
	return true;
}

std::string Wallet::toString()
{
	std::string s;

	// Escape if there is no currencies in the wallet
	if (currencies.size() == 0)
	{
		s = "The wallet is empty\nMoths just flew out!\n";
		return s;
	}

	// Iterate through the currencies and add them to the string
	for (std::pair<std::string, double> pair : currencies)
	{
		std::string currency = pair.first;
		double amount = pair.second;
		s += currency + " : " + std::to_string(amount) + "\n";
	}

	return s;
}