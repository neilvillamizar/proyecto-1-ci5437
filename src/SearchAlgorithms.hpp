#pragma once

#include <vector>
#include <queue>
#include <time.h>
#include <stdio.h>
#include "Node.hpp"

using namespace std;

// breadth first search without pruning
Node* bfs(Node *root);

void print_nodes_per_height();