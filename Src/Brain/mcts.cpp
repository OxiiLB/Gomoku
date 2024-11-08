/*
** EPITECH PROJECT, 2024
** Gomoku
** File description:
** mcts
*/

#include <iostream>
#include "mcts.hpp"

Node *MCTS::select(Node *node)
{
    while (!node->isTerminal() && node->isFullyExpanded()) {
        node = node->findBestChild();
    }
    return node;
}

Node *MCTS::expand(Node *node)
{
    if (node->isFullyExpanded()) {
        return node;
    }
    return node->expand();
}

GAME_STATE MCTS::simulate(Node *node)
{
    gomoku_t simulatedState = node->getGameState();
    bool isCurrentPlayer = simulatedState.my_turn;

    if (simulatedState.state != GAME_STATE::PLAY) {
        return simulatedState.state;
    }

    std::vector<std::pair<int, int>> availableMoves = _gameLogic.getAvailableMoves(simulatedState);

    std::vector<std::pair<int, int>> adjacentMoves;
    for (const auto &move : availableMoves) {
        if (std::abs(move.first - node->getMove().first) <= 1 &&
            std::abs(move.second - node->getMove().second) <= 1) {
            adjacentMoves.push_back(move);
        }
    }

    if (!adjacentMoves.empty()) {
        availableMoves = adjacentMoves;
    }

    while (simulatedState.state == GAME_STATE::PLAY) {
        std::pair<int, int> move = availableMoves[rand() % availableMoves.size()];

        simulatedState.map[move.first][move.second] = isCurrentPlayer ? TILE_STATE::ME : TILE_STATE::PLAYER2;
        simulatedState.my_turn = !isCurrentPlayer;

        if (isCurrentPlayer && _gameLogic.checkWin(simulatedState)) {
            simulatedState.state = GAME_STATE::WIN;
            break;
        }

        availableMoves = _gameLogic.getAvailableMoves(simulatedState);

        if (_gameLogic.checkDraw(simulatedState)) {
            simulatedState.state = GAME_STATE::LOSE;
            break;
        }

        isCurrentPlayer = !isCurrentPlayer;
    }

    return simulatedState.state;
}


void MCTS::backPropagate(Node *node, double result)
{
    while (node != nullptr) {
        node->updateNbOfVisits();
        node->updateValue(result);
        node = node->getParent();
    }
}

std::pair<int, int> MCTS::findBestMove(gomoku_t &game)
{
    _root = std::make_unique<Node>(game, nullptr, game.opponent);

    auto start = std::chrono::steady_clock::now();
    auto timeLimit = std::chrono::duration<double>(_timeLimit);
    if (timeLimit == std::chrono::duration<double>(0)) { ///////////////////// temp
        timeLimit = std::chrono::duration<double>(1);
    }

    while (std::chrono::steady_clock::now() - start < timeLimit) {
        Node *node = select(_root.get());
        if (!node->isTerminal()) {
            node = expand(node);
        }
        
        GAME_STATE result = simulate(node);
        if (result == GAME_STATE::WIN) {

            std::cout << "WIN: " << static_cast<double>(result) << std::endl; ////////////////////////////////////
        } else {
            std::cout << "LOSE: " << static_cast<double>(result) << std::endl; ////////////////////////////////////
        }

        backPropagate(node, static_cast<double>(result));
    }

    std::pair<int, int> bestMove = _root->findBestChild(0)->getMove();

    return bestMove;
}
