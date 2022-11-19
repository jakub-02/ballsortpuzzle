#include <stdio.h>
#include <stdlib.h> 
#include "ballsortpuzzle.h"

void generator(const int rows, const int columns, char field[rows][columns]){
    //prazdne pole
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            field[i][j] = ' ';
        }
    }
}

void game_field(const int rows, const int columns, char field[rows][columns]){
    //uzatvorenie stlpcov zhora
    printf("  |");
    for (int j = 0; j < columns; ++j) {
        printf("***|");
    }
    printf("\n");

    //vypis pola s oznacenim riadkov
    for (int i = 0; i < rows; ++i) {
        printf("%d |", i+1);
        for (int j = 0; j < columns; ++j) {
            printf(" %c |", field[i][j]);
        }
        printf("\n");
    }

    //uzatvorenie stlpcov zdola
    printf("  |");
    for (int j = 0; j < columns; ++j) {
        printf("***|");
    }
    printf("\n");

    //ocislovanie stlpcov
    printf("  ");
    for (int j = 0; j < columns; ++j) {
        printf("  %d ", j+1);
    }
    printf("\n");
}

