/*
** EPITECH PROJECT, 2019
** IndieStudio_2018
** File description:
** Generation.hpp
*/

#pragma once

#include <string>

namespace game
{
    class Generation
    {
        public:
            std::string const genMap(const std::size_t len);
            std::string getResult(std::vector<std::string> &map);
            bool isBlockNext(std::vector<std::string> map, int j, int k);
    };
}; // namespace game