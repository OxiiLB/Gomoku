/*
** EPITECH PROJECT, 2024
** Gomoku
** File description:
** system
*/

#pragma once
#include "i_system.hpp"
#include "struct.hpp"

class System: virtual public ISystem {
    public:
        System();
        ~System();
        void gameLoop() override;
        gomoku_t *getGame() override;
        void initiateStruct(gomoku_t *game) override;
        std::vector<std::string> splitString(const std::string &str) override;
        void displayGame(gomoku_t *game) override;

    protected:
        gomoku_t *game;
};