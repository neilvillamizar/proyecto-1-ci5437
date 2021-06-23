#include "heuristics.hpp"
#include "utils.hpp"

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


vector<abstraction_t*> abstractions;
vector<state_map_t*> state_maps;

void add_abs(abstraction_t *a) {
    abstractions.push_back(a);
}

void clear_abs() {
    abstractions.clear();
}

void add_state_maps(state_map_t *st_mp) {
    state_maps.push_back(st_mp);
}

void clear_state_maps() {
    state_maps.clear();
}

int max_heuristic(node *u) {
    int n = abstractions.size();
    state_t *aux = new state_t;
    int mx = 0;
    for (int i = 0; i < n; ++i) {
        abstract_state(abstractions[i], u->state, aux);
        int *val = state_map_get(state_maps[i], aux);
        if (val == nullptr)
            return INF();
        mx = max(mx, *val);
        delete val;
    }
    return mx;
}

int additive_heuristic(node *u) {
    int n = abstractions.size();
    state_t *aux = new state_t;
    int sm = 0;
    for (int i = 0; i < n; ++i) {
        abstract_state(abstractions[i], u->state, aux);
        int *val = state_map_get(state_maps[i], aux);
        if (val == nullptr)
            return INF();
        sm += *val;
        delete val;
    }
    return sm;
}

void load_heuristics() {
    string inp;
    char *inp_arr;
    while (true) {
        printf("De el path del archivo con la abstraccion o 0 para no cargar mas\n");
        scanf("%s", S);
        if (strcmp(S, "0") == 0)
            break;

        abstractions.push_back(read_abstraction_from_file(S));

        printf("De el path del archivo pdb\n");
        scanf("%s", S);

        FILE *fp = fopen(S, "r");

        state_maps.push_back(read_state_map(fp));
        fclose(fp);

        if (abstractions.back() == nullptr || state_maps.back() == nullptr) {
            printf("Error en alguno de los 2 paths dados\n");
            abstractions.pop_back();
            state_maps.pop_back();
        }
    }
}