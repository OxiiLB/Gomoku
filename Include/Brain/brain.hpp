/*
** EPITECH PROJECT, 2024
** Gomoku
** File description:
** brain
*/

#pragma once

#include "struct.hpp"
#include "mcts.hpp"

class Brain {
    public:
        Brain() {}
        // ~Brain() {}
        void getBestAttackMove(gomoku_t *game)
        {
            MCTS mcts(*game);
            std::pair<int, int> getBestAttackMove = mcts.findBestMove(*game);
            game->attack.best_move.x = getBestAttackMove.first;
            game->attack.best_move.y = getBestAttackMove.second;
        }
};
