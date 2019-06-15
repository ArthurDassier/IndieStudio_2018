/*
** EPITECH PROJECT, 2019
** IndieStudio_2018
** File description:
** Game.hpp
*/

#pragma once

#include <iostream>
#include <memory>
#include <vector>
#include <boost/shared_ptr.hpp>

#include "Character.hpp"
#include "EntityManager.hpp"
#include "Game/Bomb.hpp"
#include "Game/Fire.hpp"
#include "Game/Character.hpp"
#include "Game/EntityManager.hpp"
#include "Game/Ground.hpp"
#include "Game/IEntity.hpp"
#include "Game/Lib.hpp"
#include "Game/MovableEntity.hpp"
#include "Server/Session.hpp"
// #include "Utils/ConfigManager.hpp"
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

            bool checkCollisions(t_entity::element_type*);

            void fillEntitiesMap(const std::string);

            void updatePosition(const t_id, const std::string);

            void setPlayer(boost::shared_ptr<game::Character>);
            boost::shared_ptr<game::Character> getPlayer() const noexcept;

            void sendPacket(const std::string packet);

            void updateParticipants(std::shared_ptr<t_vector>);

            std::string const getMap();

            void putBomb(t_id);
            void refreshBomb();
            void destroyMap(size_t power,float x, float z);

            void destroyV(size_t power, s_pos pos);
            void destroyH(size_t power, s_pos pos);

            s_pos determineBombPos(int x, int z, std::string sens);
            s_pos roundPos(int x, int z, std::string sens);


            void dropBonus(float x, float z);
            void takeBonus(t_entity::element_type* entity, float x, float z, std::string sens);

            void checkDeath(float x, float z);
        private:
            Generation _generation;
            EntityManager _EM;
            utils::Packet _packet;
            boost::shared_ptr<game::Character> _player;
            std::shared_ptr<t_vector> _participants;
            std::vector<Bomb> _allBomb;
    };
}; // namespace game
