/*
** EPITECH PROJECT, 2019
** IndieStudio_2018
** File description:
** Packet.hpp
*/

#pragma once

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <ostream>
#include <sstream>

namespace utils
{
    class Packet
    {
        public:
            Packet() = default;
            ~Packet() = default;

            std::string const getPacket() noexcept;

            void setType(const std::string);

            template <typename T>
            void addData(const std::string name, const T data)
            {
                root.put(name, data);
            }

            void clear();

        private:
            boost::property_tree::ptree root;
    };
}; // namespace utils