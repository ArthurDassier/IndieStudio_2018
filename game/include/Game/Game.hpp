/*
** EPITECH PROJECT, 2019
** IndieStudio_2018
** File description:
** Game.hpp
*/

#pragma once

#include <boost/shared_ptr.hpp>
#include <iostream>
#include <memory>
#include <vector>

#include "Character.hpp"
#include "Server/Session.hpp"
#include "Utils/Packet.hpp"

using t_entity = boost::shared_ptr<game::Character>;
using t_vector = std::vector<t_entity>;

namespace game
{
    class Game
    {
        public:
            Game() = default;
            ~Game() = default;
            
            void gameLoop();
            
            void checkCollisions(t_entity);

            void setPlayer(boost::shared_ptr<game::Character>);
            boost::shared_ptr<game::Character> getPlayer() const noexcept;
            
            void updateParticipants(std::shared_ptr<t_vector>);

            std::string const getMap();

        private:
            Generation _generation;
            utils::Packet _packet;
            boost::shared_ptr<game::Character> _player;
            std::shared_ptr<t_vector> _participants;
    };
}; // namespace game