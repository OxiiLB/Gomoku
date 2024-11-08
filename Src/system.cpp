/*
** EPITECH PROJECT, 2024
** Gomoku
** File description:
** system
*/

#include "system.hpp"
#include "command.hpp"
#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

System::System() {}

System::~System() {}

void System::initiateStruct(gomoku_t *game)
{
  game->win = GAME_STATE::PLAY, game->map.resize(0);
  game->size = 0;
  game->my_turn = false;
  game->me.x = 0;
  game->me.y = 0;
  game->opponent.x = 0;
  game->opponent.y = 0;
  game->map.resize(0);
  game->global_info.timeout_turn = std::chrono::milliseconds(0);
  game->global_info.timeout_match = std::chrono::milliseconds(0);
  game->global_info.max_memory = 0;
  game->global_info.time_left = std::chrono::milliseconds(0);
  game->global_info.game_type = GAME_TYPE::HUMAN;
  game->global_info.rule = RULE::EXACTLY_FIVE;
  game->global_info.evaluate.x = 0;
  game->global_info.evaluate.y = 0;
  game->global_info.folder = 0;
}

std::vector<std::string> System::splitString(const std::string &str)
{
  std::istringstream iss(str);
  std::vector<std::string> result;
  std::string word;
  while (iss >> word) {
    word.erase(std::remove(word.begin(), word.end(), ','), word.end());
    result.push_back(word);
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

    if (entry.front() == "START") {
      command.start(&game, entry);
    } else if (entry.front() == "TURN") {
      command.turn(&game, entry);
    } else if (entry.front() == "BEGIN") {
      command.begin(&game);
    } else if (entry.front() == "BOARD") {
      command.board(this, &game);
    } else if (entry.front() == "ABOUT") {
      command.about();
    } else if (entry.front() == "END" || game.win == GAME_STATE::WIN || game.win == GAME_STATE::LOSE) {
      isRunning = false;
    }
    if (game.my_turn) {
      game.my_turn = false;
      std::cout << game.me.x << "," << game.me.y << std::endl;
    }

  }
}

gomoku_t *System::getGame() { return game; }