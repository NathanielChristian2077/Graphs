#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <unordered_map>

using namespace std;

struct Vertice {
  std::string nome;
};

struct Aresta {
  std::string origem;
  std::string destino;
};

class Grafo {
  private:
    std::vector<Vertice> V;
    std::vector<Aresta> A;
  public:
    void addV(const std::string& nome){ V.push_back({ nome }); }
    void addA(const std::string& u, const std::string& v){ A.push_back({u, v}); }

    void print() const {
      std::cout << "-----V-----\n";
      for (size_t i = 0; i < V.size(); ++i) {
        std::cout << i << ": " << V[i].nome << "\n";
      }
      std::cout << "-----------\n";

      std::cout << "\n-----A-----\n";
      for (size_t i = 0; i < A.size(); ++i) {
        std::cout << i << ": (" << A[i].origem << ", " << A[i].destino << ")\n";
      }
      std::cout << "-----------\n";
    }

    void mat_adj() const {
      std::unordered_map<std::string, int> pos;
      std::vector<std::vector<int>> adj(V.size(), std::vector<int>(V.size(), 0));

      for (int i = 0; i < V.size(); ++i) {
        pos[V[i].nome] = i;
      }

      for (const Aresta& a : A) {
        int u = pos[a.origem];
        int v = pos[a.destino];
        adj[u][v] += 1;
        if (u != v && adj[v][u] < 1) // Verificar orientação
        {
          adj[v][u] += 1;
        }
        
      }
      
      std::cout << "\nMatriz Adjacencia";
      for (int i = 0; i < V.size(); ++i) {
         std::cout << "\n";
        for(int j = 0; j < V.size(); ++j) {
          std::cout << adj[i][j] << " ";
        }
      }
      std::cout << "\n\n";
    }

    void mat_inc() {
      std::vector<std::vector<int>> inc(V.size(), std::vector<int>(A.size(), 0));

      
    }
};

int main() {
  Grafo g;

  g.addV("A");
  g.addV("B");
  g.addV("C");
  g.addV("D");

  g.addA("A", "B");
  g.addA("B", "C");
  g.addA("C", "D");
  g.addA("D", "A");
  g.addA("D", "B");

  g.print();

  g.mat_adj();
}
