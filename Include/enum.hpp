/*
** EPITECH PROJECT, 2024
** Gomoku
** File description:
** enum
*/

#pragma once

enum class COMMANDS {
  START,
  RECTSTART,
  BOARD,
  TURN,
  BEGIN,
  RESTART,
};

enum class GAME_STATE {
  WIN,
  LOSE,
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