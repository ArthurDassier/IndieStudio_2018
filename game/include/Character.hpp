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
            // Character(const std::string);
            ~Character() = default;

            virtual void deliver(std::string message) = 0;

            virtual t_id getId() = 0;

            void setId(const t_id);
            // t_id getId() const noexcept
            // {
            //     return _id;
            // }

            virtual player &get_playerdata() = 0;

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