/*
** EPITECH PROJECT, 2019
** IndieStudio_2018
** File description:
** Character.cpp
*/

#include "Game/Character.hpp"

game::Character::Character():
    MovableEntity(game::character),
    _hp(3)
{
    _cooldownBomb = std::chrono::high_resolution_clock::now();

}

void game::Character::setId(const t_id id)
{
    _id = id;
}

t_id game::Character::getId()
{
    return _id;
}

void game::Character::deliver(std::string)
{

}

player &game::Character::get_playerdata()
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

void game::Character::setSpawn(const s_pos spawn)
{
    _spawn = spawn;
}

game::s_pos game::Character::getSpawn() const noexcept
{
    return _spawn;
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

void game::Character::setHealthPoints(std::size_t hp)
{
    _hp = hp;
}

std::size_t &game::Character::getHealthPoints() noexcept
{
    return _hp;
}

void game::Character::setCooldownBomb()
{
    // _cooldownBomb = std::chrono::high_resolution_clock::now();

}

size_t game::Character::getCooldownBomb()
{
    auto delay = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsed = delay - _cooldownBomb;

    return elapsed.count() / 1000;
}
