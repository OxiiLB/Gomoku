/*
** EPITECH PROJECT, 2024
** Gomoku
** File description:
** attack algorithm
*/

#pragma once

#include <random>
#include <chrono>
#include <unordered_map>
#include "enum.hpp"
#include "struct.hpp"

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

class AttackAlgorithm {
    public:
        AttackAlgorithm(const gomoku_t &game) {}
        ~AttackAlgorithm() {}

        std::vector<RowInfo> getRows(gomoku_t &game);
        std::vector<std::pair<int, int>> getAvailableMoves(const gomoku_t &game);
        std::unordered_map<int, std::pair<int, int>> getBestMoveInfo(gomoku_t &game);
        bool canWin(gomoku_t &gameState, RowInfo *row, std::pair<int, int> pos, int depth);
        std::unordered_map<int, std::pair<int, int>> getBestMove(gomoku_t &game, std::vector<RowInfo> rows);
};