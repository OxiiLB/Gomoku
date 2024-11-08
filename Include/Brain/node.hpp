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
#include "macro.hpp"

class Node {
    public:
        Node(const gomoku_t &gameState, Node *parent = nullptr, coord_t move = {0, 0})
            : _state(gameState), _parent(parent), _lastMove(move), _value(0), _visits(0) { initUntriedMoves(); }

        bool isFullyExpanded() const { return _untriedMoves.empty(); }
        bool isTerminal() const { return (_state.win != GAME_STATE::PLAY); }

        Node *expand();
        Node *findBestChild(double explorationParam = 1.41) const;

        void updateValue(double result) { _value += result; }
        void updateNbOfVisits() { _visits++; }

        double getValue() const { return _value; }
        int getNbOfVisits() const { return _visits; }
        Node *getParent() const { return _parent; }
        gomoku_t getState() const { return _state; }
        std::pair<int, int> getMove() const { return {_lastMove.x, _lastMove.y}; }

    private:
        gomoku_t _state;
        Node *_parent;
        coord_t _lastMove;
        double _value;
        int _visits;
        std::vector<std::unique_ptr<Node>> _children;
        std::vector<std::pair<int, int>> _untriedMoves;

        void initUntriedMoves();
};
