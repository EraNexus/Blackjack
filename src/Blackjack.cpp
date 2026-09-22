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

    if (c.cardValueTotal(playerHand) == 21) {
        

        if (c.cardValue(dealerHand[1]) == 1) {
            cardsShowing(playerHand, wagerAmount, 0);
            return;
        }

        cout << endl;
        cout << "===========================================" << endl;
        cout << "               YOUR HAND" << endl;
        cout << "===========================================" << endl;

        for (size_t i = 0; i < playerHand.size(); i++) {
            cout << "   " << playerHand[i] << endl;
        }

        cout << "   Total: " << c.cardValueTotal(playerHand) << endl;

        if (c.cardValueTotal(dealerHand) == 21) {
            cout << endl;
            cout << "Dealer reveals: " << dealerHand[0] << endl;
            cout << "Dealer also has Blackjack!" << endl;

            result(wagerAmount, "push");
        }
        else {
            result(wagerAmount, "blackjack");
        }

        return;
    }

    cardsShowing(playerHand, wagerAmount, 0);
}

void Blackjack::cardsShowing(vector<string>& hand, double wagerAmount, int state) {
    // State 0 is the initial state, where insurance is offered
    // State 1 is the default state
    // State 2 is the first split hand
    // State 3 is the second split hand

    cout << endl;
    cout << "===========================================" << endl;
    cout << "                YOUR TURN" << endl;
    cout << "===========================================" << endl;
    cout << "Dealer:" << endl;
    cout << "   " << dealerHand[1] << endl;
    cout << "   [Hidden Card]" << endl;
    cout << "   Visible Total: " << c.cardValue(dealerHand[1]) << endl;
    cout << endl;

    if (c.cardValue(dealerHand[1]) == 1 && state == 0) {
        offerInsurance(wagerAmount);
        return;
    }

    cout << "Your Hand: " << endl;
    for (size_t i = 0; i < hand.size(); i++) {
        cout << "   " << hand[i] << endl;
    }
    
    cout << "   Total: " << c.cardValueTotal(hand) << endl; 
    cout << endl;

    cout << "-------------------------------------------" << endl;
    cout << "Available Actions: HIT | STAND";

    if ((c.cardValue(hand[0]) == c.cardValue(hand[1])) 
        && state == 0
        && p.purse >= wagerAmount)
        cout << " | SPLIT";
    if (p.purse >= wagerAmount && state == 0)
        cout << " | DOUBLE";

    cout << endl;
    cout << "Purse: $" << p.purse << endl;
    cout << "-------------------------------------------" << endl;

    playerDecision(hand, wagerAmount, state);
}

void Blackjack::playerDecision(vector<string>& hand, double wagerAmount, int state) {
    string decision;

    cout << endl;
    cout << "Decision: ";
    cin >> decision;

    if ((decision == "Hit") || (decision == "hit") || (decision == "HIT")) {
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
                    splitResult("BUST", "BUST", wagerAmount);
                }
                else {
                    dealerTurn(wagerAmount);
                }
            }
            else {
                result(wagerAmount, "loss");
            }
        }
        else {
            if (state == 0)
                cardsShowing(hand, wagerAmount, 1);
            else
                cardsShowing(hand, wagerAmount, state);
        }
    }
    else if ((decision == "Stand") || (decision == "stand") || (decision == "STAND")) {
        if (state == 2)
            cardsShowing(splitHand, wagerAmount, 3);
        else
            dealerTurn(wagerAmount);
    }
    else if (((decision == "Split") || (decision == "split") || (decision == "SPLIT"))
            && state == 0
            && p.purse >= wagerAmount
            && c.cardValue(hand[0]) == c.cardValue(hand[1])) {
        p.purse -= wagerAmount;
        splitHand = p.split(hand, deck);

        cardsShowing(playerHand, wagerAmount, 2);
    }
    else if (((decision == "Double") || (decision == "double") || (decision == "DOUBLE"))
                && state == 0
                && p.purse >= wagerAmount) {
            p.purse -= wagerAmount;
            p.doubleDown(hand, deck);

            if (p.isOver21(hand))
                result(wagerAmount * 2, "loss");
            else
                dealerTurn(wagerAmount * 2);
    }
    else {
        cout << "Invalid decision, please select from the available options" << endl;
        playerDecision(hand, wagerAmount, state);
    }
}

void Blackjack::dealerTurn(double wagerAmount) {
    cout << endl;
    cout << "===========================================" << endl;
    cout << "              DEALER'S TURN" << endl;
    cout << "===========================================" << endl;
    cout << endl;

    cout << "Dealer reveals: " << endl;
    cout << "   " << dealerHand[0] << endl;
    cout << endl;

    cout << "Dealer Hand:" << endl;
    cout << "   " << dealerHand[0] << endl;
    cout << "   " << dealerHand[1] << endl;
    cout << "   Total: " << c.cardValueTotal(dealerHand) << endl;
    cout << endl;

    while (d.isUnder17(dealerHand)) {
        d.hit(dealerHand, deck);
        
        cout << "Dealer hits:" << endl;
        cout << "   " << dealerHand.back() << endl;
        cout << "   Total: " << c.cardValueTotal(dealerHand) << endl;
        cout << endl; 
    }

    if (splitHand.empty()) {
        if (d.isOver21(dealerHand))
            result(wagerAmount, "win");
        else if (c.cardValueTotal(playerHand) > c.cardValueTotal(dealerHand))
            result(wagerAmount, "win");
        else if (c.cardValueTotal(playerHand) < c.cardValueTotal(dealerHand))
            result(wagerAmount, "loss");
        else
            result(wagerAmount, "push");

        return;
    }

    string firstResult;
    string secondResult;

    if (firstHandBust) {
        firstResult = "BUST";
    }
    else if (d.isOver21(dealerHand) ||
            c.cardValueTotal(playerHand) > c.cardValueTotal(dealerHand)) {
        firstResult = "WIN";
        p.purse += 2 * wagerAmount;
    }
    else if (c.cardValueTotal(playerHand) < c.cardValueTotal(dealerHand)) {
        firstResult = "LOSS";
    }
    else {
        firstResult = "PUSH";
        p.purse += wagerAmount;
    }

    if (secondHandBust) {
        secondResult = "BUST";
    }
    else if (d.isOver21(dealerHand) ||
            c.cardValueTotal(splitHand) > c.cardValueTotal(dealerHand)) {
        secondResult = "WIN";
        p.purse += 2 * wagerAmount;
    }
    else if (c.cardValueTotal(splitHand) < c.cardValueTotal(dealerHand)) {
        secondResult = "LOSS";
    }
    else {
        secondResult = "PUSH";
        p.purse += wagerAmount;
    }

    splitResult(firstResult, secondResult, wagerAmount);    
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
            result(wagerAmount, "push");
        else
            result(wagerAmount, "loss");
    }
    else if (c.cardValueTotal(playerHand) == 21) {
        result(wagerAmount, "blackjack");
    }
    else {
        cardsShowing(playerHand, wagerAmount, 1);
    }
}

void Blackjack::result(double wagerAmount, string outcome) {
    double payout = 0;

    cout << endl;
    cout << "===========================================" << endl;
    cout << "              ROUND RESULT" << endl;
    cout << "===========================================" << endl;
    cout << endl;

    if (outcome == "win") {
        payout = 2 * wagerAmount;
        p.purse += payout;

        cout << "                  YOU WIN!" << endl;
        cout << endl;
        cout << "   Result:  Win" << endl;
        cout << "   Payout:  1:1" << endl;
    }
    else if (outcome == "loss") {
        cout << "                 YOU LOSE" << endl;
        cout << endl;
        cout << "   Result:  Loss" << endl;
        cout << "   Payout:  $0" << endl;
    }
    else if (outcome == "push") {
        payout = wagerAmount;
        p.purse += payout;

        cout << "                    PUSH" << endl;
        cout << endl;
        cout << "   Result:  Push" << endl;
        cout << "   Wager returned" << endl;
    }
    else if (outcome == "blackjack") {
        payout = 2.5 * wagerAmount;
        p.purse += payout;

        cout << "                 BLACKJACK!" << endl;
        cout << endl;
        cout << "   Result:  Blackjack" << endl;
        cout << "   Payout:  3:2" << endl;
    }
    else {
        cout << "ERROR: Invalid game result" << endl;
        return;
    }

    cout << endl;
    cout << "-------------------------------------------" << endl;
    cout << "   Wager:    $" << wagerAmount << endl;
    cout << "   Returned: $" << payout << endl;
    cout << "   Purse:    $" << p.purse << endl;
    cout << "-------------------------------------------" << endl;
    cout << endl;
}

void Blackjack::splitResult(string firstResult, string secondResult,
                            double wagerAmount) {
    cout << endl;
    cout << "===========================================" << endl;
    cout << "              ROUND RESULT" << endl;
    cout << "===========================================" << endl;
    cout << endl;

    cout << "              SPLIT RESULTS" << endl;
    cout << endl;

    cout << "   Dealer: " << c.cardValueTotal(dealerHand);

    if (d.isOver21(dealerHand))
        cout << " (BUST)";

    cout << endl;

    cout << "   Hand 1: " << c.cardValueTotal(playerHand) << "  -> " << firstResult << endl;

    cout << "   Hand 2: " << c.cardValueTotal(splitHand) << "  -> " << secondResult << endl;

    cout << endl;
    cout << "-------------------------------------------" << endl;
    cout << "   Wager per Hand: $" << wagerAmount << endl;
    cout << "   Purse:          $" << p.purse << endl;
    cout << "-------------------------------------------" << endl;
    cout << endl;
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