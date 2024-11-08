/*
** EPITECH PROJECT, 2024
** Gomoku
** File description:
** game_logic
*/

#include "game_logic.hpp"

std::vector<std::pair<int, int>> GameLogic::getAvailableMoves(const gomoku_t &state) const
{
    int i = 0;
    int j = 0;
    std::vector<std::pair<int, int>> moves;

    for (i = 0; i < state.size; ++i) {
        for (j = 0; j < state.size; ++j) {
            if (state.map[i][j] == TILE_STATE::EMPTY) {
                moves.push_back({i, j});
            }
        }
    }

    return moves;
}

// Check for a sequence of 5
bool GameLogic::checkWin(const gomoku_t &state) const
{
    int i = 0;
    int j = 0;

    // Horizontal
    for (i = 0; i < state.size; ++i) {
        for (j = 0; j < state.size - 4; ++j) {
            if (state.map[i][j] != TILE_STATE::EMPTY &&
                state.map[i][j] == state.map[i][j + 1] &&
                state.map[i][j] == state.map[i][j + 2] &&
                state.map[i][j] == state.map[i][j + 3] &&
                state.map[i][j] == state.map[i][j + 4]) {
                return true;
            }
        }
    }
    // Vertical
    for (i = 0; i < state.size - 4; ++i) {
        for (j = 0; j < state.size; ++j) {
            if (state.map[i][j] != TILE_STATE::EMPTY &&
                state.map[i][j] == state.map[i + 1][j] &&
                state.map[i][j] == state.map[i + 2][j] &&
                state.map[i][j] == state.map[i + 3][j] &&
                state.map[i][j] == state.map[i + 4][j]) {
                return true;
            }
        }
    }
    // Diagonal
    for (i = 0; i < state.size - 4; ++i) {
        for (j = 0; j < state.size - 4; ++j) {
            if (state.map[i][j] != TILE_STATE::EMPTY &&
                state.map[i][j] == state.map[i + 1][j + 1] &&
                state.map[i][j] == state.map[i + 2][j + 2] &&
                state.map[i][j] == state.map[i + 3][j + 3] &&
                state.map[i][j] == state.map[i + 4][j + 4]) {
                return true;
            }
        }
    }
    // Other diagonal
    for (i = 0; i < state.size - 4; ++i) {
        for (j = 4; j < state.size; ++j) {
            if (state.map[i][j] != TILE_STATE::EMPTY &&
                state.map[i][j] == state.map[i + 1][j - 1] &&
                state.map[i][j] == state.map[i + 2][j - 2] &&
                state.map[i][j] == state.map[i + 3][j - 3] &&
                state.map[i][j] == state.map[i + 4][j - 4]) {
                return true;
            }
        }
    }

    return false;
}

// Check if current game state is at a draw
bool GameLogic::checkDraw(const gomoku_t &state) const
{
    int i = 0;
    int j = 0;

    for (i = 0; i < state.size; ++i) {
        for (j = 0; j < state.size; ++j) {
            if (state.map[i][j] == TILE_STATE::EMPTY) {
                return false;
            }
        }
    }

    return true;
}
