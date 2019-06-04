/*
** EPITECH PROJECT, 2019
** entity.hpp
** File description:
** entity
*/

#pragma once

#include <string>
#include "../../../lib/includes/irrlicht.h"

enum e_type
{
    WALL,
    BOOST
};

class Entity
{
    public:
        Entity();
        ~Entity();

    protected:
};

class Character : public Entity
{
    public:
        Character();
        ~Character();
        void setId(std::string);
        void setSkin(int);
        void setPosition(irr::core::vector3df);
        void setNode(irr::scene::IAnimatedMeshSceneNode *);
        std::string getId() const;
        int getSkin() const;
        irr::core::vector3df getPosition() const;
        irr::scene::IAnimatedMeshSceneNode *getNode() const;

    private:
        std::string _id;
        int _skin;
        irr::core::vector3df _position;
        irr::scene::IAnimatedMeshSceneNode *_node;

};

class Object : public Entity
{
    public:
        Object();
        ~Object();

        e_type getType()
        {
            return _type;
        }

    private:
        e_type _type;
        irr::core::vector3df _position;
        irr::scene::IAnimatedMeshSceneNode *_node;
};
