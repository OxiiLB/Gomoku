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

    for (i = 0; i < _state.size; i++)
    {
        for (j = 0; j < _state.size; ++j)
        {
            if (_state.map[i][j] == TILE_STATE::EMPTY)
            {
                _untriedMoves.emplace_back(i, j);
            }
        }
    }
}

// Applies an untried move to the game state, then creates a new child node representing the new game state.
Node *Node::expand()
{
    if (_untriedMoves.empty())
    {
        return nullptr;
    }

    auto move = _untriedMoves.back();
    _untriedMoves.pop_back();

    gomoku_t newState = _state;

    newState.map[move.first][move.second] =
        (_state.turn % 2 == 0) ? TILE_STATE::ME : TILE_STATE::PLAYER2;
    newState.turn++;

    Node *child = new Node(newState, this);
    _children.push_back(std::unique_ptr<Node>(child));

    return child;
}

// Returns the child node with the best UCB1 value.
Node *Node::findBestChild(double explorationParam) const
{
    Node *bestChild = nullptr;
    double bestValue = -std::numeric_limits<double>::infinity();

    for (const auto &child : _children)
    {
        double value = (child->_value / child->_visits) +
            explorationParam * std::sqrt(std::log(_visits) / child->_visits);
        if (value > bestValue)
        {
            bestValue = value;
            bestChild = child.get();
        }
    }
    return bestChild;
}
