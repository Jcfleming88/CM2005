#include "Wallet.h"
#include "CSVParser.h"

#include <iostream>

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

	double balance;
	if (currencies.count(type) == 0)
	{
		balance = 0;
	}
	else {
		balance = currencies[type];
	}

	balance += amount;
	currencies[type] = balance;
}

bool Wallet::removeCurrency(std::string type, double amount)
{
	if (amount < 0)
	{
		throw std::exception("Amount cannot be negative");
	}

	if (currencies.count(type) == 0)
	{
		return false;
	}
	else {
		if (containsCurrency(type, amount))
		{
			currencies[type] -= amount;
			std::cout << "Removing " << amount << " " << type << " from the wallet" << std::endl;
		}
		else
		{
			return false;
		}
	}

	return true;
}

bool Wallet::containsCurrency(std::string type, double amount)
{
	if (currencies.count(type) == 0)
		return false;
	else
		return currencies[type] >= amount;
}

bool Wallet::canFulfillOrder(OrderBookEntry order)
{
	std::vector<std::string> currencies = CSVParser::Tokenise(order.product, '/');

	// ask
	if (order.orderType == OrderBookType::ask)
	{
		double amount = order.amount;
		std::string currency = currencies[0];
		return containsCurrency(currency, amount);
	}
	// bid
	else if (order.orderType == OrderBookType::bid)
	{
		double amount = order.price * order.amount;
		std::string currency = currencies[1];
		return containsCurrency(currency, amount);
	}

	return false;
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

void Wallet::processSale(OrderBookEntry& sale)
{
	std::vector<std::string> currencies = CSVParser::Tokenise(sale.product, '/');
	
	// ask
	if (sale.orderType == OrderBookType::asksale)
	{
		double outgoingAmount = sale.amount;
		std::string outgoingCurrency = currencies[0];

		double incomingAmount = sale.price * sale.amount;
		std::string incomingCurrency = currencies[1];

		removeCurrency(outgoingCurrency, outgoingAmount);
		insertCurrency(incomingCurrency, incomingAmount);
	}
	// bid
	else if (sale.orderType == OrderBookType::bidsale)
	{
		double incomingAmount = sale.amount;
		std::string incomingCurrency = currencies[0];

		double outgoingAmount = sale.price * sale.amount;
		std::string outgoingCurrency = currencies[1];

		removeCurrency(outgoingCurrency, outgoingAmount);
		insertCurrency(incomingCurrency, incomingAmount);
	}
}