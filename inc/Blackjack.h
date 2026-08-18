#ifndef BLACKJACK_H
#define BLACKJACK_H

#include "Card.h"
#include "Dealer.h"
#include "Player.h"

class Blackjack {
    public:
        vector<string> playerHand;
        vector<string> dealerHand;
        Card c;
        Player p;
        Dealer d;
        double wagerAmount = 0.00;
        double sideBet = 0.00;

        int Blackjack::startGame();
        std::string Blackjack::cardsShowing(double wagerAmount);
        void Blackjack::playerDecision(std::string decision)
};
#endif