#pragma once

#include <list>
#include <map>
#include "node.hpp"

using namespace std;

class state_set {
public:
    map<uint64_t, list<node*>> mp;

    bool find(node *u);

    void insert(node *u);

    void erase(node *u);
};