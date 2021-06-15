#pragma once

#include <vector>
#include <map>
#include "node.hpp"

using namespace std;

class state_set {
public:
    map<uint64_t, vector<node*>> mp;

    bool find(node *u);

    void insert(node *u);
};