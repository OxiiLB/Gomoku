/*
** EPITECH PROJECT, 2024
** Gomoku
** File description:
** i_command
*/

#pragma once
#include "struct.hpp"
#include <i_system.hpp>
#include <string>

class ICommand {
public:
  virtual ~ICommand() = default;
  virtual void start(gomoku_t *game, std::vector<std::string> entry) = 0;
  virtual void turn(gomoku_t *game, std::vector<std::string> entry) = 0;
  virtual void info(gomoku_t *game, std::vector<std::string> entry) = 0;
  virtual void begin(gomoku_t *game) = 0;
  virtual void board(ISystem *system, gomoku_t *game) = 0;
  virtual void about() = 0;
  virtual void error(COMMAND_ERROR command) = 0;
};