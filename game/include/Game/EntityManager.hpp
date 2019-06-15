/*
** EPITECH PROJECT, 2019
** IndieStudio_2018
** File description:
** EntityManager.hpp
*/

#pragma once

#include <algorithm>
#include <memory>
#include <vector>

#include "Game/Block.hpp"
#include "Game/Bomb.hpp"
#include "Game/BrittleBlock.hpp"
#include "Game/Character.hpp"

namespace game
{
    using p_entity = std::unique_ptr<Entity>;

    class EntityManager
    {
        public:
            template <typename T>
            void addEntity(T entity)
            {
                _entities.push_back(std::move(std::make_unique<T>(entity)));
            }

            template <typename T>
            void removeEntity(T entity)
            {
                auto it = std::find_if(_entities.begin(), _entities.end(),
                                        [&](const std::unique_ptr<Entity> &i) {
                                            return i->id == entity->id;
                                        });
                if (it != _entities.end())
                    _entities.erase(it);
                else
                    std::cerr << "not found" << std::endl;
            }

            p_entity::pointer getEntity(s_pos pos);
            p_entity::pointer getEntity(t_id id);

            EntityType getEntityType(s_pos pos);

            std::vector<p_entity::pointer> getEntitiesInRange(s_pos pos, int range);
            std::vector<p_entity> const &getEntities() const noexcept;

            void deleteFromPos(float x, float y);
            p_entity::pointer getBot();

        private:
            std::vector<p_entity> _entities;
    };
}; // namespace game
