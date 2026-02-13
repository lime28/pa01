// Authors: Liam Habiby (A4W6417) and Kaden Warner (A2W9Y75)
#include "card.h"
#include "card_list.h"

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

string capturePrint(const CardList& list) {
    std::streambuf* old = std::cout.rdbuf();
    ostringstream oss;
    std::cout.rdbuf(oss.rdbuf());
    list.print();
    std::cout.rdbuf(old);
    return oss.str();
}

string cardToString(const Card& card) {
    ostringstream oss;
    oss << card;
    return oss.str();
}

void loadCards(CardList& hand, const vector<Card>& cards) {
    for (const auto& c : cards) {
        hand.insert(c);
    }
}

void playGame(CardList& alice, CardList& bob, std::ostream& out) {
    bool alicePick = true;
    while (true) {
        bool found = false;
        if (alicePick) {
            for (auto it = alice.begin(); it != alice.end(); it++) {
                if (bob.contains(*it)) {
                    out << "Alice picked matching card " << *it << "\n";
                    Card picked = *it;
                    bob.erase(picked);
                    alice.erase(picked);
                    found = true;
                    break;
                }
            }
        } else {
            for (auto it = bob.rbegin(); it != bob.rend(); it++) {
                if (alice.contains(*it)) {
                    out << "Bob picked matching card " << *it << "\n";
                    Card picked = *it;
                    alice.erase(picked);
                    bob.erase(picked);
                    found = true;
                    break;
                }
            }
        }
        if (!found) {
            break;
        }
        alicePick = !alicePick;
    }
}

struct TestRunner {
    int passed = 0;
    int failed = 0;

    void check(bool condition, const string& name) {
        if (condition) {
            ++passed;
            cout << "[PASS] " << name << "\n";
        } else {
            ++failed;
            cout << "[FAIL] " << name << "\n";
        }
    }
};

void testInsert(TestRunner& t) {
    CardList list1;
    Card c1 = Card("c", "a");
    t.check(list1.insert(c1), "insert #1: empty tree accepts first card");

    CardList list2;
    Card c2 = Card("d", "10");
    t.check(list2.insert(c2) && !list2.insert(c2), "insert #2: duplicate rejected");

    CardList list3;
    Card a = Card("c", "2");
    Card b = Card("c", "a");
    Card c = Card("h", "k");
    bool ok3 = list3.insert(a) && list3.insert(b) && list3.insert(c);
    t.check(ok3, "insert #3: multiple unique inserts succeed");

    CardList list4;
    Card root = Card("d", "7");
    Card left = Card("c", "5");
    Card right = Card("h", "3");
    list4.insert(root);
    bool ok4 = list4.insert(left) && list4.insert(right);
    t.check(ok4, "insert #4: inserts work on both sides of root");

    CardList list5;
    Card x = Card("s", "9");
    list5.insert(x);
    list5.erase(x);
    t.check(list5.insert(x), "insert #5: reinsert after erase succeeds");
}

void testContains(TestRunner& t) {
    CardList list1;
    Card c1 = Card("c", "a");
    t.check(!list1.contains(c1), "contains #1: empty tree false");

    CardList list2;
    Card c2 = Card("d", "3");
    list2.insert(c2);
    t.check(list2.contains(c2), "contains #2: single-node present true");

    CardList list3;
    Card c3 = Card("d", "3");
    Card miss = Card("d", "4");
    list3.insert(c3);
    t.check(!list3.contains(miss), "contains #3: single-node absent false");

    CardList list4;
    Card a = Card("c", "2");
    Card b = Card("d", "10");
    Card c = Card("h", "k");
    loadCards(list4, {a, b, c});
    t.check(list4.contains(b), "contains #4: multi-node lookup true");

    CardList list5;
    Card z = Card("s", "q");
    list5.insert(z);
    list5.erase(z);
    t.check(!list5.contains(z), "contains #5: erased card not found");
}

void testErase(TestRunner& t) {
    CardList list1;
    Card c1 = Card("c", "a");
    t.check(!list1.erase(c1), "erase #1: empty tree false");

    CardList list2;
    Card c2 = Card("d", "3");
    Card miss = Card("d", "4");
    list2.insert(c2);
    t.check(!list2.erase(miss), "erase #2: missing key false");

    CardList list3;
    Card root = Card("d", "7");
    Card leaf = Card("c", "a");
    list3.insert(root);
    list3.insert(leaf);
    bool ok3 = list3.erase(leaf) && !list3.contains(leaf) && list3.contains(root);
    t.check(ok3, "erase #3: remove leaf");

    CardList list4;
    Card a = Card("d", "7");
    Card b = Card("c", "5");
    Card c = Card("c", "4");
    loadCards(list4, {a, b, c});
    bool ok4 = list4.erase(b) && !list4.contains(b) && list4.contains(c);
    t.check(ok4, "erase #4: remove node with one child");

    CardList list5;
    Card n1 = Card("d", "7");
    Card n2 = Card("c", "5");
    Card n3 = Card("h", "8");
    Card n4 = Card("d", "6");
    loadCards(list5, {n1, n2, n3, n4});
    bool ok5 = list5.erase(n1) && !list5.contains(n1) && list5.contains(n2) && list5.contains(n3) && list5.contains(n4);
    t.check(ok5, "erase #5: remove node with two children");
}

void testPrint(TestRunner& t) {
    CardList list1;
    t.check(capturePrint(list1) == "", "print #1: empty tree prints no lines");

    CardList list2;
    Card c2 = Card("c", "a");
    list2.insert(c2);
    t.check(capturePrint(list2) == "c a\n", "print #2: single node on one line");

    CardList list3;
    Card c1 = Card("h", "3");
    Card c2b = Card("c", "2");
    Card c3 = Card("d", "a");
    loadCards(list3, {c1, c2b, c3});
    t.check(capturePrint(list3) == "c 2\nd a\nh 3\n", "print #3: multiple nodes sorted in-order by lines");

    CardList list4;
    Card a = Card("c", "2");
    Card b = Card("d", "a");
    Card c = Card("h", "3");
    loadCards(list4, {a, b, c});
    list4.erase(b);
    t.check(capturePrint(list4) == "c 2\nh 3\n", "print #4: order updates after erase");

    CardList list5;
    Card d = Card("s", "10");
    list5.insert(d);
    list5.insert(d);
    t.check(capturePrint(list5) == "s 10\n", "print #5: duplicates are not printed twice");
}

void testIterator(TestRunner& t) {
    CardList empty;
    t.check(empty.begin() == empty.end(), "iter #1: empty begin == end");
    t.check(empty.rbegin() == empty.rend(), "iter #2: empty rbegin == rend");

    CardList single;
    Card only = Card("d", "5");
    single.insert(only);
    auto it = single.begin();
    bool ok3 = (it != single.end()) && ((*it) == only);
    ++it;
    ok3 = ok3 && (it == single.end());
    t.check(ok3, "iter #3: single node forward traversal");

    auto rit = single.rbegin();
    bool ok4 = (rit != single.rend()) && ((*rit) == only);
    ++rit;
    ok4 = ok4 && (rit == single.rend());
    t.check(ok4, "iter #4: single node reverse traversal");

    CardList multi;
    Card a = Card("c", "2");
    Card b = Card("d", "a");
    Card c = Card("h", "3");
    loadCards(multi, {c, a, b});
    vector<string> seq;
    for (auto i = multi.begin(); i != multi.end(); ++i) {
        seq.push_back(cardToString(*i));
    }
    t.check(seq == vector<string>({"c 2", "d a", "h 3"}), "iter #5: ++ gives in-order sequence");

    vector<string> rev;
    for (auto i = multi.rbegin(); i != multi.rend(); ++i) {
        rev.push_back(cardToString(*i));
    }
    t.check(rev == vector<string>({"h 3", "d a", "c 2"}), "iter #6: reverse iterator sequence");

    auto endIt = multi.end();
    ++endIt;
    t.check(endIt == multi.end(), "iter #7: increment past end is safe");

    auto rendIt = multi.rend();
    --rendIt;
    t.check(rendIt == multi.rend(), "iter #8: decrement past rend is safe");

    auto b1 = multi.begin();
    auto b2 = multi.begin();
    auto r1 = multi.rbegin();
    t.check((b1 == b2) && (b1 != r1), "iter #9: == and != comparison semantics");
}

void testPlayGame(TestRunner& t) {
    {
        CardList alice;
        CardList bob;
        loadCards(alice, {Card("c", "3"), Card("d", "a"), Card("h", "9")});
        loadCards(bob, {Card("c", "3"), Card("d", "a"), Card("s", "2")});
        ostringstream out;

        playGame(alice, bob, out);

        bool ok = !alice.contains(Card("c", "3")) && !alice.contains(Card("d", "a")) &&
                  !bob.contains(Card("c", "3")) && !bob.contains(Card("d", "a")) &&
                  alice.contains(Card("h", "9")) && bob.contains(Card("s", "2")) &&
                  out.str() == "Alice picked matching card c 3\nBob picked matching card d a\n";
        t.check(ok, "game #1: common cards are matched and removed from both");
    }

    {
        CardList alice;
        CardList bob;
        loadCards(bob, {Card("c", "3"), Card("d", "a")});
        ostringstream out;

        playGame(alice, bob, out);

        bool ok = out.str().empty() && bob.contains(Card("c", "3")) && bob.contains(Card("d", "a"));
        t.check(ok, "game #2: one empty hand exits immediately");
    }

    {
        CardList alice;
        CardList bob;
        loadCards(alice, {Card("c", "3"), Card("h", "9")});
        loadCards(bob, {Card("d", "a"), Card("s", "2")});
        ostringstream out;

        playGame(alice, bob, out);

        bool ok = out.str().empty() && alice.contains(Card("c", "3")) && alice.contains(Card("h", "9")) &&
                  bob.contains(Card("d", "a")) && bob.contains(Card("s", "2"));
        t.check(ok, "game #3: no common cards terminates with no removals");
    }
}

int main() {
    TestRunner t;

    testInsert(t);
    testContains(t);
    testErase(t);
    testPrint(t);
    testIterator(t);
    testPlayGame(t);

    cout << "\nSummary: " << t.passed << " passed, " << t.failed << " failed\n";
    if (t.failed != 0) {
        return 1;
    }

    return 0;
}
