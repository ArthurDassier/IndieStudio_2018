/*
** EPITECH PROJECT, 2019
** room.cpp
** File description:
** room
*/

#include "../include/server/room.hpp"

void Room::join(boost::shared_ptr<Participant> participant)
{
    // To connected players
    for (boost::shared_ptr<Participant> p : _participants) {
        boost::property_tree::ptree root;
        std::stringstream ss;

        root.put("id", participant->get_id());
        root.put("type", "newplayer");
        root.put("x", std::to_string(10 * _participants.size()));
        root.put("y", 0);
        root.put("z", std::to_string(10 * _participants.size()));
        boost::property_tree::write_json(ss, root);
        p->deliver(ss.str());
    }
    // To the new player
    for (boost::shared_ptr<Participant> p : _participants) {
        boost::property_tree::ptree root;
        std::stringstream ss;

        root.put("id", p->get_id());
        root.put("type", "newplayer");
        root.put("x", p->get_playerdata().pos.x);
        root.put("y", 0);
        root.put("z", p->get_playerdata().pos.z);
        boost::property_tree::write_json(ss, root);
        participant->deliver(ss.str());
    }
    boost::property_tree::ptree root;
    std::stringstream ss;

    root.put("type", "you");
    root.put("id", participant->get_id());
    root.put("diagram", "111111111\n100000001\n100000001\n100000001\n100000001\n111111111");
    root.put("x", std::to_string(10 * _participants.size()));
    root.put("y", 0);
    root.put("z", std::to_string(10 * _participants.size()));
    boost::property_tree::write_json(ss, root);
    participant->deliver(ss.str());
    _participants.push_back(participant);
}

void Room::update_participants()
{
    // A trouver
    std::string clientmessage = boost::lexical_cast<std::string>(_participants.size());

    std::for_each(_participants.begin(), _participants.end(),
        boost::bind(&Participant::deliver, _1, clientmessage));
}

void Room::updatePosition(std::string id, std::string new_sens)
{
    boost::property_tree::ptree root;
    size_t i = 0;

    root.put("id", id);
    for (; i < _participants.size(); ++i) {
        if (id == _participants[i]->get_id()) {
            player &data = _participants[i]->get_playerdata();
            data.sens = new_sens;
            if (new_sens.compare("up") == 0)
                data.pos.z += 2;
            else if (new_sens.compare("down") == 0)
                data.pos.z -= 2;
            else if (new_sens.compare("left") == 0)
                data.pos.x -= 2;
            else if (new_sens.compare("right") == 0)
                data.pos.x += 2;
            break;
        }
    }
    root.put("sens", new_sens);
    for (i = 0; i < _participants.size(); ++i) {
        root.put("type", "moveother");
        std::stringstream ss;
        boost::property_tree::write_json(ss, root);
        _participants[i]->deliver(ss.str());
    }
}

void Room::stratPosi(boost::shared_ptr<Participant> participant)
{
    static int nb_player = 1;

    switch (nb_player) {
        case 1:
            participant->get_playerdata().pos.x = 40;
            participant->get_playerdata().pos.y = 10;
            participant->get_playerdata().pos.z = 40;
            break;
        case 2:
            participant->get_playerdata().pos.x = 20;
            participant->get_playerdata().pos.y = 10;
            participant->get_playerdata().pos.z = 20;
            break;
        case 3:
            participant->get_playerdata().pos.x = 10;
            participant->get_playerdata().pos.y = 10;
            participant->get_playerdata().pos.z = 10;
            break;
        case 4:
            participant->get_playerdata().pos.x = 30;
            participant->get_playerdata().pos.y = 10;
            participant->get_playerdata().pos.z = 30;
            break;
        default:
            participant->get_playerdata().pos.x = 0;
            participant->get_playerdata().pos.y = 0;
            participant->get_playerdata().pos.z = 0;
            break;
    }
    nb_player++;
}

int Room::nbParticipants()
{
    return (_participants.size());
}