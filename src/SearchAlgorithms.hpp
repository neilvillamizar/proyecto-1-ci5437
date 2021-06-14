#pragma once

#include <vector>
#include <queue>
#include <time.h>
#include <set>
#include <stdio.h>
#include "Node.hpp"

using namespace std;

// breadth first search without pruning
Node* bfs(Node *root);

// breadth first search with pruning
Node* bfs_with_pruning(Node *root);

void print_nodes_per_height();