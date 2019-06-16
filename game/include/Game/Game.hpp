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
#include "Game/IEntity.hpp"
#include "Game/Lib.hpp"
#include "Game/MovableEntity.hpp"
#include "Server/Session.hpp"
#include "Utils/Packet.hpp"
#include "Game/Lib.hpp"
#include "Game/Bot.hpp"

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

            void iniNewBot();

            void putBomb(t_id);
            void putBombBot(t_id id);
            void refreshBomb();
            void destroyMap(size_t power,float x, float z);

            void destroyV(size_t power, s_pos pos);
            void destroyH(size_t power, s_pos pos);

            s_pos determineBombPos(int x, int z, std::string sens);
            bool isBotActive() {return _botActive;}
            void setBotActive(bool newState) {_botActive = newState;}
            game::p_entity::pointer getBot();
            bool updatePositionBot(const std::string direction);
            s_pos roundPos(int x, int z, std::string sens);

            void dropBonus(float x, float z);
            void takeBonus(t_entity::element_type* entity, float x, float z, std::string sens);
            void updateBot();    
            void checkDeath(float x, float z);
            void setSolo(bool solo);
            bool isSolo();
            void setBotCreated(bool bot);
        private:
            Generation _generation;
            EntityManager _EM;
            utils::Packet _packet;
            boost::shared_ptr<game::Character> _player;
            std::shared_ptr<t_vector> _participants;
            std::vector<Bomb> _allBomb;
            game::Bot _bot;
            bool _botActive = false;
            std::chrono::time_point<std::chrono::high_resolution_clock> _cooldownMove;
            std::chrono::time_point<std::chrono::high_resolution_clock> _cooldownBombBot;
            size_t sens_bot = 0;
            std::vector<std::string> sens = {"left", "up", "right", "down"};
            bool _isSolo;
            bool _botCreated;
    };
}; // namespace game
