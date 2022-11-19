#include <stdio.h>
#include <stdlib.h>
#include "ballsortpuzzle.h"

int main(){
    int rows = 4;
    int columns = 6;
    char field[rows][columns];

    generator(rows, columns, field);
    game_field(rows, columns, field);

    return 0;
}