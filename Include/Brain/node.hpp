/*
** EPITECH PROJECT, 2024
** Gomoku
** File description:
** node
*/

#pragma once

#include "board.hpp"
#include <vector>

class Node
{
    public:
        Board _board;
        Node *_parent;
        std::vector<Node *> _children;
        std::pair<int, int> _move;
        int _visits;
        int _score;

        Node(Board board, Node *parent = nullptr, std::pair<int, int> move = {-1, -1})
            : _board(board), _parent(parent), _move(move), _visits(0), _score(0) {}

        bool hasChildren() { return (!_children.empty()); }

        void expand(int boardSize);

        Node *selectBestChild();

    private:
};
