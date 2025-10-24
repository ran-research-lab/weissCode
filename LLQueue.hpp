#include <iostream>
#include <stdexcept>

template <typename T> class Queue {
private:
  struct Node {
    T data;
    Node *next;

    Node() : next(nullptr) {}
    Node(const T &value) : data(value), next(nullptr) {}
  };

  Node *head;
  Node *rear;
  int count;

public:
  Queue() : count(0) {
    // nodo sentinela
    head = new Node();
    rear = head;
  }

  ~Queue() {
    clear();
    delete head;
  }

  // Constructor de copia
  Queue(const Queue &other) : count(0) {
    head = new Node();
    rear = head;

    Node *current = other.head->next;
    while (current != nullptr) {
      push(current->data);
      current = current->next;
    }
  }

  // Operador de asignación
  Queue &operator=(const Queue &other) {
    if (this != &other) {
      clear();

      Node *current = other.head->next;
      while (current != nullptr) {
        push(current->data);
        current = current->next;
      }
    }
    return *this;
  }

  void push(const T &value) {
    Node *newNode = new Node(value);
    rear->next = newNode;
    rear = newNode;
    count++;
  }

  T pop() {
    if (isEmpty()) {
      throw std::underflow_error("Queue is empty");
    }

    Node *firstNode = head->next;
    T value = firstNode->data;

    head->next = firstNode->next;

    if (head->next == nullptr) {
      rear = head;
    }

    delete firstNode;
    count--;
    return value;
  }

  T &front() {
    if (isEmpty()) {
      throw std::underflow_error("Queue is empty");
    }
    return head->next->data;
  }

  const T &front() const {
    if (isEmpty()) {
      throw std::underflow_error("Queue is empty");
    }
    return head->next->data;
  }

  bool isEmpty() const { return head->next == nullptr; }

  int size() const { return count; }

  void clear() {
    while (!isEmpty()) {
      pop();
    }
  }
};