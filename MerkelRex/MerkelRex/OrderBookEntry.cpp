#include <iostream>
#include <string>
#include "OrderBookEntry.h"

OrderBookEntry::OrderBookEntry(
    double price,
    double amount,
    std::string timestamp,
    std::string product,
    OrderBookType orderType)
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