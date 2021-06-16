#include <iostream>
#include <stdio.h>
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


    int sz = read_state(INPUT, root->state);
    if (sz < 0) {
        printf("Error en el estado dado\n");
        return -2;
    }

    printf("Que desea hacer?\n");
    printf("1) Bfs sin eliminacion de duplicados\n");
    printf("2) Bfs con eliminacion parcial de duplicados\n");
    printf("3) A* con distancia manhattan\n");

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

    if (goal == nullptr)
        printf("No se logro llegar a un estado objetivo\n");
    else {
        sprint_state(OUTPUT, 256, goal->state);
        printf("GOAL : %s\n", OUTPUT);
    }
    print_nodes_per_height();



    return 0;
}