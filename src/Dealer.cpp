#include "Dealer.h"
#include "Card.h"

#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <cstdlib>

vector<string> Dealer::initialDeal(vector<string>& hand, vector<string>& deck) {
    // Dealer is dealt two cards
    for (int i = 0; i < 2; i++) {
        int x = rand() % deck.size();
        hand.push_back(deck[x]);
        deck.erase(deck.begin() + x);
        hand.cardValueTotal += hand[0];
    }

    return hand;
}

vector<string> Dealer::hit(vector<string>& hand, vector<string>& deck) {
    // Player is dealt one card
    int x = rand() % deck.size();
    hand.push_back(deck[x]);
    deck.erase(deck.begin() + x);
    hand.cardValueTotal += hand[0];

    return hand;
}

vector<string> Dealer::stand(vector<string>& hand, vector<string>& deck) {
    // Player is dealt no cards
    return hand;
}

bool Dealer::isUnder17(vector<string>& hand) {
    return (hand.cardValueTotal < 17);
}

bool Dealer::isOver21(vector<string>& hand) {
    return (hand.cardValueTotal > 21);
}