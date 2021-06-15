#pragma once

using namespace std;

class node {
public:
    state_t *state; // psvn state
    node *parent; // node father
    int action; // action that generated this node
    int h; // height
    int g; // cost

    node();

    ~node();

    node* create_succ(int rule_id);
};