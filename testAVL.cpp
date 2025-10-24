#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <numeric>
#include <iostream>

// Include your AVL header after doctest
#include "AvlTree.hpp"

// Helper: capture the sorted order produced by printTree()
template <typename T>
static std::vector<T> inorder_as_vec(AvlTree<T>& t) {
    std::streambuf* old = std::cout.rdbuf();
    std::ostringstream oss;
    std::cout.rdbuf(oss.rdbuf());
    t.printTree();
    std::cout.rdbuf(old);

    std::vector<T> out;
    std::istringstream iss(oss.str());
    T v;
    // printTree prints each item on its own line
    while (iss >> v) out.push_back(v);
    return out;
}

TEST_CASE("Empty tree: isEmpty, findMin/findMax throw") {
    AvlTree<int> t;
    CHECK(t.isEmpty());
    CHECK_THROWS_AS(t.findMin(), UnderflowException);
    CHECK_THROWS_AS(t.findMax(), UnderflowException);
}

TEST_CASE("Insert and contains (including balancing via typical AVL sequences)") {
    AvlTree<int> t;
    // Classic sequence that triggers multiple rotations in an AVL:
    // RR, LL, RL, LR across these inserts
    for (int v : {10, 20, 30, 40, 50, 25}) t.insert(v);

    CHECK_FALSE(t.isEmpty());
    for (int v : {10, 20, 25, 30, 40, 50}) {
        CHECK(t.contains(v));
    }
    CHECK_FALSE(t.contains(99));

    CHECK(t.findMin() == 10);
    CHECK(t.findMax() == 50);

    auto inorder = inorder_as_vec(t);
    std::vector<int> expected{10, 20, 25, 30, 40, 50};
    CHECK(inorder == expected); // must be strictly sorted
}

TEST_CASE("Duplicates are ignored") {
    AvlTree<int> t;
    for (int v : {5, 3, 7, 3, 5, 7, 5}) t.insert(v);

    // Still contains each unique element
    CHECK(t.contains(3));
    CHECK(t.contains(5));
    CHECK(t.contains(7));

    // In-order output should have no duplicates
    auto inorder = inorder_as_vec(t);
    std::vector<int> unique(inorder);
    unique.erase(std::unique(unique.begin(), unique.end()), unique.end());
    CHECK(inorder == unique);
    CHECK(inorder == std::vector<int>({3,5,7}));
}

TEST_CASE("Copy constructor makes a deep copy") {
    AvlTree<int> a;
    for (int v : {4, 2, 6, 1, 3, 5, 7}) a.insert(v);

    AvlTree<int> b = a; // copy-ctor
    CHECK(b.contains(1));
    CHECK(b.contains(7));
    auto ai = inorder_as_vec(a);
    auto bi = inorder_as_vec(b);
    CHECK(ai == bi);

    // Mutate original; copy should not change
    a.insert(8);
    CHECK(a.contains(8));
    CHECK_FALSE(b.contains(8));
}

TEST_CASE("Copy assignment operator (deep copy via copy-and-swap)") {
    AvlTree<int> a;
    for (int v : {10, 5, 15}) a.insert(v);

    AvlTree<int> c;
    c = a; // copy-assign
    CHECK(c.contains(5));
    CHECK(c.contains(15));

    a.insert(20);
    CHECK(a.contains(20));
    CHECK_FALSE(c.contains(20));
}

TEST_CASE("Move constructor leaves source empty and transfers ownership") {
    AvlTree<int> a;
    for (int v : {8, 4, 12}) a.insert(v);

    AvlTree<int> b = std::move(a);
    CHECK(b.contains(8));
    CHECK(b.contains(4));
    CHECK(b.contains(12));
    CHECK(a.isEmpty()); // per your move-ctor: rhs.root = nullptr
}

TEST_CASE("Move assignment leaves source empty and transfers ownership") {
    AvlTree<int> a;
    for (int v : {50, 25, 75}) a.insert(v);

    AvlTree<int> b;
    b = std::move(a);
    CHECK(b.contains(25));
    CHECK(b.contains(50));
    CHECK(b.contains(75));
    CHECK(a.isEmpty());
}

TEST_CASE("remove: deleting leaf, one-child, and two-children cases") {
    AvlTree<int> t;
    // Build a tree that will hit all removal shapes
    for (int v : {10, 5, 15, 3, 7, 12, 18, 6}) t.insert(v);
    // Current in-order: 3 5 6 7 10 12 15 18

    // Remove leaf (e.g., 3)
    t.remove(3);
    CHECK_FALSE(t.contains(3));
    CHECK(t.contains(5));
    auto inorder1 = inorder_as_vec(t);
    CHECK(inorder1 == std::vector<int>({5,6,7,10,12,15,18}));

    // Remove node with one child (e.g., 7 has one child 6 after previous removal)
    t.remove(7);
    CHECK_FALSE(t.contains(7));
    CHECK(t.contains(6));
    auto inorder2 = inorder_as_vec(t);
    CHECK(inorder2 == std::vector<int>({5,6,10,12,15,18}));

    // Remove node with two children (e.g., 10 has 5 and 15)
    t.remove(10);
    CHECK_FALSE(t.contains(10));
    auto inorder3 = inorder_as_vec(t);
    CHECK(inorder3 == std::vector<int>({5,6,12,15,18}));

    // Min/Max after removals
    CHECK(t.findMin() == 5);
    CHECK(t.findMax() == 18);
}

TEST_CASE("makeEmpty empties the tree and allows reuse") {
    AvlTree<int> t;
    for (int i = 1; i <= 7; ++i) t.insert(i);
    CHECK_FALSE(t.isEmpty());

    t.makeEmpty();
    CHECK(t.isEmpty());
    CHECK_THROWS_AS(t.findMin(), UnderflowException);

    // Reuse after empty
    t.insert(42);
    CHECK_FALSE(t.isEmpty());
    CHECK(t.contains(42));
    CHECK(t.findMin() == 42);
    CHECK(t.findMax() == 42);
}

TEST_CASE("Stress-ish: insert many ascending (should still behave and stay sorted)") {
    AvlTree<int> t;
    for (int i = 1; i <= 200; ++i) t.insert(i); // would be pathological for an unbalanced BST
    CHECK(t.findMin() == 1);
    CHECK(t.findMax() == 200);

    auto inorder = inorder_as_vec(t);
    std::vector<int> expected(200);
    std::iota(expected.begin(), expected.end(), 1);
    CHECK(inorder == expected);
}
