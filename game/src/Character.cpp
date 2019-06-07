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

void game::Character::setId(const t_id id)
{
    _id = id;
}

void game::Character::setPosition(const s_pos pos)
{
    _pos = pos;
}

game::s_pos &game::Character::getPosition() noexcept
{
    return _pos;
}

void game::Character::setPosition3df(const irr::core::vector3df pos)
{
    _pos3df = pos;
}

irr::core::vector3df game::Character::getPosition3df() const noexcept
{
    return _pos3df;
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

void game::Character::setNode(irr::scene::IAnimatedMeshSceneNode *node)
{
    _node = node;
}

irr::scene::IAnimatedMeshSceneNode *game::Character::getNode() const noexcept
{
    return _node;
}