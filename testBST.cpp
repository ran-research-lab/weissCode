#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "BST.hpp"
#include "doctest.h"
#include <sstream>
#include <stdexcept>

using namespace std;

TEST_CASE("BinarySearchTree basic operations") {
  BinarySearchTree<int> bst;

  SUBCASE("New tree is empty") {
    CHECK(bst.isEmpty());
    CHECK_THROWS_AS(bst.findMin(), std::underflow_error);
    CHECK_THROWS_AS(bst.findMax(), std::underflow_error);
  }

  SUBCASE("Insertion and containment") {
    bst.insert(10);
    bst.insert(5);
    bst.insert(20);
    bst.insert(15);
    bst.insert(30);

    // bst.printTree(std::cout);
    cout << "aaaa" << bst.toInorderStr() << endl;

    CHECK_FALSE(bst.isEmpty());
    CHECK(bst.contains(10));
    CHECK(bst.contains(5));
    CHECK(bst.contains(20));
    CHECK_FALSE(bst.contains(999));

    CHECK_EQ(bst.findMin(), 5);
    CHECK_EQ(bst.findMax(), 30);

    BinarySearchTree<string> s;
    s.insert("alce");
    s.insert("zorra");
    s.insert("vaca");
    cout << "aaaa" << s.toInorderStr() << endl;
    CHECK(s.toInorderStr() == "alce vaca zorra");
  }

  SUBCASE("Duplicate insertions are ignored") {
    bst.insert(10);
    bst.insert(10);
    bst.insert(10);
    CHECK(bst.contains(10));
    // Only one 10 should exist (but tree doesn't expose size, so just check no
    // errors)
  }

  SUBCASE("Remove leaf node") {
    bst.insert(10);
    bst.insert(5);
    bst.insert(20);
    bst.remove(5);
    CHECK_FALSE(bst.contains(5));
    CHECK(bst.contains(10));
    CHECK(bst.contains(20));
  }

  SUBCASE("Remove node with one child") {
    bst.insert(10);
    bst.insert(5);
    bst.insert(20);
    bst.remove(5);
    CHECK_FALSE(bst.contains(5));
    CHECK(bst.contains(10));
    CHECK(bst.contains(20));
  }

  SUBCASE("Remove node with one child") {
    bst.insert(10);
    bst.insert(5);
    bst.insert(1); // 5 has one child
    bst.remove(5);
    CHECK_FALSE(bst.contains(5));
    CHECK(bst.contains(1));
  }

  SUBCASE("Remove node with two children") {
    bst.insert(10);
    bst.insert(5);
    bst.insert(15);
    bst.insert(12);
    bst.insert(18);

    bst.remove(15); // node with two children
    CHECK_FALSE(bst.contains(15));
    CHECK(bst.contains(12));
    CHECK(bst.contains(18));
  }

  SUBCASE("Remove non-existent element does nothing") {
    bst.insert(10);
    bst.remove(999);
    CHECK(bst.contains(10));
  }

  SUBCASE("makeEmpty clears the tree") {
    bst.insert(10);
    bst.insert(20);
    bst.makeEmpty();
    CHECK(bst.isEmpty());
    CHECK_THROWS_AS(bst.findMin(), std::underflow_error);
  }

  SUBCASE("printTree outputs sorted order") {
    bst.insert(10);
    bst.insert(5);
    bst.insert(20);
    bst.insert(15);

    std::ostringstream oss;
    bst.printTree(oss);

    std::string output = oss.str();
    CHECK(output.find("5") < output.find("10"));
    CHECK(output.find("10") < output.find("15"));
    CHECK(output.find("15") < output.find("20"));
  }

  SUBCASE("Copy constructor produces deep copy") {
    bst.insert(10);
    bst.insert(5);
    bst.insert(20);

    BinarySearchTree<int> copy(bst);
    CHECK(copy.contains(10));
    CHECK(copy.contains(5));
    CHECK(copy.contains(20));

    bst.remove(5);
    CHECK_FALSE(bst.contains(5));
    CHECK(copy.contains(5)); // ensure independence
  }

  SUBCASE("Move constructor transfers ownership") {
    bst.insert(10);
    bst.insert(5);

    BinarySearchTree<int> moved(std::move(bst));
    CHECK(moved.contains(10));
    CHECK(moved.contains(5));
    CHECK(bst.isEmpty()); // original should be empty
  }

  SUBCASE("Copy assignment works") {
    bst.insert(1);
    bst.insert(2);

    BinarySearchTree<int> other;
    other.insert(100);
    other = bst;

    CHECK(other.contains(1));
    CHECK(other.contains(2));
    CHECK_FALSE(other.contains(100));
  }

  SUBCASE("Move assignment works") {
    bst.insert(42);

    BinarySearchTree<int> other;
    other = std::move(bst);

    CHECK(other.contains(42));
    CHECK(bst.isEmpty());
  }
}