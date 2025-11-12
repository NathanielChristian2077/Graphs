#include <iostream>
#include <string>
using namespace std;

void analyze(const string& s, int freq[256], bool seq[256]) {
    for (int i = 0; i < 256; ++i) { freq[i] = 0; seq[i] = false; }
    unsigned char prev = 0;
    bool hasPrev = false;
    for (unsigned char c : s) {
        if (hasPrev && c == prev) seq[c] = true;
        ++freq[c];
        prev = c;
        hasPrev = true;
    }
}

bool getReps(const string& s) {
    int freq[256]; bool seq_[256];
    analyze(s, freq, seq_);
    for (int i = 0; i < 256; ++i) if (freq[i] >= 2) return true;
    return false;
}

bool getSeqReps(const string& s) {
    int freq[256]; bool seq_[256];
    analyze(s, freq, seq_);
    for (int i = 0; i < 256; ++i) if (seq_[i]) return true;
    return false;
}

void printSetReps(const int freq[256]) {
    bool first = true;
    for (int i = 0; i < 256; ++i) if (freq[i] >= 2) {
        if (!first) cout << ", ";
        cout << static_cast<char>(i);
        first = false;
    }
}

void printSetSeq(const bool seq[256]) {
    bool first = true;
    for (int i = 0; i < 256; ++i) if (seq[i]) {
        if (!first) cout << ", ";
        cout << static_cast<char>(i);
        first = false;
    }
}

void printWord(const string& s) {
    int freq[256]; bool seq[256];
    analyze(s, freq, seq);

    bool temReps = false, temSeq = false;
    for (int i = 0; i < 256; ++i) { temReps |= (freq[i] >= 2); temSeq |= seq[i]; }

    if (!temReps && !temSeq) {
        cout << s << " - não há caracteres repetidos, tamanho: " << s.size() << "\n";
        return;
    }

    cout << s << " - ";
    if (temReps) {
        cout << "há caracteres repetidos (";
        printSetReps(freq);
        cout << ")";
        if (temSeq) cout << ", ";
    } else {
        cout << "não há caracteres repetidos";
        if (temSeq) cout << ", ";
    }

    if (temSeq) {
        cout << "há caracteres repetidos em sequência (";
        printSetSeq(seq);
        cout << ")";
    } else if (!temReps) {
        cout << "não há caracteres repetidos em sequência";
    }

    cout << ", tamanho: " << s.size() << "\n";
}

int main() {
    printWord("casa");
    printWord("cassa");
    printWord("carro1233007");
    printWord("abc012345");
    printWord("!!??!!");
}
