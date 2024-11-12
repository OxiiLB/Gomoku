/*
** EPITECH PROJECT, 2024
** Gomoku
** File description:
** defenseAlgorithm
*/

#include "defenseAlgorithm.hpp"

defenseAlgorithm::defenseAlgorithm()
{
}

defenseAlgorithm::~defenseAlgorithm()
{
}

bool defenseAlgorithm::canBlockMove(gomoku_t *game, int x, int y)
{
    return checkDirection(game, x, y, 0, 1) ||
           checkDirection(game, x, y, 1, 0) ||
           checkDirection(game, x, y, 1, 1) ||
           checkDirection(game, x, y, 1, -1);
}

bool defenseAlgorithm::checkDirection(gomoku_t *game, int x, int y, int dx, int dy)
{
    int count = 0;

    for (int i = -4; i <= 4; i++)
    {
        int nx = x + i * dx;
        int ny = y + i * dy;
        if (nx >= 0 && nx < game->size.x && ny >= 0 && ny < game->size.y)
        {
            if (game->map[ny][nx] == TILE_STATE::PLAYER2)
                count++;
            else if (game->map[ny][nx] == TILE_STATE::ME || game->map[ny][nx] == TILE_STATE::EMPTY)
                count = 0;
            if (count == 4)
                return true;
        }
    }
    return false;
}

bool defenseAlgorithm::checkDefenseMove(gomoku_t *game, int x, int y, TILE_STATE player, TILE_STATE opponent)
{
    if (game->map[y][x] == TILE_STATE::EMPTY)
    {
        if (canBlockMove(game, x, y))
            return true;
    }
    return false;
}

void defenseAlgorithm::executeDefense(gomoku_t *game)
{
    for (int y = 0; y < game->size.y; y++)
    {
        for (int x = 0; x < game->size.x; x++)
        {
            if (checkDefenseMove(game, x, y, TILE_STATE::ME, TILE_STATE::PLAYER2))
            {
                game->defense.best_move.x = x;
                game->defense.best_move.y = y;
                return;
            }
        }
    }
}
