/*
** EPITECH PROJECT, 2024
** Gomoku
** File description:
** mcts
*/

#pragma once

#include <random>
#include <chrono>
#include "node.hpp"
#include "game_logic.hpp"

class MCTS {
    public:
        MCTS(const gomoku_t &game) : _root(nullptr), _timeLimit(game.global_info.timeout_turn.count() / 1000.0), _gameLogic() {}

        std::pair<int, int> findBestMove(gomoku_t &game);

    private:
        double _timeLimit;
        std::unique_ptr<Node> _root;
        GameLogic _gameLogic;

        Node *select(Node *node);
        Node *expand(Node *node);
        double simulate(Node *node);
        void backPropagate(Node *node, double result);
};
