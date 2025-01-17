#pragma once
#include "OrderBookEntry.h"
#include "CSVParser.h"

#include <string>
#include <vector>

class OrderBook
{

public:
	/** Construct, reading a csv data file */
	OrderBook(std::string filename);

	/** Return vector of all know products in the dataset*/
	std::vector<std::string> getKnownProducts();

	/* Return vector of Orders according to the sent filters. 
	   If the product or timestamp are left empty then this 
	   filter is ignored and all orders are returned that match 
	   the type.
	*/
	std::vector<OrderBookEntry> getOrders(OrderBookType type,
		std::string product = "",
		std::string timestamp = "");

	/** Return the earliest time in the list of orders */
	std::string getEarliestTime();

	/** Return the next time in the list of orders. If there is no next timestamp then the timestamp is reset to the start. */
	std::string getNextTime(std::string timeStamp);

	/** Return the number of entries in the list of orders */
	unsigned int getSize();

	/** Return the number of entries in the list of orders */
	static unsigned int getSize(std::vector<OrderBookEntry>& orders);

	/** Will return the average price of a group of orders. If there is no entries then it will return zero. */
	static double getAveragePrice(std::vector<OrderBookEntry>& orders);

	/** Will return the lowest price of a set orders. If there is no product then it will return zero (nothing good is ever free!) */
	static double getLowPrice(std::vector<OrderBookEntry>& orders);

	/** Will return the highest price for a group of orders. If there is not product then it will return zero. */
	static double getHighPrice(std::vector<OrderBookEntry>& orders);

	/** Will return the difference between the highest and the lowest prices. If there are no entries then it will return zero. */
	static double getPriceSpread(std::vector<OrderBookEntry>& orders);

	/** Insert an order into the order book */
	void insertOrder(OrderBookEntry& order);

	/** Match asks to bids */
	std::vector<OrderBookEntry> matchAsksToBids(std::string product, std::string timestamp);

private:
	std::vector<OrderBookEntry> orders;

};