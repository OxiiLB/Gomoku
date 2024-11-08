/*
** EPITECH PROJECT, 2024
** Gomoku
** File description:
** i_command
*/

#pragma once
#include "struct.hpp"
#include <string>
#include <i_system.hpp>

class ICommand {
    public:
        virtual ~ICommand() = default;
        virtual void start(gomoku_t *game, std::vector<std::string> entry) = 0;
        virtual void turn(int x, int y) = 0;
        virtual void begin() = 0;
        virtual void board(ISystem *system, gomoku_t *game) = 0;
        virtual void about() = 0;
        virtual void error(COMMANDERROR command) = 0;
};