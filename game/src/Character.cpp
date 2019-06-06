/*
** EPITECH PROJECT, 2019
** IndieStudio_2018
** File description:
** Character.cpp
*/

#include "../include/Character.hpp"

game::Character::Character():
    Entity(game::character)
{
}

void game::Character::setPosition(const s_pos pos)
{
    _pos = pos;
}

game::s_pos &game::Character::getPosition() noexcept
{
    return _pos;
}

void game::Character::setSkin(const int skin)
{
    _skin = skin;
}

int &game::Character::getSkin() noexcept
{
    return _skin;
}

void game::Character::setDirection(const std::string direction)
{
    _direction = direction;
}

std::string &game::Character::getDirection() noexcept
{
    return _direction;
}