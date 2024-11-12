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
            int depth = bestChild->getMinWinningDepth();

            game->attack.best_move.x = bestChild->getMove().first;
            game->attack.best_move.y = bestChild->getMove().second;

            if (depth == 0) {
                game->attack.win_level = 1001;
            } else if (depth == 1) {
                game->attack.win_level = 101;
            } else {
                game->attack.win_level = 0;
            }

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
