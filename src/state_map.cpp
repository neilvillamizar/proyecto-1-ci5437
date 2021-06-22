#include "state_map.hpp"
#include "utils.hpp"

using namespace std;


/*
    insert:

    param:
        u = pointer to a node
        c = cost of the node

    inserts the given node with the given cost, if there is already a
    node with the same state it changes it with the new one
*/
void state_map::insert(node *u, int c) {
    uint64_t hash = hash_state(u->state);
    for (auto it = table[hash].begin(); it != table[hash].end(); it++)
        if (compare_states(u->state, it->first->state) == 0) {
            it->first = u;
            it->second = c;
            return;
        }
    table[hash].push_back({u, c});
}

/*
    erase:

    param:
        u = pointer to a node

    deletes the given node from the hash table
*/
void state_map::erase(node *u) {
    uint64_t hash = hash_state(u->state);
    for (auto it = table[hash].begin(); it != table[hash].end(); it++)
        if (compare_states(u->state, it->first->state) == 0) {
            table[hash].erase(it);
            return;
        }
}

/*
    find:

    param:
        u = pointer to a node

    returns true if there exists a node with the same state
    as the given one
*/
bool state_map::find(node *u) {
    uint64_t hash = hash_state(u->state);
    for (auto it = table[hash].begin(); it != table[hash].end(); it++)
        if (compare_states(u->state, it->first->state) == 0)
            return true;
    return false;
}

/*
    get_cost:

    param:
        u = pointer to a node

    returns the cost of the given node or INF if it doesnt exist
*/
int state_map::get_cost(node *u) {
    uint64_t hash = hash_state(u->state);
    for (auto it = table[hash].begin(); it != table[hash].end(); it++)
        if (compare_states(u->state, it->first->state) == 0)
            return it->second;
    return INF();
}