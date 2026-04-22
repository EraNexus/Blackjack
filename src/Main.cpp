#include "Blackjack.h"
#include "Card.h"
#include "Player.h"

#include <iostream>

using namespace std;

int main() {
    Card c;
    Player p;

    vector<string> deck = c.buildDeck();
    vector<string> hand;
    hand = p.initialDeal(hand, deck);
    //c.printDeck(deck);

    cout << "Current Hand:" << endl;

    c.printDeck(hand);

    return 0;
}