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
    if (clue_1 != 0)
    {
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
    }
    if (clue_2 != 0)
    {
        index = row->size;
        count = 0;
        tallest = 0;
        while (index--)
        {
            current = row->board[index];
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
    }
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

char    generateAndValidatePemutations(board *row, board *row_clone, char *permutation, char size, char c1, char c2)
{
    char    i = 0;
    char    temp;
    if (size == 1)
        return (validatePermutation(c1, c2, row, row_clone, permutation));
    while (i < size)
    {
        if (generateAndValidatePemutations(row, row_clone, permutation, size - 1, c1, c2))
            return (1);
        if (size % 2 == 1)
        {
            temp = permutation[0];
            permutation[0] = permutation[size - 1];
            permutation[size - 1] = temp;
        }
        else
        {
            temp = permutation[i];
            permutation[i] = permutation[size - 1];
            permutation[size - 1] = temp;
        }
        i++;
    }
    return (0);
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
    char    result;
    char    empty_cells;
    char    *permutation;
    char    size = game_board->size;
    board   *row = cloneBoardLinearSection(game_board, y * size + 0, y * size + (size - 1));
    if (!row)
        return (0);
    board   *row_clone = newSection(row->size);
    if (!row_clone)
        return (0);
    row->board[x] = value;
    empty_cells = countEmptyCells(row, 0);
    if (empty_cells == 0)
    {
        freeBoard(row_clone);
        freeBoard(row);
        return (1);
    }
    permutation = newPermutationsArray(row, empty_cells);
    result = generateAndValidatePemutations(
        row,
        row_clone,
        permutation,
        empty_cells,
        game_board->input->input[3 * game_board->size + y],
        game_board->input->input[1 * game_board->size + y]);
    freeBoard(row_clone);
    freeBoard(row);
    free(permutation);
    return (result);
}

char    canBeSolvedVertical(board *game_board, char x, char y, char value)
{
    char    result;
    char    empty_cells;
    char    *permutation;
    char    size = game_board->size;
    board   *row = cloneBoardLinearSection(game_board, 0 * size + x, (game_board->size - 1) * size + x);
    if (!row)
        return (0);
    board   *row_clone = newSection(row->size);
    if (!row_clone)
        return (0);
    row->board[y] = value;
    empty_cells = countEmptyCells(row, 0);
    if (empty_cells == 0)
    {
        freeBoard(row_clone);
        freeBoard(row);
        return (1);
    }
    permutation = newPermutationsArray(row, empty_cells);
    result = generateAndValidatePemutations(
        row,
        row_clone,
        permutation,
        empty_cells,
        game_board->input->input[0 * game_board->size + x],
        game_board->input->input[2 * game_board->size + x]);
    freeBoard(row_clone);
    freeBoard(row);
    free(permutation);
    return (result);
}

char    isSolvable(board *game_board, char x, char y, char value)
{
    if (!isUniqueColumn(game_board, x, value) || !isUniqueRow(game_board, y, value))
        return (0);
    if (!canBeSolvedHorizontal(game_board, x, y, value) || !canBeSolvedVertical(game_board, x, y, value))
        return (0);
    return (1);
}