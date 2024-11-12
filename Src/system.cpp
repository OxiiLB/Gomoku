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
#include <thread>
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

void System::initiateStruct(gomoku_t *_game)
{
  _game->state = GAME_STATE::PLAY, _game->map.resize(0);
  _game->size.x = 0;
  _game->size.y = 0;
  _game->my_turn = false;
  _game->me.x = 0;
  _game->me.y = 0;
  _game->opponent.x = 0;
  _game->opponent.y = 0;
  _game->map.resize(0);
  _game->global_info.timeout_turn = std::chrono::milliseconds(0);
  _game->global_info.timeout_match = std::chrono::milliseconds(0);
  _game->global_info.max_memory = 0;
  _game->global_info.time_left = std::chrono::milliseconds(0);
  _game->global_info.game_type = GAME_TYPE::HUMAN;
  _game->global_info.rule = RULE::EXACTLY_FIVE;
  _game->global_info.evaluate.x = 0;
  _game->global_info.evaluate.y = 0;
  _game->global_info.folder = 0;
  _game->god_mode.map = false;
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
      subword.erase(
          std::remove_if(subword.begin(),
                         subword.end(),
                         [](unsigned char c) { return std::isspace(c); }),
          subword.end());
      if (!subword.empty()) {
        result.push_back(subword);
      }
    }
  }
  return result;
}

void System::command(gomoku_t *_game,
                     std::vector<std::string> entry,
                     bool *isRunning)
{
  Command command;
  if (entry.front() == "START")
    command.start(_game, entry);
  else if (_game->state == GAME_STATE::PLAY && entry.front() == "TURN")
    command.turn(_game, entry);
  else if (entry.front() == "INFO")
    command.info(_game, entry);
  else if (_game->state == GAME_STATE::PLAY && entry.front() == "BEGIN")
    command.begin(_game);
  else if (_game->state == GAME_STATE::PLAY && entry.front() == "BOARD")
    command.board(this, _game);
  else if (entry.front() == "ABOUT")
    command.about();
  else if (entry.front() == "RECTSTART")
    command.rectStart(_game, entry);
  else if (_game->state == GAME_STATE::PLAY && entry.front() == "RESTART")
    command.reStart(_game);
  else if (entry.front() == "GODMOD")
    command.godMode(_game, entry);
  else if (entry.front() == "END")
    *isRunning = false;
}

void System::gameLoop()
{
  bool isRunning = true;
  initiateStruct(&_game);

  _brain = Brain(); ////////////////////////////////
  _defense = defenseAlgorithm();

  while (isRunning) {
    std::string line;
    std::getline(std::cin, line);
    std::vector<std::string> entry = splitString(line);

    command(&_game, entry, &isRunning);

    if (_game.state == GAME_STATE::PLAY && isRunning) {
      if (_game.my_turn) {
        std::thread bgThread([&]() { _defense.executeDefense(&_game); });
        _brain.getBestAttackMove(&_game); ////////////////////////////////////////////////
        bool playing = true;
        _game.my_turn = false;

        if (bgThread.joinable())
          bgThread.join();
        _game.map[_game.defense.best_move.y][_game.defense.best_move.x] =
            TILE_STATE::ME;
        _game.me.x = _game.defense.best_move.x;
        _game.me.y = _game.defense.best_move.y;
        std::cout << _game.defense.best_move.x << ","
                  << _game.defense.best_move.y << std::endl;
      }
      if (_game.god_mode.map)
        displayGame(&_game);
    }
  }
}

gomoku_t *System::getGame() { return &_game; }

void System::displayGame(gomoku_t *_game)
{
  int space = 1;
  for (int i = _game->size.y; i > 9; i /= 10)
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
  for (int i = 0; i < _game->size.y; i++) {
    std::cout << i;
    placeSpaceHeight(space, i);
    std::cout << "| ";
    for (int j = 0; j < _game->size.x; j++) {
      std::cout << _game->map[i][j] << " ";
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}