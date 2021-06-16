#include "state_set.hpp"

using namespace std;

/*
    find:

    param:
        u = pointer to a node

    returns true if there exists a node with the same state
    as the given one
*/
bool state_set::find(node *u) {
    uint64_t hash = hash_state(u->state);
    for (auto &v : mp[hash]) {
        if (compare_states(u->state, v->state) == 0)
            return true;
    }
    return false;
}

/*
    insert:

    param:
        u = pointer to a node

    inserts the given node in the set if it doesnt exist already
*/
void state_set::insert(node *u) {
    if (find(u)) return;
    mp[hash_state(u->state)].push_back(u);
}
