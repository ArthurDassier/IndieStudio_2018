/*
** EPITECH PROJECT, 2019
** IndieStudio_2018
** File description:
** Entity.hpp
*/

#pragma once

#include <iostream>

#include "IEntity.hpp"

using t_id = std::size_t;

namespace game
{
    class Entity : public IEntity
    {
        public:
            Entity();
            Entity(const s_pos &);

            void setPosition(const s_pos &);
            s_pos getPosition() const noexcept;

            const t_id id;

        private:
            s_pos _pos;
            
            t_id generateID() const noexcept;
    };
}; // namespace game