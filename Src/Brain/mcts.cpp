/*
** EPITECH PROJECT, 2024
** Gomoku
** File description:
** mcts
*/

#include <iostream>
#include <ctime>
#include <unordered_map>
#include "mcts.hpp"

bool MCTS::canWin(gomoku_t &gameState, RowInfo *row, std::pair<int, int> pos, int depth)
{
    int i = 0;
    int j = 0;
    depth += 1;
    switch (row->direction)
    {
    case Direction::HORIZONTAL:
        for (i = pos.first + 1; i < pos.first + depth && i < gameState.size.x; i++)
        {
            std::cout << "checking: " << i << ", " << pos.second << std::endl; //////////////////////////////////////////////
            if (gameState.map[pos.second][i] != TILE_STATE::EMPTY)
            {
                std::cout << "is not empty: " << i << ", " << pos.second << std::endl; //////////////////////////////////////////////
                for (i = pos.first - 1; i > pos.first - depth && i > 0; i--)
                {
                    if (gameState.map[pos.second][i] != TILE_STATE::EMPTY)
                    {
                        return false;
                    }
                }
                row->positive = false;
                std::cout << "row->positive is false" << std::endl; //////////////////////////////////////////////
                break;
            }
        }
        break;
    case Direction::VERTICAL:
        for (j = pos.second + 1; j < pos.second + depth && j < gameState.size.y; j++)
        {
            if (gameState.map[j][pos.first] != TILE_STATE::EMPTY)
            {
                for (j = pos.second - 1; j > pos.second - depth && j > 0; j--)
                {
                    if (gameState.map[j][pos.first] != TILE_STATE::EMPTY)
                    {
                        return false;
                    }
                }
                row->positive = false;
                break;
            }
        }
        break;
    case Direction::LEFT_DIAGONAL:
        for (i = pos.first + 1, j = pos.second + 1; i < pos.first + depth && i < gameState.size.x && j < pos.second + depth && j < gameState.size.y; i++, j++)
        {
            if (gameState.map[j][i] != TILE_STATE::EMPTY)
            {
                for (i = pos.first - 1, j = pos.second - 1; i > pos.first - depth && i > 0 && j > pos.second - depth && j > 0; i--, j--)
                {
                    if (gameState.map[j][i] != TILE_STATE::EMPTY)
                    {
                        return false;
                    }
                }
                row->positive = false;
                break;
            }
        }
        break;
    case Direction::RIGHT_DIAGONAL:
        for (i = pos.first - 1, j = pos.second + 1; i > pos.first - depth && i > 0 && j < gameState.size.y && j < pos.second + depth; i--, j++)
        {
            if (gameState.map[j][i] != TILE_STATE::EMPTY)
            {
                for (i = pos.first + 1, j = pos.second - 1; i < pos.first + depth && i < gameState.size.x && j > pos.second - depth && j > 0; i++, j--)
                {
                    if (gameState.map[j][i] != TILE_STATE::EMPTY)
                    {
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

std::unordered_map<int, std::pair<int, int>> MCTS::getBestMove(gomoku_t &gameState, std::vector<RowInfo> rows)
{
    RowInfo bestRow;
    int longestRow = 0;
    std::pair<int, int> lastMove;
    int i = 0;
    while (!rows.empty())
    {
        for (const auto &row : rows)
        {
            //std::cout << "row.len: " << row.len << std::endl; //////////////////////////////////////////////
            if (row.len > longestRow)
            {
                longestRow = row.len;
                bestRow = row;
            }
        }
        std::cout << "bestRow.len: " << bestRow.len << std::endl; //////////////////////////////
        std::cout << "bestRow.startPos: " << bestRow.startPos.first << ", " << bestRow.startPos.second << std::endl; //////////////////////////////
        std::cout << "bestRow.endPos: " << bestRow.endPos.first << ", " << bestRow.endPos.second << std::endl;       //////////////////////////////
        std::cout << "bestRow.direction: " << (int)bestRow.direction << std::endl; //////////////////////////////////////////////
        int depth = (5 - bestRow.len);
        if (canWin(gameState, &bestRow, bestRow.startPos, depth))
        {
            std::cout << "startPos canWin" << std::endl; //////////////////////////////////////////////
            lastMove = bestRow.startPos;
        }
        else if (canWin(gameState, &bestRow, bestRow.endPos, depth))
        {
            std::cout << "endPos canWin" << std::endl; //////////////////////////////////////////////
            lastMove = bestRow.endPos;
        }
        else
        {
            // I need it to try every other direction before moving on to the next one
            rows.erase(rows.begin() + i);
            i++;
            continue;
        }
        std::cout << "lastMove: " << lastMove.first << ", " << lastMove.second << std::endl; //////////////////////////////
        std::cout << "bestRow.positive: " << bestRow.positive << std::endl; //////////////////////////////////////////////
        std::pair<int, int> bestMove;
        switch (bestRow.direction)
        {
        case Direction::HORIZONTAL:
            if (bestRow.positive)
            {
                bestMove = {lastMove.first + 1, lastMove.second};
            }
            else
            {
                bestMove = {lastMove.first - 1, lastMove.second};
            }
            break;
        case Direction::VERTICAL:
            if (bestRow.positive)
            {
                bestMove = {lastMove.first, lastMove.second + 1};
            }
            else
            {
                bestMove = {lastMove.first, lastMove.second - 1};
            }
            break;
        case Direction::LEFT_DIAGONAL:
            if (bestRow.positive)
            {
                bestMove = {lastMove.first + 1, lastMove.second + 1};
            }
            else
            {
                bestMove = {lastMove.first - 1, lastMove.second - 1};
            }
            break;
        case Direction::RIGHT_DIAGONAL:
            if (bestRow.positive)
            {
                bestMove = {lastMove.first - 1, lastMove.second + 1};
            }
            else
            {
                bestMove = {lastMove.first + 1, lastMove.second - 1};
            }
            break;
        }
        return {{depth, bestMove}};
    }
    return {};
}

std::vector<std::pair<int, int>> MCTS::getAvailableMoves(const gomoku_t &gameState)
{
    int i = 0;
    int j = 0;
    std::vector<std::pair<int, int>> moves;

    for (i = 0; i < gameState.size.y; ++i)
    {
        for (j = 0; j < gameState.size.x; ++j)
        {
            if (gameState.map[i][j] == TILE_STATE::EMPTY)
            {
                moves.push_back({j, i});
            }
        }
    }

    return moves;
}

std::vector<RowInfo> MCTS::getRows(gomoku_t &gameState)
{
    std::vector<RowInfo> rows;

    // Horizontal Check
    for (int i = 0; i < gameState.size.y; i++)
    {
        // std::cout << "horizontal" << std::endl; ///////////////////////////////////////////////
        int count = 0;
        std::pair<int, int> startPos;
        for (int j = 0; j < gameState.size.x; j++)
        {
            if (gameState.map[i][j] == TILE_STATE::ME)
            {
                if (count == 0)
                {
                    startPos = {j, i};
                }
                count++;
                //std::cout << "count: " << count << std::endl; ///////////////////////////////////////////////
                //std::cout << "pos: " << j << ", " << i << std::endl; ///////////////////////////////////////////////
            } else {
                if (count > 0)
                {
                    RowInfo rowInfo;
                    rowInfo.len = count;
                    rowInfo.direction = Direction::HORIZONTAL;
                    rowInfo.startPos = startPos;
                    if (count == 1)
                    {
                        rowInfo.endPos = startPos;
                    }
                    else
                    {
                        rowInfo.endPos = {j - 1, i};
                    }
                    rows.push_back(rowInfo);
                }
                count = 0;
            }
        }
    }

    // Vertical Check
    for (int j = 0; j < gameState.size.y; j++)
    {
        // std::cout << "vertical" << std::endl; ///////////////////////////////////////////////
        int count = 0;
        std::pair<int, int> startPos;
        for (int i = 0; i < gameState.size.x; i++)
        {
            if (gameState.map[i][j] == TILE_STATE::ME)
            {
                if (count == 0)
                {
                    startPos = {j, i};
                }
                count++;
            }
            else
            {
                if (count > 0)
                {
                    RowInfo rowInfo;
                    rowInfo.len = count;
                    rowInfo.direction = Direction::VERTICAL;
                    rowInfo.startPos = startPos;
                    if (count == 1)
                    {
                        rowInfo.endPos = startPos;
                    }
                    else
                    {
                        rowInfo.endPos = {j, i - 1};
                    }
                    rows.push_back(rowInfo);
                }
                count = 0;
            }
        }
    }

    // Diagonal Check (top-left to bottom-right)
    for (int i = 0; i <= gameState.size.y; i++)
    {
        // std::cout << "left diagonal" << std::endl; ///////////////////////////////////////////////
        for (int j = 0; j <= gameState.size.x; j++)
        {
            int count = 0;
            std::pair<int, int> startPos;
            for (int k = 0; k + i < gameState.size.y && k + j < gameState.size.x; k++)
            {
                if (gameState.map[i + k][j + k] == TILE_STATE::ME)
                {
                    if (count == 0)
                    {
                        startPos = {j, i};
                    }
                    count++;
                }
                else
                {
                    if (count > 0)
                    {
                        RowInfo rowInfo;
                        rowInfo.len = count;
                        rowInfo.direction = Direction::LEFT_DIAGONAL;
                        rowInfo.startPos = startPos;
                        if (count == 1)
                        {
                            rowInfo.endPos = startPos;
                        }
                        else
                        {
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
    for (int i = 0; i <= gameState.size.y; i++)
    {
        // std::cout << "right diagonal" << std::endl; ///////////////////////////////////////////////
        for (int j = -1; j < gameState.size.x; j++)
        {
            int count = 0;
            std::pair<int, int> startPos;
            for (int k = 0; k + i < gameState.size.y && j - k >= 0; k++)
            {
                if (gameState.map[i + k][j - k] == TILE_STATE::ME)
                {
                    if (count == 0)
                    {
                        startPos = {j, i};
                    }
                    count++;
                }
                else
                {
                    if (count > 0)
                    {
                        RowInfo rowInfo;
                        rowInfo.len = count;
                        rowInfo.direction = Direction::RIGHT_DIAGONAL;
                        rowInfo.startPos = startPos;
                        if (count == 1)
                        {
                            rowInfo.endPos = startPos;
                        }
                        else
                        {
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

std::unordered_map<int, std::pair<int, int>> MCTS::getBestMoveInfo(gomoku_t &game)
{
    std::unordered_map<int, std::pair<int, int>> bestMoveInfo;
    std::vector<RowInfo> rows = getRows(game);

    srand((unsigned)time(0));
    if (rows.empty())
    {
        std::cout << "rows is empty" << std::endl; ///////////////////////////////////////////////
        std::vector<std::pair<int, int>> availableMoves = getAvailableMoves(game);
        return {{3, availableMoves[rand() % availableMoves.size()]}};
    }

    bestMoveInfo = getBestMove(game, rows);

    return bestMoveInfo;
}
