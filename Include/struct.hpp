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
  BEGIN,
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

typedef struct gomoku_s {
  std::vector<std::vector<TILE_STATE>> map;
  int size;
  int turn;
  int player;
  int x;
  int y;
  GAME_STATE win;
  int **win_pos;
} gomoku_t;
