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
    for (int i = rows; i >= 0; i--) {
        for (int j = 0; j < columns; ++j) {
            if(j != stlpecA && j != stlpecB){
                if(pocitadlo >= sizeof(poleZnakov)){
                    field[i][j] = ' ';
                }
                else{
                    field[i][j] = poleZnakov[pocitadlo];
                    pocitadlo++;
                }
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
    //testovacie pole nacita prvky z prveho riadku
    char test[columns];
    for (int i = 0; i < columns; ++i) {
        test[i] = field[0][i];
    }
    test[columns] = '\0';

    //zistovanie rovnosti znakov v stlpci
    int pocitadlo = 0;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            if(field[i][j] == test[j]){
                pocitadlo++;
            }
        }
    }

    if(pocitadlo == rows * columns){
        return true;
    }
    else{
        return false;
    }
}
/*
void down_possible(const int rows, const int columns, char field[rows][columns], int x, int y){
    //prekonvertovanie na frontend
    x = x - 1;
    y = y - 1;

    //premiestnenie
    field[x][y] = field[0][x];
    field[0][x] = ' ';

}*/
