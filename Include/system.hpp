/*
** EPITECH PROJECT, 2024
** Gomoku
** File description:
** system
*/

#pragma once
#include "i_system.hpp"
#include "defenseAlgorithm.hpp"
#include "struct.hpp"
#include <thread>
#include <atomic>
#include <memory>

class System : virtual public ISystem
{
public:
  System();
  ~System();
  void gameLoop() override;
  gomoku_t *getGame() override;
  void initiateStruct(std::shared_ptr<gomoku_t> game) override;
  std::vector<std::string> splitString(const std::string &str) override;
  void displayGame(std::shared_ptr<gomoku_t> game) override;
  void command(std::shared_ptr<gomoku_t> game,
               std::vector<std::string> entry,
               bool *isRunning) override;

protected:
  defenseAlgorithm defense;
  std::thread bgThread;

  std::shared_ptr<gomoku_t> game;
};