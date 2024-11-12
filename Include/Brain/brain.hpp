/*
** EPITECH PROJECT, 2024
** Gomoku
** File description:
** brain
*/

#pragma once

#include "mcts.hpp"
#include "struct.hpp"

class Brain {
public:
    Brain() {}
    // ~Brain() {}
    void getBestAttackMove(gomoku_t *game);
};
