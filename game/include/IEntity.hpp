/*
** EPITECH PROJECT, 2019
** IndieStudio_2018
** File description:
** IEntity.hpp
*/

#pragma once

#include "Lib.hpp"

struct player
{
    int skin;
};

namespace game
{
    class IEntity
    {
        public:
            virtual ~IEntity() = default;

            virtual void setPosition(const s_pos &) = 0;
            virtual s_pos getPosition() const noexcept = 0;

            // virtual void deliver(std::string) = 0;
            // virtual player &get_playerdata() = 0;
    };

    enum EntityType
    {
        bomb,
        character
    };
}; // namespace game