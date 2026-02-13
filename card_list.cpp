// card_list.cpp
// Authors: Liam Habiby (A4W6417) and Kaden Warner (A2W9Y75)
// Implementation of the classes defined in card_list.h
//
#include "card_list.h"
#include "card.h"

#include <iostream>
using std::cout;

// constructor sets up empty tree
CardList::CardList() {
    root = nullptr;
}

// destructor deletes all nodes
CardList::~CardList() {
    clear(root);
}

// recursive helper for destructor
void CardList::clear(Node *n) {
    if (!n) return;
    clear(n->left);
    clear(n->right);
    delete n;
}

// insert value in tree; return false if duplicate
bool CardList::insert(const Card& card) {
    if (!root) {
        root = new Node(card);
        return true;
    } else {
        return insert(card, root);
    }
}

// recursive helper for insert (assumes n is never 0)
bool CardList::insert(const Card& card, Node *n) {
    if (card > n->info) {
        if (n->right) {
            return insert(card, n->right);
        } else {
            Node* newNode = new Node(card);
            n->right = newNode;
            newNode->parent = n;
            return true;
        }
    } else if (card < n->info) {
        if (n->left) {
            return insert(card, n->left);
        } else {
            Node* newNode = new Node(card);
            n->left = newNode;
            newNode->parent = n;
            return true;
        }
    } else {
        return false;
    }
}

// print tree data in-order, with helper
void CardList::print() const {
    if (!root) return;
    print(root);
}
void CardList::print(Node *n) const {
    if (n->left) print(n->left);
    cout << n->info << "\n";
    if (n->right) print(n->right);
}

CardList::Node* CardList::getNodeFor(const Card& card, Node* n) const{
    if (!n) return nullptr;

    if (card > n->info) {
        return getNodeFor(card, n->right);
    } else if (card < n->info) {
        return getNodeFor(card, n->left);
    } else {
        return n;
    }
}

// returns true if value is in the tree; false if not
bool CardList::contains(const Card& card) const {
    if (!root) return false;
    return contains(card, root);
}

bool CardList::contains(const Card& card, Node* n) const {
    if (!n) return false;

    if (card > n->info) {
        return contains(card, n->right);
    } else if (card < n->info) {
        return contains(card, n->left);
    } else {
        return true;
    }
}

// returns the Node containing the predecessor of the given value
CardList::Node* CardList::getPredecessorNode(Node* n) const {
    if (!n) return nullptr;

    if (n->left) {
        n = n->left;
        while (n->right) {
            n = n->right;
        }
        return n;
    } else {
        Node* prev = n;
        while (n->parent) {
            n = n->parent;
            if (n->right == prev) return n;
            prev = n;
        }
        return nullptr;
    }
}

// returns the Node containing the successor of the given value
CardList::Node* CardList::getSuccessorNode(Node* n) const {
    if (!n) return nullptr;

    if (n->right) {
        n = n->right;
        while (n->left) {
            n = n->left;
        }
        return n;
    } else {
        Node* prev = n;
        while (n->parent) {
            n = n->parent;
            if (n->left == prev) return n;
            prev = n;
        }
        return nullptr;
    }
}

// deletes the Node containing the given value from the tree
// returns true if the node exist and was deleted or false if the node does not exist
bool CardList::erase(const Card& card){
    Node* n = getNodeFor(card, root);
    if (!n) return false;

    if (n->left && n->right) {
        Node* succ = getSuccessorNode(n);
        n->info = succ->info;
        n = succ;
    }

    Node* child = (n->left) ? n->left : n->right;

    if (child) {
        child->parent = n->parent;
    }

    if (!n->parent) {
        root = child;
    } else if (n == n->parent->left) {
        n->parent->left = child;
    } else {
        n->parent->right = child;
    }

    delete n;
    return true;
}

CardList::Node* CardList::getSmallest() const {
    if (!root) return nullptr;
    Node* curr = root;
    while (curr->left) {
        curr = curr->left;
    }
    return curr;
}

CardList::Node* CardList::getLargest() const {
    if (!root) return nullptr;
    Node* curr = root;
    while (curr->right) {
        curr = curr->right;
    }
    return curr;
}

CardList::Iterator CardList::begin() const {
    return Iterator(getSmallest(), false, this);
}

CardList::Iterator CardList::rbegin() const {
    return Iterator(getLargest(), true, this);
}

CardList::Iterator CardList::end() const {
    return Iterator(nullptr, false, this);
}

CardList::Iterator CardList::rend() const {
    return Iterator(nullptr, true, this);
}

CardList::Iterator& CardList::Iterator::operator++() {
    curr = reverse ? list->getPredecessorNode(curr) : list->getSuccessorNode(curr);
    return *this;
}

CardList::Iterator& CardList::Iterator::operator--() {
    curr = reverse ? list->getSuccessorNode(curr) : list->getPredecessorNode(curr);
    return *this;
}

CardList::Iterator CardList::Iterator::operator++(int) {
    Iterator old = *this;
    ++(*this);
    return old;
}

CardList::Iterator CardList::Iterator::operator--(int) {
    Iterator old = *this;
    --(*this);
    return old;
}

const Card& CardList::Iterator::operator*() const {
    return curr->info;
}

const Card* CardList::Iterator::operator->() const {
    return &(curr->info);
}

bool CardList::Iterator::operator==(const Iterator& other) const {
    return curr == other.curr && reverse == other.reverse;
}

bool CardList::Iterator::operator!=(const Iterator& other) const {
    return curr != other.curr || reverse != other.reverse;
}
