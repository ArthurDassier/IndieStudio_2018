/*
** EPITECH PROJECT, 2019
** IndieStudio_2018
** File description:
** Character.hpp
*/

#pragma once

#include "Game/MovableEntity.hpp"
#include "irrlicht/irrlicht.h"
#include <chrono>


namespace game
{
    class Character : public MovableEntity
    {
        public:
            Character();
            ~Character() = default;

            void deliver(std::string);
            player &get_playerdata();
            t_id getId();

            void setPosition3df(const irr::core::vector3df);
            irr::core::vector3df getPosition3df() const noexcept;

            void setSpawn(const s_pos);
            s_pos getSpawn() const noexcept;

            void setSkin(const int);
            int &getSkin() noexcept;

            void setDirection(const std::string);
            std::string &getDirection() noexcept;

            void setNode(irr::scene::IAnimatedMeshSceneNode *);
            irr::scene::IAnimatedMeshSceneNode *getNode() const noexcept;

            void setHealthPoints(std::size_t);
            std::size_t &getHealthPoints() noexcept;

            void setCooldownBomb();
            size_t getCooldownBomb();


        private:
            t_id _id;
            s_pos _pos;
            s_pos _spawn;
            irr::core::vector3df _pos3df;
            int _skin;
            std::string _direction;
            irr::scene::IAnimatedMeshSceneNode *_node;
            std::size_t _hp;
            std::chrono::time_point<std::chrono::high_resolution_clock> _cooldownBomb;
    };
}; // namespace game
