/*
** EPITECH PROJECT, 2024
** Gomoku
** File description:
** log
*/

#include "log.hpp"
#include <fstream>

Log::Log() {}

Log::~Log() {}

void Log::SendResponse(std::string message)
{
  std::cout << message << std::endl;
}

void Log::printCommandError(COMMANDS command)
{
  std::string message;
  switch (command)
  {
  case COMMANDS::START:
    message = "ERROR message - unsupported size or other error";
    break;
  case COMMANDS::BOARD:
    message = "ERROR message - tile already placed or other error";
    break;
  case COMMANDS::TURN:
    message = "ERROR message - tile already placed or other error";
    break;
  case COMMANDS::BEGIN:
    message = "ERROR message - game already started or other error";
    break;
  case COMMANDS::RECTSTART:
    message = "ERROR message - unsupported size or other error";
    break;
  case COMMANDS::RESTART:
    message = "ERROR message - game not started or other error";
    break;
  case COMMANDS::PLAY:
    message = "ERROR message - unsupported size or other error";
    break;
  default:
    break;
  }
  SendResponse(message);
}

void Log::printCommandSuccess(COMMANDS command)
{
  std::string message;
  switch (command)
  {
  case COMMANDS::START:
    message = "OK";
    break;
  case COMMANDS::BOARD:
    message = "OK - tile placed";
    break;
  case COMMANDS::TURN:
    message = "OK - turn played";
    break;
  case COMMANDS::BEGIN:
    message = "OK - game started";
    break;
  case COMMANDS::RECTSTART:
    message = "OK - parameters are good";
    break;
  case COMMANDS::RESTART:
    message = "OK - game restarted";
    break;
  default:
    break;
  }
  SendResponse(message);
}

void Log::writeInFile(std::string message)
{
  std::ofstream file("pbrain-gomoku-f/log.txt", std::ios::app);
  file << message << std::endl;
  file.close();
}