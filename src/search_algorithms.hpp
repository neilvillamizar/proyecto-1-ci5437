#pragma once

#include <vector>
#include <queue>
#include <time.h>
#include <set>
#include <stdio.h>
#include "node.hpp"
#include "state_set.hpp"

using namespace std;

// breadth first search without pruning
node* bfs(node *root);

// breadth first search with pruning
node* bfs_with_pruning(node *root);

void print_nodes_per_height();