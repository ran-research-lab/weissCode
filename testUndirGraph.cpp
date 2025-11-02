#include "UndirGraph.hpp"
#include <vector>

using namespace std;

int main() {
  UndirGraph G;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      G.addVertex(pair<float, float>{i, j});
    }
  }
  G.addEdge(0, 10);
  G.addEdge(5, 0);
  G.addEdge(2, 4);
  //   G.print();
  //   auto li = G.getNeighbors(0);
  //   for (auto p : li) {
  //     cout << p << endl;
  //   }
  //   cout << G.getNumberVertices() << "\n";
  //   cout << G.getNumberEdges() << "\n";
  //   cout << "=====\n";
  //   G.deleteVertex(10);
  //   G.print();
  //   cout << "=====\n";
  //   G.deleteVertex(2);
  //   G.print();

  WirelessNetwork W(10, 500);
  W.trim();
  W.toDot();
}