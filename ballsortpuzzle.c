#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ballsortpuzzle.h"

void generator(const int rows, const int columns, char field[rows][columns]){
    srand(time(0));
    //prazdne pole
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            field[i][j] = ' ';
        }
    }

    //generovanie dvoch vynechanych stlpcov
    int stlpecA = rand() % (columns-1 + 1 - 0) + 0;
    int stlpecB = stlpecA;

    while(stlpecA == stlpecB){
        stlpecB = rand() % (columns-1 + 1 - 0) + 0;
    }

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            if(j != stlpecA && j != stlpecB){
                field[i][j] = '*';
            }
        }
    }

}

void game_field(const int rows, const int columns, char field[rows][columns]){
    //uzatvorenie stlpcov zhora
    printf("    ,");
    for (int j = 0; j < columns; ++j) {
        printf("~~~,");
    }
    printf("\n");

    //vypis pola s oznacenim riadkov
    for (int i = 0; i < rows; ++i) {
        printf("[%d] |", i+1);
        for (int j = 0; j < columns; ++j) {
            printf(" %c |", field[i][j]);
        }
        printf("\n");
    }

    //uzatvorenie stlpcov zdola
    printf("    `");
    for (int j = 0; j < columns; ++j) {
        printf("~~~`");
    }
    printf("\n");

    //ocislovanie stlpcov
    printf("    ");
    for (int j = 0; j < columns; ++j) {
        printf(" [%d]", j+1);
    }
    printf("\n");
}

