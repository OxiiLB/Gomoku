/*
** EPITECH PROJECT, 2024
** Gomoku
** File description:
** node
*/

#include "node.hpp"

void Node::expand(int boardSize)
{
    auto moves = _board.getAvailableMoves(boardSize);

    for (const auto &move : moves) {
        Board expandedBoard = _board;
        expandedBoard.play(move.first, move.second);
        _children.push_back(new Node(expandedBoard, this, move));
    }
}

// Identifies & returns child node with highest average score per visit.
Node *Node::selectBestChild()
{
    Node* bestNode = nullptr;
    float bestAvgScore = 0;
    float avgScore = 0;

    for (Node *child : _children) {
        avgScore = static_cast<float>(child->_score / child->_visits);
        if (avgScore > bestAvgScore) {
            bestAvgScore = avgScore;
            bestNode = child;
        }
    }
    return bestNode;
}
