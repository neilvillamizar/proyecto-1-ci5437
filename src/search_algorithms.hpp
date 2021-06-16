#pragma once

#include <vector>
#include <queue>
#include <time.h>
#include <set>
#include <stdio.h>
#include <iostream>
#include "node.hpp"
#include "state_set.hpp"
#include "state_map.hpp"

using namespace std;

// breadth first search without pruning
node* bfs(node *root);

// breadth first search with pruning
node* bfs_with_pruning(node *root);

node* a_star(node *root, int (*h)(state_t*));

pair<state_t*, vector<int>> ida_star(state_t *root, int (*h)(state_t*));

void print_nodes_per_height();
