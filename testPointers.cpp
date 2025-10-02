#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "BST.hpp"
#include "doctest.h"
#include <sstream>
#include <stdexcept>

using namespace std;

void foo(int *&p) {
  cout << "address of p:" << p << endl;
  p = new int;
}

TEST_CASE("BinarySearchTree basic operations") {
  int *a = new int;
  cout << "address at main: " << a << endl;
  cout << "foo...." << endl;
  foo(a);
  cout << "address at main: " << a << endl;
}