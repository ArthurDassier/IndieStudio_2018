/*
** EPITECH PROJECT, 2019
** entity.hpp
** File description:
** entity
*/

#pragma once

#include <string>
#include "../../../lib/includes/irrlicht.h"

using t_id = std::size_t;

namespace client
{
    enum e_type
    {
        WALL,
        BOOST
    };

    class Entity
    {
        public:
            Entity() = default;
            ~Entity() = default;

        protected:
    };

    class Character : public Entity
    {
        public:
            Character() = default;
            ~Character() = default;

            void setId(const t_id);
            t_id getId() const noexcept;
            
            void setSkin(int);
            int getSkin() const;
            
            void setPosition(irr::core::vector3df);
            irr::core::vector3df getPosition() const;
            
            void setNode(irr::scene::IAnimatedMeshSceneNode *);
            irr::scene::IAnimatedMeshSceneNode *getNode() const;

        private:
            t_id _id;
            int _skin;
            irr::core::vector3df _position;
            irr::scene::IAnimatedMeshSceneNode *_node;

    };

    class Object : public Entity
    {
        public:
            Object() = default;
            ~Object() = default;

            e_type getType()
            {
                return _type;
            }

        private:
            e_type _type;
            irr::core::vector3df _position;
            irr::scene::IAnimatedMeshSceneNode *_node;
    };
}; // namespace client