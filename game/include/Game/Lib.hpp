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
        float x = 0;
        float y = 0;
        float z = 0;

        inline s_pos operator=(s_pos p)
        {
            x = p.x;
            y = p.y;
            z = p.z;
            return p;
        }

        inline s_pos operator<<(float new_x)
        {
            return {x + new_x, y, z};
        }

        inline s_pos operator<<=(float new_y)
        {
            return {x, y + new_y, z};
        }

        inline s_pos operator<=(float new_z)
        {
            return {x, y, z + new_z};
        }

        inline bool operator==(s_pos p)
        {
            return (p.x == x && p.y == y && p.z == z);
        }
    };
}; // namespace game