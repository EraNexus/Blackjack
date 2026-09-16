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
    // Player is dealt no cards
    return hand;
}

vector<string> Player::split(vector<string>& hand, vector<string>& deck) {
    // Hand is split in two
    vector<string> splitHand;

    splitHand.push_back(hand[1]);
    hand.erase(hand.begin() + 1);

    splitHand.push_back(deck.back());
    deck.pop_back();

    hand.push_back(deck.back());
    deck.pop_back();

    return splitHand;
}

vector<string> Player::doubleDown(vector<string>& hand, vector<string>& deck) {
    // Player is dealt ONLY one card
    int x = rand() % deck.size();
    hand.push_back(deck[x]);
    deck.erase(deck.begin() + x);

    return hand;
}

bool Player::isOver21(vector<string>& hand) {
    return (cardValueTotal(hand) > 21);
}