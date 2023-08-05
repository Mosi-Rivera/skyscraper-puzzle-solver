#include <stdio.h>
#include <stdlib.h>
#include "lib.h"

board   *newSection(char size)
{
    int i = 0;
    char board_size = size;
    board* result = (board*)malloc(sizeof(board));
    if (!result)
        return (0);
    result->input = 0;
    result->board = (char *)malloc(sizeof(char) * board_size);
    if (!result->board)
    {
        free(result);
        return (0);
    }
    result->size = size;
    while (i < board_size)
        result->board[i++] = 0;
    return (result);
}

board   *newBoard(char size)
{
    board   *result = newSection(size * size);
    result->size = size;
    return result;
}

void    freeBoard(board *board_data)
{
    if (board_data->input)
        free(board_data->input);
    if (board_data->board)
        free(board_data->board);
    free(board_data);
}

board   *cloneBoardLinearSection(board* board_data, char start, char end)
{
    char    i = 0;
    char    j = 0;
    char    section_size = end + 1 - start;
    board    *section;
    if (section_size > board_data->size)
    {
        section_size = section_size / board_data->size + 1;
        section = newSection(section_size);
        if (!section)
            return (0);
        while (i < section_size)
            section->board[j++] = board_data->board[start + board_data->size * i++];
    }
    else
    {
        section = newSection(section_size);
        if (!section)
            return (0);
        while (i < section_size)
            section->board[j++] = board_data->board[start + i++];
    }
    return (section);
}

void    printSection(board *section)
{
    char i = 0;
    char limit = section->size;
    printf("size: %i | ", section->size);
    while (i < limit)
        printf("%i, ", section->board[i++]);
    printf("\n");
}

void    printBoard(board *game_board, char print_input)
{
    int x;
    int y = 0;
    int size = game_board->size;
    if (print_input)
    {
        printInput(game_board->input);
        printf("\n");
    }
    while (y < size)
    {
        x = 0;
        while (x < size)
        {
            printf("%i ", game_board->board[y * size + x]);
            x++;
        }
        printf("\n");
        y++;
    }
}