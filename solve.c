#include "lib.h"
#include <stdio.h>

char    findEmptyCellPosition(board *game_board, char *x, char *y)
{
    char    *board_data = game_board->board;
    int size = game_board->size;
    char    ix;
    char    iy = 0;
    while (iy < size)
    {
        ix = 0;
        while (ix < size)
        {
            if (board_data[iy * size + ix] == 0)
            {
                *x = ix;
                *y = iy;
                return (1);
            }
            ix++;
        }
        iy++;
    }
    return (0);
}

char    solve(board *game_board)
{
    char x;
    char y;
    char index = 1;
    char    size = game_board->size;
    if (!findEmptyCellPosition(game_board, &x, &y))
        return (1);
    while (index <= size)
    {
        if (isSolvable(game_board, x, y, index))
        {
            game_board->board[y * size + x] = index;
            if (solve(game_board))
                return (1);
            else
            {
                game_board->board[y * size + x] = 0;
            }
        }
        index++;
    }
    return (0);
}