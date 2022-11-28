#include <stdio.h>
#include <stdlib.h>
#include <time.h>
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
    int velkost = rows * columns - (2 * rows);
    char poleZnakov[velkost];

    if (columns > 5){
        velkost = 4 * rows;
        for (int i = 0; i < velkost; ++i) {
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
    }

    if(columns == 3){
        for (int i = 0; i < velkost; ++i) {
            poleZnakov[i] = '+';
        }
    }

    if(columns == 4){
        for (int i = 0; i < velkost; ++i) {
            if (i < velkost/2) {
                poleZnakov[i] = '+';
            }
            else if (i >= velkost/2 && i < velkost) {
                poleZnakov[i] = '*';
            }
        }
    }

    if(columns == 5){
        for (int i = 0; i < velkost; ++i) {
            if (i < velkost/3) {
                poleZnakov[i] = '+';
            }
            else if (i >= velkost/3 && i < 2 * velkost/3) {
                poleZnakov[i] = '*';
            }
            else if (i >= 2 * velkost/3 && i < velkost) {
                poleZnakov[i] = '@';
            }
        }
    }

    poleZnakov[velkost] = '\0';

    //rozhadzanie pola znakov
    for (int i = 0; i < velkost; ++i) {
        int swapIndex = rand() % velkost;
        char temp = poleZnakov[i];
        poleZnakov[i] = poleZnakov[swapIndex];
        poleZnakov[swapIndex] = temp;
    }

    poleZnakov[velkost] = '\0';

    //naplnenie pola
    int pocitadlo = 0;
    for (int i = rows-1; i >= 0; i--) {
        for (int j = 0; j < columns; ++j) {
            if(j != stlpecA && j != stlpecB){
                if(pocitadlo == velkost){
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
        printf("You won!\n");
        return true;
    }
    else{
        return false;
    }
}

void down_possible(const int rows, const int columns, char field[rows][columns], int x, int y){
    //prekonvertovanie na frontend
    x = x - 1;
    y = y - 1;

    int vyska = 0;
    int zalozna = 0;
    char znak = ' ';

    //vybratie znaku zo stlpca
    while(vyska < rows){
        if(field[vyska][x] == ' '){
            vyska++;
        }
        else{
            zalozna = vyska;
            znak = field[vyska][x];
            field[vyska][x] = ' ';
            break;
        }
    }

    //kontrola ci necheme ist na rovnaky stlpec
    if(x == y){
        field[zalozna][x] = znak;
        printf("Cannot move to the same column.\n");
        game_field(rows, columns, field);
    }

        //kontrola ci stlpec nie je prazdny
    else if(vyska == rows && znak == ' '){
        printf("Cannot move, column is empty.\n");
        game_field(rows, columns, field);
    }

        //kontrola ci stlpec nie je plny
    else if(field[0][y] != ' '){
        field[zalozna][x] = znak;
        printf("Cannot move, column is full.\n");
        game_field(rows, columns, field);
    }

    else{
        vyska = 0;
        //hladanie prazdneho pola
        while((vyska != rows - 1) && field[vyska][y] == ' '){
            if(field[vyska][y] != ' '){
                break;
            }
            else{
                vyska ++;
            }
        }

        //spodok stlpca je prazdny
        if(vyska == rows - 1 && field[vyska][y] == ' '){
            field[vyska][y] = znak;
            game_field(rows, columns, field);
        }

        //presun znaku na spravne miesto
        else if(field[vyska][y] == znak){
            field[vyska - 1][y] = znak;
            game_field(rows, columns, field);
        }

        //kontrola nespravneho presunu
        else if(field[vyska][y] != znak){
            field[zalozna][x] = znak;
            printf("Cannot move to column with different character.\n");
            game_field(rows, columns, field);
        }
    }
}

void ball_sort_puzzle(){
    int rows = 6;
    int columns = 8;
    char field[rows][columns];
    int x;
    int y;
    generator(rows, columns, field);
    game_field(rows, columns, field);

    while(check(rows, columns, field) == false){
        printf("Enter what: \n");
        scanf("%d", &x);
        printf("Enter where: \n");
        scanf("%d", &y);

        //kontrola spravneho vstupu
        if(x > columns || x < 0){
            printf("You must enter correct column number.\n");
            printf("Enter what: \n");
            scanf("%d", &x);
            printf("Enter where: \n");
            scanf("%d", &y);
        }

        if(y > columns || y < 0){
            printf("You must enter correct column number.\n");
            printf("Enter what: \n");
            scanf("%d", &x);
            printf("Enter where: \n");
            scanf("%d", &y);
        }

        down_possible(rows, columns, field, x, y);
    }
}