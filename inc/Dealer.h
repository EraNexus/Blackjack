#ifndef DEALER_H
#define DEALER_H

#include "Card.h"

#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>

class Dealer{
    public:
        std::vector<std::string> Dealer::initialDeal(std::vector<std::string>& hand, std::vector<std::string>& deck)
        std::vector<std::string> hit(std::vector<std::string>& hand, std::vector<std::string>& deck);
        std::vector<std::string> stand(std::vector<std::string>& hand, std::vector<std::string>& deck);
        bool isUnder17(std::vector<std::string>& hand);
        bool isOver21(std::vector<std::string>& hand);
};
#endif