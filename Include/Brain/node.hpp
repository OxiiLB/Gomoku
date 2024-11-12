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
    : _gameState(gameState), _parent(parent), _lastMove(move), _value(0), 
      _minWinDepth(0) { initUntriedMoves(); }

    bool isFullyExpanded() const { return _untriedMoves.empty(); }
    bool isTerminal() const { return (_gameState.state != GAME_STATE::PLAY); }

    Node *expand();
    Node *findBestChild();

    void updateValue(double result) { _value += result; }
    void addWinningDepth(int depth)
    {
        _totalWinDepth += depth;
        _winCount++;
        if (depth < _minWinDepth || _minWinDepth == 0)
        {
            _minWinDepth = depth;
        }
    }

    double getValue() const { return _value; }
    double getAverageWinningDepth() const
    {
        return (_winCount > 0) ? (_totalWinDepth / _winCount) : 0;
    }
    int getMinWinningDepth() const
    {
        return (_winCount > 0) ? _minWinDepth : 0;
    }
    Node *getParent() const { return _parent; }
    gomoku_t getGameState() const { return _gameState; }
    std::pair<int, int> getMove() const { return {_lastMove.x, _lastMove.y}; }

private:
    gomoku_t _gameState;
    Node *_parent;
    coord_t _lastMove;
    double _value;
    int _totalWinDepth = 0;
    int _winCount = 0;
    int _minWinDepth = 0;
    std::vector<std::unique_ptr<Node>> _children;
    std::vector<std::pair<int, int>> _untriedMoves;

    void initUntriedMoves();
};
