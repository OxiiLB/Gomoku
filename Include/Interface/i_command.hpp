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
#include <memory>

class ICommand {
public:
  virtual ~ICommand() = default;
  virtual void start(std::shared_ptr<gomoku_t> game, std::vector<std::string> entry) = 0;
  virtual void rectStart(std::shared_ptr<gomoku_t> game, std::vector<std::string> entry) = 0;
  virtual void reStart(std::shared_ptr<gomoku_t> game) = 0;
  virtual void turn(std::shared_ptr<gomoku_t> game, std::vector<std::string> entry) = 0;
  virtual void info(std::shared_ptr<gomoku_t> game, std::vector<std::string> entry) = 0;
  virtual void begin(std::shared_ptr<gomoku_t> game) = 0;
  virtual void board(ISystem *system, std::shared_ptr<gomoku_t> game) = 0;
  virtual void about() = 0;
  virtual void error(COMMAND_ERROR command) = 0;
  virtual void godMode(std::shared_ptr<gomoku_t> game, std::vector<std::string> entry) = 0;
};