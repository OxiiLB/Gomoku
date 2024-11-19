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
  bool isPossible = false;
  defenseAlgorithm_t possibility;

  if (checkDirection(game, x, y, 0, 1, &pIndex))
  {
    bestMove(game, x, y, 0, 1, pIndex, possibility);
    isPossible = true;
  }
  if (checkDirection(game, x, y, 1, 0, &pIndex))
  {
    bestMove(game, x, y, 1, 0, pIndex, possibility);
    isPossible = true;
  }
  if (checkDirection(game, x, y, 1, 1, &pIndex))
  {
    bestMove(game, x, y, 1, 1, pIndex, possibility);
    isPossible = true;
  }
  if (checkDirection(game, x, y, 1, -1, &pIndex))
  {
    bestMove(game, x, y, 1, -1, pIndex, possibility);
    isPossible = true;
  }
  if (checkDirection(game, x, y, 0, -1, &pIndex))
  {
    bestMove(game, x, y, 0, -1, pIndex, possibility);
    isPossible = true;
  }
  if (checkDirection(game, x, y, -1, 0, &pIndex))
  {
    bestMove(game, x, y, -1, 0, pIndex, possibility);
    isPossible = true;
  }
  if (checkDirection(game, x, y, -1, -1, &pIndex))
  {
    std::cout << "Check direction up" << std::endl;
    bestMove(game, x, y, -1, -1, pIndex, possibility);
    isPossible = true;
  }
  if (checkDirection(game, x, y, -1, 1, &pIndex))
  {
    bestMove(game, x, y, -1, 1, pIndex, possibility);
    isPossible = true;
  }

  if (isPossible)
  {
    _possibility.push_back(possibility);
    // std::cout << "Best move: " << possibility.best_move.x << " " << possibility.best_move.y << std::endl;
    // std::cout << "Risk level: " << possibility.risk_level << std::endl;
    possibility.risk_level = 0;
    return true;
  }
  return false;
}

void defenseAlgorithm::bestMove(
    gomoku_t *game, int x, int y, int dx, int dy, int pIndex, defenseAlgorithm_t &possibility)
{
  int bestMoveIdx = _posBestMove[pIndex][0];
  int bestMoveScore = _posBestMove[pIndex][1];

  int nx = x + dx * bestMoveIdx;
  int ny = y + dy * bestMoveIdx;
  if (nx >= 0 && nx < game->size.x && ny >= 0 && ny < game->size.y)
  {
    if (game->map[ny][nx] == TILE_STATE::EMPTY)
    {
      possibility.best_move.x = nx;
      possibility.best_move.y = ny;
      possibility.risk_level += bestMoveScore;
    }
  }
}

bool defenseAlgorithm::checkDirection(
    gomoku_t *game, int x, int y, int dx, int dy, int *pIndex)
{
  int nbrOfSame = 0;
  int empty = 0;
  Log log;
  for (int i = 0; i < 5; i++)
  {
    int nx = x + dx * i;
    int ny = y + dy * i;
    log.writeInFile("nx: " + std::to_string(nx) + " ny: " + std::to_string(ny));
    if (nx < 0 || nx >= game->size.x || ny < 0 || ny >= game->size.y)
    {
      _direction.clear();
      log.writeInFile("------");
      return false;
    }

    if (game->map[ny][nx] == TILE_STATE::EMPTY)
      empty++;
    _direction.push_back(game->map[ny][nx]);
    if (empty == 3)
    {
      _direction.clear();
      log.writeInFile("------");
      return false;
    }
  }
  for (int i = 0; i < _pattern.size(); i++)
  {
    if (_direction == _pattern[i])
    {
      *pIndex = i;
      log.writeInFile("------");
      return true;
    }
  }
  log.writeInFile("------");
  _direction.clear();
  return false;
}

bool defenseAlgorithm::checkDefenseMove(gomoku_t *game)
{

  for (int y = 0; y < game->size.y; y++)
  {
    for (int x = 0; x < game->size.x; x++)
    {
      canBlockMove(game, x, y);
    }
  }
  for (int i = 0; i < _possibility.size(); i++)
  {
    if (_possibility[i].risk_level > game->defense.risk_level)
    {
      game->defense.best_move.x = _possibility[i].best_move.x;
      game->defense.best_move.y = _possibility[i].best_move.y;
      game->defense.risk_level = _possibility[i].risk_level;
    }
  }
  _possibility.clear();
  return false;
}

void defenseAlgorithm::executeDefense(gomoku_t *game)
{
  game->defense.best_move.x = -1;
  game->defense.best_move.y = -1;
  game->defense.risk_level = 0;
  if (checkDefenseMove(game))
  {
    return;
  }
}
