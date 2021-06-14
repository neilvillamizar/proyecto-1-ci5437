#include "Node.hpp"

using namespace std;

Node::Node() {
    state = new state_t;
    parent = NULL;
    action = -1;
    h = g = 0;
}

Node::~Node() {
    delete state;
}

Node* Node::create_succ(int rule_id) {
    Node *succ = new Node;
    succ->parent = this;
    succ->h = h + 1;
    succ->g = g + get_fwd_rule_cost(rule_id);
    apply_fwd_rule(rule_id, state, succ->state);
    return succ;
}

