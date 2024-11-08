/*
** EPITECH PROJECT, 2024
** Gomoku
** File description:
** system
*/

#include "system.hpp"
#include "command.hpp"
#include <algorithm>
#include <cstring>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

System::System() {}

System::~System() {}

void System::initiateStruct(gomoku_t *game)
{
  game->win = GAME_STATE::PLAY, game->map.resize(0);
  game->player = 0;
  game->size = 0;
  game->turn = 0;
  game->win_pos = NULL;
  game->x = 0;
  game->y = 0;
}

std::vector<std::string> System::splitString(const std::string &str)
{
  std::istringstream iss(str);
  std::vector<std::string> result;
  std::string word;
  while (iss >> word) {
    word.erase(std::remove(word.begin(), word.end(), ','), word.end());
    result.push_back(word);
    std::cout << "splitString: " << word << std::endl;
  }
  return result;
}

void System::gameLoop()
{
  Command command;
  bool isRunning = true;
  gomoku_t game;
  initiateStruct(&game);

  while (isRunning) {
    std::string line;
    std::getline(std::cin, line);
    std::vector<std::string> entry = splitString(line);

    if (std::strcmp("START\0", entry.front().c_str()) == 0) {
      std::cout << "START" << std::endl;
      command.start(&game, entry);
    } else if (std::strcmp("TURN\0", entry.front().c_str()) == 0) {
      command.turn(9, 9);
    } else if (std::strcmp("BEGIN\0", entry.front().c_str()) == 0) {
      command.begin();
    } else if (std::strcmp("BOARD\0", entry.front().c_str()) == 0) {
      command.board(this, &game);
    } else if (std::strcmp("ABOUT\0", entry.front().c_str()) == 0) {
      command.about();
    } else if (std::strcmp("END\0", entry.front().c_str()) == 0) {
      isRunning = false;
    }
  }
}

gomoku_t *System::getGame() { return game; }