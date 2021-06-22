#pragma once

using namespace std;

#include <vector>
#include <string>
#include "node.hpp"

int manhattan_puzzle15(node *u);

int manhattan_puzzle24(node *u);

vector<string> split_state_str(node *u);

void add_abs(abstraction_t *a);

void clear_abs();

void add_state_maps(state_map_t *st_mp);

void clear_state_maps();

int max_heuristic(node *u);

int additive_heuristic(node *u);

void load_heuristics();