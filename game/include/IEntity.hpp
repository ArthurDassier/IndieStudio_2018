/*
** EPITECH PROJECT, 2019
** IndieStudio_2018
** File description:
** IEntity.hpp
*/

#pragma once

#include "Lib.hpp"

namespace game
{
    class IEntity
    {
        public:
            virtual ~IEntity() = default;

            virtual void setPosition(const s_pos &) = 0;
            virtual s_pos getPosition() const noexcept = 0;
    };
}; // namespace game