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
    void printBreak();
    bool processUserOption(int userOption);
};

