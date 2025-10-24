#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "LLQueue.hpp"
#include "doctest.h"
#include <string>

TEST_CASE("Queue - Constructor y estado inicial") {
  Queue<int> q;

  CHECK(q.isEmpty());
  CHECK(q.size() == 0);
}

TEST_CASE("Queue - push un elemento") {
  Queue<int> q;

  q.push(10);

  CHECK_FALSE(q.isEmpty());
  CHECK(q.size() == 1);
  CHECK(q.front() == 10);
}

TEST_CASE("Queue - push múltiples elementos") {
  Queue<int> q;

  q.push(10);
  q.push(20);
  q.push(30);

  CHECK(q.size() == 3);
  CHECK(q.front() == 10);
}

TEST_CASE("Queue - pop mantiene orden FIFO") {
  Queue<int> q;

  q.push(10);
  q.push(20);
  q.push(30);
  q.push(40);

  CHECK(q.pop() == 10);
  CHECK(q.size() == 3);

  CHECK(q.pop() == 20);
  CHECK(q.size() == 2);

  CHECK(q.pop() == 30);
  CHECK(q.size() == 1);

  CHECK(q.pop() == 40);
  CHECK(q.isEmpty());
}

TEST_CASE("Queue - pop en cola vacía lanza excepción") {
  Queue<int> q;

  CHECK_THROWS_AS(q.pop(), std::underflow_error);
}

TEST_CASE("Queue - Front en cola vacía lanza excepción") {
  Queue<int> q;

  CHECK_THROWS_AS(q.front(), std::underflow_error);
}

TEST_CASE("Queue - Front no modifica la cola") {
  Queue<int> q;

  q.push(100);
  q.push(200);

  CHECK(q.front() == 100);
  CHECK(q.size() == 2);
  CHECK(q.front() == 100); // Sigue siendo el mismo
}

TEST_CASE("Queue - Modificar elemento con front()") {
  Queue<int> q;

  q.push(10);
  q.push(20);

  q.front() = 99;

  CHECK(q.front() == 99);
  CHECK(q.pop() == 99);
  CHECK(q.front() == 20);
}

TEST_CASE("Queue - Clear vacía la cola") {
  Queue<int> q;

  q.push(1);
  q.push(2);
  q.push(3);
  q.push(4);
  q.push(5);

  q.clear();

  CHECK(q.isEmpty());
  CHECK(q.size() == 0);
}

TEST_CASE("Queue - Operaciones después de clear") {
  Queue<int> q;

  q.push(1);
  q.push(2);
  q.clear();

  q.push(10);
  q.push(20);

  CHECK(q.size() == 2);
  CHECK(q.pop() == 10);
  CHECK(q.pop() == 20);
}

TEST_CASE("Queue - Constructor de copia") {
  Queue<int> q1;

  q1.push(10);
  q1.push(20);
  q1.push(30);

  Queue<int> q2(q1);

  CHECK(q2.size() == 3);
  CHECK(q2.pop() == 10);
  CHECK(q2.pop() == 20);
  CHECK(q2.pop() == 30);

  // q1 no debe haberse modificado
  CHECK(q1.size() == 3);
  CHECK(q1.front() == 10);
}

TEST_CASE("Queue - Constructor de copia con cola vacía") {
  Queue<int> q1;
  Queue<int> q2(q1);

  CHECK(q2.isEmpty());
  CHECK(q2.size() == 0);
}

TEST_CASE("Queue - Operador de asignación") {
  Queue<int> q1;
  q1.push(100);
  q1.push(200);

  Queue<int> q2;
  q2.push(5);
  q2.push(6);
  q2.push(7);

  q2 = q1;

  CHECK(q2.size() == 2);
  CHECK(q2.pop() == 100);
  CHECK(q2.pop() == 200);

  // q1 no debe haberse modificado
  CHECK(q1.size() == 2);
}

TEST_CASE("Queue - Auto-asignación") {
  Queue<int> q1;
  q1.push(10);
  q1.push(20);

  q1 = q1;

  CHECK(q1.size() == 2);
  CHECK(q1.front() == 10);
}

TEST_CASE("Queue - Con strings") {
  Queue<std::string> q;

  q.push("Hola");
  q.push("Mundo");
  q.push("C++");

  CHECK(q.size() == 3);
  CHECK(q.pop() == "Hola");
  CHECK(q.pop() == "Mundo");
  CHECK(q.front() == "C++");
}

TEST_CASE("Queue - Con doubles") {
  Queue<double> q;

  q.push(3.14);
  q.push(2.71);
  q.push(1.41);

  CHECK(q.pop() == doctest::Approx(3.14));
  CHECK(q.pop() == doctest::Approx(2.71));
  CHECK(q.pop() == doctest::Approx(1.41));
}

TEST_CASE("Queue - push y pop intercalados") {
  Queue<int> q;

  q.push(1);
  q.push(2);
  CHECK(q.pop() == 1);

  q.push(3);
  q.push(4);
  CHECK(q.pop() == 2);
  CHECK(q.pop() == 3);

  q.push(5);
  CHECK(q.size() == 2);
  CHECK(q.front() == 4);
}

TEST_CASE("Queue - Muchos elementos") {
  Queue<int> q;

  for (int i = 1; i <= 1000; i++) {
    q.push(i);
  }

  CHECK(q.size() == 1000);

  for (int i = 1; i <= 1000; i++) {
    CHECK(q.pop() == i);
  }

  CHECK(q.isEmpty());
}

TEST_CASE("Queue - pop hasta vaciar y volver a llenar") {
  Queue<int> q;

  q.push(1);
  q.push(2);
  q.pop();
  q.pop();

  CHECK(q.isEmpty());

  q.push(10);
  q.push(20);

  CHECK(q.size() == 2);
  CHECK(q.front() == 10);
}

TEST_CASE("Queue - Estructura con centinela funciona correctamente") {
  Queue<int> q;

  // Agregar y quitar un elemento
  q.push(1);
  q.pop();

  // El centinela debe seguir funcionando
  q.push(2);
  CHECK(q.front() == 2);
  CHECK(q.size() == 1);
}