/*
** EPITECH PROJECT, 2024
** Gomoku
** File description:
** log
*/

#pragma once

#include "enum.hpp"
#include <iostream>

class Log {
public:
  Log();
  ~Log();

  void SendResponse(std::string message);
  void printCommandError(COMMANDS command);
  void printCommandSuccess(COMMANDS command);
  void writeInFile(std::string message);
};