/*
** EPITECH PROJECT, 2019
** entity
** File description:
** entity
*/

#include "Client/Entity.hpp"

Entity::Entity()
{
}

Entity::~Entity()
{
}

Character::Character()
{
}

Character::~Character()
{
}

void Character::setId(const std::size_t id)
{
    _id = id;
}

void Character::setSkin(int skin)
{
    _skin = skin;
}

void Character::setPosition(irr::core::vector3df position)
{
    _position = position;
}

void Character::setNode(irr::scene::IAnimatedMeshSceneNode * node)
{
    _node = node;
}

std::size_t Character::getId() const noexcept
{
    return _id;
}

int Character::getSkin() const
{
    return _skin;
}

irr::core::vector3df Character::getPosition() const
{
    return _position;
}

irr::scene::IAnimatedMeshSceneNode *Character::getNode() const
{
    return _node;
}

Object::Object()
{
}

Object::~Object()
{
}
