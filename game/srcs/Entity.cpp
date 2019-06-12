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

t_id const game::Entity::getId() const noexcept
{
    return id;
}

void game::Entity::setPosition(const s_pos &pos)
{
    _pos = pos;
}

game::s_pos &game::Entity::getPosition() noexcept
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
