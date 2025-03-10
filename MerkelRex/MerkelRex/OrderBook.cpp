#include "OrderBook.h"

#include <algorithm>
#include <map>

OrderBook::OrderBook(std::string filename) {
	orders = CSVParser::ReadFile(filename);

	if (orders.size() == 0)
	{
		std::cout << "Failed to load orderbook." << std::endl;
	}
	else
	{
		std::cout << "Orderbook loaded successfully." << std::endl;
	}
}

unsigned int OrderBook::getSize() {
    return orders.size();
}

unsigned int OrderBook::getSize(std::vector<OrderBookEntry>& orders) {
	return orders.size();
}

std::vector<std::string> OrderBook::getKnownProducts() {
	std::vector<std::string> products;
	std::map<std::string, bool> productMap;

	for (const OrderBookEntry& order : orders)
	{
		productMap[order.product] = true;
	}

	for (const auto& e : productMap)
	{
		products.push_back(e.first);
	}

	return products;
}

std::vector<OrderBookEntry> OrderBook::getOrders(OrderBookType type,
	std::string product,
	std::string timestamp) {
	std::vector<OrderBookEntry> output;
	
    for (const OrderBookEntry& order : orders)
	{
		if (order.orderType == type &&
			(product == "" || order.product == product) &&
			(timestamp == "" || order.timestamp == timestamp))
		{
            output.push_back(order);
		}
	}

	return output;
}

double OrderBook::getAveragePrice(std::vector<OrderBookEntry>& orders)
{
    double total = 0;
    const int size = orders.size();

    if (size == 0) {
        return 0;
    }

    for (OrderBookEntry& entry : orders) {
        total += entry.price;
    }

    return total / size;
}

double OrderBook::getLowPrice(std::vector<OrderBookEntry>& orders)
{
    double min = 0;

    for (OrderBookEntry& entry : orders)
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

double OrderBook::getHighPrice(std::vector<OrderBookEntry>& orders)
{
    double max = 0;

    for (OrderBookEntry& entry : orders)
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

double OrderBook::getPriceSpread(std::vector<OrderBookEntry>& orders)
{
    double max = getHighPrice(orders);
    double min = getLowPrice(orders);

    return max - min;
}

std::string OrderBook::getEarliestTime() {
	std::string earliestTime = orders[0].timestamp;

	for (OrderBookEntry& order : orders) {
		if (order.timestamp < earliestTime) {
			earliestTime = order.timestamp;
		}
	}

	return earliestTime;
}

std::string OrderBook::getNextTime(std::string timestamp) {
	std::string nextTime = "";
    
    for (OrderBookEntry& order : orders) {
        if (order.timestamp > timestamp) {
            nextTime = order.timestamp;
            break;
		}
	}

	if (nextTime == "") {
		nextTime = getEarliestTime();
	}

	return nextTime;
}

void OrderBook::insertOrder(OrderBookEntry& order)
{
	orders.push_back(order);
	std::sort(orders.begin(), orders.end(), OrderBookEntry::compareByTimestamp);
}

std::vector<OrderBookEntry> OrderBook::matchAsksToBids(std::string product, std::string timestamp) 
{
	std::vector<OrderBookEntry> asks = getOrders(OrderBookType::ask, product, timestamp);
	std::vector<OrderBookEntry> bids = getOrders(OrderBookType::bid, product, timestamp);

	std::vector<OrderBookEntry> sales;

	std::sort(asks.begin(), asks.end(), OrderBookEntry::compareByPriceAsc);
	std::sort(bids.begin(), bids.end(), OrderBookEntry::compareByPriceDesc);

	for (OrderBookEntry& ask : asks)
	{
		// Check if it's an empty amount and skip if so
		if (ask.amount == 0) {
			continue;
		}

		for (OrderBookEntry& bid : bids)
		{
			// Check if the bid price is greater than or equal to the ask price and there's an amount
			if (bid.price >= ask.price && bid.amount != 0)
			{
				// Create a sale
				OrderBookEntry sale{
					timestamp,
					product,
					OrderBookType::asksale,
					ask.price,
					0
				};

				OrderBookType type = OrderBookType::asksale;
				if (bid.username == "simuser") {
					sale.orderType = OrderBookType::bidsale;
					sale.username = "simuser";
				}
				if (ask.username == "simuser") {
					sale.orderType = OrderBookType::asksale;
					sale.username = "simuser";
				}

				if (bid.amount == ask.amount) {
					// Set the amount sold
					sale.amount = ask.amount;
					sales.push_back(sale);

					// make sure the bid is not processed again
					bid.amount = 0;

					// can do no more with this ask, go onto the next ask
					break;
				}
				else if (bid.amount > ask.amount) {
					// Ask is gone but the bid is sliced
					sale.amount = ask.amount;
					sales.push_back(sale);

					// Adjust the bid in place so it can be used to process the next ask
					bid.amount -= ask.amount;

					// Ask is gone so go onto the next ask
					break;
				}
				else if (bid.amount < ask.amount) {
					// Bid is gone but the ask is sliced
					sale.amount = bid.amount;
					sales.push_back(sale);

					// Update the ask so it can be used to process the next bid
					ask.amount -= bid.amount;
					bid.amount = 0;
				}
			}
			else {
				// Break the loop if there was no higher bid found as there will now only be
				// lower priced bids so there will be no matching
				break;
			}
		}
	}

	return sales;
}