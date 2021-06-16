#pragma once

using namespace std;

#include <list>
#include <map>
#include "node.hpp"

class state_map
{
    map<uint64_t, list<pair<node*, int>>> table;
public:
    void insert(node *u, int c);

    void erase(node *u);

    bool find(node *u);

    int get_cost(node *u);
};