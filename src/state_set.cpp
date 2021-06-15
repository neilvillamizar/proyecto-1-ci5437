#include "state_set.hpp"

using namespace std;

bool state_set::find(node *u) {
    uint64_t hash = hash_state(u->state);
    for (auto &v : mp[hash]) {
        if (compare_states(u->state, v->state) == 0)
            return true;
    }
    return false;
}

void state_set::insert(node *u) {
    if (find(u)) return;
    mp[hash_state(u->state)].push_back(u);
}
