#pragma once

#include <vector>
#include <queue>
#include <time.h>
#include <set>
#include <stdio.h>
#include "node.hpp"
#include "state_set.hpp"
#include "state_map.hpp"

using namespace std;

// breadth first search without pruning
node* bfs(node *root);

// breadth first search with pruning
node* bfs_with_pruning(node *root);

node* a_star(node *root, int (*h)(node*));

pair<node*, vector<int>> ida_star(node *root, int (*h)(node*));

void print_nodes_per_height();

void print_time();