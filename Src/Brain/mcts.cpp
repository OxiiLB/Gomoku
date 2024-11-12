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

int MCTS::simulate(Node *node) {
    gomoku_t simulatedState = node->getGameState();
    bool isCurrentPlayer = simulatedState.my_turn;
    int depth = 0;

    if (simulatedState.state != GAME_STATE::PLAY) {
        return -1;
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
        depth++;

        if (isCurrentPlayer && _gameLogic.checkWin(simulatedState)) {
            simulatedState.state = GAME_STATE::WIN;
            return depth;
        }

        availableMoves = _gameLogic.getAvailableMoves(simulatedState);
        if (_gameLogic.checkDraw(simulatedState)) {
            simulatedState.state = GAME_STATE::LOSE;
            return -1;
        }

        isCurrentPlayer = !isCurrentPlayer;
    }
    return -1;
}


void MCTS::backPropagate(Node *node, int depth) {
    while (node != nullptr) {
        if (depth > 0) {
            node->updateValue(1.0);
            node->addWinningDepth(depth);
        } else {
            node->updateValue(0.0);
        }

        node = node->getParent();
    }
}


Node *MCTS::getBestChildInfo(gomoku_t &game)
{
    _root = std::make_unique<Node>(game, nullptr, game.opponent);

    auto start = std::chrono::steady_clock::now();
    auto timeLimit = std::chrono::duration<double>(_timeLimit);
    if (timeLimit == std::chrono::duration<double>(0)) { ///// Temporary fix
        timeLimit = std::chrono::duration<double>(1);
    }

    while (std::chrono::steady_clock::now() - start < timeLimit) {
        Node *node = select(_root.get());
        if (!node->isTerminal()) {
            node = expand(node);
        }
        
        int depth = simulate(node);

        backPropagate(node, depth);
    }

    Node *bestChild = _root->findBestChild();

    return bestChild;
}
