#pragma once

#include "OrderBookEntry.h"

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

	/** check if the wallet can fulfill an order */
	bool canFulfillOrder(OrderBookEntry order);

	/** processes a sale. Assumes the order was made by the owner of the wallet  */
	void processSale(OrderBookEntry& sale);

	/** generate a string representation of the wallet */
	std::string toString();

private:
	std::map<std::string, double> currencies;
};