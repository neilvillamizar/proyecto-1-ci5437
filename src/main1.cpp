#include <iostream>
#include <stdio.h>
#include <vector>
#include "node.hpp"
#include "search_algorithms.hpp"
#include "heuristics.hpp"

using namespace std;

const int MX_INP_SZ = 256;
char INPUT[MX_INP_SZ], OUTPUT[MX_INP_SZ];

int main() {
    node *root = new node;
    printf("De el estado inicial\n");
    if (fgets(INPUT, sizeof(INPUT), stdin) == NULL) {
        printf("Error en el estado dado\n");
        return -1;
    }

    printf("estado que meti xd xd: \n%s\n", INPUT);

    int sz = read_state(INPUT, root->state);
    if (sz < 0) {
        printf("Error en el estado dado\n");
        return -2;
    }

    printf("Que desea hacer?\n");
    printf("1) Bfs sin eliminacion de duplicados\n");
    printf("2) Bfs con eliminacion parcial de duplicados\n");
    printf("3) A* con distancia manhattan\n");
    printf("4) IDA* con distancia manhattan y uso eficiente de memoria\n");
    printf("5) A* con PDBs aditivas\n");
    printf("6) IDA* con PDBs aditivas\n");
    printf("7) A* con maximo de PDBs\n");
    printf("8) IDA* con maximo de PDBs\n");

    int aux;
    if (scanf("%d", &aux) <= 0) {
        printf("Error en el valor dado\n");
        return -3;
    }

    node *goal;
    if (aux == 1)
        goal = bfs(root);
    else if (aux == 2)
        goal = bfs_with_pruning(root);
    else if (aux == 3)
        goal = a_star(root, manhattan_puzzle15);
    else if (aux == 4)
        goal = ida_star(root, manhattan_puzzle15).first;
    else if (aux == 5) {
        load_heuristics();
        goal = a_star(root, additive_heuristic);
    }
    else if (aux == 6) {
        load_heuristics();
        goal = ida_star(root, additive_heuristic).first;
    }
    else if (aux == 7) {
        load_heuristics();
        goal = a_star(root, max_heuristic);
    }
    else if (aux == 8) {
        load_heuristics();
        goal = ida_star(root, max_heuristic).first;
    }

    if (goal == nullptr)
        printf("No se logro llegar a un estado objetivo\n");
    else if (aux != 4 && aux != 6 && aux != 8) {
        sprint_state(OUTPUT, 256, goal->state);
        printf("GOAL : %s\n\n", OUTPUT);
        printf("PATH : \n");
        auto path = goal->get_path();
        for (int i = 0; i < path.size(); ++i) {
            sprint_state(OUTPUT, 256, path[i]->state);
            printf("\t%s\n", OUTPUT);
        }
        printf("\n");
    }
    else if (aux == 4 || aux == 6 || aux == 8) {
        sprint_state(OUTPUT, 256, goal->state);
        printf("GOAL : %s\n\n", OUTPUT);
    }
    print_nodes_per_height();
    print_time();


    return 0;
}