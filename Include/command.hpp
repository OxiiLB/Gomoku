/*
** EPITECH PROJECT, 2024
** Gomoku
** File description:
** command
*/

#pragma once

#include "i_command.hpp"
#include <iostream>
#include <memory>

class Command : virtual public ICommand
{
public:
  Command();
  ~Command();
  void start(gomoku_t *game, std::vector<std::string> entry) override;
  void rectStart(gomoku_t *game, std::vector<std::string> entry) override;
  void reStart(gomoku_t *game) override;
  void turn(gomoku_t *game, std::vector<std::string> entry) override;
  void info(gomoku_t *game, std::vector<std::string> entry) override;
  void begin(gomoku_t *game) override;
  void board(ISystem *system, gomoku_t *game) override;
  void about() override;
  void error(COMMAND_ERROR command) override;
  void godMode(gomoku_t *game, std::vector<std::string> entry) override;
  void takeBack(gomoku_t *game, std::vector<std::string> entry) override;
  void play(gomoku_t *game, std::vector<std::string> entry) override;
};