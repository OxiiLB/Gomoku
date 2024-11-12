/*
** EPITECH PROJECT, 2024
** Gomoku
** File description:
** defenseAlgorithm
*/

#pragma once

#include "struct.hpp"
#include <iostream>
#include <mutex>
#include <memory>

class defenseAlgorithm
{
public:
    defenseAlgorithm();
    ~defenseAlgorithm();

    bool checkDefenseMove(gomoku_t *game, int x, int y, TILE_STATE player, TILE_STATE opponent);

    void executeDefense(gomoku_t *game);
    void bestMove(gomoku_t *game, int x, int y, int dx, int dy, int pIndex);

private:
    bool canBlockMove(gomoku_t *game, int x, int y);

    bool checkDirection(gomoku_t *game, int x, int y, int dx, int dy, int *pIndex);

    std::vector<std::vector<TILE_STATE>> _pattern = {
        {TILE_STATE::PLAYER2, TILE_STATE::PLAYER2, TILE_STATE::PLAYER2, TILE_STATE::PLAYER2, TILE_STATE::EMPTY}, // 4
        {TILE_STATE::PLAYER2, TILE_STATE::PLAYER2, TILE_STATE::PLAYER2, TILE_STATE::EMPTY, TILE_STATE::PLAYER2}, // 3
        {TILE_STATE::PLAYER2, TILE_STATE::PLAYER2, TILE_STATE::EMPTY, TILE_STATE::PLAYER2, TILE_STATE::PLAYER2}, // 2
        {TILE_STATE::PLAYER2, TILE_STATE::EMPTY, TILE_STATE::PLAYER2, TILE_STATE::PLAYER2, TILE_STATE::PLAYER2}, // 1
        {TILE_STATE::EMPTY, TILE_STATE::PLAYER2, TILE_STATE::PLAYER2, TILE_STATE::PLAYER2, TILE_STATE::PLAYER2}, // 0
        {TILE_STATE::PLAYER2, TILE_STATE::PLAYER2, TILE_STATE::PLAYER2, TILE_STATE::EMPTY, TILE_STATE::EMPTY}, // 3
        {TILE_STATE::PLAYER2, TILE_STATE::PLAYER2, TILE_STATE::EMPTY, TILE_STATE::PLAYER2, TILE_STATE::EMPTY}, // 2
        {TILE_STATE::PLAYER2, TILE_STATE::PLAYER2, TILE_STATE::EMPTY, TILE_STATE::EMPTY, TILE_STATE::PLAYER2}, // 2
        {TILE_STATE::PLAYER2, TILE_STATE::EMPTY, TILE_STATE::PLAYER2, TILE_STATE::PLAYER2, TILE_STATE::EMPTY}, // 1
        {TILE_STATE::PLAYER2, TILE_STATE::EMPTY, TILE_STATE::PLAYER2, TILE_STATE::EMPTY, TILE_STATE::PLAYER2}, // 1
        {TILE_STATE::PLAYER2, TILE_STATE::EMPTY, TILE_STATE::EMPTY, TILE_STATE::PLAYER2, TILE_STATE::PLAYER2}, // 2
        {TILE_STATE::EMPTY, TILE_STATE::PLAYER2, TILE_STATE::PLAYER2, TILE_STATE::PLAYER2, TILE_STATE::EMPTY}, // 0
        {TILE_STATE::EMPTY, TILE_STATE::PLAYER2, TILE_STATE::PLAYER2, TILE_STATE::EMPTY, TILE_STATE::PLAYER2}, // 3
        {TILE_STATE::EMPTY, TILE_STATE::PLAYER2, TILE_STATE::EMPTY, TILE_STATE::PLAYER2, TILE_STATE::PLAYER2}, // 1
        {TILE_STATE::EMPTY, TILE_STATE::EMPTY, TILE_STATE::PLAYER2, TILE_STATE::PLAYER2, TILE_STATE::PLAYER2}, // 1

    };
    std::vector<int> _posBestMove = {
        4, 3, 2, 1, 0, 3, 2, 2, 1, 1, 2, 0, 3, 1, 1
    };
    std::vector<TILE_STATE> _direction;
};
