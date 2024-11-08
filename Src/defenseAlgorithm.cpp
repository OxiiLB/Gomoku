/*
** EPITECH PROJECT, 2024
** Gomoku
** File description:
** defenseAlgorithm
*/

#include "defenseAlgorithm.hpp"

defenseAlgorithm::defenseAlgorithm(gomoku_t *game) : game(game)
{
}

defenseAlgorithm::~defenseAlgorithm()
{
}

bool defenseAlgorithm::canBlockMove(int x, int y)
{
    return checkDirection(x, y, 0, 1) ||
           checkDirection(x, y, 1, 0) ||
           checkDirection(x, y, 1, 1) ||
           checkDirection(x, y, 1, -1);
}

bool defenseAlgorithm::checkDirection(int x, int y, int dx, int dy)
{
    int count = 0;

    for (int i = -4; i <= 4; i++)
    {
        int nx = x + i * dx;
        int ny = y + i * dy;
        if (nx >= 0 && nx < game->size && ny >= 0 && ny < game->size)
        {
            if (game->map[nx][ny] == TILE_STATE::PLAYER2)
                count++;
            else if (game->map[nx][ny] == TILE_STATE::ME || game->map[nx][ny] == TILE_STATE::EMPTY)
                count = 0;
            if (count == 4)
                return true;
        }
    }
    return false;
}

void defenseAlgorithm::updateGame(gomoku_t *game)
{
    std::lock_guard<std::mutex> lock(_mutex);
    this->game = game;
}

bool defenseAlgorithm::checkDefenseMove(int x, int y, TILE_STATE player, TILE_STATE opponent)
{
    if (game->map[x][y] == TILE_STATE::EMPTY)
    {
        if (canBlockMove(x, y))
            return true;
    }
    return false;
}

void defenseAlgorithm::executeDefense()
{
    std::lock_guard<std::mutex> lock(_mutex);

    for (int x = 0; x < game->size; x++)
    {
        for (int y = 0; y < game->size; y++)
        {
            if (game->map[x][y] == TILE_STATE::EMPTY && canBlockMove(x, y))
            {
                std::lock_guard<std::mutex> lock(_mutex);
                game->me.x = x;
                game->me.y = y;
                return;
            }
        }
    }
}
