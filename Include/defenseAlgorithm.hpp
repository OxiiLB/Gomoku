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

class defenseAlgorithm
{
public:
    defenseAlgorithm(gomoku_t *game);
    ~defenseAlgorithm();

    void updateGame(gomoku_t *game);

    bool checkDefenseMove(int x, int y, TILE_STATE player, TILE_STATE opponent);

    void executeDefense();

private:
    gomoku_t *game;
    std::mutex _mutex;

    bool canBlockMove(int x, int y);

    bool checkDirection(int x, int y, int dx, int dy);
};
