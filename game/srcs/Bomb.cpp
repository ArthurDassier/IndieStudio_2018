/*
** EPITECH PROJECT, 2019
** IndieStudio_2018
** File description:
** Bomb.cpp
*/

#include "Game/Bomb.hpp"

game::Bomb::Bomb(float x, float y, size_t power):
    Entity(game::bomb)
{
    _posX = x;
    _posY = y;
    _power = power;
    _cooldownExplose = std::chrono::high_resolution_clock::now();

}

size_t game::Bomb::checkTimeExplosion()
{
    auto delay = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsed = delay - _cooldownExplose;

    return elapsed.count() / 1000;
}

float game::Bomb::getPosX() const noexcept
{
    return _posX;
}


float game::Bomb::getPosZ() const noexcept
{
    return _posY;
}

game::Bomb &game::Bomb::operator=(Bomb const &other)
{
    Bomb b(_posX, _posY, _power);
    return b;
}

void game::Bomb::RefreshBomb()
{
    if (checkTimeExplosion() < 1)
        return;
    _alive = false;
}

bool game::Bomb::getAlive()
{
    return _alive;
}
