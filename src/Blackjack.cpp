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

void Blackjack::startGame() {
    playerHand.clear();
    dealerHand.clear();

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
    cardsShowing(wagerAmount, 0);
}

void Blackjack::cardsShowing(double wagerAmount, int state) {
    // State 0 is the initial state, where insurance is offered
    // State 1 is the default state
    // State 2 is
    // State 3 is

    cout << "Dealer is showing: " << dealerHand[1] << " and one more card";
    cout << "Dealer card value total: " << c.cardValue(dealerHand[1]);

    if (c.cardValue(dealerHand[1]) == 1 && state == 0)
        offerInsurance(wagerAmount);

    cout << "You are showing: " << endl;
    for (int i = 0; i < playerHand.size(); i++) {
        cout << playerHand[i];
    }

    cout << "Options available: " << endl;
    cout << "Hit" << endl;
    cout << "Stand" << endl;

    if ((c.cardValue(playerHand[0]) == c.cardValue(playerHand[1])) 
        && ((state == 0) || (state == 1) || (state == 2)))
        cout << "Split" << endl;
    if ((p.purse >= wagerAmount)
        && ((state == 0) || (state == 1) || (state == 3)))
        cout << "Double Down \n" << endl;

    cout << "Purse: $" << p.purse;

    playerDecision(wagerAmount, state);
}

void Blackjack::playerDecision(double wagerAmount, int state) {
    string decision;

    cout << "What is your decision?" << endl;
    cin >> decision;

    if ((decision == "Hit") || (decision == "hit")) {
        p.hit(playerHand, deck);
        
        if (p.isOver21(playerHand))
            loss(wagerAmount);
        else 
            cardsShowing(wagerAmount, 1);
    }
    else if ((decision == "Stand") || (decision == "stand"))
        dealerTurn(wagerAmount);
    else if else if (((decision == "Split") || (decision == "split"))
        && ((state == 0) || (state == 1) || (state == 2))) { {
        p.split(playerHand, deck, 0);
        p.split(playerHand, deck, 1);
    }
    else if else if (((decision == "Double Down") || (decision == "double down"))
            && ((state == 0) || (state == 1) || (state == 3))
            && (p.purse >= wagerAmount))
        p.doubleDown(playerHand, deck);
    else {
        cout << "Invalid decision, please select from the available options" << endl;
        playerDecision(wagerAmount, state);
    }
}

void Blackjack::dealerTurn(double wagerAmount) {
    cout << "Dealer reveals: " << dealerHand[0] << endl;

    while (d.isUnder17(dealerHand)) {
        d.hit(dealerHand, deck);
        cout << "Dealer hits: " << dealerHand.back() << endl;
    }

    if (d.isOver21(dealerHand))
        win(wagerAmount);
    else if (c.cardValueTotal(playerHand) > c.cardValueTotal(dealerHand))
        win(wagerAmount);
    else if (c.cardValueTotal(playerHand) < c.cardValueTotal(dealerHand))
        loss(wagerAmount);
    else
        push(wagerAmount);
}

void Blackjack::offerInsurance(double wagerAmount) {
    string answer;

    cout << "The dealer is showing an Ace, would you like to take insurance? [Y/N]" << endl;
    cin >> answer;

    if (answer == "Yes" || answer == "yes" || answer == "Y" || answer == "y") {
        cout << "How much would you like to wager? (up to half the original wager)";
        cin >> sideBet;
        
        while (sideBet <= 0 || sideBet >= p.purse || sideBet > 0.5 * wagerAmount) {
            cout << "Please enter a valid amount" << endl;
            cin >> sideBet;
        }

        p.purse -= sideBet;

        if (c.cardValue(dealerHand[0]) == 10) {
            cout << "The dealer reveals: " << dealerHand[0] << endl;
            cout << "Therefore, the dealer has Blackjack" << endl;
            cout << "Insurance pays 2:1, you win $" << sideBet;

            p.purse += 3 * sideBet;

            if (c.cardValueTotal(dealerHand) == c.cardValueTotal(playerHand))
                push(wagerAmount);
            else
                loss(wagerAmount);
        }
        else {
            cardsShowing(wagerAmount, 1);
        }
    }
    else
        cardsShowing(wagerAmount, 1);
}

void Blackjack::push(double wagerAmount) {
    p.purse += wagerAmount;

    cout << "This game resulted in a push, so all wagers are returned" << endl;
    cout << "Purse: $" << p.purse << endl;

    playAgain();
}

void Blackjack::loss(double wagerAmount) {
    cout << "This game resulted in a loss, so you lost your wager" << endl;
    cout << "Purse: $" << p.purse << endl;

    playAgain();
}

void Blackjack::win(double wagerAmount) {
    p.purse += 2 * wagerAmount;

    cout << "This game resulted in a win, which pays 1:1" << endl;
    cout << "Purse: $" << p.purse << endl;

    playAgain();
}

void Blackjack::blackjack(double wagerAmount) {
    p.purse += 2.5 * wagerAmount;
    
    cout << "This game resulted in a blackjack, which pays 3:2" << endl;
    cout << "Purse: $" << p.purse << endl;

    playAgain();
}

void Blackjack::playAgain() {
    string answer;

    if (p.purse < 5.00) {
        cout << "You fell below the minimum wager, so you have lost" << endl;
        cout << "Thanks for playing!" << endl;

        return;
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

    if (answer == "Yes" || answer == "yes" || answer == "Y" || answer == "y")
        startGame();
    else
        cout << "Thanks for playing!" << endl;
        return;
}