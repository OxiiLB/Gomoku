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
        Brain(gomoku_t &game) : _game(game), _mcts(game) {}

        std::pair<int, int> getNextMove() { return _mcts.findBestMove(_game); }
    
    private:
        gomoku_t &_game;
        MCTS _mcts;
};
