/*
** EPITECH PROJECT, 2024
** Gomoku
** File description:
** defenseAlgorithm
*/

#include "defenseAlgorithm.hpp"

defenseAlgorithm::defenseAlgorithm() {}

defenseAlgorithm::~defenseAlgorithm() {}

bool defenseAlgorithm::canBlockMove(gomoku_t *game, int x, int y)
{
  int pIndex = 0;
  if (checkDirection(game, x, y, 0, 1, &pIndex)) {
    bestMove(game, x, y, 0, 1, pIndex);
    return true;
  } else if (checkDirection(game, x, y, 1, 0, &pIndex)) {
    bestMove(game, x, y, 1, 0, pIndex);
    return true;
  } else if (checkDirection(game, x, y, 1, 1, &pIndex)) {
    bestMove(game, x, y, 1, 1, pIndex);
    return true;
  } else if (checkDirection(game, x, y, 1, -1, &pIndex)) {
    bestMove(game, x, y, 1, -1, pIndex);
    return true;
  }
  return false;
}

void defenseAlgorithm::bestMove(
    gomoku_t *game, int x, int y, int dx, int dy, int pIndex)
{
  int bestMoveIdx = _posBestMove[pIndex];

  int nx = x + dx * bestMoveIdx;
  int ny = y + dy * bestMoveIdx;

  if (nx >= 0 && nx < game->size.x && ny >= 0 && ny < game->size.y) {
    if (game->map[ny][nx] == TILE_STATE::EMPTY) {
      game->defense.best_move.x = nx;
      game->defense.best_move.y = ny;
    }
  }
}

bool defenseAlgorithm::checkDirection(
    gomoku_t *game, int x, int y, int dx, int dy, int *pIndex)
{
  int nbrOfSame = 0;
  for (int i = 0; i < 5; i++) {
    int nx = x + dx * i;
    int ny = y + dy * i;
    if (nx < 0 || nx >= game->size.x || ny < 0 || ny >= game->size.y) {
      _direction.clear();
      return false;
    }
    _direction.push_back(game->map[ny][nx]);
  }
  for (int i = 0; i < _pattern.size(); i++) {
    if (_direction == _pattern[i]) {
      *pIndex = i;
      return true;
    }
  }
  _direction.clear();
  return false;
}

bool defenseAlgorithm::checkDefenseMove(
    gomoku_t *game, int x, int y, TILE_STATE player, TILE_STATE opponent)
{
  if (game->map[y][x] == TILE_STATE::PLAYER2) {
    if (canBlockMove(game, x, y))
      return true;
  }
  return false;
}

void defenseAlgorithm::executeDefense(gomoku_t *game)
{
  game->defense.best_move.x = -1;
  game->defense.best_move.y = -1;
  for (int y = 0; y < game->size.y; y++) {
    for (int x = 0; x < game->size.x; x++) {
      if (checkDefenseMove(game, x, y, TILE_STATE::ME, TILE_STATE::PLAYER2)) {
        return;
      }
    }
  }
  if (game->defense.best_move.x == -1 && game->defense.best_move.y == -1) {
    bool playing = true;
    for (int y = 0; playing != false && y < game->size.y; y++) {
      for (int x = 0; playing != false && x < game->size.x; x++) {
        if (game->map[y][x] == TILE_STATE::EMPTY) {
          game->map[y][x] = TILE_STATE::ME;
          game->defense.best_move.x = x;
          game->defense.best_move.y = y;
          playing = false;
        }
      }
    }
  }
}
