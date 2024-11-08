/*
** EPITECH PROJECT, 2024
** Gomoku
** File description:
** game_logic
*/

#include "game_logic.hpp"

std::vector<std::pair<int, int>> GameLogic::getAvailableMoves(const gomoku_t &gameState) const
{
    int i = 0;
    int j = 0;
    std::vector<std::pair<int, int>> moves;

    for (i = 0; i < gameState.size; ++i) {
        for (j = 0; j < gameState.size; ++j) {
            if (gameState.map[i][j] == TILE_STATE::EMPTY) {
                moves.push_back({i, j});
            }
        }
    }

    return moves;
}

// Check for a sequence of 5
bool GameLogic::checkWin(const gomoku_t &gameState) const
{
    int i = 0;
    int j = 0;

    // Horizontal
    for (i = 0; i < gameState.size; ++i) {
        for (j = 0; j < gameState.size - 4; ++j) {
            if (gameState.map[i][j] != TILE_STATE::EMPTY &&
                gameState.map[i][j] == gameState.map[i][j + 1] &&
                gameState.map[i][j] == gameState.map[i][j + 2] &&
                gameState.map[i][j] == gameState.map[i][j + 3] &&
                gameState.map[i][j] == gameState.map[i][j + 4]) {
                return true;
            }
        }
    }
    // Vertical
    for (i = 0; i < gameState.size - 4; ++i) {
        for (j = 0; j < gameState.size; ++j) {
            if (gameState.map[i][j] != TILE_STATE::EMPTY &&
                gameState.map[i][j] == gameState.map[i + 1][j] &&
                gameState.map[i][j] == gameState.map[i + 2][j] &&
                gameState.map[i][j] == gameState.map[i + 3][j] &&
                gameState.map[i][j] == gameState.map[i + 4][j]) {
                return true;
            }
        }
    }
    // Diagonal
    for (i = 0; i < gameState.size - 4; ++i) {
        for (j = 0; j < gameState.size - 4; ++j) {
            if (gameState.map[i][j] != TILE_STATE::EMPTY &&
                gameState.map[i][j] == gameState.map[i + 1][j + 1] &&
                gameState.map[i][j] == gameState.map[i + 2][j + 2] &&
                gameState.map[i][j] == gameState.map[i + 3][j + 3] &&
                gameState.map[i][j] == gameState.map[i + 4][j + 4]) {
                return true;
            }
        }
    }
    // Other diagonal
    for (i = 0; i < gameState.size - 4; ++i) {
        for (j = 4; j < gameState.size; ++j) {
            if (gameState.map[i][j] != TILE_STATE::EMPTY &&
                gameState.map[i][j] == gameState.map[i + 1][j - 1] &&
                gameState.map[i][j] == gameState.map[i + 2][j - 2] &&
                gameState.map[i][j] == gameState.map[i + 3][j - 3] &&
                gameState.map[i][j] == gameState.map[i + 4][j - 4]) {
                return true;
            }
        }
    }

    return false;
}

// Check if current game state is at a draw
bool GameLogic::checkDraw(const gomoku_t &gameState) const
{
    int i = 0;
    int j = 0;

    for (i = 0; i < gameState.size; ++i) {
        for (j = 0; j < gameState.size; ++j) {
            if (gameState.map[i][j] == TILE_STATE::EMPTY) {
                return false;
            }
        }
    }

    return true;
}
