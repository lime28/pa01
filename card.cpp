// card.cpp
// Authors: Liam Habiby (A4W6417) and Kaden Warner (A2W9Y75)
// Implementation of the classes defined in card.h
#include <string>
#include <iostream>
#include "card.h"
using namespace std;


Card::Card(string setSuit, string setValue) : suit(-1), value(-1) {
    for (int i = 0; i < suits.size(); i++) {
        if (suits[i] == setSuit) {
            suit = i;
            break;
        }
    }
    for (int i = 0; i < values.size(); i++) {
        if (values[i] == setValue) {
            value = i;
            break;
        }
    }
    if (suit == -1 || value == -1) {
        cout << "Card initialization failed\n";
    }
}

int Card::getValueInt() const {
    return value;
}

string Card::getValueString() const {
    return values[value];
}

int Card::getSuitInt() const {
    return suit;
}

string Card::getSuitString() const {
    return suits[suit];
}

bool Card::operator==(const Card& other) const {
    return (suit == other.suit && value == other.value);
}
bool Card::operator>(const Card& other) const {
    if (suit != other.suit) return suit > other.suit;
    return value > other.value;
}
bool Card::operator<(const Card& other) const {
    if (suit != other.suit) return suit < other.suit;
    return value < other.value;
}
bool Card::operator>=(const Card& other) const {
    return *this == other || *this > other;
}
bool Card::operator<=(const Card& other) const {
    return *this == other || *this < other;
}

ostream& operator<<(ostream& os, const Card& card) {
    os << card.getSuitString() + " " + card.getValueString();
    return os;
}
