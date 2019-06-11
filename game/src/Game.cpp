/*
** EPITECH PROJECT, 2019
** IndieStudio_2018
** File description:
** Game.cpp
*/

#include "../include/Game.hpp"

void game::Game::gameLoop()
{  
    for (auto &it : *_participants) {
        if (it->getId() == _player->getId())
            continue;
        checkCollisions(it);
    }
}

/*----------------------------------------------\\
void DemoFunction()
{
    if (condition) {
        action();
        if (need to update entity?)
            _packet.setType(typeOfUpdate);
            _packet.addData(all sort of data (it's a template lol));
            for (auto &it : *_participants)
                it->deliver(_packet.getPacket());
    }
}

Concrete example:
    
    if (_player->getDirection().compare("up") == 0) {
        _packet.setType("explosion");
        _packet.addData("damage", 2);
        for (auto &it : *_participants)
            it->deliver(_packet.getPacket());
        _player->setDirection("down");
    }

//----------------------------------------------*/

void game::Game::checkCollisions(t_entity entity)
{

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