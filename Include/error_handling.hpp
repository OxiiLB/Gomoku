/*
** EPITECH PROJECT, 2024
** Gomoku
** File description:
** error_handling
*/

#pragma once

#include <exception>

class Example : public std::exception {
    const char *what() const noexcept override { return "Example"; }
};
