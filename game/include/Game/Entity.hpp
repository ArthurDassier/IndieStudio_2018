/*
** EPITECH PROJECT, 2019
** IndieStudio_2018
** File description:
** Entity.hpp
*/

#pragma once

#include <iostream>
#include "Game/IEntity.hpp"

using t_id = std::size_t;

namespace game
{
    class Entity : public IEntity
    {
        public:
            Entity(const EntityType &);

            t_id const getId() const noexcept;

            void setPosition(const s_pos &);
            s_pos &getPosition() noexcept;

            EntityType getType() const noexcept;

        private:
            const t_id id;
            s_pos _pos;
            EntityType _type;

            t_id generateID() const noexcept;
    };
}; // namespace game
