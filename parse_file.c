#include "lib.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

char    *newDataBuffer(char size)
{
    char *data;
    size = 1 + (size + 1) * 4 + (size + 1) * size + 1;
    data = (char*)malloc(sizeof(char) * size);
    data[size - 1] = '\0';
    return (data);
}

char    isValidCharacter(char c, char size)
{
    return (!(c < '0' || c > '9') && c - '0' <= size);
}

char    *parseDataInput(board *game_board, char *data)
{
    char    i = 0;
    char    j = 0;
    char    current;
    char size = game_board->size;
    while (i < 4)
    {
        current = *++data;
        if (current == '\n')
        {
            i++;
            continue;
        }
        if (isValidCharacter(current, size))
        {
            current -= '0';
            if (j > game_board->input->size * 4 - 1)
                return (0);
            game_board->input->input[j++] = current;
        }
        else
            return (0);
    }
    return (data + 1);
}

char    parseDataBoard(board *game_board, char *data)
{
    char    i = 0;
    char    j = 0;
    char    current;
    char    size = game_board->size;
    char    len = size * size - 1;
    while (i < size)
    {
        current = *data++;
        if (current == '\n')
        {
            i++;
            continue;
        }
        if (isValidCharacter(current, size))
        {
            current -= '0';
            if (j > len)
                return (0);
            game_board->board[j++] = current;
        }
        else
            return (0);
    }
    return (1);
}

board   *createBoardFromData(char *data, char size)
{
    board   *game_board = newBoard(size);
    char    *board_data;
    if (!game_board)
        return (0);
    game_board->input = newParsedInput(size * 4);
    if (!game_board->input)
    {
        freeBoard(game_board);
        return (0);
    }
    board_data = parseDataInput(game_board, data);
    if (!board_data)
    {
        freeBoard(game_board);
        return (0);
    }
    parseDataBoard(game_board, board_data);
    if (!board_data)
    {
        freeBoard(game_board);
        return (0);
    }
    return (game_board);
}

board   *parseFile(char *src)
{
    char    size;
    int     fd;
    char    *data;
    char    data_size;
    board   *result;
    fd = open(src, O_RDONLY);
    if (fd == -1)
        return (0);
    if (!read(fd, &size, 1))
        return (0);
    size = size - '0';
    if (size > 9 || size < 1)
        return (0);
    data_size = (size + 1) * 4 + (size + 1) * size + 2;
    data = newDataBuffer(size);
    if (!read(fd, data, data_size))
        return (0);
    result = createBoardFromData(data, size);
    if (!result)
        return (0);
    free(data);
    if (close(fd) == -1)
    {
        freeBoard(result);
        return (0);
    }
    return (result);
}