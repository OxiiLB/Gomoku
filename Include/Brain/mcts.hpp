/*
** EPITECH PROJECT, 2024
** Gomoku
** File description:
** mcts
*/

#pragma once

#include <random>
#include <chrono>
#include <unordered_map>
#include "node.hpp"
#include "game_logic.hpp"

enum class Direction {
    HORIZONTAL,
    VERTICAL,
    LEFT_DIAGONAL,
    RIGHT_DIAGONAL
};

struct RowInfo {
    int len = 0;
    Direction direction;
    bool positive = true;
    std::pair<int, int> startPos;
    std::pair<int, int> endPos;
};

class MCTS {
    public:
        MCTS(const gomoku_t &game) {}
        ~MCTS() {}

        std::vector<RowInfo> getRows(gomoku_t &game);
        std::vector<std::pair<int, int>> getAvailableMoves(const gomoku_t &game);
        std::unordered_map<int, std::pair<int, int>> getBestMoveInfo(gomoku_t &game);
        bool canWin(gomoku_t &gameState, RowInfo row, std::pair<int, int> pos, int depth);
        std::unordered_map<int, std::pair<int, int>> getBestMove(gomoku_t &game, std::vector<RowInfo> rows);
};
