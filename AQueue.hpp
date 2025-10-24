#include <iostream>
#include <stdexcept>

// WARNING: THIS IS AN INCOMPLETE IMPLEMENTATION - THE BIG 5 ARE MISSING!

template <typename T> class Queue {
private:
  T *a;
  int _front;
  int _back;
  int aSize;
  int cap;

  void resize(int newCap) {
    T *newa = new T[newCap];
    for (int i = 0; i < aSize; i++) {
      newa[i] = a[(_front + i) % cap];
    }
    delete[] a;
    a = newa;
    cap = newCap;
    _front = 0;
    _back = (aSize == 0 ? 0 : aSize - 1);
  }

public:
  Queue(int initCap = 8)
      : a(new T[initCap]), _front(0), _back(0), aSize(0), cap(initCap) {}

  ~Queue() { delete[] a; }

  bool empty() const { return aSize == 0; }

  int size() const { return aSize; }

  void push(const T &value) {
    if (aSize == cap)
      resize(cap * 2);

    if (empty()) {
      _front = _back = 0;
    } else {
      _back = (_back + 1) % cap;
    }
    a[_back] = value;
    aSize++;
  }

  void pop() {
    if (empty())
      throw std::out_of_range("pop from empty queue");
    if (aSize == 1) {
      _front = _back = aSize = 0;
    } else {
      _front = (_front + 1) % cap;
      aSize--;
    }
  }

  T front() {
    if (empty())
      throw std::out_of_range("front from empty queue");
    return a[_front];
  }
};
