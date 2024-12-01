#pragma once
class PricingUtils
{
public:
    /** Will return the average price of a group of entries. If there is no entries then it will return zero. */
    double computeAveragePrice(std::vector<OrderBookEntry>& entries);

    /** Will return the lowest price of a set entries. If there is no product then it will return zero (nothing good is ever free!) */
    double computeLowPrice(std::vector<OrderBookEntry>& entries);

    /** Will return the highest price for a group of entries. If there is not product then it will return zero. */
    double computeHighPrice(std::vector<OrderBookEntry>& entries);

    /** Will return the difference between the highest and the lowest prices. If there are no entries then it will return zero. */
    double computePriceSpread(std::vector<OrderBookEntry>& entries);
};