/*
** EPITECH PROJECT, 2019
** IndieStudio_2018
** File description:
** Lib.hpp
*/

#pragma once

namespace game
{
    struct s_pos
    {
        float x;
        float y;
        float z;

        inline s_pos operator=(s_pos p)
        {
            x = p.x;
            y = p.y;
            z = p.z;
            return p;
        }

        inline s_pos operator+(s_pos p)
        {
            return {p.x + x, p.y + y, p.z + z};
        }

        inline bool operator==(s_pos p)
        {
            return (p.x == x && p.y == y && p.z == z);
        }
    };
}; // namespace game