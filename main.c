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
    {
        printf("Please provide input.");
        return (1);
    }
    char    *input = argv[1];
    board   *game_board;
    int len = inputLen(input);
    if (len == 1)
        game_board = parseFile(input);
    else
        game_board = isValidInput(inputLen(input), input);
    if (!game_board)
    {
        printf("Please provide valid input.");
        return (1);
    }
    if (solve(game_board))
    {
        printBoard(game_board, 0);
    }
    else {
        printf("Puzzle can not be solved.");
    }
    freeBoard(game_board);
    return (0);
}