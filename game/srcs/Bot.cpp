/*
** EPITECH PROJECT, 2019
** IndieStudio_2018
** File description:
** Bot.cpp
*/

#include "Game/Bot.hpp"

game::Bot::Bot():
    MovableEntity(bot),
    _hp(3),
    _id(300)
{
    _cooldownBomb = std::chrono::high_resolution_clock::now();
}

t_id game::Bot::getId()
{
    return _id;
}

void game::Bot::deliver(std::string)
{
}

player &game::Bot::get_playerdata()
{
}

void game::Bot::setSpawn(const s_pos spawn)
{
    _spawn = spawn;
}

game::s_pos game::Bot::getSpawn() const noexcept
{
    return _spawn;
}

void game::Bot::setPosition3df(const irr::core::vector3df pos)
{
    _pos3df = pos;
}

irr::core::vector3df game::Bot::getPosition3df() const noexcept
{
    return _pos3df;
}

void game::Bot::setSkin(const int skin)
{
    _skin = skin;
}

int &game::Bot::getSkin() noexcept
{
    return _skin;
}

void game::Bot::setDirection(const std::string direction)
{
    _direction = direction;
}

std::string &game::Bot::getDirection() noexcept
{
    return _direction;
}

void game::Bot::setNode(irr::scene::IAnimatedMeshSceneNode *node)
{
    _node = node;
}

irr::scene::IAnimatedMeshSceneNode *game::Bot::getNode() const noexcept
{
    return _node;
}

void game::Bot::setHealthPoints(std::size_t hp)
{
    _hp = hp;
}

std::size_t &game::Bot::getHealthPoints() noexcept
{
    return _hp;
}

void game::Bot::setCooldownBomb()
{
    _cooldownBomb = std::chrono::high_resolution_clock::now();
}

size_t game::Bot::getPower()
{
    return _power;
}

size_t game::Bot::getCooldownBomb()
{
    auto delay = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsed = delay - _cooldownBomb;

    return elapsed.count() / 1000;
}
