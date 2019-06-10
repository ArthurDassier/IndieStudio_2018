/*
** EPITECH PROJECT, 2019
** room.cpp
** File description:
** room
*/

#include <iostream>
#include "server/room.hpp"
#include "game/Generation.hpp"


void Room::join(boost::shared_ptr<game::Character> participant)
{
    // To connected players ->send the participant to all

    startPosi(participant);
    for (boost::shared_ptr<game::Character> p : _participants) {
        boost::property_tree::ptree root;
        std::stringstream ss;

        root.put("type", "new_player");
        updateJson(root, participant);
        boost::property_tree::write_json(ss, root);
        p->deliver(ss.str());
    }
    // To the new player
    for (boost::shared_ptr<game::Character> p : _participants) {
        boost::property_tree::ptree root;
        std::stringstream ss;

        root.put("type", "new_player");
        updateJson(root, p);
        boost::property_tree::write_json(ss, root);
        participant->deliver(ss.str());
    }
    boost::property_tree::ptree root;
    std::stringstream ss;

    root.put("type", "local_player");
    root.put("diagram", genMap(10));
    updateJson(root, participant);
    boost::property_tree::write_json(ss, root);
    participant->deliver(ss.str());
    _participants.push_back(participant);
}

void Room::updateJson(boost::property_tree::ptree &root, boost::shared_ptr<game::Character> p)
{
    root.put("id", p->getId());
    root.put("x", p->getPosition().x);
    root.put("y", p->getPosition().y);
    root.put("z", p->getPosition().z);
    root.put("skin", p->get_playerdata().skin);
}

void Room::update_participants()
{
    // A trouver
    std::string clientmessage = boost::lexical_cast<std::string>(_participants.size());

    std::for_each(_participants.begin(), _participants.end(),
        boost::bind(&game::Character::deliver, _1, clientmessage));
}

void Room::updatePosition(const t_id id, std::string new_sens)
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

void Room::startPosi(boost::shared_ptr<game::Character> participant)
{
    static int nb_player = 1;

    switch (nb_player) {
        case 1:
            participant->setPosition({40, 10, 40});
            participant->get_playerdata().skin = 0;
            // participant->setSkin(0);
            break;
        case 2:
            participant->setPosition({20, 10, 20});
            participant->get_playerdata().skin = 1;
            // participant->setSkin(1);
            break;
        case 3:
            participant->setPosition({10, 10, 10});
            participant->get_playerdata().skin = 2;
            // participant->setSkin(2);
            break;
        case 4:
            participant->setPosition({30, 10, 30});
            participant->get_playerdata().skin = 3;
            // participant->setSkin(3);
            break;
        default:
            participant->setPosition({0, 0, 0});
            participant->get_playerdata().skin = 42;
            // participant->setSkin(42);
            break;
    }
    nb_player++;
}

int Room::nbParticipants()
{
    return (_participants.size());
}
