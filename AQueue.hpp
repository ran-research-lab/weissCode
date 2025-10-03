#include <iostream>
#include <stdexcept>

// WARNING: THIS IS AN INCOMPLETE IMPLEMENTATION - THE BIG 5 ARE MISSING!

template <typename T> class Queue {
private:
  T *data;    // dynamic array
  int _front; // index of front element
  int _back;  // index of last element
  int aSize;  // current number of elements
  int cap;    // capacity of array

  void resize(int newCap) {
    T *newData = new T[newCap];
    for (int i = 0; i < aSize; i++) {
      newData[i] = data[(_front + i) % cap];
    }
    delete[] data;
    data = newData;
    cap = newCap;
    _front = 0;
    _back = (aSize == 0 ? 0 : aSize - 1);
  }

public:
  Queue(int initCap = 8)
      : data(new T[initCap]), _front(0), _back(0), aSize(0), cap(initCap) {}

  ~Queue() { delete[] data; }

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
    data[_back] = value;
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
    return data[_front];
  }
};
