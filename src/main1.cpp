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


    int sz = read_state(INPUT, root->state);
    if (sz < 0) {
        printf("Error en el estado dado\n");
        return -2;
    }

    printf("Que desea hacer?\n");
    printf("1) Bfs sin eliminacion de duplicados\n");
    printf("2) Bfs con eliminacion parcial de duplicados\n");
    printf("3) A* con distancia manhattan\n");
    printf("4) IDA* con uso eficiente de memoria\n");

    int aux;
    if (scanf("%d", &aux) <= 0) {
        printf("Error en el valor dado\n");
        return -3;
    }

    node *goal;
    pair<state_t*, vector<int>> ida_goal;
    if (aux == 1)
        goal = bfs(root);
    else if (aux == 2)
        goal = bfs_with_pruning(root);
    else if (aux == 3)
        goal = a_star(root, manhattan_puzzle15);
    else if (aux == 4)
        ida_goal = ida_star(root->state, manhattan_puzzle15);

    if (goal == nullptr || ida_goal.first == nullptr)
        printf("No se logro llegar a un estado objetivo\n");
    else if (aux <= 3) {
        sprint_state(OUTPUT, 256, goal->state);
        printf("OBJETIVO : %s\n\n", OUTPUT);
        printf("CAMINO : \n");
        auto path = goal->get_path();
        for (int i = 0; i < path.size(); ++i) {
            sprint_state(OUTPUT, 256, path[i]->state);
            printf("\t%s\n", OUTPUT);
        }
        printf("\n");
    }
    else {
        sprint_state(OUTPUT, 256, ida_goal.first);
        printf("OBJETIVO : %s\n\n", OUTPUT);
    }
    print_nodes_per_height();
    return 0;
}