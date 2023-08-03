#include "lib.h"

char    isUniqueRow(board *game_board, char y, char value)
{
    char    x = 0;
    char    size = game_board->size;
    while (x < size)
        if (game_board->board[y * size + x++] == value)
            return (0);
    return (1);
}

char    isUniqueColumn(board *game_board, char x, char value)
{
    char    y = 0;
    char    size = game_board->size;
    while (y < size)
        if (game_board->board[y++ * size + x] == value)
            return (0);
    return (1);
}

char    isSolvable(board *game_board, char x, char y, char value)
{
    if (!isUniqueColumn(game_board, x, value) || !isUniqueRow(game_board, y, value))
        return (0);
    return (1);
}