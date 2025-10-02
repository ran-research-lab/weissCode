#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "LListLab.hpp"
#include <string>

TEST_CASE("Empty list")
{
    LList<int> L;
    CHECK(L.empty());
    CHECK(L.size() == 0);
}

TEST_CASE("Push and Pop operations")
{
    LList<int> L;

    SUBCASE("push_back and pop_back")
    {
        L.push_back(10);
        L.push_back(20);
        CHECK(L.size() == 2);
        CHECK(L.back() == 20);

        L.pop_back();
        CHECK(L.size() == 1);
        CHECK(L.back() == 10);

        L.pop_back();
        CHECK(L.empty());
    }

    SUBCASE("push_front and pop_front")
    {
        L.push_front(5);
        L.push_front(15);
        CHECK(L.size() == 2);
        CHECK(L.front() == 15);

        L.pop_front();
        CHECK(L.size() == 1);
        CHECK(L.front() == 5);

        L.pop_front();
        CHECK(L.empty());
    }
}

TEST_CASE("Front and Back")
{
    LList<int> L;
    L.push_back(1);
    L.push_back(2);
    L.push_back(3);
    CHECK(L.front() == 1);
    CHECK(L.back() == 3);
}

TEST_CASE("Insert and Erase")
{
    LList<int> L;
    for (int i = 1; i <= 3; ++i)
        L.push_back(i); // 1,2,3

    auto it = L.begin();
    ++it;             // points to 2
    L.insert(it, 99); // LList: 1, 99, 2, 3
    CHECK(L.size() == 4);

    it = L.begin();
    ++it; // 99
    CHECK(*it == 99);

    L.erase(it); // remove 99
    CHECK(L.size() == 3);

    std::vector<int> expected{1, 2, 3};
    int idx = 0;
    for (auto &x : L)
        CHECK(x == expected[idx++]);
}

TEST_CASE("Iterator traversal")
{
    LList<std::string> L;
    L.push_back("a");
    L.push_back("b");
    L.push_back("c");

    auto it = L.begin();
    CHECK(*it == "a");
    ++it;
    CHECK(*it == "b");
    ++it;
    CHECK(*it == "c");
    ++it;
    CHECK(it == L.end());
}

TEST_CASE("Copy constructor")
{
    LList<int> L;
    L.push_back(1);
    L.push_back(2);

    LList<int> M = L; // copy
    CHECK(M.size() == 2);
    CHECK(M.front() == 1);
    CHECK(M.back() == 2);

    // Ensure deep copy
    M.pop_back();
    CHECK(L.size() == 2);
    CHECK(M.size() == 1);
}

TEST_CASE("Copy assignment")
{
    LList<int> L;
    L.push_back(42);

    LList<int> M;
    M.push_back(1);
    M.push_back(2);

    M = L; // copy assignment
    CHECK(M.size() == 1);
    CHECK(M.front() == 42);
}

TEST_CASE("Move constructor")
{
    LList<int> L;
    L.push_back(10);
    L.push_back(20);

    LList<int> M = std::move(L);
    CHECK(M.size() == 2);
    CHECK(M.front() == 10);
    CHECK(M.back() == 20);

    CHECK(L.size() == 0); // source emptied
}

TEST_CASE("Move assignment")
{
    LList<int> L;
    L.push_back(5);

    LList<int> M;
    M.push_back(100);

    M = std::move(L);
    CHECK(M.size() == 1);
    CHECK(M.front() == 5);
    CHECK(L.size() == 0); // source emptied
}

TEST_CASE("Clear LList")
{
    LList<int> L;
    for (int i = 0; i < 5; ++i)
        L.push_back(i);
    CHECK(L.size() == 5);

    L.clear();
    CHECK(L.empty());
}

TEST_CASE("Remove Odd LList")
{
    LList<int> L;
    for (int i = 1; i <= 4; ++i)
        L.push_back(i);
    CHECK(L.size() == 4);

    L.reverse();
    for (auto it = L.begin(); it != L.end(); it++)
        cout << *it << endl;

    L.reverse();
    L.push_back(5);

    L.reverse();
    for (LList<int>::const_iterator it = L.begin(); it != L.end(); it++) {
        cout << *it << endl;
    }


    // L.removeOdd();
    // for (auto it = L.begin(); it != L.end(); it++)
    //     cout << *it << endl;
}
