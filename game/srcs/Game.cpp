/*
** EPITECH PROJECT, 2019
** IndieStudio_2018
** File description:
** Game.cpp
*/

#include "Game/Game.hpp"

void game::Game::gameLoop()
{
    for (auto &it : *_participants) {
        checkCollisions(it);
        if (it->getId() == _player->getId())
            continue;
    }
}

bool game::Game::checkCollisions(t_entity entity)
{
    s_pos pos_player = _player->getPosition();
    std::cout << _player->getPosition().x << ", " << _player->getPosition().z << std::endl;
    if (_player->getDirection().compare("up") == 0)
        pos_player.z += 10;
    else if (_player->getDirection().compare("down") == 0)
        pos_player.z -= 10;
    else if (_player->getDirection().compare("left") == 0)
        pos_player.x -= 10;
    else if (_player->getDirection().compare("right") == 0)
        pos_player.x += 10;
    // if (dynamic_cast<Banana *>(_entity.getEntity(pos_player)) || dynamic_cast<Banana *>(_entity.getEntity(pos_player))) {
    //
    // }
    //     _packet.setType("explosion");
    //     _packet.addData("damage", 2);
    //     for (auto &it : *_participants)
    //         it->deliver(_packet.getPacket());
    //     _player->setDirection("down");
    // }
}



void game::Game::setPlayer(boost::shared_ptr<game::Character> player)
{
    _player = player;
}

boost::shared_ptr<game::Character> game::Game::getPlayer() const noexcept
{
    return _player;
}

void game::Game::updateParticipants(std::shared_ptr<t_vector> participants)
{
    _participants = participants;
}

std::string const game::Game::getMap()
{
    return _generation.genMap(10);
}
