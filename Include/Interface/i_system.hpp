/*
** EPITECH PROJECT, 2024
** Gomoku
** File description:
** i_system
*/

#pragma once
#include "struct.hpp"
#include <string>
#include <memory>

class ISystem
{
public:
  virtual ~ISystem() = default;
  virtual void gameLoop() = 0;
  virtual gomoku_t *getGame() = 0;
  virtual void initiateStruct(gomoku_t *_game) = 0;
  virtual std::vector<std::string> splitString(const std::string &str) = 0;
  virtual void displayGame(gomoku_t *_game) = 0;
  virtual void
  command(gomoku_t *_game, std::vector<std::string> entry, bool *isRunning) = 0;
};