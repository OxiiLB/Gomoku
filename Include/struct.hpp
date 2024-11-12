/*
** EPITECH PROJECT, 2024
** Gomoku
** File description:
** struct
*/

#pragma once

#include <chrono>
#include <vector>
#include "enum.hpp"

typedef struct coord_s {
  int x;
  int y;
} coord_t;

/**
 * @struct global_info_s
 * @brief Structure to hold global information for the Gomoku game.
 *
 * This structure contains various parameters and settings related to the game,
 * such as time limits, memory limits, game type, rules, and current mouse
 * cursor position.
 *
 * @var std::chrono::milliseconds global_info_s::timeout_turn
 * Time limit for each move in milliseconds. A value of 0 means to play as fast
 * as possible.
 *
 * @var std::chrono::milliseconds global_info_s::timeout_match
 * Time limit for the entire match in milliseconds. A value of 0 means there is
 * no limit.
 *
 * @var long int global_info_s::max_memory
 * Memory limit in bytes. A value of 0 means there is no limit.
 *
 * @var std::chrono::milliseconds global_info_s::time_left
 * Remaining time limit for the entire match in milliseconds.
 *
 * @var int global_info_s::game_type
 * Type of the game. Possible values are:
 * - 0: Opponent is human
 * - 1: Opponent is brain
 * - 2: Tournament
 * - 3: Network tournament
 *
 * @var int global_info_s::rule
 * Bitmask or sum representing the game rules. Possible values are:
 * - 1: Exactly five in a row win
 * - 2: Continuous game
 * - 4: Renju
 * - 8: Caro
 *
 * @var coord_t global_info_s::evaluate
 * Coordinates (X, Y) representing the current position of the mouse cursor.
 *
 * @var int global_info_s::folder
 * Additional parameter for future use.
 */
typedef struct global_info_s {
  std::chrono::milliseconds timeout_turn;
  std::chrono::milliseconds timeout_match;
  std::chrono::milliseconds time_left;
  long int max_memory;
  GAME_TYPE game_type;
  RULE rule;
  coord_t evaluate;
  int folder;
} global_info_t;

typedef struct god_mode_s {
  bool map;
} god_mode_t;

typedef struct defenseAlgorithm_s {
  coord_t best_move;
  int risk_level;
} defenseAlgorithm_t;

typedef struct attackAlgorithm_s {
  coord_t best_move;
  int win_level;
} attackAlgorithm_t;

typedef struct gomoku_s {
  std::vector<std::vector<TILE_STATE>> map;
  bool my_turn;
  GAME_STATE state;
  coord_t size;
  coord_t me;
  coord_t opponent;
  global_info_t global_info;
  god_mode_t god_mode;
  defenseAlgorithm_t defense;
  attackAlgorithm_t attack;
} gomoku_t;
