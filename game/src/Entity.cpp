/*
** EPITECH PROJECT, 2019
** IndieStudio_2018
** File description:
** Entity.cpp
*/

#include "Entity.hpp"

game::Entity::Entity():
    id(generateID())
{
}

game::Entity::Entity(const s_pos &pos):
    id(generateID()),
    _pos(pos)
{
}

void game::Entity::setPosition(const s_pos &pos)
{
    _pos = pos;
}

game::s_pos game::Entity::getPosition() const noexcept
{
    return _pos;
}

t_id game::Entity::generateID() const noexcept
{
    static t_id lastID = 0;
    return (lastID++);
}