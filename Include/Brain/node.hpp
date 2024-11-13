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
          _minWinDepth(-1) {}

    // bool isFullyExpanded() const { return _untriedMoves.empty(); }
    bool isTerminal() const { return (_gameState.state != GAME_STATE::PLAY); }

    Node *expand(std::pair<int, int> move);
    Node *findBestChild();

    void updateValue(double result) { _value += result; }
    void addWinningDepth(int depth)
    {
        _winningDepths.push_back(depth);
        if (_minWinDepth == -1 || depth < _minWinDepth)
        {
            _minWinDepth = depth;
        }
    }

    double getValue() const { return _value; }

    int getMinWinningDepth() const
    {
        return _minWinDepth;
    }
    Node *getParent() const { return _parent; }
    gomoku_t getGameState() const { return _gameState; }
    std::pair<int, int> getMove() const { return {_lastMove.x, _lastMove.y}; }
    void setFirstMove(std::pair<int, int> move) { _firstMove = move; }
    std::pair<int, int> getFirstMove() const { return _firstMove; }

    std::vector<int> _winningDepths;
    int _winCount = 0;
    int _minWinDepth = std::numeric_limits<int>::max();

private:
    gomoku_t _gameState;
    Node *_parent;
    coord_t _lastMove;
    std::pair<int, int> _firstMove;
    double _value;
    std::vector<std::unique_ptr<Node>> _children;
    // std::vector<std::pair<int, int>> _untriedMoves;

    void initUntriedMoves();
};
