/*
** EPITECH PROJECT, 2019
** IndieStudio_2018
** File description:
** Bomb.cpp
*/

#include "Game/Bomb.hpp"

game::Bomb::Bomb():
    Explosion(game::bomb, 0, 0),
    _power(3)
{
}

game::Bomb::Bomb(float x, float y, size_t power = 3):
    Explosion(game::bomb, x, y),
    _power(power)
{
    // _cooldownExplose = std::chrono::high_resolution_clock::now();
}

game::Bomb game::Bomb::operator=(Bomb const &other)
{
    Bomb b(other.getPosX(), other.getPosZ(), _power);
    return b;
}

size_t game::Bomb::getPower() const noexcept
{
    return _power;
}
