#include "node.hpp"

using namespace std;

node::node() {
    state = new state_t;
    parent = NULL;
    action = -1;
    h = g = 0;
}

node::~node() {
    delete state;
}

node* node::create_succ(int rule_id) {
    node *succ = new node;
    succ->parent = this;
    succ->h = h + 1;
    succ->g = g + get_fwd_rule_cost(rule_id);
    apply_fwd_rule(rule_id, state, succ->state);
    return succ;
}

