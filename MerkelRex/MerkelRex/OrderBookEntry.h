#include <iostream>
#include <string>

#include "TextUtils.h"

#pragma once
enum class OrderBookType
{
    bid,
    ask,
    sale,
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
        double amount
    );

    double price;
    double amount;
    std::string timestamp;

    /** In the format offering/requesting */
    std::string product;
    OrderBookType orderType;

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

