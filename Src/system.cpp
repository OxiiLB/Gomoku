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

std::ostream &operator<<(std::ostream &os, const TILE_STATE &entry)
{
  switch (entry) {
  case TILE_STATE::EMPTY:
    os << "X";
    break;
  case TILE_STATE::ME:
    os << "1";
    break;
  case TILE_STATE::PLAYER2:
    os << "2";
    break;
  default:
    os << "UNDEFINED";
    break;
  }
  return os;
}

System::System() {}

System::~System() {}

void System::initiateStruct(gomoku_t *game)
{
  game->state = GAME_STATE::PLAY, game->map.resize(0);
  game->size.x = 0;
  game->size.y = 0;
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
  game->god_mode.map = false;
}

std::vector<std::string> System::splitString(const std::string &str)
{
  std::istringstream iss(str);
  std::vector<std::string> result;
  std::string word;
  while (std::getline(iss, word, ' ')) {
    std::istringstream subiss(word);
    std::string subword;
    while (std::getline(subiss, subword, ',')) {
      if (!subword.empty()) {
        result.push_back(subword);
      }
    }
  }
  return result;
}

void System::command(gomoku_t *game, std::vector<std::string> entry, bool *isRunning)
{
  Command command;
  if (entry.front() == "START")
    command.start(game, entry);
  else if (entry.front() == "TURN")
    command.turn(game, entry);
  else if (entry.front() == "INFO")
    command.info(game, entry);
  else if (entry.front() == "BEGIN")
    command.begin(game);
  else if (entry.front() == "BOARD")
    command.board(this, game);
  else if (entry.front() == "ABOUT")
    command.about();
  else if (entry.front() == "RECTSTART")
    command.rectStart(game, entry);
  else if (entry.front() == "RESTART")
    command.reStart(game);
  else if (entry.front() == "GODMOD")
    command.godMode(game, entry);
  else if (entry.front() == "END")
    *isRunning = false;
}

void System::gameLoop()
{
  bool isRunning = true;
  gomoku_t game;
  initiateStruct(&game);

  while (isRunning) {

    std::string line;
    std::getline(std::cin, line);
    std::vector<std::string> entry = splitString(line);

    command(&game, entry, &isRunning);

    if (game.state == GAME_STATE::PLAY && isRunning) {
      if (game.god_mode.map)
        displayGame(&game);
      if (game.my_turn) {
        game.my_turn = false;
        std::cout << game.me.x << "," << game.me.y << std::endl;
      }
    }
  }
}

gomoku_t *System::getGame() { return game; }

void System::displayGame(gomoku_t *game)
{
  int space = 1;
  for (int i = game->size.y; i > 9; i /= 10)
    space++;

  auto placeSpaceHeight = [](int x, int nbr) {
    int remove_space = 0;
    for (int i = nbr; i > 9; i /= 10)
      remove_space++;
    x -= remove_space;
    for (int i = 0; i < x; i++)
      std::cout << " ";
  };

  std::cout << std::endl;
  for (int i = 0; i < game->size.y; i++) {
    std::cout << i;
    placeSpaceHeight(space, i);
    std::cout << "| ";
    for (int j = 0; j < game->size.x; j++) {
      std::cout << game->map[i][j] << " ";
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}