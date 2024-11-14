/*
** EPITECH PROJECT, 2024
** Gomoku
** File description:
** node
*/

#include <cmath>
#include <limits>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include "node.hpp"

Node *Node::expand(std::pair<int, int> move)
{
    gomoku_t newGameState = _gameState;

    newGameState.map[move.first][move.second] = TILE_STATE::ME;

    coord_t moveCoord = {move.first, move.second};
    auto child = std::make_unique<Node>(newGameState, this, moveCoord);
    _children.push_back(std::move(child));

    return _children.back().get();
}

Node *Node::findBestChild() {
    Node *bestChild = nullptr;
    int bestDepth = std::numeric_limits<int>::max();

    for (auto &child : _children) {
        if (child->getMinWinningDepth() < bestDepth) {
            bestDepth = child->getMinWinningDepth();
            bestChild = child.get();
        }
    }
    return bestChild;
}
