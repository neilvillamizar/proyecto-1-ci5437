#include "heuristics.hpp"

using namespace std;

const int MX_STR_SZ = 256;
char S[MX_STR_SZ];

int manhattan_puzzle15(node *u) {
    int dst = 0;
    auto toks = split_state_str(u);

    for (int i = 0; i < toks.size(); ++i) {
        if (toks[i][0] == 'B') continue;

        int k = stoi(toks[i]);
        dst += abs(k / 4 - i / 4) + abs(k % 4 - i % 4);
    }
    return dst;
}

int manhattan_puzzle24(node *u) {
    int dst = 0;
    auto toks = split_state_str(u);

    for (int i = 0; i < toks.size(); ++i) {
        if (toks[i][0] == 'B') continue;

        int k = stoi(toks[i]);
        dst += abs(k / 5 - i / 5) + abs(k % 5 - i % 5);
    }
    return dst;
}

vector<string> split_state_str(node *u) {
    vector<string> ret;

    int sz = sprint_state(S, MX_STR_SZ, u->state);
    string aux;
    for (int i = 0; i < sz; ++i) {
        if (S[i] == ' ') {
            if (!aux.empty()) {
                ret.push_back(aux);
                aux.clear();
            }
        }
        else
            aux += S[i];
    }
    return ret;
}