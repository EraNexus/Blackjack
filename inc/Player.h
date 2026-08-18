#ifndef PLAYER_H
#define PLAYER_H

#include "Card.h"

#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>

class Player : public Card {
    public:
        double purse = 100.00;

        std::vector<std::string> initialDeal(std::vector<std::string>& hand, std::vector<std::string>& deck);
        std::vector<std::string> hit(std::vector<std::string>& hand, std::vector<std::string>& deck);
        std::vector<std::string> stand(std::vector<std::string>& hand, std::vector<std::string>& deck);
        std::vector<std::string> split(std::vector<std::string>& hand, std::vector<std::string>& deck, int index);
        std::vector<std::string> doubleDown(std::vector<std::string>& hand, std::vector<std::string>& deck);
        bool isOver21(std::vector<std::string>& hand);
};
#endif