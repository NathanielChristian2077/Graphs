#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

struct Vertice {
    string nome;
};
struct Aresta {
    string u, v;
};

class Grafo {
private:
    vector<Vertice> V;
    vector<Aresta>  A;

    unordered_map<string,int> make_pos() const {
        unordered_map<string,int> pos;
        pos.reserve(V.size()*2);
        for (size_t i = 0; i < V.size(); ++i) pos[V[i].nome] = static_cast<int>(i);
        return pos;
    }

    static string key_undir(const string& a, const string& b) {
        return (a <= b) ? (a + "|" + b) : (b + "|" + a);
    }
    static string key_dir(const string& a, const string& b) {
        return a + "->" + b;
    }

public:
    void addV(const string& nome) { V.push_back({nome}); }
    void addA(const string& u, const string& v) { A.push_back({u,v}); }

    bool eh_orientado() const {
        unordered_map<string,int> cnt;
        cnt.reserve(A.size()*2);
        for (const auto& e : A) if (e.u != e.v) cnt[key_dir(e.u,e.v)]++;
        for (const auto& kv : cnt) {
            const string& k = kv.first;
            int c = kv.second;
            size_t p = k.find("->");
            string u = k.substr(0, p), v = k.substr(p+2);
            int rv = cnt[key_dir(v,u)];
            if (c != rv) return true;
        }
        return false;
    }

    bool laco() const {
        for (const auto& e : A) if (e.u == e.v) return true;
        return false;
    }

    bool multiarestas(bool orientado) const {
        unordered_map<string,int> cnt;
        cnt.reserve(A.size()*2);
        for (const auto& e : A) {
            string k = orientado ? key_dir(e.u,e.v) : key_undir(e.u,e.v);
            if (++cnt[k] > 1) return true;
        }
        return false;
    }

    bool simples(bool orientado) const {
        return !laco() && !multiarestas(orientado);
    }

    vector<int> graus_nao_dir() const {
        auto pos = make_pos();
        vector<int> g(V.size(), 0);
        for (const auto& e : A) {
            int u = pos.at(e.u), v = pos.at(e.v);
            if (u == v) g[u] += 2; else { g[u]++; g[v]++; }
        }
        return g;
    }
    pair<vector<int>,vector<int>> graus_dir() const {
        auto pos = make_pos();
        vector<int> out(V.size(), 0), in(V.size(), 0);
        for (const auto& e : A) { out[pos.at(e.u)]++; in[pos.at(e.v)]++; }
        return {out,in};
    }

    vector<vector<long long>> mat_adj(bool orientado) const {
        auto pos = make_pos();
        size_t n = V.size();
        vector<vector<long long>> adj(n, vector<long long>(n, 0));
        for (const auto& e : A) {
            int u = pos.at(e.u), v = pos.at(e.v);
            adj[u][v] += 1;
            if (!orientado && u != v) adj[v][u] += 1;
        }
        return adj;
    }

    vector<vector<long long>> mat_inc(bool orientado) const {
        auto pos = make_pos();
        size_t n = V.size(), m = A.size();
        vector<vector<long long>> inc(n, vector<long long>(m, 0));
        for (size_t j = 0; j < m; ++j) {
            int u = pos.at(A[j].u), v = pos.at(A[j].v);
            if (!orientado) {
                if (u == v) inc[u][j] = 2;
                else { inc[u][j] = 1; inc[v][j] = 1; }
            } else {
                if (u != v) { inc[u][j] = -1; inc[v][j] = +1; }
            }
        }
        return inc;
    }

    void printVA() const {
        cout << "----- Vértices -----\n";
        for (size_t i = 0; i < V.size(); ++i) cout << i << ": " << V[i].nome << "\n";
        cout << "--------------------\n\n";

        cout << "----- Arestas ------\n";
        for (size_t i = 0; i < A.size(); ++i) cout << "e" << i << ": (" << A[i].u << ", " << A[i].v << ")\n";
        cout << "--------------------\n\n";
    }

    void print_mat_adj(const vector<vector<long long>>& adj) const {
        size_t n = V.size();
        cout << "Matriz de Adjacência\n     ";
        for (size_t j = 0; j < n; ++j) cout << setw(4) << V[j].nome;
        cout << "\n";
        for (size_t i = 0; i < n; ++i) {
            cout << setw(4) << V[i].nome;
            for (size_t j = 0; j < n; ++j) cout << setw(4) << adj[i][j];
            cout << "\n";
        }
        cout << "\n";
    }

    void print_mat_inc(const vector<vector<long long>>& inc) const {
        size_t n = V.size(), m = A.size();
        cout << "Matriz de Incidência\n     ";
        for (size_t j = 0; j < m; ++j) cout << setw(5) << ("e"+to_string(j));
        cout << "\n";
        for (size_t i = 0; i < n; ++i) {
            cout << setw(4) << V[i].nome;
            for (size_t j = 0; j < m; ++j) cout << setw(5) << inc[i][j];
            cout << "\n";
        }
        cout << "\n";
    }

    void relatorio() const {
        if (V.empty()) { cout << "Grafo vazio.\n"; return; }

        bool orientado = eh_orientado();
        bool _laco = laco();
        bool multi = multiarestas(orientado);
        bool _simples = simples(orientado);

        cout << "=== Grafo ===\n";
        cout << "Vértices: " << V.size() << "  Arestas: " << A.size() << "\n";
        cout << "Orientado: " << (orientado ? "sim" : "nao") << "\n";
        cout << "Tem laço: " << (_laco ? "sim" : "nao") << "\n";
        cout << "Tem arestas múltiplas: " << (multi ? "sim" : "nao") << "\n";
        cout << "É simples: " << (_simples ? "sim" : "nao") << "\n\n";

        if (!orientado) {
            auto g = graus_nao_dir();
            cout << "Grau dos vértices (não orientado):\n";
            for (size_t i = 0; i < V.size(); ++i)
                cout << "  " << V[i].nome << ": " << g[i] << "\n";
        } else {
            auto gr = graus_dir();
            auto& outd = gr.first; auto& ind = gr.second;
            cout << "Graus (orientado):\n";
            for (size_t i = 0; i < V.size(); ++i)
                cout << "  " << V[i].nome << ": out=" << outd[i] << " in=" << ind[i] << "\n";
        }
        cout << "\n";

        printVA();

        auto adj = mat_adj(orientado);
        print_mat_adj(adj);

        auto inc = mat_inc(orientado);
        print_mat_inc(inc);
    }
};

int main() {
    Grafo g;

    g.addV("A");
    g.addV("B");
    g.addV("C");
    g.addV("D");

    g.addA("A","B");
    g.addA("B","C");
    g.addA("C","D");
    g.addA("D","A");
    g.addA("D","B");
    // para "não orientado":
    // g.addA("B","A");
    // g.addA("C","B");
    // g.addA("D","C");
    // g.addA("A","D");
    // g.addA("B","D");

    g.relatorio();

    return 0;
}
