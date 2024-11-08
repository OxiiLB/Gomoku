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

    std::cout << "command: " << entry.front() << std::endl;

    if (entry.front() == "START") {
      std::cout << "START" << std::endl;
      command.start(&game, entry);
    } else if (entry.front() == "TURN\0") {
      command.turn(9, 9);
    } else if (entry.front() == "BEGIN\0") {
      command.begin();
    } else if (entry.front() == "BOARD\0") {
      command.board(this, &game);
    } else if (entry.front() == "ABOUT\0") {
      command.about();
    } else if (entry.front() == "END\0") {
      isRunning = false;
    }
  }
}

gomoku_t *System::getGame() { return game; }