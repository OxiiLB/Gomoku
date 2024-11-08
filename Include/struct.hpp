/*
** EPITECH PROJECT, 2024
** Gomoku
** File description:
** struct
*/

#pragma once

#include <vector>

enum class COMMAND_ERROR {
  START,
  BOARD,
};

enum class GAME_STATE {
  WIN,
  LOSE,
  PLAY,
};

enum class TILE_STATE {
  EMPTY,
  ME,
  PLAYER2,
};

typedef struct coord_s {
  int x;
  int y;
} coord_t;

typedef struct gomoku_s {
  std::vector<std::vector<TILE_STATE>> map;
  int size;
  bool my_turn;
  int player;
  coord_t me;
  coord_t opponent;
  GAME_STATE win;
  int **win_pos;
} gomoku_t;
