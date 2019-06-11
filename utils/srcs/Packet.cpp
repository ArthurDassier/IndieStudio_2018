/*
** EPITECH PROJECT, 2019
** IndieStudio_2018
** File description:
** Packet.cpp
*/

#include "Utils/Packet.hpp"

std::string const utils::Packet::getPacket() noexcept
{
    std::ostringstream buf;
    boost::property_tree::write_json(buf, root);
    return buf.str();
}

void utils::Packet::setType(const std::string type)
{
    root.put("type", type);
}

void utils::Packet::clear()
{
    root.clear();
}