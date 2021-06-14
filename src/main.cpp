#include <iostream>
#include <stdio.h>
#include "Node.hpp"

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





    return 0;
}