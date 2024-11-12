/*
** EPITECH PROJECT, 2024
** Gomoku
** File description:
** brain
*/

#pragma once

#include "struct.hpp"
#include "mcts.hpp"

class Brain
{
public:
    Brain() {}
    // ~Brain() {}
    void getBestAttackMove(gomoku_t *game)
    {
        MCTS mcts(*game);
        Node *bestChild = mcts.getBestChildInfo(*game);
        if (bestChild)
        {
            game->attack.best_move.x = bestChild->getMove().first;
            game->attack.best_move.y = bestChild->getMove().second;
            game->attack.win_level = bestChild->getMinWinningDepth();
        }
        else
        {
            bool playing = true;
            for (int y = 0; playing != false && y < game->size.y; y++)
            {
                for (int x = 0; playing != false && x < game->size.x; x++)
                {
                    if (game->map[y][x] == TILE_STATE::EMPTY)
                    {
                        game->map[y][x] = TILE_STATE::ME;
                        game->attack.best_move.x = x;
                        game->attack.best_move.y = y;
                        playing = false;
                    }
                }
            }
        }
    }
};
