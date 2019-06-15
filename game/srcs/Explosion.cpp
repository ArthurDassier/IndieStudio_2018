/*
** EPITECH PROJECT, 2019
** IndieStudio_2018
** File description:
** Explosion.cpp
*/

#include "Game/Explosion.hpp"

game::Explosion::Explosion(const EntityType &type, float x, float y):
    Entity(type),
    _posX(x),
    _posY(y),
    _alive(true),
    _cooldownExplose(std::chrono::high_resolution_clock::now())
{
    // _cooldownExplose = std::chrono::high_resolution_clock::now();
}

size_t game::Explosion::checkTime()
{
    auto delay = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsed = delay - _cooldownExplose;

    return elapsed.count() / 1000;
}

float game::Explosion::getPosX() const noexcept
{
    return _posX;
}


float game::Explosion::getPosZ() const noexcept
{
    return _posY;
}

void game::Explosion::refresh()
{
    if (checkTime() < 1)
        return;
    _alive = false;
}


bool game::Explosion::getAlive()
{
    return _alive;
}
