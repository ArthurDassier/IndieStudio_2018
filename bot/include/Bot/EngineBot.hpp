/*
** EPITECH PROJECT, 2019
** Bot.hpp
** File description:
** Bot.hpp
*/

#pragma once

#include "Game/Entity.hpp"


namespace engineBot
{
    class EngineBot
    {
        public:
            EngineBot();
            ~EngineBot() = default;
            void updateBot(game::Entity *);
        private:
    };
}; // namespace bot
