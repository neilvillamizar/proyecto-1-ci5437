#include "node.hpp"

using namespace std;

/*
    constructor:

    creates a new node, reserves space for the state and
    sets all variable to null values
*/
node::node() {
    state = new state_t;
    parent = nullptr;
    action = -1;
    h = g = 0;
}

/*
    destructor:

    frees the space of the state
*/
node::~node() {
    delete state;
}

/*
    create_succ:

    param:
        rule_id = id of the psvn rule

    return:
        pointer to a node, the succesor of the current node

    creates a succesor node of the current one using the given
    rule id
*/
node* node::create_succ(int rule_id) {
    node *succ = new node;
    succ->parent = this;
    succ->h = h + 1;
    succ->g = g + get_fwd_rule_cost(rule_id);
    apply_fwd_rule(rule_id, state, succ->state);
    return succ;
}

/*
    get_path:

    return:
        vector of node pointers representing the path to the current node
*/
vector<node*> node::get_path() {
    vector<node*> ret;
    node *it = this;
    while (it != nullptr) {
        ret.push_back(it);
        it = it->parent;
    }
    reverse(ret.begin(), ret.end());
    return ret;
}