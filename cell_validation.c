#include "lib.h"
#include <stdlib.h>
#include <stdio.h>

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

char    isValidRow(char clue_1, char clue_2, board *row)
{
    char count = 0;
    char tallest = 0;
    char index = 0;
    char size = row->size;
    char current;
    while (index < size)
    {
        current = row->board[index++];
        if (current > tallest)
        {
            count++;
            tallest = current;
            if (current == size)
                break;
        }
    }
    if (count != clue_1)
        return (0);
    count = 0;
    tallest = 0;
    while (index--)
    {
        current = row->board[index++];
        if (current > tallest)
        {
            count++;
            tallest = current;
            if (current == size)
                break;
        }
    }
    if (count != clue_2)
        return (0);
    return (1);
}

char    validatePermutation(char c1, char c2, board *row, board *row_clone, char *permutation)
{
    char    index = 0;
    char    size = row->size;
    char    current;
    while (index < size)
    {
        current = row->board[index];
        if (current == 0)
            row_clone->board[index] = *permutation++;
        else
            row_clone->board[index] = current;
        index++;
    }
    return (isValidRow(c1, c2, row_clone));
}

char    countEmptyCells(board *row, char index)
{
    if (index >= row->size)
        return (0);
    return (countEmptyCells(row, index + 1) + (row->board[index] == 0 ? 1 : 0));
}

char    *newPermutationsArray(board *row, char size)
{
    char    current;
    char    i = 0;
    char    j = 0;
    char    log[127] = {0};
    char    *result = (char*)malloc(sizeof(char) * size + 1);
    if (!result)
        return (0);
    result[size] = 0;
    while (i < row->size)
    {
        current = row->board[i++];
        if (current != 0)
            log[current] = 1;
    }
    i = 1;
    while (i <= row->size)
    {
        if (log[i] == 0)
            result[j++] = i;
        i++;
    }
    return (result);
}

char    canBeSolvedHorizontal(board *game_board, char x, char y, char value)
{
    char    empty_cells;
    char    *permutation;
    char    size = game_board->size;
    board   *row = cloneBoardLinearSection(game_board, y * size + 0, y * size + (size - 1));
    if (!row)
        return (0);
    row->board[x] = value;
    empty_cells = countEmptyCells(row, 0);
    if (empty_cells == 0)
    {
        freeBoard(row);
        return (1);
    }
    permutation = newPermutationsArray(row, empty_cells);
    printf("%i, %i\n", game_board->input->input[3 * game_board->size + y], game_board->input->input[1 * game_board->size + y]);
    // if (!generateAndValidatePemutations(game_board->input->input[3 * game_board->size + y], game_board->input->input[1 * game_board->size + y], row, row_clone, permutation))
    // {
    //     freeBoard(row);
    //     freeBoard(row_clone);
    //     free(permutation);
    //     return (0);
    // }
    printSection(row);
    freeBoard(row);
    free(permutation);
    return (1);
}

char    canBeSolvedVertical(board *game_board, char x, char y, char value)
{
    char    empty_cells;
    char    *permutation;
    char    size = game_board->size;
    board   *row = cloneBoardLinearSection(game_board, 0 * size + x, (game_board->size - 1) * size + (size - 1));
    if (!row)
        return (0);
    row->board[x] = value;
    empty_cells = countEmptyCells(row, 0);
    if (empty_cells == 0)
    {
        freeBoard(row);
        return (1);
    }
    permutation = newPermutationsArray(row, empty_cells);
    printf("%i, %i\n", game_board->input->input[0 * game_board->size + x], game_board->input->input[2 * game_board->size + x]);
    // if (!generateAndValidatePemutations(c1, c2, row, row_clone, permutation))
    // {
    //     freeBoard(row);
    //     freeBoard(row_clone);
    //     free(permutation);
    //     return (0);
    // }
    printSection(row);
    freeBoard(row);
    free(permutation);
    return (1);
}

char    isSolvable(board *game_board, char x, char y, char value)
{
    if (!isUniqueColumn(game_board, x, value) || !isUniqueRow(game_board, y, value))
        return (0);
    if (!canBeSolvedHorizontal(game_board, x, y, value)/* || !canBeSolvedVertical(game_board, x, y, value)*/)
        return (0);
    return (1);
}