#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "ballsortpuzzle.h"

void generator(const int rows, const int columns, char field[rows][columns]) {
    srand(time(0));

    //prazdne pole
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            field[i][j] = ' ';
        }
    }

    //generovanie dvoch vynechanych stlpcov
    int stlpecA = rand() % (columns - 1 + 1 - 0) + 0;
    int stlpecB = stlpecA;

    while (stlpecA == stlpecB) {
        stlpecB = rand() % (columns - 1 + 1 - 0) + 0;
    }

    //generovanie pola znakov
    char poleZnakov[4 * rows];

    for (int i = 0; i < 4 * rows; ++i) {
        if (i < rows) {
            poleZnakov[i] = '+';
        }
        else if (i >= rows && i < 2 * rows) {
            poleZnakov[i] = '*';
        }
        else if (i >= 2 * rows && i < 3 * rows) {
            poleZnakov[i] = '@';
        }
        else if (i >= 3 * rows && i < 4 * rows) {
            poleZnakov[i] = '^';
        }
    }

    poleZnakov[4 * rows] = '\0';

    //rozhadzanie pola znakov
    for (int i = 0; i < strlen(poleZnakov); ++i) {
        int swapIndex = rand() % strlen(poleZnakov);
        char temp = poleZnakov[i];
        poleZnakov[i] = poleZnakov[swapIndex];
        poleZnakov[swapIndex] = temp;
    }

    //naplnenie pola
    int pocitadlo = 0;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            if(j != stlpecA && j != stlpecB){
                field[i][j] = poleZnakov[pocitadlo];
                pocitadlo++;
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

bool check(const int rows, const int columns, char field[rows][columns]){
    //vymena riadkov za stlpce
    char otocene[columns][rows];
    for (int i = 0; i < columns; ++i) {
        for (int j = 0; j < rows; ++j) {
            otocene[i][j] = field[j][i];
        }
    }

    if(rows * rows == rows){
        printf("true\n");
        return true;
    }
    else{
        printf("false\n");
        return false;
    }
}

