/*
** EPITECH PROJECT, 2024
** Gomoku
** File description:
** game_logic
*/

#pragma once

#include <iostream> ////////
#include <vector>
#include <utility>
#include "struct.hpp"

class GameLogic {
    public:
        std::vector<std::pair<int, int>> getAvailableMoves(const gomoku_t &state) const;

        bool checkWin(const gomoku_t &state) const;
        bool checkDraw(const gomoku_t &state) const;
};
