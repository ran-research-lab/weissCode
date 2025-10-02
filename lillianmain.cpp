// Gran cantidad de este código fue generado por chatGPT
// Yo lo adapté para simplificarlo para la clase

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "lilliandlist.hpp"
#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

TEST_CASE("Lillian Let's grow some lists and compare them") {
  cout << "Este es el main de Lillian..." << endl;
  DLList<int> L{42};
  DLList<int> M{10, 20, 30, 40, 50, 60, 70, 80, 90, 100};

  // CHECK(M.toString() == "10 20 30 40 50 60 70 80 90 100");

  // L.concat(M);
  // CHECK(L.toString() == "42 10 20 30 40 50 60 70 80 90 100");

  // CHECK(M.size() == 0);
}
