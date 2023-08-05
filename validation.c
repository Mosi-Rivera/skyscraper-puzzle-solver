#include "lib.h"
#include <stdio.h>
#include <stdlib.h>
#define MAX_LENGTH 255

char    is_valid_number(char c)
{
    return (c > '0' && c <= '9');
}

char    isValidLength(int length)
{
    int i = 1;
    while (i <= MAX_LENGTH)
    {
        if (i * 4 == length)
            return (i);
        i++;
    }
    return (0);
}

t_input    *newParsedInput(char size)
{
    t_input    *result = (t_input*)malloc(sizeof(t_input));
    if (!result)
        return (0);
    result->size = size;
    result->input = (char*)malloc(sizeof(char) * size);
    if (!result->input)
    {
        free(result);
        return (0);
    }
    return result;
}

char    *freeParsedInput(t_input *parsed_input)
{
    if (parsed_input->input)
        free(parsed_input->input);
    free(parsed_input);
}

char    specialAtoi(char **input_pointer)
{
    char *str = *input_pointer;
    char result = 0;
    while (*str)
    {
        if (!*str || *str == ' ')
            break;
        if (!is_valid_number(*str))
            return (0);
        result *= 10;
        result += *str - '0';
        str++;
    }
    *input_pointer = str;
    return (result);
}

t_input    *validateChars(int length, char* input, char size)
{
    int     index = 0;
    t_input   *parsed_input;
    parsed_input = newParsedInput(length);
    if (!parsed_input)
        return (0);
    char    space_flag = 0;
    while (*input)
    {
        if (*input != ' ')
        {
            if (space_flag)
                return (0);
            space_flag = 1;
            parsed_input->input[index] = specialAtoi(&input);
            if (parsed_input->input[index] == 0 || parsed_input->input[index] > size)
            {
                freeParsedInput(parsed_input);
                return (0);
            }
            index++;
        }
        else
        {
            if (!space_flag)
                return (0);
            space_flag = 0;
            input++;
        }
    }
    if (!space_flag)
        return (0);
    return (parsed_input);
}

void    printInput(t_input *parsed_input)
{
    char    *input_data = parsed_input->input;
    char    length = parsed_input->size;
    char    i = 0;
    while (i < length)
    {
        printf("%i, ", input_data[i]);
        i++;
    }
}

board    *isValidInput(int length, char* input)
{
    char    size = isValidLength(length);
    if (!size)
        return (0);
    t_input   *parsed_input = validateChars(length, input, size);
    if (!parsed_input)
        return (0);
    board *game_board = newBoard(size);
    if (!game_board)
        return (0);
    game_board->input = parsed_input;
    if (!game_board->input)
    {
        freeBoard(game_board);
        return (0);
    }
    return (game_board);
}