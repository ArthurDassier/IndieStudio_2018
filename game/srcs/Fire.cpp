/*
** EPITECH PROJECT, 2019
** IndieStudio_2018
** File description:
** Fire.cpp
*/

#include "Game/Fire.hpp"

game::Fire::Fire(float x, float y):
    Explosion(game::fire, x, y)
{
    _posX = x;
    _posY = y;
    _cooldownExplose = std::chrono::high_resolution_clock::now();
}

game::Fire &game::Fire::operator=(game::Fire const &other)
{
    Fire f(_posX, _posY);

    return f;
}
