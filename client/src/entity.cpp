/*
** EPITECH PROJECT, 2019
** entity
** File description:
** entity
*/

#include "../include/client/entity.hpp"

void client::Character::setId(const t_id id)
{
    _id = id;
}

t_id client::Character::getId() const noexcept
{
    return _id;
}

void client::Character::setSkin(int skin)
{
    _skin = skin;
}

int client::Character::getSkin() const
{
    return _skin;
}

void client::Character::setPosition(irr::core::vector3df position)
{
    _position = position;
}

irr::core::vector3df client::Character::getPosition() const
{
    return _position;
}

void client::Character::setNode(irr::scene::IAnimatedMeshSceneNode * node)
{
    _node = node;
}

irr::scene::IAnimatedMeshSceneNode *client::Character::getNode() const
{
    return _node;
}