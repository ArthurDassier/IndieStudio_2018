/*
** EPITECH PROJECT, 2019
** IndieStudio_2018
** File description:
** EntityManager.cpp
*/

#include "Game/EntityManager.hpp"

// game::p_entity::pointer game::EntityManager::getEntity(s_pos pos)
// {
//     auto it = std::find_if(_entities.begin(), _entities.end(),
//                             [&](const std::unique_ptr<Entity> &i) {
//                                 return i->getPosition() == pos;
//                             });
//     if (it != _entities.end())
//         return it->get();
// }

// game::p_entity::pointer game::EntityManager::getEntity(t_id id){
//     auto it = std::find_if(_entities.begin(), _entities.end(),
//                             [&](const std::unique_ptr<Entity> &i) {
//                                return i->id == id;
//                             });
//     if (it != _entities.end())
//         return it->get();
// }

std::vector<game::p_entity> const &game::EntityManager::getEntities() const noexcept
{
    return _entities;
}
