#ifndef DLLIST_HPP
#define DLLIST_HPP

#include <algorithm>
using namespace std;

template <typename T> class DLList {
private:
  // The basic doubly linked DLList node. Nested inside of DLList, can be public
  // because the Node is itself private
  struct Node {
    T data;
    Node *prev;
    Node *next;

    Node(const T &d = T{}, Node *p = nullptr, Node *n = nullptr)
        : data{d}, prev{p}, next{n} {}

    Node(T &&d, Node *p = nullptr, Node *n = nullptr)
        : data{std::move(d)}, prev{p}, next{n} {}
  };

  string toStr(const T &value) const {
    ostringstream oss;
    oss << value;
    return oss.str();
  }

public:
  class const_iterator {
  public:
    // Public constructor for const_iterator.
    const_iterator() : current{nullptr} {}

    // Return the T stored at the current position.
    // For const_iterator, this is an accessor with a
    // const reference return type.
    const T &operator*() const { return retrieve(); }

    const_iterator &operator++() {
      current = current->next;
      return *this;
    }

    const_iterator operator++(int) {
      const_iterator old = *this;
      ++(*this);
      return old;
    }

    const_iterator &operator--() {
      current = current->prev;
      return *this;
    }

    const_iterator operator--(int) {
      const_iterator old = *this;
      --(*this);
      return old;
    }

    bool operator==(const const_iterator &rhs) const {
      return current == rhs.current;
    }

    bool operator!=(const const_iterator &rhs) const { return !(*this == rhs); }

  protected:
    Node *current;

    // Protected helper in const_iterator that returns the object
    // stored at the current position. Can be called by all
    // three versions of operator* without any type conversions.
    T &retrieve() const { return current->data; }

    // Protected constructor for const_iterator.
    // Expects a pointer that represents the current position.
    const_iterator(Node *p) : current{p} {}

    friend class DLList<T>;
  };

  class iterator : public const_iterator {
  public:
    // Public constructor for iterator. Calls the base-class constructor.
    // Must be provided because the private constructor is written;
    // otherwise zero-parameter constructor
    // would be disabled.
    iterator() {}

    T &operator*() { return const_iterator::retrieve(); }

    // Return the T stored at the current position.
    // For iterator, there is an accessor with a
    // const reference return type and a mutator with
    // a reference return type. The accessor is shown first.
    const T &operator*() const { return const_iterator::operator*(); }

    iterator &operator++() {
      this->current = this->current->next;
      return *this;
    }

    iterator operator++(int) {
      iterator old = *this;
      ++(*this);
      return old;
    }

    iterator &operator--() {
      this->current = this->current->prev;
      return *this;
    }

    iterator operator--(int) {
      iterator old = *this;
      --(*this);
      return old;
    }

  protected:
    // Protected constructor for iterator.
    // Expects the current position.
    iterator(Node *p) : const_iterator{p} {}

    friend class DLList<T>;
  };

public:
  DLList() { init(); }

  ~DLList() {
    clear();
    delete head;
    delete tail;
  }

  DLList(const DLList &rhs) {
    init();
    for (auto &x : rhs)
      push_back(x);
  }

  DLList &operator=(const DLList &rhs) {
    DLList copy = rhs;
    std::swap(*this, copy);
    return *this;
  }

  DLList(DLList &&rhs) : theSize{rhs.theSize}, head{rhs.head}, tail{rhs.tail} {
    rhs.theSize = 0;
    rhs.head = nullptr;
    rhs.tail = nullptr;
  }

  DLList &operator=(DLList &&rhs) {
    theSize = rhs.theSize;
    head = rhs.head;
    tail = rhs.tail;
    rhs.tail = rhs.head = nullptr;
    rhs.theSize = 0;
    // Arreglado por RAN
    // std::swap( theSize, rhs.theSize );
    // std::swap( head, rhs.head );
    // std::swap( tail, rhs.tail );

    return *this;
  }

  DLList(initializer_list<T> init) : DLList() {
    for (const T &val : init) {
      push_back(val);
    }
  }

  string toString() const {
    string st = "";
    if (theSize == 0)
      return st;
    auto it = begin();
    st = toStr(*it++);
    for (; it != end(); it++) {
      st = st + " " + toStr(*it);
    }
    return st;
  }

  // Return iterator representing beginning of DLList.
  // Mutator version is first, then accessor version.
  iterator begin() { return iterator(head->next); }

  const_iterator begin() const { return const_iterator(head->next); }

  // Return iterator representing endmarker of DLList.
  // Mutator version is first, then accessor version.
  iterator end() { return iterator(tail); }

  const_iterator end() const { return const_iterator(tail); }

  // Return number of elements currently in the DLList.
  int size() const { return theSize; }

  // Return true if the DLList is empty, false otherwise.
  bool empty() const { return size() == 0; }

  void clear() {
    while (!empty())
      pop_front();
  }

  // front, back, push_front, push_back, pop_front, and pop_back
  // are the basic double-ended queue operations.
  T &front() { return *begin(); }

  const T &front() const { return *begin(); }

  T &back() { return *--end(); }

  const T &back() const { return *--end(); }

  void push_front(const T &x) { insert(begin(), x); }

  void push_back(const T &x) { insert(end(), x); }

  void push_front(T &&x) { insert(begin(), std::move(x)); }

  void push_back(T &&x) { insert(end(), std::move(x)); }

  void pop_front() { erase(begin()); }

  void pop_back() { erase(--end()); }

  // Insert x before itr.
  iterator insert(iterator itr, const T &x) {
    Node *p = itr.current;
    ++theSize;
    return iterator(p->prev = p->prev->next = new Node{x, p->prev, p});
  }

  // Insert x before itr.
  iterator insert(iterator itr, T &&x) {
    Node *p = itr.current;
    ++theSize;
    return iterator(p->prev = p->prev->next =
                        new Node{std::move(x), p->prev, p});
  }

  // Erase item at itr.
  iterator erase(iterator itr) {
    Node *p = itr.current;
    iterator retVal(p->next);
    p->prev->next = p->next;
    p->next->prev = p->prev;
    delete p;
    --theSize;

    return retVal;
  }

  iterator erase(iterator from, iterator to) {
    for (iterator itr = from; itr != to;)
      itr = erase(itr);

    return to;
  }

  void removeOdd() {
    Node *curr = head->next;
    while (curr != tail) {
      Node *before = curr->prev;
      Node *after = curr->next;
      if (curr->data % 2) {
        before->next = after;
        after->prev = before;
        delete curr;
        theSize--;
      }
      curr = after;
    }
  }

  void reverse() {
    Node *fwd = head->next;
    Node *rev = tail->prev;
    bool swappedMid = false;
    while (fwd != tail && fwd != rev && !swappedMid) {

      Node *fwdNext = fwd->next;
      Node *revPrev = rev->prev;

      fwd->prev->next = rev;
      rev->next->prev = fwd;

      if (fwd->next != rev) {
        fwd->next->prev = rev;
        rev->prev->next = fwd;
        std::swap(fwd->next, rev->next);
        std::swap(fwd->prev, rev->prev);
      } else {
        fwd->next = rev->next;
        rev->next = fwd;
        rev->prev = fwd->prev;
        fwd->prev = rev;
        swappedMid = true;
      }

      fwd = fwdNext;
      rev = revPrev;
    }
  }

  // // concat
  // void concat(DLList &other){
  //   // link last non-sentinel node of calling object to first non-sentinel
  //   node of other DLList tail->prev->next = other.head->next;
  //   other.head->next->prev = tail->prev;
  //   // link last sentinel node of calling object to last non-sentinel node of
  //   other DLList tail->prev = other.tail->prev; other.tail->prev->next =
  //   tail;
  //   // link first and last sentinel nodes of other DLList
  //   other.head->next = other.tail;
  //   other.tail->prev = other.head;
  //   // update both DLList sizes
  //   theSize += other.theSize;
  //   other.theSize = 0;
  // }

  // DLList encode() const{
  //   DLList<T> encList;

  //   auto it = begin();
  //   int counter = 0;
  //   T trend = *it;

  //   for(; it != end(); it++){
  //     if (*it == trend) counter++;
  //     // found a different element so we push the trend and counter to
  //     encoded list else{
  //       encList.push_back(trend);
  //       encList.push_back(counter);
  //       trend = *it; // update trend
  //       counter = 1; // reset counter for new trend
  //     }
  //   }
  //   // push the last element and its counter
  //   encList.push_back(trend);
  //   encList.push_back(counter);

  //   return encList;
  // }

  // DLList getStrideList(int k) const{

  // }
private:
  int theSize;
  Node *head;
  Node *tail;

  void init() {
    theSize = 0;
    head = new Node;
    tail = new Node;
    head->next = tail;
    tail->prev = head;
  }
};

#endif
