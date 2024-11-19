/*
** EPITECH PROJECT, 2024
** Gomoku
** File description:
** mcts
*/

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
            for (i = pos.first + 1; i < pos.first + depth; i++) {
                if (i > sizeX - 1 || (gameState.map[pos.second][i] != TILE_STATE::EMPTY && i == pos.first + 1) || (gameState.map[pos.second][i] == TILE_STATE::PLAYER2 && i > pos.first + 1)) {
                    for (i = pos.first - 1; i > pos.first - depth; i--) {
                        if (i < 0 || (gameState.map[pos.second][i] != TILE_STATE::EMPTY && i == pos.first - 1) || (gameState.map[pos.second][i] == TILE_STATE::PLAYER2 && i < pos.first - 1)) {
                            return false;
                        }
                    }
                    row->positive = false;
                    break;
                }
            }
        break;
        case Direction::VERTICAL:
            for (j = pos.second + 1; j < pos.second + depth; j++) {
                if (j > sizeY - 1 || (gameState.map[j][pos.first] != TILE_STATE::EMPTY && j == pos.second + 1) || (gameState.map[j][pos.first] == TILE_STATE::PLAYER2 && j > pos.second + 1)) {
                    for (j = pos.second - 1; j > pos.second - depth; j--) {
                        if (j < 0 || (gameState.map[j][pos.first] != TILE_STATE::EMPTY && j == pos.second - 1) || (gameState.map[j][pos.first] == TILE_STATE::PLAYER2 && j < pos.second - 1)) {
                            return false;
                        }
                    }
                    row->positive = false;
                    break;
                }
            }
        break;
        case Direction::LEFT_DIAGONAL:
            for (i = pos.first + 1, j = pos.second + 1; i < pos.first + depth && j < pos.second + depth; i++, j++) {
                if (i > sizeX - 1 || j > sizeY - 1 || (gameState.map[j][i] != TILE_STATE::EMPTY && i == pos.first + 1 && j == pos.second + 1) || (gameState.map[j][i] == TILE_STATE::PLAYER2 && i > pos.first + 1 && j > pos.second + 1)) {
                    for (i = pos.first - 1, j = pos.second - 1; i > pos.first - depth && j > pos.second - depth; i--, j--) {
                        if (i < 0 || j < 0 || (gameState.map[j][i] != TILE_STATE::EMPTY && i == pos.first - 1 && j == pos.second - 1) || (gameState.map[j][i] == TILE_STATE::PLAYER2 && i < pos.first - 1 && j < pos.second - 1)) {
                            return false;
                        }
                    }
                    row->positive = false;
                    break;
                }
            }
        break;
        case Direction::RIGHT_DIAGONAL:
            for (i = pos.first - 1, j = pos.second + 1; i > pos.first - depth && j < pos.second + depth; i--, j++) {
                if (i < 0 || j > sizeY - 1 || (gameState.map[j][i] != TILE_STATE::EMPTY && i == pos.first - 1 && j == pos.second + 1) || (gameState.map[j][i] == TILE_STATE::PLAYER2 && i < pos.first - 1 && j > pos.second + 1)) {
                    for (i = pos.first + 1, j = pos.second - 1; i < pos.first + depth && j > pos.second - depth; i++, j--) {
                        if (i > sizeX - 1 || j < 0 || (gameState.map[j][i] != TILE_STATE::EMPTY && i == pos.first + 1 && j == pos.second - 1) || (gameState.map[j][i] == TILE_STATE::PLAYER2 && i > pos.first + 1 && j < pos.second - 1)) {
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
    int i = -1;
    int depth = 0;
    std::pair<int, int> lastMove;
    std::pair<int, int> bestMove;

    while (!rows.empty()) {
        i++;
        RowInfo bestRow;
        int longestRow = 0;
        for (auto &row : rows) {
            if (row.priority) {
                bestRow = row;
                break;
            }
            if (row.len > longestRow) {
                longestRow = row.len;
                bestRow = row;
            }
        }

        depth = (5 - bestRow.len);

        if (bestRow.priority == false) {
            if (canWin(gameState, &bestRow, bestRow.startPos, depth)) {
                lastMove = bestRow.startPos;
            } else if (canWin(gameState, &bestRow, bestRow.endPos, depth)) {
                lastMove = bestRow.endPos;
            } else {
                rows.erase(rows.begin() + i);
                i = -1;
                continue;
            }
        } else {
            lastMove = bestRow.endPos;
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

    // Horizontal
    for (int i = 0; i < gameState.size.y; i++) {
        int count = 0;
        std::pair<int, int> startPos;
        for (int j = 0; j < gameState.size.x; j++) {
            if (gameState.map[i][j] == TILE_STATE::ME) {
                if (count == 0) {
                    startPos = {j, i};
                }
                count++;
                if (j != gameState.size.x - 1) {
                    continue;
                }
            }
            if (gameState.map[i][j] == TILE_STATE::PLAYER2) {
                for (int l = 0; l < 5 - count; l++) {
                    if (startPos.first - l <= 0 || gameState.map[i][startPos.first - l] == TILE_STATE::PLAYER2) {
                        count = 0;
                        break;
                    }
                }
            }
            if (count > 0) {
                RowInfo rowInfo;
                if (gameState.map[i][j] == TILE_STATE::EMPTY) {
                    for (int t = j + 1; t < (j + (5 - count)); t++) {
                        if (t >= gameState.size.x || gameState.map[i][t] != TILE_STATE::ME) {
                            rowInfo.priority = true;
                            break;
                        }
                    }
                    rowInfo.priority = !rowInfo.priority;
                }
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

    // Vertical
    for (int j = 0; j < gameState.size.x; j++) {
        int count = 0;
        std::pair<int, int> startPos;
        for (int i = 0; i < gameState.size.y; i++) {
            if (gameState.map[i][j] == TILE_STATE::ME) {
                if (count == 0) {
                    startPos = {j, i};
                }
                count++;
                if (i != gameState.size.x - 1) {
                    continue;
                }
            }
            if (gameState.map[i][j] == TILE_STATE::PLAYER2) {
                for (int l = 0; l < 5 - count; l++) {
                    if (startPos.second - l <= 0 || gameState.map[startPos.second - l][j] == TILE_STATE::PLAYER2) {
                        count = 0;
                        break;
                    }
                }
            }
            if (count > 0) {
                RowInfo rowInfo;
                if (gameState.map[i][j] == TILE_STATE::EMPTY) {
                    for (int t = i + 1; (i + (5 - count)); t++) {
                        if (t >= gameState.size.y || gameState.map[t][j] != TILE_STATE::ME) {
                            rowInfo.priority = true;
                            break;
                        }
                    }
                    rowInfo.priority = !rowInfo.priority;
                }
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

    // Diagonal (top-left to bottom-right)
    for (int i = 0; i < gameState.size.y; i++) {
        for (int j = 0; j < gameState.size.x; j++) {
            int count = 0;
            std::pair<int, int> startPos;
            if (gameState.map[i][j] != TILE_STATE::ME) {
                continue;
            }
            for (int k = 0; (i + k) < gameState.size.y && (j + k) < gameState.size.x; k++) {
                if (gameState.map[i + k][j + k] == TILE_STATE::ME) {
                    if (count == 0) {
                        startPos = {j, i};
                    }
                    count++;
                    if (i != gameState.size.y - 1) {
                        continue;
                    }
                }
                if (gameState.map[i + k][j + k] == TILE_STATE::PLAYER2) {
                    for (int l = 0; l < 5 - count; l++) {
                        if (startPos.first - l < 0 || startPos.second - l < 0 || gameState.map[startPos.second - l][startPos.first - l] == TILE_STATE::PLAYER2) {
                            count = 0;
                            break;
                        }
                    }
                }
                if (count > 0) {
                    RowInfo rowInfo;
                    if (gameState.map[i + k][j + k] == TILE_STATE::EMPTY) {
                        for (int t = 1; t < (4 - count); t++) {
                            if ((i + t) >= gameState.size.y || (j + t) >= gameState.size.x || gameState.map[i + t][j + t] != TILE_STATE::ME) {
                                rowInfo.priority = true;
                                break;
                            }
                        }
                        rowInfo.priority = !rowInfo.priority;
                    }
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
                break;
            }
        }
    }

    // Anti-diagonal (top-right to bottom-left)
    for (int i = 0; i < gameState.size.y; i++) {
        for (int j = 0; j < gameState.size.x; j++) {
            int count = 0;
            std::pair<int, int> startPos;
            if (gameState.map[i][j] != TILE_STATE::ME) {
                continue;
            }
            for (int k = 0; (i + k) < gameState.size.y && (j - k) > 0; k++) {
                if (gameState.map[i + k][j - k] == TILE_STATE::ME) {
                    if (count == 0) {
                        startPos = {j, i};
                    }
                    count++;
                    if (i != gameState.size.y - 1) {
                        continue;
                    }
                }
                if (gameState.map[i + k][j - k] == TILE_STATE::PLAYER2) {
                    for (int l = 0; l < 5 - count; l++) {
                        if (startPos.first + l > gameState.size.x || startPos.second - l < 0 || gameState.map[startPos.second - l][startPos.first + l] == TILE_STATE::PLAYER2) {
                            count = 0;
                            break;
                        }
                    }
                }
                if (count > 0) {
                    RowInfo rowInfo;
                    if (gameState.map[i + k][j - k] == TILE_STATE::EMPTY) {
                        for (int t = 1; t < (4 - count); t++) {
                            if ((i + t) >= gameState.size.y || (j - t) < 0 || gameState.map[i + t][j - t] != TILE_STATE::ME) {
                                rowInfo.priority = true;
                                break;
                            }
                        }
                        rowInfo.priority = !rowInfo.priority;
                    }
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
                break;
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
        return {{5, availableMoves[rand() % availableMoves.size()]}};
    }

    bestMoveInfo = getBestMove(game, rows);

    if (bestMoveInfo.empty()) {
        std::vector<std::pair<int, int>> availableMoves = getAvailableMoves(game);
        return {{5, availableMoves[rand() % availableMoves.size()]}};
    }

    return bestMoveInfo;
}
