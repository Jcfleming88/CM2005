#include <iostream>
#include <string>

#include "TextUtils.h"

#pragma once
enum class OrderBookType
{
    bid,
    ask,
    asksale,
    bidsale,
	unknown
};

#pragma once
class OrderBookEntry
{
public:
    OrderBookEntry();

    OrderBookEntry(
        std::string timestamp,
        std::string product,
        OrderBookType orderType,
        double price,
        double amount,
		std::string username = "dataset"
    );

    double price;
    double amount;
    std::string timestamp;

    /*
    For an ask, offering x amount to buy y price.
	For a bid, offering to buy x amount using y price.
    */
    std::string product;
    OrderBookType orderType;

	std::string username;

    void printPrice();
    void printEntry();

    static OrderBookType stringToOrderBookType(const std::string& s);
    
    static bool compareByTimestamp(const OrderBookEntry& e1, const OrderBookEntry& e2)
    {
        return e1.timestamp < e2.timestamp;
    };
    static bool compareByPriceAsc(OrderBookEntry& e1, OrderBookEntry& e2)
    {
        return e1.price < e2.price;
    };
    static bool compareByPriceDesc(OrderBookEntry& e1, OrderBookEntry& e2)
    {
        return e1.price > e2.price;
    };
};

