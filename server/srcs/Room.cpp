/*
** EPITECH PROJECT, 2019
** room.cpp
** File description:
** room
*/

#include <iostream>

#include "Server/Room.hpp"
#include "Game/Generation.hpp"

void server::Room::join(boost::shared_ptr<game::Character> participant)
{
    // To connected players ->send the participant to all
    startPosi(participant);
    for (boost::shared_ptr<game::Character> p : _participants) {
        addParticipant(participant, p);
        addParticipant(p, participant);
    }
    // To the new player
    addLocalPlayer(participant);
}

void server::Room::addParticipant(boost::shared_ptr<game::Character> p, boost::shared_ptr<game::Character> to)
{
    _packet.setType("new_player");
    _packet.addData("id", p->getId());
    _packet.addData("x", p->getPosition().x);
    _packet.addData("y", p->getPosition().y);
    _packet.addData("z", p->getPosition().z);
    _packet.addData("skin", p->get_playerdata().skin);
    to->deliver(_packet.getPacket());
    _packet.clear();
}

void server::Room::addLocalPlayer(boost::shared_ptr<game::Character> p)
{
    _packet.setType("local_player");
    _packet.addData("diagram", _map);
    _packet.addData("id", p->getId());
    _packet.addData("x", p->getPosition().x);
    _packet.addData("y", p->getPosition().y);
    _packet.addData("z", p->getPosition().z);
    _packet.addData("skin", p->get_playerdata().skin);
    p->deliver(_packet.getPacket());
    _participants.push_back(p);
}

void server::Room::sendDeath(boost::shared_ptr<game::Character> p)
{
    boost::property_tree::ptree root;

    for (auto &it : _participants) {
        root.put("type", "death");
        root.put("id", p->getId());
        std::stringstream ss;
        boost::property_tree::write_json(ss, root);
        it->deliver(ss.str());
    }
}

void server::Room::startPosi(boost::shared_ptr<game::Character> participant)
{
    static int nb_player = 1;
    game::s_pos pos;

    switch (nb_player) {
        case 1:
            pos = {11, 5, 11};
            participant->setPosition(pos);
            participant->setSpawn(pos);
            participant->get_playerdata().skin = 0;
            break;
        case 2:
            pos = {81, 5, 11};
            participant->setPosition(pos);
            participant->setSpawn(pos);
            participant->get_playerdata().skin = 1;
            break;
        case 3:
            pos = {91, 5, 11};
            participant->setPosition(pos);
            participant->setSpawn(pos);
            participant->get_playerdata().skin = 2;
            break;
        case 4:
            pos = {11, 5, 91};
            participant->setPosition(pos);
            participant->setSpawn(pos);
            participant->get_playerdata().skin = 3;
            break;
        default:
            pos = {0, 0, 0};
            participant->setPosition(pos);
            participant->setSpawn(pos);
            participant->get_playerdata().skin = 42;
            break;
    }
    nb_player++;
}

int server::Room::nbParticipants()
{
    return (_participants.size());
}

void server::Room::setMap(const std::string map)
{
    _map = map;
}

std::shared_ptr<t_vector> server::Room::getParticipants() const noexcept
{
    return std::make_shared<t_vector>(_participants);
}
