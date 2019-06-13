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


void game::Bomb::destroyMap()
{
    // for (int i = _posX + 1, j = 0; i != map.size() && j != _power; i++, j++) {
    //     if (std::rand() % 25 == 12)
    //         map[i][_posY] = 'F';
    //     else
    //         map[i][_posY] = ' ';
    // }
    // for (int i = _posX - 1, j = 0; i != - 1 && i != _power; i--, j++) {
    //     if (std::rand() % 25 == 12)
    //         map[i][_posY] = 'F';
    //     else
    //         map[i][_posY] = ' ';
    // }
    // for (int i = _posY + 1, j = 0; i != map[_posX].size() - 1 && j != _power; i++, j++) {
    //     if (std::rand() % 25 == 12)
    //         map[_posX][i] = 'F';
    //     else
    //         map[_posX][i] = ' ';
    // }
    // for (int i = _posY - 1, j = 0; i != - 1 && j != _power; i--, j++) {
    //     if (std::rand() % 25 == 12)
    //         map[_posX][i] = 'F';
    //     else
    //         map[_posX][i] = ' ';
    // }
}

void game::Bomb::RefreshBomb()
{
    // map[_posX][_posY] = 'O';
    if (checkTimeExplosion() < 1)
        return;
    destroyMap();
    _alive = false;
}

bool game::Bomb::getAlive()
{
    return _alive;
}
