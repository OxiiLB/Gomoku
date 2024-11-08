/*
** EPITECH PROJECT, 2024
** Gomoku
** File description:
** mcts
*/

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

double MCTS::simulate(Node *node)
{
    gomoku_t simulatedState = node->getState();

    while (simulatedState.win == GAME_STATE::PLAY) {
        std::vector<std::pair<int, int>> availableMoves = _gameLogic.getAvailableMoves(simulatedState);
        std::pair<int, int> randomMove = availableMoves[rand() % availableMoves.size()];

        simulatedState.map[randomMove.first][randomMove.second] = 
            (simulatedState.my_turn ? TILE_STATE::ME : TILE_STATE::PLAYER2);
        simulatedState.my_turn = !simulatedState.my_turn;

        if (_gameLogic.checkWin(simulatedState)) {
            simulatedState.win = simulatedState.my_turn ? GAME_STATE::LOSE : GAME_STATE::WIN;
        } else if (_gameLogic.checkDraw(simulatedState)) {
            simulatedState.win = GAME_STATE::LOSE;
        }
    }
    return simulatedState.win == GAME_STATE::WIN ? 1.0 : (simulatedState.win == GAME_STATE::LOSE ? 0.0 : 0.5);

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

    while (std::chrono::steady_clock::now() - start < timeLimit) {
        Node *node = select(_root.get());
        if (!node->isTerminal()) {
            node = expand(node);
        }
        double result = simulate(node);
        backPropagate(node, result);
    }
    return _root->findBestChild(0)->getMove();
}
