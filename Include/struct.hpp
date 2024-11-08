/*
** EPITECH PROJECT, 2024
** Gomoku
** File description:
** struct
*/

#ifndef STRUCT_H_
#define STRUCT_H_

#include <vector>

enum class COMMANDERROR{
    START,
    BEGIN,
};

enum class GAMESTATE {
    WIN,
    LOSE,
    PLAY,
};

enum class TILESTATE {
    EMPTY,
    ME,
    PLAYER2,
};

typedef struct gomoku_s {
    std::vector<std::vector<TILESTATE>> map;
    int size;
    int turn;
    int player;
    int x;
    int y;
    GAMESTATE win;
    int **win_pos;
} gomoku_t;

#endif /* !STRUCT_H_ */
