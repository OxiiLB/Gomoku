/*
** EPITECH PROJECT, 2024
** Gomoku
** File description:
** node
*/

#pragma once

#include <vector>
#include <memory>
#include <utility>
#include "struct.hpp"

class Node
{
public:
    Node(const gomoku_t &gameState, Node *parent = nullptr, coord_t move = {0, 0})
        : _gameState(gameState), _parent(parent), _lastMove(move), _minWinDepth(-1) {}

    bool isTerminal() const { return (_gameState.state != GAME_STATE::PLAY); }

    Node *expand(std::pair<int, int> move);
    Node *findBestChild();

    void addWinningDepth(int depth)
    {
        _winningDepths.push_back(depth);
        if (_minWinDepth == -1 || depth < _minWinDepth)
        {
            _minWinDepth = depth;
        }
    }
    
    void setFirstMove(std::pair<int, int> move) { _firstMove = move; }
    
    int getMinWinningDepth() const { return _minWinDepth; }
    std::pair<int, int> getFirstMove() const { return _firstMove; }
    std::pair<int, int> getLastMove() const { return {_lastMove.x, _lastMove.y}; }
    gomoku_t getGameState() const { return _gameState; }
    Node *getParent() const { return _parent; }

    int _winCount = 0;
    int _minWinDepth = std::numeric_limits<int>::max();
    std::vector<int> _winningDepths;

private:
    gomoku_t _gameState;
    Node *_parent;
    coord_t _lastMove;
    std::pair<int, int> _firstMove;
    std::vector<std::unique_ptr<Node>> _children;
};
