/*
** EPITECH PROJECT, 2024
** Gomoku
** File description:
** defenseAlgorithm
*/

#pragma once

#include "struct.hpp"
#include <iostream>
#include <memory>
#include <mutex>

class defenseAlgorithm {
public:
  defenseAlgorithm();
  ~defenseAlgorithm();

  bool checkDefenseMove(gomoku_t *game);

  void executeDefense(gomoku_t *game);
  void bestMove(gomoku_t *game, int x, int y, int dx, int dy, int pIndex);

private:
  bool canBlockMove(gomoku_t *game, int x, int y);

  bool
  checkDirection(gomoku_t *game, int x, int y, int dx, int dy, int *pIndex);

  std::vector<std::vector<TILE_STATE>> _pattern = {
      {TILE_STATE::PLAYER2,
       TILE_STATE::PLAYER2,
       TILE_STATE::PLAYER2,
       TILE_STATE::PLAYER2,
       TILE_STATE::EMPTY}, // 4
      {TILE_STATE::PLAYER2,
       TILE_STATE::PLAYER2,
       TILE_STATE::PLAYER2,
       TILE_STATE::EMPTY,
       TILE_STATE::PLAYER2}, // 3
      {TILE_STATE::PLAYER2,
       TILE_STATE::PLAYER2,
       TILE_STATE::EMPTY,
       TILE_STATE::PLAYER2,
       TILE_STATE::PLAYER2}, // 2
      {TILE_STATE::PLAYER2,
       TILE_STATE::EMPTY,
       TILE_STATE::PLAYER2,
       TILE_STATE::PLAYER2,
       TILE_STATE::PLAYER2}, // 1
      {TILE_STATE::EMPTY,
       TILE_STATE::PLAYER2,
       TILE_STATE::PLAYER2,
       TILE_STATE::PLAYER2,
       TILE_STATE::PLAYER2}, // 0
      {TILE_STATE::PLAYER2,
       TILE_STATE::PLAYER2,
       TILE_STATE::PLAYER2,
       TILE_STATE::EMPTY,
       TILE_STATE::EMPTY}, // 3
      {TILE_STATE::PLAYER2,
       TILE_STATE::PLAYER2,
       TILE_STATE::EMPTY,
       TILE_STATE::PLAYER2,
       TILE_STATE::EMPTY}, // 2
      {TILE_STATE::PLAYER2,
       TILE_STATE::PLAYER2,
       TILE_STATE::EMPTY,
       TILE_STATE::EMPTY,
       TILE_STATE::PLAYER2}, // 2
      {TILE_STATE::PLAYER2,
       TILE_STATE::EMPTY,
       TILE_STATE::PLAYER2,
       TILE_STATE::PLAYER2,
       TILE_STATE::EMPTY}, // 1
      {TILE_STATE::PLAYER2,
       TILE_STATE::EMPTY,
       TILE_STATE::PLAYER2,
       TILE_STATE::EMPTY,
       TILE_STATE::PLAYER2}, // 1
      {TILE_STATE::PLAYER2,
       TILE_STATE::EMPTY,
       TILE_STATE::EMPTY,
       TILE_STATE::PLAYER2,
       TILE_STATE::PLAYER2}, // 2
      {TILE_STATE::EMPTY,
       TILE_STATE::PLAYER2,
       TILE_STATE::PLAYER2,
       TILE_STATE::PLAYER2,
       TILE_STATE::EMPTY}, // 0
      {TILE_STATE::EMPTY,
       TILE_STATE::PLAYER2,
       TILE_STATE::PLAYER2,
       TILE_STATE::EMPTY,
       TILE_STATE::PLAYER2}, // 3
      {TILE_STATE::EMPTY,
       TILE_STATE::PLAYER2,
       TILE_STATE::EMPTY,
       TILE_STATE::PLAYER2,
       TILE_STATE::PLAYER2}, // 1
      {TILE_STATE::EMPTY,
       TILE_STATE::EMPTY,
       TILE_STATE::PLAYER2,
       TILE_STATE::PLAYER2,
       TILE_STATE::PLAYER2}, // 1

  };
  std::vector<std::vector<int>> _posBestMove = {{4, 1000},
                                                {3, 1000},
                                                {2, 1000},
                                                {1, 1000},
                                                {0, 1000},
                                                {3, 100},
                                                {2, 100},
                                                {2, 100},
                                                {1, 100},
                                                {1, 100},
                                                {2, 100},
                                                {0, 100},
                                                {3, 100},
                                                {1, 100},
                                                {1, 100}};
  std::vector<TILE_STATE> _direction;

  std::vector<defenseAlgorithm_t> _possibility;
};
