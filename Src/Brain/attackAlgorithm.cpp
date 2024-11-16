/*
** EPITECH PROJECT, 2024
** Gomoku
** File description:
** mcts
*/

#include <iostream> ////////
#include "attackAlgorithm.hpp"

bool AttackAlgorithm::canWin(gomoku_t &gameState, RowInfo *row, std::pair<int, int> pos, int depth)
{
    int i = 0;
    int j = 0;
    int sizeX = gameState.size.x;
    int sizeY = gameState.size.y;

    depth += 1;

    switch (row->direction) {
        case Direction::HORIZONTAL:
            for (i = pos.first + 1; i < pos.first + depth && i < sizeX; i++) {
                if (gameState.map[pos.second][i] != TILE_STATE::EMPTY || i >= sizeX - 1) {
                    for (i = pos.first - 1; i > pos.first - depth && i > 0; i--) {
                        if (gameState.map[pos.second][i] != TILE_STATE::EMPTY || i <= 0) {
                            return false;
                        }
                    }
                    row->positive = false;
                    break;
                }
            }
        break;
        case Direction::VERTICAL:
            for (j = pos.second + 1; j < pos.second + depth && j < sizeY; j++) {
                if (gameState.map[j][pos.first] != TILE_STATE::EMPTY || j >= sizeY - 1) {
                    for (j = pos.second - 1; j > pos.second - depth && j > 0; j--) {
                        if (gameState.map[j][pos.first] != TILE_STATE::EMPTY || j <= 0) {
                            return false;
                        }
                    }
                    row->positive = false;
                    break;
                }
            }
        break;
        case Direction::LEFT_DIAGONAL:
            for (i = pos.first + 1, j = pos.second + 1; i < pos.first + depth && i < sizeX && j < pos.second + depth && j < sizeY; i++, j++) {
                if (gameState.map[j][i] != TILE_STATE::EMPTY || i >= sizeX - 1 || j >= sizeY - 1) {
                    for (i = pos.first - 1, j = pos.second - 1; i > pos.first - depth && i > 0 && j > pos.second - depth && j > 0; i--, j--) {
                        if (gameState.map[j][i] != TILE_STATE::EMPTY || i <= 0 || j <= 0) {
                            return false;
                        }
                    }
                    row->positive = false;
                    break;
                }
            }
        break;
        case Direction::RIGHT_DIAGONAL:
            for (i = pos.first - 1, j = pos.second + 1; i > pos.first - depth && i > 0 && j < sizeY && j < pos.second + depth; i--, j++) {
                if (gameState.map[j][i] != TILE_STATE::EMPTY || i <= 0 || j >= sizeY - 1) {
                    for (i = pos.first + 1, j = pos.second - 1; i < pos.first + depth && i < sizeX && j > pos.second - depth && j > 0; i++, j--) {
                        if (gameState.map[j][i] != TILE_STATE::EMPTY || i >= sizeX - 1 || j <= 0) {
                            return false;
                        }
                    }
                    row->positive = false;
                    break;
                }
            }
        break;
    }
    return true;
}

std::unordered_map<int, std::pair<int, int>> AttackAlgorithm::getBestMove(gomoku_t &gameState, std::vector<RowInfo> rows)
{
    int i = 0;
    int depth = 0;
    int longestRow = 0;
    RowInfo bestRow;
    std::pair<int, int> lastMove;
    std::pair<int, int> bestMove;

    while (!rows.empty()) {
        for (const auto &row : rows) {
            if (row.len > longestRow) {
                longestRow = row.len;
                bestRow = row;
            }
        }

        depth = (5 - bestRow.len);

        if (canWin(gameState, &bestRow, bestRow.startPos, depth)) {
            lastMove = bestRow.startPos;
        } else if (canWin(gameState, &bestRow, bestRow.endPos, depth)) {
            lastMove = bestRow.endPos;
        } else {
            rows.erase(rows.begin() + i);
            i++;
            continue;
        }
        
        switch (bestRow.direction) {
            case Direction::HORIZONTAL:
                if (bestRow.positive) {
                    bestMove = {lastMove.first + 1, lastMove.second};
                } else {
                    bestMove = {lastMove.first - 1, lastMove.second};
                }
            break;
            case Direction::VERTICAL:
                if (bestRow.positive) {
                    bestMove = {lastMove.first, lastMove.second + 1};
                } else {
                    bestMove = {lastMove.first, lastMove.second - 1};
                }
            break;
            case Direction::LEFT_DIAGONAL:
                if (bestRow.positive) {
                    bestMove = {lastMove.first + 1, lastMove.second + 1};
                } else {
                    bestMove = {lastMove.first - 1, lastMove.second - 1};
                }
            break;
            case Direction::RIGHT_DIAGONAL:
                if (bestRow.positive) {
                    bestMove = {lastMove.first - 1, lastMove.second + 1};
                } else {
                    bestMove = {lastMove.first + 1, lastMove.second - 1};
                }
            break;
        }
        return {{depth, bestMove}};
    }
    return {};
}

std::vector<std::pair<int, int>> AttackAlgorithm::getAvailableMoves(const gomoku_t &gameState)
{
    int i = 0;
    int j = 0;
    std::vector<std::pair<int, int>> moves;

    for (i = 0; i < gameState.size.y; ++i) {
        for (j = 0; j < gameState.size.x; ++j) {
            if (gameState.map[i][j] == TILE_STATE::EMPTY) {
                moves.push_back({j, i});
            }
        }
    }
    return moves;
}

std::vector<RowInfo> AttackAlgorithm::getRows(gomoku_t &gameState)
{
    std::vector<RowInfo> rows;

    // Horizontal Check
    for (int i = 0; i < gameState.size.y; i++) {
        int count = 0;
        std::pair<int, int> startPos;
        for (int j = 0; j < gameState.size.x; j++) {
            if (gameState.map[i][j] == TILE_STATE::ME) {
                if (count == 0) {
                    startPos = {j, i};
                }
                count++;
            } else {
                if (gameState.map[i][j] == TILE_STATE::PLAYER2) {
                    for (int l = 0; l < 6 - count; l++) {
                        if (startPos.first - l <= 0 || gameState.map[i][startPos.first - l] == TILE_STATE::PLAYER2) {
                            count = 0;
                            break;
                        }
                    }
                }
                if (count > 0) {
                    RowInfo rowInfo;
                    rowInfo.len = count;
                    rowInfo.direction = Direction::HORIZONTAL;
                    rowInfo.startPos = startPos;
                    if (count == 1) {
                        rowInfo.endPos = startPos;
                    } else {
                        rowInfo.endPos = {j - 1, i};
                    }
                    rows.push_back(rowInfo);
                }
                count = 0;
            }
        }
    }

    // Vertical Check
    for (int j = 0; j < gameState.size.y; j++) {
        int count = 0;
        std::pair<int, int> startPos;
        for (int i = 0; i < gameState.size.x; i++) {
            if (gameState.map[i][j] == TILE_STATE::ME) {
                if (count == 0) {
                    startPos = {j, i};
                }
                count++;
            } else {
                if (gameState.map[i][j] == TILE_STATE::PLAYER2) {
                    for (int l = 0; l < 6 - count; l++) {
                        if (startPos.second - l <= 0 || gameState.map[startPos.second - l][j] == TILE_STATE::PLAYER2) {
                            count = 0;
                            break;
                        }
                    }
                }
                if (count > 0) {
                    RowInfo rowInfo;
                    rowInfo.len = count;
                    rowInfo.direction = Direction::VERTICAL;
                    rowInfo.startPos = startPos;
                    if (count == 1) {
                        rowInfo.endPos = startPos;
                    } else {
                        rowInfo.endPos = {j, i - 1};
                    }
                    rows.push_back(rowInfo);
                }
                count = 0;
            }
        }
    }

    // Diagonal Check (top-left to bottom-right)
    for (int i = 0; i <= gameState.size.y; i++) {
        for (int j = 0; j <= gameState.size.x; j++) {
            int count = 0;
            std::pair<int, int> startPos;
            for (int k = 0; k + i < gameState.size.y && k + j < gameState.size.x; k++) {
                if (gameState.map[i + k][j + k] == TILE_STATE::ME) {
                    if (count == 0) {
                        startPos = {j, i};
                    }
                    count++;
                } else {
                    if (gameState.map[i + k][j + k] == TILE_STATE::PLAYER2) {
                        for (int l = 0; l < 6 - count; l++) {
                            if (startPos.first - l <= 0 || startPos.second - l <= 0 || gameState.map[startPos.second - l][startPos.first - l] == TILE_STATE::PLAYER2) {
                                count = 0;
                                break;
                            }
                        }
                    }
                    if (count > 0) {
                        RowInfo rowInfo;
                        rowInfo.len = count;
                        rowInfo.direction = Direction::LEFT_DIAGONAL;
                        rowInfo.startPos = startPos;
                        if (count == 1) {
                            rowInfo.endPos = startPos;
                        } else {
                            rowInfo.endPos = {j + k - 1, i + k - 1};
                        }
                        rows.push_back(rowInfo);
                    }
                    count = 0;
                }
            }
        }
    }

    // Anti-diagonal Check (top-right to bottom-left)
    for (int i = 0; i <= gameState.size.y; i++) {
        for (int j = -1; j < gameState.size.x; j++) {
            int count = 0;
            std::pair<int, int> startPos;
            for (int k = 0; k + i < gameState.size.y && j - k >= 0; k++) {
                if (gameState.map[i + k][j - k] == TILE_STATE::ME) {
                    if (count == 0) {
                        startPos = {j, i};
                    }
                    count++;
                } else {
                    if (gameState.map[i + k][j - k] == TILE_STATE::PLAYER2) {
                        for (int l = 0; l < 6 - count; l++) {
                            if (startPos.first + l >= gameState.size.x || startPos.second - l <= 0 || gameState.map[startPos.second - l][startPos.first + l] == TILE_STATE::PLAYER2) {
                                count = 0;
                                break;
                            }
                        }
                    }
                    if (count > 0) {
                        RowInfo rowInfo;
                        rowInfo.len = count;
                        rowInfo.direction = Direction::RIGHT_DIAGONAL;
                        rowInfo.startPos = startPos;
                        if (count == 1) {
                            rowInfo.endPos = startPos;
                        } else {
                            rowInfo.endPos = {j - k + 1, i + k - 1};
                        }
                        rows.push_back(rowInfo);
                    }
                    count = 0;
                }
            }
        }
    }

    return rows;
}

std::unordered_map<int, std::pair<int, int>> AttackAlgorithm::getBestMoveInfo(gomoku_t &game)
{
    std::unordered_map<int, std::pair<int, int>> bestMoveInfo;
    std::vector<RowInfo> rows;

    srand((unsigned)time(0));
    
    rows = getRows(game);

    if (rows.empty()) {
        std::vector<std::pair<int, int>> availableMoves = getAvailableMoves(game);
        return {{3, availableMoves[rand() % availableMoves.size()]}};
    }
    return (getBestMove(game, rows));
}
