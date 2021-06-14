#include <iostream>
#include <stdio.h>
#include <vector>
#include <stdlib.h>

using namespace std;

int R, C;

char tags[4][10] = {"UP", "DOWN", "RIGHT", "LEFT"};
int dr[4] = { -1, 1, 0, 0};
int dc[4] = {0, 0, 1, -1};

bool valid(int r, int c) {
    return min(r, c) >= 0 && r < R && c < C;
}

void print_rules(int r, int c, vector< vector<char> > &mat) {
    mat[r][c] = 'b';

    for (int d = 0; d < 4; ++d) {
        int new_r = r + dr[d], new_c = c + dc[d];
        if (valid(new_r, new_c)) {
            mat[new_r][new_c] = 'X';
            for (int i = 0; i < R; ++i)
                for (int j = 0; j < C; ++j)
                    printf("%c ", mat[i][j]);
            swap(mat[r][c], mat[new_r][new_c]);
            printf("=> ");
            for (int i = 0; i < R; ++i)
                for (int j = 0; j < C; ++j)
                    printf("%c ", mat[i][j]);
            printf("LABEL %s\n", tags[d]);
            swap(mat[r][c], mat[new_r][new_c]);
            mat[new_r][new_c] = '-';
        }
    }

    mat[r][c] = '-';
}



// los valores recibidos deben ser fila y columna
int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("ERROR EN LOS ARGUMENTOS DADOS\n");
        exit(-1);
    }

    R = atoi(argv[1]), C = atoi(argv[2]);
    if (R == 0 || C == 0) {
        printf("ERROR EN LOS ARGUMENTOS DADOS\n");
        exit(-2);
    }

    printf("DOMAIN tile %d\n", R * C);
    printf("b");
    for (int i = 1; i < R * C; ++i) printf(" %d", i);
    printf("\n\n");

    printf("%d", R * C);
    for (int i = 0; i < R * C; ++i) printf(" tile");
    printf("\n\n");


    vector< vector<char> > mat(R, vector<char>(C, '-'));
    for (int i = 0; i < R; ++i)
        for (int j = 0; j < C; ++j)
            print_rules(i, j, mat);
    printf("\n");

    printf("GOAL b");
    for (int i = 1; i < R * C; ++i) printf(" %d", i);
    printf("\n");
}