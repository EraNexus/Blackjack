#include "Blackjack.h"
#include "Card.h"
#include "Player.h"
#include "Dealer.h"

#include <string>
#include <vector>
#include <unordered_map>
#include <cstdlib>
#include <iostream>

using namespace std;

void Blackjack::startup() {
    cout << " ========== WELCOME TO BLACKJACK! ==========" << endl;
    cout << endl;
    cout << "  PLEASE SELECT FROM THE AVAILABLE OPTIONS: " << endl;
    cout << endl;
    cout << "  PLAY             DEBUG               QUIT" << endl; 
    cout << endl;
    cout << " ===========================================" << endl;
    
    cin >> option;

    bool validOption = false;

    do {
        if (option == "PLAY" || option == "Play" || option == "play") {
            validOption = true;

            do {
                startGame();
            }
            while (playAgain());
        }
        else if (option == "DEBUG" || option == "Debug" || option == "debug") {
            validOption = true;
            debug();
        }
        else if (option == "QUIT" || option == "Quit" || option == "quit") {
            validOption = true;
            return;
        }
        else {
            cout << "Invalid option. Please select from the options above" << endl;
            cin >> option;
        }
    }
    while (!validOption);
}

void Blackjack::debug() {
    string debugOption;

    cout << " ============ DEBUG MODE ============" << endl;
    cout << endl;
    cout << "  SELECT A SCENARIO TO TEST:" << endl;
    cout << endl;
    cout << "  BLACKJACK" << endl;
    cout << "  SPLIT" << endl;
    cout << "  INSURANCE" << endl;
    cout << "  DOUBLE" << endl;
    cout << "  BUST" << endl;
    cout << "  BACK" << endl;
    cout << endl;
    cout << " ====================================" << endl;

    cin >> debugOption;

    playerHand.clear();
    dealerHand.clear();
    splitHand.clear();
    deck = c.buildDeck();

    if (debugOption == "BLACKJACK" || debugOption == "blackjack") {
        playerHand.push_back("Ace of Spades");
        playerHand.push_back("King of Hearts");

        dealerHand.push_back("Seven of Clubs");
        dealerHand.push_back("Nine of Diamonds");

        cardsShowing(playerHand, 10, 0);
    }
    else if (debugOption == "SPLIT" || debugOption == "split") {
        playerHand.push_back("Eight of Spades");
        playerHand.push_back("Eight of Hearts");

        dealerHand.push_back("Seven of Clubs");
        dealerHand.push_back("Nine of Diamonds");

        cardsShowing(playerHand, 10, 0);
    }
    else if (debugOption == "INSURANCE" || debugOption == "insurance") {
        playerHand.push_back("Ten of Spades");
        playerHand.push_back("Seven of Hearts");

        dealerHand.push_back("King of Clubs");
        dealerHand.push_back("Ace of Diamonds");

        cardsShowing(playerHand, 10, 0);
    }
    else if (debugOption == "DOUBLE" || debugOption == "double") {
        playerHand.push_back("Five of Spades");
        playerHand.push_back("Six of Hearts");

        dealerHand.push_back("Seven of Clubs");
        dealerHand.push_back("Nine of Diamonds");

        cardsShowing(playerHand, 10, 0);
    }
    else if (debugOption == "BUST" || debugOption == "bust") {
        playerHand.push_back("King of Spades");
        playerHand.push_back("Six of Hearts");

        dealerHand.push_back("Seven of Clubs");
        dealerHand.push_back("Nine of Diamonds");

        cardsShowing(playerHand, 10, 0);
    }
    else if (debugOption == "BACK" || debugOption == "back") {
        startup();
    }
    else {
        cout << "Invalid debug option" << endl;
        debug();
    }
}

void Blackjack::startGame() {
    playerHand.clear();
    dealerHand.clear();
    splitHand.clear();

    firstHandBust = false;
    secondHandBust = false;

    deck = c.buildDeck();

    cout << "Welcome to Blackjack!" << endl;
    cout << "The minimum wager is $5.00" << endl;
    cout << "How much would you like to wager?" << endl;
    cin >> wagerAmount;

    while (wagerAmount < 5.00 || wagerAmount > p.purse) {
        cout << "Please enter a valid amount" << endl;
        cin >> wagerAmount;
    }

    p.purse -= wagerAmount;

    cout << "Starting game... " << endl;
    p.initialDeal(playerHand, deck);
    d.initialDeal(dealerHand, deck);

    if (c.cardValueTotal(playerHand) == 21 
            && c.cardValue(dealerHand[1]) != 1) {
        blackjack(wagerAmount);
        return;
    }

    cardsShowing(playerHand, wagerAmount, 0);
}

void Blackjack::cardsShowing(vector<string>& hand, double wagerAmount, int state) {
    // State 0 is the initial state, where insurance is offered
    // State 1 is the default state
    // State 2 is the first split hand
    // State 3 is the second split hand

    cout << "Dealer is showing: " << dealerHand[1] << " and one more card" << endl;
    cout << "Dealer card value total: " << c.cardValue(dealerHand[1]) << endl;

    if (c.cardValue(dealerHand[1]) == 1 && state == 0) {
        offerInsurance(wagerAmount);
        return;
    }

    cout << "You are showing: " << endl;
    for (size_t i = 0; i < hand.size(); i++) {
        cout << hand[i] << endl;
    }

    cout << "Options available: " << endl;
    cout << "Hit" << endl;
    cout << "Stand" << endl;

    if ((c.cardValue(hand[0]) == c.cardValue(hand[1])) 
        && state == 0
        && p.purse >= wagerAmount)
        cout << "Split" << endl;
    if (p.purse >= wagerAmount && state == 0)
        cout << "Double" << endl;

    cout << "Purse: $" << p.purse << endl;

    playerDecision(hand, wagerAmount, state);
}

void Blackjack::playerDecision(vector<string>& hand, double wagerAmount, int state) {
    string decision;

    cout << "What is your decision?" << endl;
    cin >> decision;

    if ((decision == "Hit") || (decision == "hit")) {
        p.hit(hand, deck);
        
        if (p.isOver21(hand)) {
            if (state == 2) {
                firstHandBust = true;
                cout << "First hand busted!" << endl;
                cardsShowing(splitHand, wagerAmount, 3);
            }
            else if (state == 3) {
                secondHandBust = true;
                cout << "Second hand busted!" << endl;
                
                if (firstHandBust) {
                    cout << "Both hands lost" << endl;
                    cout << "Purse: $" << p.purse << endl;
                }
                else {
                    dealerTurn(wagerAmount);
                }
            }
            else {
                loss(wagerAmount);
            }
        }
        else {
            if (state == 0)
                cardsShowing(hand, wagerAmount, 1);
            else
                cardsShowing(hand, wagerAmount, state);
        }
    }
    else if ((decision == "Stand") || (decision == "stand")) {
        if (state == 2)
            cardsShowing(splitHand, wagerAmount, 3);
        else
            dealerTurn(wagerAmount);
    }
    else if (((decision == "Split") || (decision == "split"))
            && state == 0
            && p.purse >= wagerAmount
            && c.cardValue(hand[0]) == c.cardValue(hand[1])) {
        p.purse -= wagerAmount;
        splitHand = p.split(hand, deck);

        cardsShowing(playerHand, wagerAmount, 2);
    }
    else if (((decision == "Double") || (decision == "double"))
                && state == 0
                && p.purse >= wagerAmount) {
            p.purse -= wagerAmount;
            p.doubleDown(hand, deck);

            if (p.isOver21(hand))
                loss(wagerAmount * 2);
            else
                dealerTurn(wagerAmount * 2);
    }
    else {
        cout << "Invalid decision, please select from the available options" << endl;
        playerDecision(hand, wagerAmount, state);
    }
}

void Blackjack::dealerTurn(double wagerAmount) {
    cout << "Dealer reveals: " << dealerHand[0] << endl;

    while (d.isUnder17(dealerHand)) {
        d.hit(dealerHand, deck);
        cout << "Dealer hits: " << dealerHand.back() << endl;
    }

    if (splitHand.empty()) {
        if (d.isOver21(dealerHand))
            win(wagerAmount);
        else if (c.cardValueTotal(playerHand) > c.cardValueTotal(dealerHand))
            win(wagerAmount);
        else if (c.cardValueTotal(playerHand) < c.cardValueTotal(dealerHand))
            loss(wagerAmount);
        else
            push(wagerAmount);

        return;
    }

    if (firstHandBust) {
        cout << "First hand busted" << endl;
    }
    else if (d.isOver21(dealerHand) ||
            c.cardValueTotal(playerHand) > c.cardValueTotal(dealerHand)) {
        cout << "First hand wins" << endl;
        p.purse += 2 * wagerAmount;
    }
    else if (c.cardValueTotal(playerHand) < c.cardValueTotal(dealerHand)) {
        cout << "First hand loses" << endl;
    }
    else {
        cout << "First hand pushes" << endl;
        p.purse += wagerAmount;
    }

    if (secondHandBust) {
        cout << "Second hand busted" << endl;
    }
    else if (d.isOver21(dealerHand) ||
            c.cardValueTotal(splitHand) > c.cardValueTotal(dealerHand)) {
        cout << "Second hand wins" << endl;
        p.purse += 2 * wagerAmount;
    }
    else if (c.cardValueTotal(splitHand) < c.cardValueTotal(dealerHand)) {
        cout << "Second hand loses" << endl;
    }
    else {
        cout << "Second hand pushes" << endl;
        p.purse += wagerAmount;
    }

    cout << "Purse: $" << p.purse << endl;
}

void Blackjack::offerInsurance(double wagerAmount) {
    string answer;
    bool tookInsurance = false;

    cout << "The dealer is showing an Ace, would you like to take insurance? [Y/N]" << endl;
    cin >> answer;

    while (answer != "Yes" && answer != "yes" &&
            answer != "Y" && answer != "y" &&
            answer != "No" && answer != "no" &&
            answer != "N" && answer != "n") {
    cout << "Invalid decision, please select from the available options" << endl;
    cin >> answer;
    }

    if (answer == "Yes" || answer == "yes" || answer == "Y" || answer == "y") {
        tookInsurance = true;

        cout << "How much would you like to wager? (up to half the original wager)" << endl;
        cin >> sideBet;

        while (sideBet <= 0 || sideBet > p.purse || sideBet > 0.5 * wagerAmount) {
            cout << "Please enter a valid amount" << endl;
            cin >> sideBet;
        }

        p.purse -= sideBet;
    }

    if (c.cardValue(dealerHand[0]) == 10) {
        cout << "The dealer reveals: " << dealerHand[0] << endl;
        cout << "Therefore, the dealer has Blackjack" << endl;

        if (tookInsurance) {
            cout << "Insurance pays 2:1, you win $" << sideBet * 2 << endl;
            p.purse += 3 * sideBet;
        }

        if (c.cardValueTotal(playerHand) == 21)
            push(wagerAmount);
        else
            loss(wagerAmount);
    }
    else if (c.cardValueTotal(playerHand) == 21) {
        blackjack(wagerAmount);
    }
    else {
        cardsShowing(playerHand, wagerAmount, 1);
    }
}

void Blackjack::push(double wagerAmount) {
    p.purse += wagerAmount;

    cout << "This game resulted in a push, so all wagers are returned" << endl;
    cout << "Purse: $" << p.purse << endl;
}

void Blackjack::loss(double wagerAmount) {
    cout << "This game resulted in a loss, so you lost your wager" << endl;
    cout << "Purse: $" << p.purse << endl;
}

void Blackjack::win(double wagerAmount) {
    p.purse += 2 * wagerAmount;

    cout << "This game resulted in a win, which pays 1:1" << endl;
    cout << "Purse: $" << p.purse << endl;
}

void Blackjack::blackjack(double wagerAmount) {
    p.purse += 2.5 * wagerAmount;
    
    cout << "This game resulted in a blackjack, which pays 3:2" << endl;
    cout << "Purse: $" << p.purse << endl;
}

bool Blackjack::playAgain() {
    string answer;

    if (p.purse < 5.00) {
        cout << "You fell below the minimum wager, so you have lost" << endl;
        cout << "Thanks for playing!" << endl;

        return false;
    }
    cout << "Would you like to play again? [Y/N]" << endl;
    cin >> answer;

    while (answer != "Yes" && answer != "yes" &&
            answer != "Y" && answer != "y" &&
            answer != "No" && answer != "no" &&
            answer != "N" && answer != "n") {
        cout << "Please select a valid option [Y/N]" << endl;
        cin >> answer;
    }

    if (answer == "Yes" || answer == "yes" || 
        answer == "Y" || answer == "y")
        return true;
    
    cout << "Thanks for playing!" << endl;
    return false;
}