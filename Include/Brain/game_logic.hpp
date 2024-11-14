/*
** EPITECH PROJECT, 2024
** Gomoku
** File description:
** game_logic
*/

#pragma once

#include <iostream>
#include <vector>
#include <utility>
#include <set>
#include "enum.hpp"
#include "struct.hpp"

class GameLogic {
    public:
        std::vector<std::pair<int, int>> getAvailableMoves(const gomoku_t &gameState) const;
        std::vector<std::pair<int, int>> getAvailableAdjacentMoves(const gomoku_t &gameState, TILE_STATE tileState) const;

        bool checkWin(const gomoku_t &gameState, TILE_STATE tileState) const;
        bool checkDraw(const gomoku_t &gameState) const;
};
