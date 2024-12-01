#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "OrderBookEntry.h"
#include "PricingUtils.h"
#include "MerkelMain.h"

void MerkelMain::init()
{
    bool runScript = true;
    while (runScript)
    {
        printMenu();
        int userOption = getUserInput();
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
}

int MerkelMain::getUserInput()
{
    std::cout << "=======================" << std::endl;
    std::cout << "Type in 1-6 or 9 to exit" << std::endl;

    int userOption;
    std::cin >> userOption;
    return userOption;
}

void MerkelMain::printHelp()
{
    std::cout << "Help - your aim is to make money. Analyse the market and make bids and offers." << std::endl;
}

void MerkelMain::printMarketStats()
{
    std::cout << "Market looks good" << std::endl;
}

void MerkelMain::enterAsk()
{
    std::cout << "Make an offer - enter the amount" << std::endl;
}
void MerkelMain::enterBid()
{
    std::cout << "Make a bid - enter the amount" << std::endl;
}

void MerkelMain::printWallet()
{
    std::cout << "Your wallet is empty" << std::endl;
}

void MerkelMain::gotoNextTimeframe()
{
    std::cout << "Going to next time frame" << std::endl;
}

void MerkelMain::printExitMessage()
{
    std::cout << "Exiting" << std::endl;
    std::cout << "=======================" << std::endl;
}

void MerkelMain::printInvalidInput()
{
    std::cout << "Invalid choice. Choose 1-6 or 9 to exit." << std::endl;
}

void MerkelMain::printBreak()
{
    std::cout << "=======================" << std::endl;
}

bool MerkelMain::processUserOption(int userOption)
{
    printBreak();
    std::cout << "You chose: " << userOption << std::endl;
    printBreak();

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

    printBreak();
    return true;
}