/*
** EPITECH PROJECT, 2024
** Gomoku
** File description:
** mcts
*/

#include <iostream>
#include "mcts.hpp"

///////////////////////////////////////////////////////////////////////////////////////////
std::ostream &operator<<(std::ostream &os, const TILE_STATE entry)
{
  switch (entry) {
  case TILE_STATE::EMPTY:
    os << "X";
    break;
  case TILE_STATE::ME:
    os << "1";
    break;
  case TILE_STATE::PLAYER2:
    os << "2";
    break;
  default:
    os << "UNDEFINED";
    break;
  }
  return os;
}
void displayCurrGame(gomoku_t *_game)
{
  int space = 1;
  for (int i = _game->size.y; i > 9; i /= 10)
    space++;

  auto placeSpaceHeight = [](int x, int nbr) {
    int remove_space = 0;
    for (int i = nbr; i > 9; i /= 10)
      remove_space++;
    x -= remove_space;
    for (int i = 0; i < x; i++)
      std::cout << " ";
  };

  std::cout << std::endl;
  for (int i = 0; i < _game->size.y; i++) {
    std::cout << i;
    placeSpaceHeight(space, i);
    std::cout << "| ";
    for (int j = 0; j < _game->size.x; j++) {
      std::cout << _game->map[i][j] << " ";
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}
/////////////////////////////////////////////////////////////////////////////////////////////

Node *MCTS::select(Node *node)
{
    // while (!node->isTerminal() && node->isFullyExpanded())
    // {
    //     node = node->findBestChild();
    // }
    return node;
}

Node *MCTS::expand(Node *node)
{
    // if (node->isFullyExpanded())
    // {
    //     return node;
    // }
    // return node->expand();
    return node;
}

int MCTS::simulate(Node *node)
{
    gomoku_t simulatedState = node->getGameState();
    bool isCurrentPlayer = simulatedState.my_turn;
    int depth = 0;

    if (simulatedState.state != GAME_STATE::PLAY)
    {
        return -1;
    }
    std::pair<int, int> move;
    std::vector<std::pair<int, int>> availableMovesMe = _gameLogic.getAvailableAdjacentMoves(simulatedState, TILE_STATE::ME);
    std::vector<std::pair<int, int>> availableMovesOpponent = _gameLogic.getAvailableAdjacentMoves(simulatedState, TILE_STATE::PLAYER2);
    while (simulatedState.state == GAME_STATE::PLAY)
    {
        if (availableMovesMe.empty())
        {
            availableMovesMe = _gameLogic.getAvailableMoves(simulatedState);
        }
        if (availableMovesOpponent.empty())
        {
            availableMovesOpponent = _gameLogic.getAvailableMoves(simulatedState);
        }

        if (isCurrentPlayer)
        {
            move = availableMovesMe[rand() % availableMovesMe.size()];
        }
        else
        {
            move = availableMovesOpponent[rand() % availableMovesOpponent.size()];
        }
        simulatedState.map[move.first][move.second] = isCurrentPlayer ? TILE_STATE::ME : TILE_STATE::PLAYER2;
        simulatedState.my_turn = !isCurrentPlayer;

        if (isCurrentPlayer && _gameLogic.checkWin(simulatedState))
        {
            simulatedState.state = GAME_STATE::WIN;
            return depth;
        }

        if (_gameLogic.checkDraw(simulatedState))
        {
            simulatedState.state = GAME_STATE::LOSE;
            return -1;
        }

        isCurrentPlayer = !isCurrentPlayer;
        availableMovesMe = _gameLogic.getAvailableAdjacentMoves(simulatedState, TILE_STATE::ME);
        availableMovesOpponent = _gameLogic.getAvailableAdjacentMoves(simulatedState, TILE_STATE::PLAYER2);

        depth++;
    }
    return -1;
}

void MCTS::backPropagate(Node *node, int depth)
{
    while (node != nullptr)
    {
        if (depth >= 0)
        {
            node->updateValue(1.0);
            node->addWinningDepth(depth);
        }

        node = node->getParent();
    }
}

Node *MCTS::getBestChildInfo(gomoku_t &game)
{
    std::cout << "root move: " << game.me.x << " " << game.me.y << std::endl; ////////////////////
    _root = std::make_unique<Node>(game, nullptr, game.me);
    std::vector<std::pair<int, int>> testMoves = _gameLogic.getAvailableAdjacentMoves(game, TILE_STATE::ME);

    for (auto &move : testMoves)
    {
        if (game.me.x == move.first && game.me.y == move.second)
        {
            continue;
        }
        std::cout << "test move: " << move.first << " " << move.second << std::endl; ////////////////////
        Node *child = _root->expand(move);
        child->setFirstMove(move);
        int depth = simulate(child);
        std::cout << "depth: " << depth << std::endl; ////////////////////
        backPropagate(child, depth);
    }
    Node *bestChild = _root->findBestChild();
    return bestChild;
}
