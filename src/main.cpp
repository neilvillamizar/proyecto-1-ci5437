#include <iostream>
#include <stdio.h>
#include "Node.hpp"
#include "SearchAlgorithms.hpp"

using namespace std;

const int MX_INP_SZ = 256;

char INPUT[MX_INP_SZ], OUTPUT[MX_INP_SZ];

int main() {
    Node *root = new Node;
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

    Node *goal = bfs(root);

    if (goal == nullptr)
        printf("No se logro llegar a un estado objetivo\n");
    else {
        sprint_state(OUTPUT, 256, goal->state);
        printf("GOAL : %s\n", OUTPUT);

        print_nodes_per_height();
    }



    return 0;
}