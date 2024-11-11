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

class Command : virtual public ICommand {
public:
  Command();
  ~Command();
  void start(std::shared_ptr<gomoku_t> game, std::vector<std::string> entry) override;
  void rectStart(std::shared_ptr<gomoku_t> game, std::vector<std::string> entry) override;
  void reStart(std::shared_ptr<gomoku_t> game) override;
  void turn(std::shared_ptr<gomoku_t> game, std::vector<std::string> entry) override;
  void info(std::shared_ptr<gomoku_t> game, std::vector<std::string> entry) override;
  void begin(std::shared_ptr<gomoku_t> game) override;
  void board(ISystem *system, std::shared_ptr<gomoku_t> game) override;
  void about() override;
  void error(COMMAND_ERROR command) override;
  void godMode(std::shared_ptr<gomoku_t> game, std::vector<std::string> entry) override;
};