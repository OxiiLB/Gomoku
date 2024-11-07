/*
** EPITECH PROJECT, 2024
** Gomoku
** File description:
** mcts
*/

#pragma once

#include "node.hpp"

class MCTS {
    public:
        Node *run(Board startingBoard, int boardSize, int iterations);

    private:
        float calculate(Node *node, int parentVisits, float explorationParam = 1.4);
        Node *select(Node *node);
        void expand(Node *node, int boardSize);
        void backpropagate(Node *node, int result);
};
