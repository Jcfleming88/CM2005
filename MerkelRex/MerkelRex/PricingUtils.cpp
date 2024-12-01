#include <iostream>
#include <string>
#include <vector>

#include "./OrderBookEntry.h"
#include "./PricingUtils.h"

double PricingUtils::computeAveragePrice(std::vector<OrderBookEntry>& entries)
{
    double total = 0;
    const int size = entries.size();

    if (size == 0) {
        return 0;
    }

    for (OrderBookEntry& entry : entries) {
        total += entry.price;
    }

    return total / size;
}

double PricingUtils::computeLowPrice(std::vector<OrderBookEntry>& entries)
{
    double min = 0;

    for (OrderBookEntry& entry : entries)
    {
        if (min == 0 || min > entry.price)
        {
            // Update the min price
            min = entry.price;
        }
        else {
            // Do nothing
        };
    }

    return min;
}

double PricingUtils::computeHighPrice(std::vector<OrderBookEntry>& entries)
{
    double max = 0;

    for (OrderBookEntry& entry : entries)
    {
        if (max == 0 || max < entry.price)
        {
            // Update the min price
            max = entry.price;
        }
        else
        {
            // Do nothing
        };
    }

    return max;
}

double PricingUtils::computePriceSpread(std::vector<OrderBookEntry>& entries)
{
    double max = computeHighPrice(entries);
    double min = computeLowPrice(entries);

    return max - min;
}