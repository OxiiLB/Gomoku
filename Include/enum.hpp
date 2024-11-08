/*
** EPITECH PROJECT, 2024
** Gomoku
** File description:
** enum
*/

#pragma once

enum class COMMAND_ERROR {
  START,
  BOARD,
  TURN,
  BEGIN,
};

enum class GAME_STATE {
  LOSE,
  WIN,
  PLAY,
  WAIT,
};

enum class TILE_STATE {
  EMPTY,
  ME,
  PLAYER2,
};

enum class GAME_TYPE {
  HUMAN,
  BRAIN,
  TOURNAMENT,
  NETWORK_TOURNAMENT,
};

enum class RULE {
  EXACTLY_FIVE,
  CONTINUOUS,
  RENJU,
  CARO,
};