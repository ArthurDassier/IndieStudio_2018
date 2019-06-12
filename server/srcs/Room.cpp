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

void server::Room::update_participants()
{
    // A trouver
    std::string clientmessage = boost::lexical_cast<std::string>(_participants.size());

    std::for_each(_participants.begin(), _participants.end(),
        boost::bind(&game::Character::deliver, _1, clientmessage));
}

void server::Room::updatePosition(const t_id id, std::string new_sens)
{
    boost::property_tree::ptree root;
    size_t i = 0;

    root.put("id", id);
    for (auto &it : _participants)
        if (it->getId() == id) {
            player &data = it->get_playerdata();
            it->setDirection(new_sens);
            if (new_sens.compare("up") == 0)
                it->getPosition().z += 2;
            else if (new_sens.compare("down") == 0)
                it->getPosition().z -= 2;
            else if (new_sens.compare("left") == 0)
                it->getPosition().x -= 2;
            else if (new_sens.compare("right") == 0)
                it->getPosition().x += 2;
            break;
        }
    root.put("sens", new_sens);
    for (auto &it : _participants) {
        root.put("type", "move_other");
        std::stringstream ss;
        boost::property_tree::write_json(ss, root);
        it->deliver(ss.str());
    }
}

void server::Room::sendDeath(boost::shared_ptr<game::Character> p)
{
    boost::property_tree::ptree root;

    for (auto &it : _participants) {
        root.put("type", "death");
        root.put("id", p->getId());
        root.put("x", p->getPosition().x);
        root.put("y", p->getPosition().y);
        root.put("z", p->getPosition().z);
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
            // participant->setSkin(0);
            break;
        case 2:
            pos = {90, 5, 90};
            participant->setPosition(pos);
            participant->setSpawn(pos);
            participant->get_playerdata().skin = 1;
            // participant->setSkin(1);
            break;
        case 3:
            pos = {90, 5, 10};
            participant->setPosition(pos);
            participant->setSpawn(pos);
            participant->get_playerdata().skin = 2;
            // participant->setSkin(2);
            break;
        case 4:
            pos = {10, 5, 90};
            participant->setPosition(pos);
            participant->setSpawn(pos);
            participant->get_playerdata().skin = 3;
            // participant->setSkin(3);
            break;
        default:
            pos = {0, 0, 0};
            participant->setPosition(pos);
            participant->setSpawn(pos);
            participant->get_playerdata().skin = 42;
            // participant->setSkin(42);
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
