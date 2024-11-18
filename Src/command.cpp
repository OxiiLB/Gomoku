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
  if (entry.size() < 2)
  {
    _log.printCommandError(COMMANDS::START);
    return;
  }
  game->size.x = atoi(entry.back().c_str());
  game->size.y = atoi(entry.back().c_str());
  if (game->size.x < 5)
  {
    _log.printCommandError(COMMANDS::START);
    return;
  }
  game->map.resize(game->size.y,
                   std::vector<TILE_STATE>(game->size.x, TILE_STATE::EMPTY));
  game->state = GAME_STATE::PLAY;
  _log.printCommandSuccess(COMMANDS::START);
}

void Command::rectStart(gomoku_t *game, std::vector<std::string> entry)
{
  if (entry.size() < 3)
  {
    _log.printCommandError(COMMANDS::START);
    return;
  }
  game->size.x = atoi(entry.at(1).c_str());
  game->size.y = atoi(entry.at(2).c_str());
  if (game->size.x < 5 || game->size.y < 5)
  {
    _log.printCommandError(COMMANDS::RECTSTART);
    return;
  }
  game->map.resize(game->size.y,
                   std::vector<TILE_STATE>(game->size.x, TILE_STATE::EMPTY));
  game->state = GAME_STATE::PLAY;
  _log.printCommandSuccess(COMMANDS::RECTSTART);
}

void Command::reStart(gomoku_t *game)
{
  game->map.clear();
  game->map.resize(game->size.y,
                   std::vector<TILE_STATE>(game->size.x, TILE_STATE::EMPTY));
  _log.printCommandSuccess(COMMANDS::RESTART);
}

void Command::turn(gomoku_t *game, std::vector<std::string> entry)
{
  if (entry.size() < 3)
  {
    _log.printCommandError(COMMANDS::TURN);
    return;
  }
  game->opponent.x = atoi(entry.at(1).c_str());
  game->opponent.y = atoi(entry.at(2).c_str());
  if (game->opponent.x < 0 || game->opponent.y < 0 ||
      game->opponent.x >= game->size.x || game->opponent.y >= game->size.y ||
      game->map[game->opponent.y][game->opponent.x] != TILE_STATE::EMPTY)
  {
    _log.printCommandError(COMMANDS::TURN);
    return;
  }
  game->map[game->opponent.y][game->opponent.x] = TILE_STATE::PLAYER2;
  game->my_turn = true;
  if (game->initialMoves.size() < 5)
  {
    coord_t coord = {game->opponent.x, game->opponent.y};
    game->initialMoves.push_back(coord);
  }
}

void Command::begin(gomoku_t *game) { game->my_turn = true; }

void Command::board(ISystem *system, gomoku_t *game)
{
  bool isRunning = true;
  while (isRunning)
  {
    std::string line;
    std::getline(std::cin, line);
    std::vector<std::string> entry = system->splitString(line);
    if (entry.at(0) == "DONE")
      isRunning = false;
    else
    {
      if (entry.size() < 3)
      {
        _log.printCommandError(COMMANDS::BOARD);
        continue;
      }
      int x = atoi(entry.at(0).c_str());
      int y = atoi(entry.at(1).c_str());
      int player = atoi(entry.at(2).c_str());
      if (x < 0 || y < 0 || x >= game->size.x || y >= game->size.y ||
          game->map[y][x] != TILE_STATE::EMPTY)
      {
        _log.printCommandError(COMMANDS::BOARD);
        return;
      }
      if (player == 1)
      {
        game->map[y][x] = TILE_STATE::ME;
        game->me.x = x;
        game->me.y = y;
      }
      else
      {
        game->map[y][x] = TILE_STATE::PLAYER2;
        game->opponent.x = x;
        game->opponent.y = y;
      }
      if (game->initialMoves.size() < 5)
      {
        coord_t coord = {x, y};
        game->initialMoves.push_back(coord);
      }
    }
  }
  game->my_turn = true;
  game->state = GAME_STATE::PLAY;
}

void Command::about()
{
  _log.SendResponse("name=\"pbrain-gomoku-ai\",version=\"1.0\",author=\"Dvaking,"
                    "Oxi,Alea\",country=\"FR\"");
}

void Command::info(gomoku_t *game, std::vector<std::string> entry)
{
  if (entry.size() < 3)
  {
    _log.printCommandError(COMMANDS::START);
    return;
  }
  int value = atoi(entry.at(2).c_str());
  std::string command = entry.at(1);
  if (command == "timeout_turn")
  {
    game->global_info.timeout_turn = std::chrono::milliseconds(value);
  }
  else if (command == "timeout_match")
  {
    game->global_info.timeout_match = std::chrono::milliseconds(value);
  }
  else if (command == "time_left")
  {
    game->global_info.time_left = std::chrono::milliseconds(value);
  }
  else if (command == "max_memory")
  {
    game->global_info.max_memory = value;
  }
  else if (command == "game_type")
  {
    switch (value)
    {
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
  }
  else if (command == "rule")
  {
    switch (value)
    {
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
  }
  else if (command == "evaluate")
  {
    if (entry.size() < 4)
      return;
    game->global_info.evaluate.x = atoi(entry.at(2).c_str());
    game->global_info.evaluate.y = atoi(entry.at(3).c_str());
  }
  else if (command == "folder")
  {
    game->global_info.folder = value;
  }
}

void Command::godMode(gomoku_t *game, std::vector<std::string> entry)
{
  if (entry.size() < 2)
  {
    return;
  }
  if (entry.at(1) == "map")
    game->god_mode.map = !game->god_mode.map;
}

void Command::takeBack(gomoku_t *game, std::vector<std::string> entry)
{
  if (entry.size() < 3)
    return;

  int x = atoi(entry.at(1).c_str());
  int y = atoi(entry.at(2).c_str());
  if (x < 0 || y < 0 || x >= game->size.x || y >= game->size.y)
    return;
  game->map[y][x] = TILE_STATE::EMPTY;
}

void Command::play(gomoku_t *game, std::vector<std::string> entry)
{
  if (entry.size() < 3)
  {
    _log.printCommandError(COMMANDS::PLAY);
    return;
  }
  game->me.x = atoi(entry.at(1).c_str());
  game->me.y = atoi(entry.at(2).c_str());
  if (game->me.x < 0 || game->me.y < 0 ||
      game->me.x >= game->size.x || game->me.y >= game->size.y ||
      game->map[game->me.y][game->me.x] != TILE_STATE::EMPTY)
  {
    _log.printCommandError(COMMANDS::PLAY);
    return;
  }
  game->map[game->me.y][game->me.x] = TILE_STATE::ME;
  game->my_turn = true;
  if (game->initialMoves.size() < 5)
  {
    coord_t coord = {game->me.x, game->me.y};
    game->initialMoves.push_back(coord);
  }
}

void Command::swap2Board(ISystem *system, gomoku_t *game)
{
  bool isRunning = true;

  // Clear any initial moves in game to start fresh
  game->initialMoves.clear();

  while (isRunning)
  {
    std::string line;
    std::getline(std::cin, line);
    std::vector<std::string> entry = system->splitString(line);

    // Fin du signal "SWAP2BOARD" en cours, on peut évaluer la situation
    if (entry.size() == 1 && entry[0] == "DONE")
    {
      int numMoves = game->initialMoves.size();

      if (numMoves == 0)
      {
        // Cas 1 : L'IA propose les trois premières pierres
        std::cout << "7,7 8,8 6,8" << std::endl;
        game->initialMoves = {{7, 7}, {8, 8}, {6, 8}};
        game->map[7][7] = TILE_STATE::ME;
        game->map[8][8] = TILE_STATE::ME;
        game->map[6][8] = TILE_STATE::ME;
        isRunning = false;
      }
      else if (numMoves == 3)
      {
        // Cas 2 : Trois pierres sont déjà placées, choix du swap ou d'un 4e coup
        bool shouldSwap = false; // Logique pour décider du swap

        if (shouldSwap)
        {
          std::cout << "SWAP" << std::endl;
        }
        else
        {
          std::cout << "8,8" << std::endl;
          game->initialMoves.push_back({8, 8}); // Ajout de la 4e pierre
        }
        isRunning = false;
      }
      else if (numMoves == 5)
      {
        // Cas 3 : Cinq pierres sont déjà placées, choix du swap ou d'un 6e coup
        bool shouldSwap = false; // Logique pour décider du swap

        if (shouldSwap)
        {
          std::cout << "SWAP" << std::endl;
        }
        else
        {
          std::cout << "6,8" << std::endl;
          game->initialMoves.push_back({6, 8}); // Ajout de la 6e pierre
        }
        isRunning = false;
      }
    }
    // Ajout des coordonnées de coups envoyés par le manager
    else if (entry.size() == 2)
    {
      int x = std::stoi(entry[0]);
      int y = std::stoi(entry[1]);
      game->initialMoves.push_back({x, y});
    }
  }
}