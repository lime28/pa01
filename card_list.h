// card_list.h
// Authors: Liam Habiby and Kaden Warner
// All class declarations related to defining a BST that represents a player's hand

#ifndef CARD_LIST_H
#define CARD_LIST_H

#include <iostream>
#include "card.h"

using namespace std;

class CardList {
private:

    struct Node {
        Card info;
        Node *left, *right, *parent;
        Node(const Card& card) : info(card), left(0), right(0), parent(0) { }
    };

    Node *root;

    Node* getNodeFor(const Card& card, Node* n) const;
    void clear(Node *n); // for destructor
    bool insert(const Card& card, Node *n); // note overloading names for simplicity
    void print(Node *n) const;
    bool contains(const Card& card, Node* n) const;
    Node* getSmallest() const;
    Node* getLargest() const;

    // these should be used by getPredecessor and getSuccessor, and ONE of them should be used by remove
    Node* getSuccessorNode(Node* n) const;   // returns the Node containing the successor of the given value
    Node* getPredecessorNode(Node* n) const; // returns the Node containing the predecessor of the given value

public:
    // ctor, dtor, insert and one print method already done in card_list.cpp:
    CardList();                   // constructor
    ~CardList();                  // destructor
    bool insert(const Card& card);     // insert value; return false if duplicate
    void print() const;       // print tree data in-order to cout
    bool contains(const Card& card) const;  // true if value is in tree

    bool erase(const Card& card);                    // deletes the Node containing the given value from the tree

    class Iterator {
    private:
        Node* curr;
        bool reverse;
        const CardList* list;
        Iterator(Node* n, bool r, const CardList* l) : curr(n), reverse(r), list(l) {};
        friend class CardList;

    public:
        Iterator() : curr(nullptr) {}

        const Card& operator*() const;
        const Card* operator->() const;
        Iterator& operator++();
        Iterator& operator--();
        Iterator operator++(int);
        Iterator operator--(int);
        bool operator==(const Iterator& other) const;
        bool operator!=(const Iterator& other) const;
    };

    Iterator begin() const;
    Iterator end() const;
    Iterator rbegin() const;
    Iterator rend() const;
};

#endif
