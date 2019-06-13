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
    posX = x;
    posY = y;
    _power = power;
    _cooldownExplose = std::chrono::high_resolution_clock::now();

}

size_t game::Bomb::checkTimeExplosion()
{
    auto delay = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsed = delay - _cooldownExplose;

    return elapsed.count() / 1000;
}

void game::Bomb::destroyMap()
{
    // for (int i = posX + 1, j = 0; i != map.size() && j != _power; i++, j++) {
    //     if (std::rand() % 25 == 12)
    //         map[i][posY] = 'F';
    //     else
    //         map[i][posY] = ' ';
    // }
    // for (int i = posX - 1, j = 0; i != - 1 && i != _power; i--, j++) {
    //     if (std::rand() % 25 == 12)
    //         map[i][posY] = 'F';
    //     else
    //         map[i][posY] = ' ';
    // }
    // for (int i = posY + 1, j = 0; i != map[posX].size() - 1 && j != _power; i++, j++) {
    //     if (std::rand() % 25 == 12)
    //         map[posX][i] = 'F';
    //     else
    //         map[posX][i] = ' ';
    // }
    // for (int i = posY - 1, j = 0; i != - 1 && j != _power; i--, j++) {
    //     if (std::rand() % 25 == 12)
    //         map[posX][i] = 'F';
    //     else
    //         map[posX][i] = ' ';
    // }
}

void game::Bomb::RefreshBomb()
{
    // map[posX][posY] = 'O';
    if (checkTimeExplosion() < 1)
        return;
    destroyMap();
    _alive = false;
}

bool game::Bomb::getAlive()
{
    return _alive;
}
