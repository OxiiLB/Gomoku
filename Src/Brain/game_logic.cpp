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

    for (i = 0; i < gameState.size.x; ++i) {
        for (j = 0; j < gameState.size.y; ++j) {
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

    // Horizontal check
    for (int i = 0; i < gameState.size.x; ++i) {
        for (int j = 0; j <= gameState.size.y - 5; ++j) {
            if (gameState.map[i][j] == TILE_STATE::ME &&
                gameState.map[i][j] == gameState.map[i][j + 1] &&
                gameState.map[i][j] == gameState.map[i][j + 2] &&
                gameState.map[i][j] == gameState.map[i][j + 3] &&
                gameState.map[i][j] == gameState.map[i][j + 4]) {
                return true;
            }
        }
    }

    // Vertical check
    for (int i = 0; i <= gameState.size.x - 5; ++i) {
        for (int j = 0; j < gameState.size.y; ++j) {
            if (gameState.map[i][j] == TILE_STATE::ME &&
                gameState.map[i + 1][j] == TILE_STATE::ME &&
                gameState.map[i + 2][j] == TILE_STATE::ME &&
                gameState.map[i + 3][j] == TILE_STATE::ME &&
                gameState.map[i + 4][j] == TILE_STATE::ME) {
                return true;
            }
        }
    }

    // Diagonal (bottom-left to top-right) check
    for (int i = 0; i <= gameState.size.x - 5; ++i) {
        for (int j = 0; j <= gameState.size.y - 5; ++j) {
            if (gameState.map[i][j] == TILE_STATE::ME &&
                gameState.map[i + 1][j + 1] == TILE_STATE::ME &&
                gameState.map[i + 2][j + 2] == TILE_STATE::ME &&
                gameState.map[i + 3][j + 3] == TILE_STATE::ME &&
                gameState.map[i + 4][j + 4] == TILE_STATE::ME) {
                return true;
            }
        }
    }

    // Diagonal (top-left to bottom-right) check
    for (int i = 0; i <= gameState.size.x - 5; ++i) {  // Start from i = 0, not i = 4
        for (int j = 0; j <= gameState.size.y - 5; ++j) { // Check columns as well
            if (gameState.map[i][j] == TILE_STATE::ME &&
                gameState.map[i + 1][j + 1] == TILE_STATE::ME &&
                gameState.map[i + 2][j + 2] == TILE_STATE::ME &&
                gameState.map[i + 3][j + 3] == TILE_STATE::ME &&
                gameState.map[i + 4][j + 4] == TILE_STATE::ME) {
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

    for (i = 0; i < gameState.size.x; ++i) {
        for (j = 0; j < gameState.size.y; ++j) {
            if (gameState.map[i][j] == TILE_STATE::EMPTY) {
                return false;
            }
        }
    }

    return true;
}
