#pragma once

#include <vector>
#include <queue>
#include <time.h>
#include "Node.hpp"

using namespace std;

vector<int> NODES_PER_HEIGHT;

clock_t START, END;
double MAX_TIME = 15 * 60;


// breadth first search without pruning
Node* bfs(Node *root);