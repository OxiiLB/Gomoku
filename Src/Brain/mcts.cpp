/*
** EPITECH PROJECT, 2024
** Gomoku
** File description:
** mcts
*/

#include "mcts.hpp"

// Utilizes the ucb1 formula to calculate the value of a node
float MCTS::calculate(Node *node, int parentVisits, float explorationParam)
{
    float exploitation = static_cast<float>(node->_score / node->_visits);
    float exploration = explorationParam * std::sqrt(std::log(parentVisits) / node->_visits);
    return (exploitation + exploration);
}

Node *MCTS::select(Node *node)
{
    while (node->hasChildren()) {
        Node* bestChild = nullptr;
        float bestValue = 0;

        for (Node *child : node->_children) {
            float value = Node::calculate(child, node->_visits);
            if (value > bestValue) {
                bestValue = value;
                bestChild = child;
            }
        }
        node = bestChild;
    }
    return node;
}
