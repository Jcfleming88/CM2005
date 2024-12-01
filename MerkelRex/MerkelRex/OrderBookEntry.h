#pragma once
enum class OrderBookType
{
    bid,
    ask
};

#pragma once
class OrderBookEntry
{
public:
    OrderBookEntry(double price,
        double amount,
        std::string timestamp,
        std::string product,
        OrderBookType orderType);

    double price;
    double amount;
    std::string timestamp;
    std::string product;
    OrderBookType orderType;

    void printPrice();
};

