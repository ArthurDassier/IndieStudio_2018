/*
** EPITECH PROJECT, 2019
** IndieStudio_2018
** File description:
** Character.hpp
*/

#pragma once

#include "Game/Entity.hpp"
#include "irrlicht/irrlicht.h"

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

            void setSkin(const int);
            int &getSkin() noexcept;

            void setDirection(const std::string);
            std::string &getDirection() noexcept;

            void setNode(irr::scene::IAnimatedMeshSceneNode *);
            irr::scene::IAnimatedMeshSceneNode *getNode() const noexcept;

        private:
            t_id _id;
            s_pos _pos;
            irr::core::vector3df _pos3df;
            int _skin;
            std::string _direction;
            irr::scene::IAnimatedMeshSceneNode *_node;
    };
}; // namespace game
