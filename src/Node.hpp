#pragma once

using namespace std;

class Node
{
public:
    state_t *state; // psvn state
    Node *parent; // node father
    int action; // action that generated this node
    int h; // height
    int g; // cost

    Node();

    ~Node();

    Node* create_succ(int rule_id);
};

