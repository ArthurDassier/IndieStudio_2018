/*
** EPITECH PROJECT, 2019
** IndieStudio_2018
** File description:
** Character.cpp
*/

#include "Character.hpp"

game::Character::Character():
    Entity()
{
}

game::Character::Character(const s_pos &pos):
    Entity(pos)
{
}