#include <stdio.h>
#include <stdlib.h>
#include "ballsortpuzzle.h"

int main() {
    int rows = 7;
    int columns = 5;
    char field[rows][columns];

    generator(rows, columns, field);
    game_field(rows, columns, field);
    check(rows, columns, field);

    /*
    int x;
    int y;
    while (true) {
    scanf("%d", &x);
    scanf("%d", &y);
    down_possible(rows, columns, field, x, y);
    game_field(rows, columns, field);
    }*/

    return 0;
}