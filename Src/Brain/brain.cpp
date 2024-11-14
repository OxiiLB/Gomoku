/*
** EPITECH PROJECT, 2024
** Gomoku
** File description:
** brain
*/

#include <unordered_map>
#include "brain.hpp"

void Brain::getBestAttackMove(gomoku_t *game)
{
  MCTS mcts(*game);
  std::unordered_map<int, std::pair<int, int>> bestMoveInfo = mcts.getBestMoveInfo(*game);
  if (!bestMoveInfo.empty())
  {
    int depth = bestMoveInfo.begin()->first;

    game->attack.best_move.x = bestMoveInfo.begin()->second.first;
    game->attack.best_move.y = bestMoveInfo.begin()->second.second;

    if (depth == 0)
    {
      game->attack.win_level = 1001;
    }
    else if (depth == 1)
    {
      game->attack.win_level = 101;
    }
    else
    {
      game->attack.win_level = 0;
    }
  }
  else
  {
    for (int y = 0; y < game->size.y; y++)
    {
      for (int x = 0; x < game->size.x; x++)
      {
        if (game->map[y][x] == TILE_STATE::EMPTY)
        {
          game->attack.best_move.x = x;
          game->attack.best_move.y = y;
          game->attack.win_level = 0;
          return;
        }
      }
    }
  }
}
