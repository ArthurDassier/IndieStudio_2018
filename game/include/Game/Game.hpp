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
#include "EntityManager.hpp"
#include "Server/Session.hpp"
#include "Utils/Packet.hpp"
#include "Game/EntityManager.hpp"

using t_entity = boost::shared_ptr<game::Character>;
using t_vector = std::vector<t_entity>;

namespace game
{
    class Game
    {
        public:
            Game();
            ~Game() = default;

            void gameLoop();

            bool checkCollisions(t_entity);

            void fillEntitiesMap(const std::string);

            void sendPosition();
            void updatePosition(const t_id, const std::string);

            void setPlayer(boost::shared_ptr<game::Character>);
            boost::shared_ptr<game::Character> getPlayer() const noexcept;

            void updateParticipants(std::shared_ptr<t_vector>);

            std::string const getMap();

        private:
            Generation _generation;
<<<<<<< HEAD
            EntityManager _entity;
=======
            EntityManager _EM;
>>>>>>> origin/EntityList
            utils::Packet _packet;
            boost::shared_ptr<game::Character> _player;
            std::shared_ptr<t_vector> _participants;
            bool _collide;
    };
}; // namespace game
