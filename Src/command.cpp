/*
** EPITECH PROJECT, 2024
** Gomoku
** File description:
** command
*/

#include "command.hpp"

Command::Command() {}

Command::~Command() {}

void Command::start(gomoku_t *game, std::vector<std::string> entry)
{
  if (entry.size() < 2) {
    error(COMMAND_ERROR::START);
    return;
  }
  game->size.x = atoi(entry.back().c_str());
  game->size.y = atoi(entry.back().c_str());
  if (game->size.x < 5) {
    error(COMMAND_ERROR::START);
    return;
  }
  game->map.resize(game->size.y,
                   std::vector<TILE_STATE>(game->size.x, TILE_STATE::EMPTY));
  game->state = GAME_STATE::PLAY;
  std::cout << "OK - everything is good" << std::endl;
}

void Command::rectStart(gomoku_t *game, std::vector<std::string> entry)
{
  if (entry.size() < 3) {
    error(COMMAND_ERROR::START);
    return;
  }
  game->size.x = atoi(entry.at(1).c_str());
  game->size.y = atoi(entry.at(2).c_str());
  if (game->size.x < 5 || game->size.y < 5) {
    error(COMMAND_ERROR::RECTSTART);
    return;
  }
  game->map.resize(game->size.y,
                   std::vector<TILE_STATE>(game->size.x, TILE_STATE::EMPTY));
  game->state = GAME_STATE::PLAY;
  std::cout << "OK - parameters are good" << std::endl;
}

void Command::reStart(gomoku_t *game)
{
  game->map.clear();
  game->map.resize(game->size.y,
                   std::vector<TILE_STATE>(game->size.x, TILE_STATE::EMPTY));
  std::cout << "OK" << std::endl;
}

void Command::turn(gomoku_t *game, std::vector<std::string> entry)
{
  if (entry.size() < 3) {
    error(COMMAND_ERROR::TURN);
    return;
  }
  game->opponent.x = atoi(entry.at(1).c_str());
  game->opponent.y = atoi(entry.at(2).c_str());
  if (game->opponent.x < 0 || game->opponent.y < 0 ||
      game->opponent.x >= game->size.x || game->opponent.y >= game->size.y ||
      game->map[game->opponent.x][game->opponent.y] != TILE_STATE::EMPTY) {
    error(COMMAND_ERROR::TURN);
    return;
  }
  game->map[game->opponent.x][game->opponent.y] = TILE_STATE::PLAYER2;
  game->my_turn = true;
  std::cout << game->opponent.x << "," << game->opponent.y << std::endl;
}

void Command::begin(gomoku_t *game)
{
  std::cout << "BEGIN" << std::endl;
  std::cout << "1, 1" << std::endl;
  game->my_turn = false;
}

void Command::board(ISystem *system, gomoku_t *game)
{
  bool isRunning = true;
  while (isRunning) {
    std::string line;
    std::getline(std::cin, line);
    std::vector<std::string> entry = system->splitString(line);
    if (entry.at(0) == "DONE")
      isRunning = false;
    else {
      if (entry.size() < 3) {
        std::cout << "ERROR message - invalid argument" << std::endl;
        error(COMMAND_ERROR::BOARD);
        return;
      }
      int x = atoi(entry.at(0).c_str());
      int y = atoi(entry.at(1).c_str());
      int player = atoi(entry.at(2).c_str());
      if (x < 0 || y < 0 || x >= game->size.x || y >= game->size.y ||
          game->map[x][y] != TILE_STATE::EMPTY) {
        error(COMMAND_ERROR::BOARD);
        return;
      }
      if (player == 1) {
        game->map[x][y] = TILE_STATE::ME;
        game->me.x = x;
        game->me.y = y;
      } else {
        game->map[x][y] = TILE_STATE::PLAYER2;
        game->opponent.x = x;
        game->opponent.y = y;
      }
    }
  }
}

void Command::about()
{
  std::cout << "name=\"pbrain-gomoku-ai\", version=\"1.0\", author=\"Dvaking, "
               "Oxi, Alea\", country=\"FR\""
            << std::endl;
}

void Command::info(gomoku_t *game, std::vector<std::string> entry)
{
  if (entry.size() < 3) {
    error(COMMAND_ERROR::START);
    return;
  }
  int value = atoi(entry.at(2).c_str());
  std::string command = entry.at(1);
  if (command == "timeout_turn") {
    game->global_info.timeout_turn = std::chrono::milliseconds(value);
  } else if (command == "timeout_match") {
    game->global_info.timeout_match = std::chrono::milliseconds(value);
  } else if (command == "time_left") {
    game->global_info.time_left = std::chrono::milliseconds(value);
  } else if (command == "max_memory") {
    game->global_info.max_memory = value;
  } else if (command == "game_type") {
    switch (value) {
    case 0:
      game->global_info.game_type = GAME_TYPE::HUMAN;
      break;
    case 1:
      game->global_info.game_type = GAME_TYPE::BRAIN;
      break;
    case 2:
      game->global_info.game_type = GAME_TYPE::TOURNAMENT;
      break;
    case 3:
      game->global_info.game_type = GAME_TYPE::NETWORK_TOURNAMENT;
      break;
    default:
      game->global_info.game_type = GAME_TYPE::HUMAN;
      break;
    }
  } else if (command == "rule") {
    switch (value) {
    case 1:
      game->global_info.rule = RULE::EXACTLY_FIVE;
      break;
    case 2:
      game->global_info.rule = RULE::CONTINUOUS;
      break;
    case 4:
      game->global_info.rule = RULE::RENJU;
      break;
    case 8:
      game->global_info.rule = RULE::CARO;
      break;
    default:
      game->global_info.rule = RULE::EXACTLY_FIVE;
      break;
    }
  } else if (command == "evaluate") {
    if (entry.size() < 4)
      return;
    game->global_info.evaluate.x = atoi(entry.at(2).c_str());
    game->global_info.evaluate.y = atoi(entry.at(3).c_str());
  } else if (command == "folder") {
    game->global_info.folder = value;
  }
}

void Command::godMode(gomoku_t *game, std::vector<std::string> entry)
{
  if (entry.size() < 2) {
    return;
  }
  if (entry.at(1) == "map")
    game->god_mode.map = !game->god_mode.map;
}

void Command::error(COMMAND_ERROR command)
{
  switch (command) {
  case COMMAND_ERROR::START:
    std::cout << "ERROR message - unsupported size or other error" << std::endl;
    break;
  case COMMAND_ERROR::BOARD:
    std::cout << "ERROR message - tile already played or argument invalid"
              << std::endl;
    break;
  case COMMAND_ERROR::TURN:
    std::cout << "ERROR message - invalid argument" << std::endl;
    break;
  case COMMAND_ERROR::BEGIN:
    std::cout << "ERROR message - invalid argument or out of table"
              << std::endl;
    break;
  case COMMAND_ERROR::RECTSTART: {
    std::cout
        << "ERROR message - rectangular board is not supported or other error"
        << std::endl;
  } break;
  default:
    break;
  }
}