#include "OrderBookEntry.h"

OrderBookEntry::OrderBookEntry() {
	price = 0;
	amount = 0;
	timestamp = "";
	product = "";
	orderType = OrderBookType::unknown;
};

OrderBookEntry::OrderBookEntry(
    std::string timestamp,
    std::string product,
    OrderBookType orderType,
    double price,
    double amount)
    : price(price),
    amount(amount),
    timestamp(timestamp),
    product(product),
    orderType(orderType)
{

};

void OrderBookEntry::printPrice()
{
    std::cout << "The price is " << price << std::endl;
    return;
};

void OrderBookEntry::printEntry()
{
	std::cout << "Order Book Entry" << std::endl;
	std::cout << "Timestamp: " << timestamp << std::endl;
	std::cout << "Product: " << product << std::endl;
	std::cout << "Order Type: " << (orderType == OrderBookType::bid ? "bid" : "ask") << std::endl;
	std::cout << "Price: " << price << std::endl;
	std::cout << "Amount: " << amount << std::endl;
	return;
};

OrderBookType OrderBookEntry::stringToOrderBookType(const std::string& s)
{
    if (s == "ask")
    {
        return OrderBookType::ask;
    }
    if (s == "bid")
    {
        return OrderBookType::bid;
    }
    return OrderBookType::unknown;
};

