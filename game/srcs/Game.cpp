/*
** EPITECH PROJECT, 2019
** IndieStudio_2018
** File description:
** Game.cpp
*/

#include "Game/Game.hpp"

game::Game::Game():
    _collide(false)
{
}

void game::Game::gameLoop()
// {
//     if (_player->getDirection().compare("up") == 0) {
//         _packet.setType("explosion");
//         _packet.addData("damage", 2);
//         // for (auto &it_c : *_participants)
//         _player->deliver(_packet.getPacket());
//         _player->setDirection("down");
//         _packet.clear();
//         _collide = true;
//     }
    for (auto &it : *_participants) {
        checkCollisions(it);
        if (it->getId() == _player->getId())
            continue;
    }
}

void game::Game::sendPosition()
{
    if (_collide == true)
        return;
    _packet.setType("move_other");
    _packet.addData("id", _player->getId());
    _packet.addData("sens", _player->getDirection());
    for (auto &it : *_participants)
        it->deliver(_packet.getPacket());
    _packet.clear();
}

void game::Game::updatePosition(const t_id id, const std::string direction)
{
    if (_collide == true) {
        std::cout << "ENTITY SIZE: " << _EM.getEntities().size() << std::endl;
        return;
    }
    for (auto &it : *_participants) {
        if (it->getId() != id)
            continue;
        it->setDirection(direction);
        if (direction.compare("up") == 0)
            it->getPosition().z += 2;
        else if (direction.compare("down") == 0)
            it->getPosition().z -= 2;
        else if (direction.compare("left") == 0)
            it->getPosition().x -= 2;
        else if (direction.compare("right") == 0)
            it->getPosition().x += 2;
        break;
    }
    _packet.setType("move_other");
    _packet.addData("id", _player->getId());
    _packet.addData("sens", _player->getDirection());
    for (auto &it : *_participants)
        it->deliver(_packet.getPacket());
    _packet.clear();
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



void game::Game::fillEntitiesMap(const std::string map)
{
    for (auto &it : map)
        switch (it) {
            case '1': {
                Block b;
                b.setPosition({0, 10, 0});
                _EM.addEntity(b);
                break;
            }
            case '2': {
                BrittleBlock bB;
                bB.setPosition({0, 20, 0});
                _EM.addEntity(bB);
                break;
            }
            default:
                break;
        }
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
<<<<<<< HEAD
    return _generation.genMap(10);
}
=======
    std::string map = _generation.genMap(10);

    fillEntitiesMap(map);
    return map;
}
>>>>>>> origin/EntityList
