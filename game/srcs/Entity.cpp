/*
** EPITECH PROJECT, 2019
** IndieStudio_2018
** File description:
** Entity.cpp
*/

#include "Game/Entity.hpp"

game::Entity::Entity(const game::EntityType &type):
    id(generateID()),
    _type(type)
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

game::EntityType game::Entity::getType() const noexcept
{
    return _type;
}

t_id game::Entity::generateID() const noexcept
{
    static t_id lastID = 0;
    return (lastID++);
}
