#include "Card.h"

#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>

using namespace std;

vector<string> Card::buildDeck() {
    vector<string> deck;
    unordered_map<int, string> valueToRank;
    unordered_map<int, string> valueToSuit;

    valueToRank[1] = "Ace";
    valueToRank[2] = "Two";
    valueToRank[3] = "Three";
    valueToRank[4] = "Four";
    valueToRank[5] = "Five";
    valueToRank[6] = "Six";
    valueToRank[7] = "Seven";
    valueToRank[8] = "Eight";
    valueToRank[9] = "Nine";
    valueToRank[10] = "Ten";
    valueToRank[11] = "Jack";
    valueToRank[12] = "Queen";
    valueToRank[13] = "King";

    valueToSuit[1] = " of Spades";
    valueToSuit[2] = " of Hearts";
    valueToSuit[3] = " of Diamonds";
    valueToSuit[4] = " of Clubs";

    for (int s = 1; s <= NUM_SUITS; s++) {
        for (int r = 1; r <= NUM_RANKS; r++) {
            deck.push_back(valueToRank[r] + valueToSuit[s]);
        }
    }

    return deck;
}

void Card::printDeck(vector<string>& deck) {
    for (int i = 0; i < deck.size(); i++) {
        cout << deck[i] << "\n";
    }
}

int Card::cardValue(string card) {
    string sub = card.substr(0, 3);

    if (sub == "Ace") return 1;
    if (sub == "Two") return 2;
    if (sub == "Thr") return 3;
    if (sub == "Fou") return 4;
    if (sub == "Fiv") return 5;
    if (sub == "Six") return 6;
    if (sub == "Sev") return 7;
    if (sub == "Eig") return 8;
    if (sub == "Nin") return 9;

    return 10;
}