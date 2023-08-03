#include <stdio.h>
#include "lib.h"

int inputLen(char *str)
{
    if (!*str)
        return (1);
    return (inputLen(str + 1) + (*str == ' ' ? 1 : 0));
}

int main(int argc, char** argv)
{
    if (argc <= 1)
        return (1);
    char    *input = argv[1];
    board *game_board = isValidInput(inputLen(input), input);
    if (!game_board)
    {
        printf("Please provide valid input.");
        return (1);
    }
    if (solve(game_board))
    {
        printBoard(game_board);
    }
    else {
        printf("Puzzle can not be solved.");
    }
    // printBoard(game_board);
    freeBoard(game_board);
    return (0);
}