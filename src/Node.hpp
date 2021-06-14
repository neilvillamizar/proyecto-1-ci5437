#pragma once

class Node
{
public:
    state_t *state; // estado de psvn
    Node *parent; // nodo padre
    int action; // accion que genero este nodo
    int h; // altura
    int g; // costo de llegar al nodo

    Node();

    ~Node();

    Node create_succ(int rule_id);
};

