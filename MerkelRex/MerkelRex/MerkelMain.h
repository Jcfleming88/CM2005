#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "OrderBook.h"
#include "OrderBookEntry.h"
#include "PricingUtils.h"
#include "TextUtils.h"
#include "CSVParser.h"
#include "Wallet.h"

#pragma once
class MerkelMain
{
public:
    MerkelMain() = default;
    /** Call this to start the sim */
    void init();

private:
    void printMenu();
    int getUserInput();
    void printHelp();
    void printMarketStats();
    void enterAsk();
    void enterBid();
    void printWallet();
    void gotoNextTimeframe();
    void printExitMessage();
    void printInvalidInput();
    bool processUserOption(int userOption);

    std::string currentTime;

    Wallet wallet{};
    OrderBook orderBook{ "C:\\Users\\jcfle\\OneDrive\\Documents\\University of London\\CM2005 - Object Orientated Programming\\Repo\\MerkelRex\\MerkelRex\\1XejnIsmSmK3o5yLJkpiUg_2402656ae54246e880715f135341f5f7_20200317.csv" };
};

