/*
** EPITECH PROJECT, 2024
** Gomoku
** File description:
** node
*/

#include <cmath>
#include <limits>
#include <cstdlib>
#include "node.hpp"

// Adds all possible moves to _untriedMoves based on the empty spaces in the current state.
void Node::initUntriedMoves()
{
    int i = 0;
    int j = 0;

    for (i = 0; i < _gameState.size.x; i++) {
        for (j = 0; j < _gameState.size.y; ++j) {
            if (_gameState.map[i][j] == TILE_STATE::EMPTY) {
                _untriedMoves.emplace_back(i, j);
            }
        }
    }
}

// Applies an untried move to the game state, then creates a new child node representing the new game state.
Node *Node::expand()
{
    if (_untriedMoves.empty()) {
        return this;
    }

    std::pair<int, int> move = _untriedMoves.back();
    _untriedMoves.pop_back();

    gomoku_t newGameState = _gameState;

    newGameState.map[move.first][move.second] = (_gameState.my_turn ? TILE_STATE::ME : TILE_STATE::PLAYER2);
    newGameState.my_turn = !newGameState.my_turn;

    coord_t moveCoord = {move.first, move.second};
    auto child = std::make_unique<Node>(newGameState, this, moveCoord);
    _children.push_back(std::move(child));

    return _children.back().get();
}

// Returns the child node with the best UCB1 value.
Node *Node::findBestChild(double explorationParam) const
{
    Node *bestChild = nullptr;
    double bestValue = -std::numeric_limits<double>::infinity();

    for (const auto &child : _children) {
        double value = (child->_value / child->_visits) +
            explorationParam * std::sqrt(std::log(_visits) / child->_visits);
        if (value > bestValue) {
            bestValue = value;
            bestChild = child.get();
        }
    }
    return bestChild;
}
