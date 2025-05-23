#include "MerkelMain.h"

void MerkelMain::init()
{
	//std::cout << "Testing wallet. Start by showing empty wallet." << std::endl;
 //   std::cout << wallet.toString() << std::endl;
	//TextUtils::printBreak();
 //   std::cout << "Inserting 10 BTC" << std::endl;
 //   wallet.insertCurrency("BTC", 10);
 //   std::cout << "Wallet contents " << wallet.toString() << std::endl;
 //   TextUtils::printBreak();
	//std::cout << "Remove 5 BTC" << std::endl;
	//wallet.removeCurrency("BTC", 5);
	//std::cout << "Wallet contents " << wallet.toString() << std::endl;
	//TextUtils::printBreak();
	//std::cout << "Check what is in the wallet" << std::endl;
 //   std::cout << "Check for 5 BTH: " << wallet.containsCurrency("BTC", 5) << std::endl;
 //   std::cout << "Check for 10 BTH: " << wallet.containsCurrency("BTC", 10) << std::endl;


	bool runScript = true;
	currentTime = orderBook.getEarliestTime();

	wallet.insertCurrency("BTC", 10);
	wallet.insertCurrency("ETH", 5);

    while (runScript)
    {
        printMenu();
        int userOption = getUserInput();
		TextUtils::clearConsole();
        runScript = processUserOption(userOption);
    }
    return;
}

void MerkelMain::printMenu()
{
    // 1 Prin help
    std::cout << "1: Print help" << std::endl;

    // 2 Print exchange stats
    std::cout << "2: Print exchange stats" << std::endl;

    // 3 Make an offer
    std::cout << "3: Make an offer" << std::endl;

    // 4 Make a bid
    std::cout << "4: Make a bid" << std::endl;

    // 5 Print wallet
    std::cout << "5: Print wallet" << std::endl;

    // 6 Continue
    std::cout << "6: Continue" << std::endl;

    // Exit
    std::cout << "9. Exit" << std::endl;

    // Current time
    TextUtils::printBreak();
	std::cout << "Current time: " << currentTime << std::endl;
}

int MerkelMain::getUserInput()
{
    TextUtils::printBreak();
    std::cout << "Type in 1-6 or 9 to exit" << std::endl;

    int userOption;
    
    std::string input;
    std::getline(std::cin, input);

	try {
		userOption = std::stoi(input);
	}
	catch (const std::exception& e) {
		std::cout << "Invalid input" << std::endl;
        userOption = getUserInput();
	}

    return userOption;
}

void MerkelMain::printHelp()
{
    std::cout << "Help - your aim is to make money. Analyse the market and make bids and offers." << std::endl;
}

void MerkelMain::printMarketStats()
{
    std::cout << "orderbook contains: " << orderBook.getSize() << " entries" << std::endl;
    std::cout << std::endl;

    // get number of asks and bids
    std::vector<OrderBookEntry> bids = orderBook.getOrders(OrderBookType::bid);
    std::vector<OrderBookEntry> asks = orderBook.getOrders(OrderBookType::ask);

    unsigned int bidNum = OrderBook::getSize(bids);
	unsigned int askNum = OrderBook::getSize(asks);

    std::cout << "bids: " << bidNum << std::endl;
    std::cout << "asks: " << askNum << std::endl;
}

void MerkelMain::enterAsk()
{
    std::cout << "Make an offer - enter the amount" << std::endl;
	std::cout << "Please enter the product in the format product, price, amount e.g. ETH/BTC, 200, 0.5" << std::endl;

    std::string input;
	std::getline(std::cin, input);

    TextUtils::printBreak();

	std::vector<std::string> tokens = CSVParser::Tokenise(input, ',');
    if (tokens.size() != 3) {
		std::cout << "Invalid input: " << input << std::endl;
    }
    else {
        try {
            OrderBookEntry newOrder = CSVParser::StringsToOBE(
                currentTime,
                tokens[0],
                OrderBookType::ask,
                tokens[1],
                tokens[2]
            );
			newOrder.username = "simuser";

			if (wallet.canFulfillOrder(newOrder))
			{
				orderBook.insertOrder(newOrder);
                std::cout << "Ask placed: " << input << std::endl;
            }
			else
			{
				std::cout << "Wallet has insufficient funds." << std::endl;
                return;
			}
        }
		catch (const std::exception& e) {
			std::cout << "Invalid input: " << std::endl;
			std::cout << e.what() << std::endl;
            std::cout << "" << std::endl;
			std::cout << "All inputs should be in the format product, price, amount e.g. ETH/BTC, 200, 0.5" << std::endl;
			std::cout << "Please choose an option to try again" << std::endl;

            return;
		}
    }
}

void MerkelMain::enterBid()
{
    std::cout << "Make a bid - enter the amount" << std::endl;
    std::cout << "Please enter the product in the format product, price, amount e.g. ETH/BTC, 200, 0.5" << std::endl;

    std::string input;
    std::getline(std::cin, input);

    TextUtils::printBreak();

    std::vector<std::string> tokens = CSVParser::Tokenise(input, ',');
    if (tokens.size() != 3) {
        std::cout << "Invalid input: " << input << std::endl;
    }
    else {
        try {
            OrderBookEntry newOrder = CSVParser::StringsToOBE(
                currentTime,
                tokens[0],
                OrderBookType::bid,
                tokens[1],
                tokens[2]
            );
            newOrder.username = "simuser";

			if (!wallet.canFulfillOrder(newOrder))
			{
				std::cout << "Wallet has insufficient funds." << std::endl;
				return;
			}
            else {
                orderBook.insertOrder(newOrder);
                std::cout << "Bid placed: " << input << std::endl;
            }
        }
        catch (const std::exception& e) {
            std::cout << "Invalid input: " << std::endl;
            std::cout << e.what() << std::endl;
            std::cout << "" << std::endl;
            std::cout << "All inputs should be in the format product, price, amount e.g. ETH/BTC, 200, 0.5" << std::endl;
            std::cout << "Please choose an option to try again" << std::endl;

            return;
        }
    }
}

void MerkelMain::printWallet()
{
    std::cout << "Your Wallet\n" << std::endl;
    std::cout << wallet << std::endl;
}

void MerkelMain::gotoNextTimeframe()
{
    std::cout << "Going to next time frame. " << std::endl;
    for (std::string& p : orderBook.getKnownProducts())
    {
        std::cout << "Matching " << p << std::endl;
        std::vector<OrderBookEntry> sales = orderBook.matchAsksToBids(p, currentTime);
        std::cout << "Sales: " << sales.size() << std::endl;
        for (OrderBookEntry& sale : sales)
        {
			std::cout << "Sale price: " << sale.price << " amount " << sale.amount << std::endl;
            if (sale.username == "simuser") {
                // Update wallet
                wallet.processSale(sale);
            }
        }
    }
    currentTime = orderBook.getNextTime(currentTime);
}


void MerkelMain::printExitMessage()
{
    std::cout << "Exiting" << std::endl;
    TextUtils::printBreak();
}

void MerkelMain::printInvalidInput()
{
    std::cout << "Invalid choice. Choose 1-6 or 9 to exit." << std::endl;
}

bool MerkelMain::processUserOption(int userOption)
{
    TextUtils::printBreak();
    std::cout << "You chose: " << userOption << std::endl;
    TextUtils::printBreak();

    switch (userOption)
    {
    case 1:
        printHelp();
        break;
    case 2:
        printMarketStats();
        break;
    case 3:
        enterAsk();
        break;
    case 4:
        enterBid();
        break;
    case 5:
        printWallet();
        break;
    case 6:
        gotoNextTimeframe();
        break;
    case 9:
        printExitMessage();
        return false;
    default:
        printInvalidInput();
        break;
    };

    TextUtils::printBreak();
    return true;
}