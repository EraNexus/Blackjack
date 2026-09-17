#ifndef BLACKJACK_H
#define BLACKJACK_H

#include "Card.h"
#include "Dealer.h"
#include "Player.h"

class Blackjack {
public:
    std::vector<std::string> playerHand;
    std::vector<std::string> dealerHand;
    std::vector<std::string> splitHand;
    std::vector<std::string> deck;

    bool firstHandBust;
    bool secondHandBust;

    Card c;
    Player p;
    Dealer d;

    std::string option;
    double wagerAmount = 0.00;
    double sideBet = 0.00;

    void startup();
    void debug();
    void startGame();
    void cardsShowing(std::vector<std::string>& hand, double wagerAmount, int state);
    void playerDecision(std::vector<std::string>& hand, double wagerAmount, int state);
    void dealerTurn(double wagerAmount);
    void offerInsurance(double wagerAmount);
    void push(double wagerAmount);
    void loss(double wagerAmount);
    void win(double wagerAmount);
    void blackjack(double wagerAmount);
    void playAgain();
};
#endif