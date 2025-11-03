
#include <iostream>
#include <list>
#include <map>
#include <random>
#include <set>
#include <vector>
using namespace std;

// addVertex, addEdge, deleteVertex, deleteEdge, getNeighbors,
// getNumberVertices, and getNumberEdges

class UndirGraph {
private:
  map<int, list<int>> adjList;
  map<int, pair<float, float>> nodes;

public:
  UndirGraph() {}
  int addVertex(const pair<float, float> &p) {
    int idx = nodes.size();
    adjList[idx].clear();
    nodes[idx] = p;
    return idx;
  }

  void addEdge(int u, int v) {
    adjList[u].push_back(v);
    adjList[v].push_back(u);
  }

  void deleteVertex(int idx) {
    nodes.erase(idx);
    adjList.erase(idx);

    for (auto &p : adjList) {
      auto &neigh = p.second;
      for (auto it = neigh.begin(); it != neigh.end(); it++) {
        if (*it == idx) {
          //   cout << "erasing .." << *it << endl;
          neigh.erase(it);
          break;
        }
      }
    }
  }

  void deleteEdge(int i, int j) {
    adjList[i].remove(j);
    adjList[j].remove(i);
  }

  void print() {
    for (auto k : adjList) {
      auto p = nodes[k.first];
      cout << p.first << " " << p.second << " : ";
      for (auto e : k.second) {
        cout << nodes[e].first << "," << nodes[e].second << " ";
      }
      cout << endl;
    }
  }

  list<int> getNeighbors(int idx) { return adjList[idx]; }

  set<int> getNeighborsAsSet(int idx) {
    set<int> res;
    for (auto e : adjList[idx])
      res.insert(e);
    return res;
  }

  int getNumberVertices() { return adjList.size(); }

  int getNumberEdges() {
    int ctr = 0;
    for (auto p : adjList)
      ctr += p.second.size();
    return ctr / 2;
  }

  pair<float, float> getVertex(int idx) { return nodes[idx]; }

  int size() { return adjList.size(); }
};

class WirelessNetwork {
private:
  UndirGraph G;

public:
  WirelessNetwork(float size = 10, int n = 20) {
    random_device rd;
    mt19937 gen(42);
    uniform_real_distribution<float> dice(0.0, size);

    float x, y;
    for (int i = 0; i < n; i++) {
      x = dice(gen);
      y = dice(gen);
      G.addVertex(pair<float, float>{x, y});
    }

    // G.addVertex(pair<float, float>{.25, 0.25});

    // G.addVertex(pair<float, float>{0, 0});

    // G.addVertex(pair<float, float>{.5, .5});
    // G.addVertex(pair<float, float>{0, .5});
    // G.addVertex(pair<float, float>{.5, 0});

    // G.addVertex(pair<float, float>{0, 1});

    // G.print();
    connect();
  }

  void connect() {
    for (int i = 0; i < G.size() - 1; i++) {
      auto p = G.getVertex(i);
      for (int j = i + 1; j < G.size(); j++) {
        auto q = G.getVertex(j);
        if ((q.first - p.first) * (q.first - p.first) +
                (q.second - p.second) * (q.second - p.second) <=
            1.0) {
          G.addEdge(i, j);
        }
      }
    }
  }

  float dist(pair<float, float> p0, pair<float, float> p1) {
    return (p0.first - p1.first) * (p0.first - p1.first) +
           (p0.second - p1.second) * (p0.second - p1.second);
  }

  void print(const set<int> &s) {
    for (auto e : s) {
      cout << e << " ";
    }
  }

  void trim() {
    for (int i = 0; i < G.size(); i++) {
      set<int> toDel;
      auto uPos = G.getVertex(i);
      // auto ne = G.getNeighbors(i);

      set<int> neighboors_i = G.getNeighborsAsSet(i); //(ne.begin(), ne.end());

      cout << "neightboors of " << i << " are: ";
      for (auto j : neighboors_i) {
        cout << j << " ";
      }
      cout << endl;
      for (auto j : neighboors_i) {
        // cout << j << " ";
        set<int> neighboors_j = G.getNeighborsAsSet(j);
        auto vPos = G.getVertex(j);

        // for (auto f : G.getNeighbors(j))
        //   neighboors_j.insert(f);
        cout << "neightboors of " << j << " are: ";
        for (auto f : neighboors_j) {
          cout << f << " ";
        }
        cout << endl;
        set<int> inter;
        for (auto f : neighboors_i) {
          if (neighboors_j.find(f) != neighboors_j.end() &&
              toDel.find(f) == toDel.end())
            inter.insert(f);
        }
        // cout << "intersection: ";
        // print(inter);

        for (auto f : inter) {
          auto wPos = G.getVertex(f);
          if (dist(uPos, wPos) < dist(uPos, vPos) &&
              dist(vPos, wPos) < dist(uPos, vPos)) {
            // cout << "\ndel: ()" << i << "," << j << ") becuase of " << f
            //  << endl;
            toDel.insert(j);
          }
        }
        cout << endl;
      }
      cout << "\n";
      for (auto e : toDel) {
        G.deleteEdge(i, e);
      }

      // //   auto itpreEnd = li.end();
      // vector<int> toDel;
      // //   itpreEnd--;
      // for (auto it = li.begin(); it != li.end(); it++) {
      //   for (auto jt = li.begin(); jt != li.end(); jt++) {

      //     if (it != jt &&
      //         dist(uPos, G.getVertex(*jt)) < dist(uPos, G.getVertex(*it))
      //         && dist(G.getVertex(*it), G.getVertex(*jt)) <
      //             dist(uPos, G.getVertex(*it))) {
      //       toDel.push_back(*it);
      //       // cout << "deleting edge (" << i << "," << *it << ") because
      //       of
      //       "
      //       //      << *jt << "\n";
      //     }
      //   }
      // }
      // for (auto e : toDel) {
      //   G.deleteEdge(i, e);
      // }
    }
  }

  void trimOLD() {
    for (int i = 0; i < G.size(); i++) {
      auto uPos = G.getVertex(i);
      auto li = G.getNeighbors(i);
      //   auto itpreEnd = li.end();
      vector<int> toDel;
      //   itpreEnd--;
      for (auto it = li.begin(); it != li.end(); it++) {
        for (auto jt = li.begin(); jt != li.end(); jt++) {

          if (it != jt &&
              dist(uPos, G.getVertex(*jt)) < dist(uPos, G.getVertex(*it)) &&
              dist(G.getVertex(*it), G.getVertex(*jt)) <
                  dist(uPos, G.getVertex(*it))) {
            toDel.push_back(*it);
            // cout << "deleting edge (" << i << "," << *it << ") because of "
            //      << *jt << "\n";
          }
        }
      }
      for (auto e : toDel) {
        G.deleteEdge(i, e);
      }
    }
  }

  void trim2() {
    for (int i = 0; i < G.size(); i++) {
      auto uPos = G.getVertex(i);
      auto li = G.getNeighbors(i);
      auto itpreEnd = li.end();
      vector<int> toDel;
      itpreEnd--;
      for (auto it = li.begin(); it != itpreEnd; it++) {
        auto jt = it;
        for (jt++; jt != li.end(); jt++) {
          if (dist(uPos, G.getVertex(*jt)) < dist(uPos, G.getVertex(*it)) &&
              dist(G.getVertex(*it), G.getVertex(*jt)) <
                  dist(uPos, G.getVertex(*it))) {
            toDel.push_back(*it);
          }
        }
      }
      for (auto e : toDel)
        G.deleteEdge(i, e);
    }
  }

  void toDot() {
    cout << "graph G {\n";
    cout << "node [shape=circle, width=0.05, height=0.05 ];\n ";
    // node [
    //     shape=box,      // Use a box shape
    //     width=.20,      // Set fixed width to 1 inch
    //     height=0.25,     // Set fixed height to 0.5 inches
    //     fixedsize=true  // Ensure the size is exactly as specified
    // ];

    for (int i = 0; i < G.size(); i++) {
      auto p = G.getVertex(i);
      cout << i << " [pos = \"" << p.first << "," << p.second
           << "!\" label = \"" << "" << "\"];\n";
    }

    cout << "\n";
    for (int i = 0; i < G.size(); i++) {
      auto p = G.getNeighbors(i);
      for (auto it = p.begin(); it != p.end(); it++) {
        if (*it > i)
          cout << i << " -- " << *it << endl;
      }
    }

    cout << "}\n";
  }
};
