/*
** EPITECH PROJECT, 2019
** IndieStudio_2018
** File description:
** Character.hpp
*/

#pragma once

#include "Entity.hpp"
#include "../../lib/includes/irrlicht.h"

namespace game
{
    class Character : public Entity
    {
        public:
            Character();
            ~Character() = default;

            void setId(const t_id);
            t_id getId() {}

            void deliver(std::string) {}
            player &get_playerdata() {}

            void setPosition(const s_pos);
            s_pos &getPosition() noexcept;

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

        private:
            t_id _id;
            s_pos _pos;
            s_pos _spawn;
            irr::core::vector3df _pos3df;
            int _skin;
            std::string _direction;
            irr::scene::IAnimatedMeshSceneNode *_node;
            std::size_t _hp;
    };
}; // namespace game