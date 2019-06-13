/*
** EPITECH PROJECT, 2019
** IndieStudio_2018
** File description:
** Bomb.cpp
*/

#include "Game/Bomb.hpp"

game::Bomb::Bomb(float x, float y, size_t power):
    Explosion(game::bomb, x, y)
{
    _posX = x;
    _posY = y;
    _power = power;
    _cooldownExplose = std::chrono::high_resolution_clock::now();

}

game::Bomb &game::Bomb::operator=(Bomb const &other)
{
    Bomb b(_posX, _posY, _power);
    return b;
}

size_t game::Bomb::getPower() const noexcept
{
    return _power;
}
