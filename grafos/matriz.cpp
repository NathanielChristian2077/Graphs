#include <iostream>
#include <vector>
using namespace std;
using matrix = std::vector<std::vector<int>>;

class Grafo {
  private:
    int ordem;
    int numA;
    std::array<int, ordem> V;
    std::array<int, numA> A;
  public:
    Grafo(int ordem, int numA){
      this->ordem = ordem;
      this->numA = numA;
    }

    int getOrdem(){ return this->ordem };
    void setOrdem(int o){ this->ordem = o };
    int getNumA(){ return this->numA };
    void setNumA(int n_a){ this->numA = n_a };

}
