// card.h
// Author: Your name
// All class declarations related to defining a single card go here
#include <string>
#include <vector>
using namespace std;

#ifndef CARD_H
#define CARD_H

class Card {
private:
    vector<string> suits = {"c", "d", "s", "h"};
    vector<string> values = {"a", "2", "3", "4", "5", "6", "7", "8", "9", "10", "j", "q", "k"};

    int suit;
    int value;

public:
    Card(string setSuit, string setValue);

    int getValueInt() const;
    string getValueString() const;
    int getSuitInt() const;
    string getSuitString() const;
    bool operator==(const Card& other) const;
    bool operator>(const Card& other) const;
    bool operator<(const Card& other) const;
    bool operator>=(const Card& other) const;
    bool operator<=(const Card& other) const;
    friend ostream& operator<<(ostream& os, const Card& card);
};

#endif
