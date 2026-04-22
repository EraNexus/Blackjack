#ifndef PLAYER_H
#define PLAYER_H

#include "Card.h"

#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>

class Player : public Card {
    public:
        int cardValueTotal = 0;

        std::vector<std::string> initialDeal(std::vector<std::string>& hand, std::vector<std::string>& deck);
        std::vector<std::string> hit(std::vector<std::string>& hand, std::vector<std::string>& deck);
        std::vector<std::string> stand(std::vector<std::string>& hand, std::vector<std::string>& deck);
        std::vector<std::string> doubleDown(std::vector<std::string>& hand, std::vector<std::string>& deck);
        std::vector<std::string> split(std::vector<std::string>& hand, std::vector<std::string>& deck);
};
#endif