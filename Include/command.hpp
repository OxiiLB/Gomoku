/*
** EPITECH PROJECT, 2024
** Gomoku
** File description:
** command
*/

#pragma once

#include "i_command.hpp"
#include <iostream>

class Command : virtual public ICommand {
public:
  Command();
  ~Command();
  void start(gomoku_t *game, std::vector<std::string> entry) override;
  void turn(int x, int y) override;
  void begin() override;
  void board(ISystem *system, gomoku_t *game) override;
  void about() override;
  void error(COMMAND_ERROR command) override;
};