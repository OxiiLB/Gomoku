/*
** EPITECH PROJECT, 2024
** Gomoku
** File description:
** command
*/

#include "command.hpp"

Command::Command() {}

Command::~Command() {}

std::ostream &operator<<(std::ostream &os, const TILE_STATE &entry)
{
  switch (entry) {
  case TILE_STATE::EMPTY:
    os << "EMPTY";
    break;
  case TILE_STATE::ME:
    os << "ME";
    break;
  case TILE_STATE::PLAYER2:
    os << "PLAYER2";
    break;
  default:
    os << "UNDEFINED";
    break;
  }
  return os;
}

void Command::start(gomoku_t *game, std::vector<std::string> entry)
{
  if (entry.size() < 2) {
    error(COMMAND_ERROR::START);
    return;
  }
  game->size = atoi(entry.back().c_str());
  if (game->size < 5) {
    error(COMMAND_ERROR::START);
    return;
  }
  game->map.resize(game->size,
                   std::vector<TILE_STATE>(game->size, TILE_STATE::EMPTY));
  std::cout << "OK - everything is good" << std::endl;
}

void Command::turn(gomoku_t *game, std::vector<std::string> entry)
{
  std::cout << "[---------TURN---------]" << std::endl;
  if (entry.size() < 3) {
    error(COMMAND_ERROR::START);
    return;
  }
  game->opponent.x = atoi(entry.at(1).c_str());
  game->opponent.y = atoi(entry.at(2).c_str());
  game->map[game->opponent.x][game->opponent.y] = TILE_STATE::PLAYER2;
}

void Command::begin() {
  std::cout << "BEGIN" << std::endl;
  std::cout << "1, 1" << std::endl;
}

void Command::board(ISystem *system, gomoku_t *game)
{
  bool isRunning = true;
  while (isRunning) {
    std::string line;
    std::getline(std::cin, line);
    std::vector<std::string> entry = system->splitString(line);
    if (entry.at(0) == "DONE")
      isRunning = false;
    else {
      if (entry.size() < 3) {
        error(COMMAND_ERROR::BOARD);
        return;
      }
      int x = atoi(entry.at(0).c_str());
      int y = atoi(entry.at(1).c_str());
      int player = atoi(entry.at(2).c_str());
      if (x < 0 || y < 0 || x >= game->size || y >= game->size ||
          game->map[x][y] != TILE_STATE::EMPTY) {
        error(COMMAND_ERROR::BOARD);
        return;
      }
      if (player == 1)
        game->map[x][y] = TILE_STATE::ME;
      else
        game->map[x][y] = TILE_STATE::PLAYER2;
    }
  }
}

void Command::about()
{
  std::cout << "name=\"pbrain-gomoku-ai\", version=\"1.0\", author=\"Dvaking, "
               "Oxi, Alea\", country=\"FR\""
            << std::endl;
}

void Command::error(COMMAND_ERROR command)
{
  switch (command) {
  case COMMAND_ERROR::START:
    std::cout << "ERROR message - unsupported size or other error" << std::endl;
    break;
  case COMMAND_ERROR::BOARD:
    std::cout << "ERROR message - tile already played or argument invalid"
              << std::endl;
    break;
  default:
    break;
  }
}