#ifndef CARD_H
#define CARD_H

#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>

class Card {
public:
    static const int NUM_CARDS = 52;
    static const int NUM_SUITS = 4;
    static const int NUM_RANKS = 13;

    std::vector<std::string> buildDeck();
    void printDeck(std::vector<std::string>& deck);
    int cardValue(std::string card);
};
#endif