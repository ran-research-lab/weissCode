#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "AQueue.hpp" // your Queue<T> implementation header
#include "doctest.h"

TEST_CASE("Queue basic operations") {
  Queue<int> q;

  CHECK(q.empty());
  CHECK(q.size() == 0);

  q.push(10);
  CHECK(!q.empty());
  CHECK(q.size() == 1);
  CHECK(q.front() == 10);
  //   CHECK(q.back() == 10);

  q.push(20);
  q.push(30);
  CHECK(q.size() == 3);
  CHECK(q.front() == 10);
  //   CHECK(q.back() == 30);

  q.pop();
  CHECK(q.size() == 2);
  CHECK(q.front() == 20);
  //   CHECK(q.back() == 30);

  q.pop();
  CHECK(q.size() == 1);
  CHECK(q.front() == 30);
  //   CHECK(q.back() == 30);

  q.pop();
  CHECK(q.empty());
  CHECK(q.size() == 0);
}

TEST_CASE("Queue push and wraparound") {
  Queue<int> q(3); // small capacity to force wraparound quickly

  q.push(1);
  q.push(2);
  q.push(3);
  CHECK(q.size() == 3);
  CHECK(q.front() == 1);
  //   CHECK(q.back() == 3);

  q.pop(); // remove 1
  CHECK(q.front() == 2);

  q.push(4); // should wrap around
  CHECK(q.size() == 3);
  CHECK(q.front() == 2);
  //   CHECK(q.back() == 4);

  q.pop(); // remove 2
  CHECK(q.front() == 3);
  //   CHECK(q.back() == 4);
}

TEST_CASE("Queue resizing") {
  Queue<int> q(2);

  q.push(10);
  q.push(20);
  CHECK(q.size() == 2);
  CHECK(q.front() == 10);
  //   CHECK(q.back() == 20);

  // force resize
  q.push(30);
  q.push(40);
  CHECK(q.size() == 4);
  CHECK(q.front() == 10);
  //   CHECK(q.back() == 40);

  q.push(15);
  q.push(33);
  CHECK(q.size() == 6);
  CHECK(q.front() == 10);
  //   CHECK(q.back() == 33);

  q.pop();
  CHECK(q.front() == 20);
}
