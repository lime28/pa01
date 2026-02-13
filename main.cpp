// This file should implement the game using a custom implementation of a BST (based on your earlier
// BST implementation)
// Authors: Liam Habiby (A4W6417) and Kaden Warner (A2W9Y75)
#include "card.h"
#include "card_list.h"
#include <fstream>
#include <iostream>
#include <string>
// Do not include set in this file

using namespace std;

void playGame(CardList& alice, CardList& bob) {
    bool alicePick = true;
    while (true) {
        bool found = false;
        if (alicePick) {
            for (auto aliceIterator = alice.begin(); aliceIterator != alice.end(); aliceIterator++) {
                if (bob.contains(*aliceIterator)) {
                    cout << "Alice picked matching card " << *aliceIterator << endl;
                    found = true;
                    bob.erase(*aliceIterator);
                    alice.erase(*aliceIterator);
                    break;
                }
            }
        } else {
            for (auto bobIterator = bob.rbegin(); bobIterator != bob.rend(); bobIterator++) {
                if (alice.contains(*bobIterator)) {
                    cout << "Bob picked matching card " << *bobIterator << endl;
                    found = true;
                    alice.erase(*bobIterator);
                    bob.erase(*bobIterator);
                    break;
                }
            }
        }

        if (!found) break;
        alicePick = !alicePick;
    }
}

int main(int argv, char **argc) {
    if (argv < 3) {
        cout << "Please provide 2 file names" << endl;
        return 1;
    }

    ifstream cardFile1(argc[1]);
    ifstream cardFile2(argc[2]);
    string line;

    if (cardFile1.fail() || cardFile2.fail()) {
        cout << "Could not open file " << argc[2];
        return 1;
    }

    CardList alice;
    CardList bob;

    // Read each file
    while (getline(cardFile1, line) && (line.length() > 0)) {
        string suit = line.substr(0, 1);
        string value = line.substr(2);
        Card newCard(suit, value);
        alice.insert(newCard);
    }
    cardFile1.close();

    while (getline(cardFile2, line) && (line.length() > 0)) {
        string suit = line.substr(0, 1);
        string value = line.substr(2);
        Card newCard(suit, value);
        bob.insert(newCard);
    }
    cardFile2.close();

    playGame(alice, bob);

    cout << "\nAlice's cards:\n";
    for (auto& card : alice) {
        cout << card << endl;
    }

    cout << "\nBob's cards:\n";
    for (auto& card : bob) {
        cout << card << endl;
    }

    return 0;
}
