/*
** EPITECH PROJECT, 2019
** IndieStudio_2018
** File description:
** EntityManager.cpp
*/

#include "Game/EntityManager.hpp"

game::p_entity::pointer game::EntityManager::getEntity(s_pos pos)
{
    auto it = std::find_if(_entities.begin(), _entities.end(),
                            [&](const std::unique_ptr<Entity> &i) {
                                return i->getPosition().x == pos.x && i->getPosition().z == pos.z;
                            });
    if (it != _entities.end())
        return it->get();
    else
        return nullptr;
}

game::p_entity::pointer game::EntityManager::getEntity(t_id id){
    auto it = std::find_if(_entities.begin(), _entities.end(),
                            [&](const std::unique_ptr<Entity> &i) {
                               return i->getId() == id;
                            });
    if (it != _entities.end())
        return it->get();
    else
        return nullptr;
}

game::EntityType game::EntityManager::getEntityType(s_pos pos)
{
    auto it = getEntity(pos);
    if (it != nullptr)
        return it->getType();
    else
        return undefined;
}

std::vector<game::p_entity::pointer> game::EntityManager::getEntitiesInRange(s_pos pos, int range)
{
    std::vector<game::p_entity::pointer> v;

    for (int i = 0; i != range + 1; i++) {
        std::vector<s_pos> v_pos = {
            {pos.x + i * 10, pos.y, pos.z},
            {pos.x, pos.y, pos.z + i * 10},
            {pos.x - i * 10, pos.y, pos.z},
            {pos.x, pos.y, pos.z - i * 10}
        };

        auto it = std::unique(v_pos.begin(), v_pos.end());
        v_pos.erase(it, v_pos.end());

        for (auto &pos : v_pos) {
            auto tmp = getEntity(pos);
            if (tmp != nullptr )
                v.push_back(tmp);
        }
    }
    return v;
}

std::vector<game::p_entity> const &game::EntityManager::getEntities() const noexcept
{
    return _entities;
}

void game::EntityManager::deleteFromPos(float x, float z)
{
    for (int i = 0; i != _entities.size(); i++) {
        if (_entities[i].get()->getPosition().x == x && _entities[i].get()->getPosition().z == z) {
            _entities.erase(_entities.begin() + i);
            return;
        }
    }
}
