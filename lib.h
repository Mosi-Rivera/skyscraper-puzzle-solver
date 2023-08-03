#ifndef LIB_H
#define LIB_H

typedef struct s_input
{
    char    size;
    char    *input;
}   t_input;

typedef struct s_board
{
    char    size;
    char*   board;
    t_input *input;
}   board;


board    *isValidInput(int length, char* input);
board   *newBoard(char size);
board   *cloneBoardLinearSection(board* board_data, char start, char end);
void    drawSection(board *section);
void    drawBoard(board *board_data);
void    printBoard(board *game_board);
void    printInput(t_input *parsed_input);
void    freeBoard(board *game_board);
char    solve(board *board_game);
char    isSolvable(board *game_board, char x, char y, char value);

#endif