/*
** EPITECH PROJECT, 2019
** IndieStudio_2018
** File description:
** Character.hpp
*/

#pragma once

#include "Entity.hpp"

struct player
{
    int skin;
};

namespace game
{
    class Character : public Entity
    {
        public:
            Character();
            // Character(const std::string);
            ~Character() = default;

            virtual void deliver(std::string message) = 0;
            virtual t_id getId() = 0;
            virtual player &get_playerdata() = 0;

            void setPosition(const s_pos);
            s_pos &getPosition() noexcept;

            void setSkin(const int);
            int &getSkin() noexcept;

            void setDirection(const std::string);
            std::string &getDirection() noexcept;

        private:
            s_pos _pos;
            int _skin;
            std::string _direction;
    };
}; // namespace game