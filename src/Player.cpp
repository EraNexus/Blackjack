#include "Player.h"
#include "Card.h"

#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <cstdlib>

using namespace std;

vector<string> Player::initialDeal(vector<string>& hand, vector<string>& deck) {
    // Player is dealt two cards
    for (int i = 0; i < 2; i++) {
        int x = rand() % deck.size();
        hand.push_back(deck[x]);
        deck.erase(deck.begin() + x);
    }

    return hand;
}

vector<string> Player::hit(vector<string>& hand, vector<string>& deck) {
    // Player is dealt one card
    int x = rand() % deck.size();
    hand.push_back(deck[x]);
    deck.erase(deck.begin() + x);

    return hand;
}

vector<string> Player::stand(vector<string>& hand, vector<string>& deck) {
    return hand;
}