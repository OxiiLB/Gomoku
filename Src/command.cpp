/*
** EPITECH PROJECT, 2024
** Gomoku
** File description:
** command
*/

#include "command.hpp"
#include <cstring>

Command::Command() {}

Command::~Command() {}

void Command::start(gomoku_t *game, std::vector<std::string> entry)
{
  std::cout << entry.size() << std::endl;
  if (entry.size() < 2) {
    error(COMMANDERROR::START);
    return;
  }
  game->size = atoi(entry.back().c_str());
  if (game->size < 5) {
    error(COMMANDERROR::START);
    return;
  }
  std::cout << game->size << std::endl;
  game->map.resize(game->size, std::vector<TILESTATE>(game->size, TILESTATE::EMPTY));
  std::cout << "OK - everything is good" << std::endl;
}

void Command::turn(int x, int y)
{
  std::cout << "TURN " << x << " " << y << std::endl;
}

void Command::begin() { std::cout << "BEGIN" << std::endl; }

void Command::board(ISystem *system, gomoku_t *game) {
  std::cout << "BOARD" << std::endl;
  bool isRunning = true;
  while (isRunning) {
    std::cout << "BOARD" << std::endl;
    std::string line;
    std::getline(std::cin, line);
    std::vector<std::string> entry = system->splitString(line);
    if (std::strcmp("DONE\0", entry.front().c_str()) == 0)
      isRunning = false;
    else {
      int x = atoi(entry.at(1).c_str());
      int y = atoi(entry.at(2).c_str());
      int player = atoi(entry.at(3).c_str());
      std::cout << "BOARD " << x << " " << y << " PLAYER:" << player << std::endl;
      if (player == 1)
        game->map[x][y] = TILESTATE::ME;
      else
        game->map[x][y] = TILESTATE::PLAYER2;
    }
  }
}

void Command::about()
{
  std::cout << "name=\"pbrain-gomoku-ai\", version=\"1.0\", author=\"Dvaking, "
               "Oxi, Alea\", country=\"FR\""
            << std::endl;
}

void Command::error(COMMANDERROR command)
{
  switch (command) {
  case COMMANDERROR::START:
    std::cout << "ERROR message - unsupported size or other error" << std::endl;
    break;
  default:
    break;
  }
}