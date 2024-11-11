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

private:
    bool canBlockMove(gomoku_t *game, int x, int y);

    bool checkDirection(gomoku_t *game, int x, int y, int dx, int dy);
};
