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
{
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
        if (it->getId() == _player->getId())
            continue;
        checkCollisions(it);
    }
}

void game::Game::updatePosition(const t_id id, const std::string direction)
{
    if (_collide == true)
        return;
    for (auto &it : *_participants) {
        if (it->getId() == id) {
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
    }
    _packet.addData("id", id);
    _packet.addData("sens", direction);
    _packet.setType("move_other");
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
    if (_EM.getEntity(pos_player) == game::EntityType::brittleBlock) {

    }
    //     _packet.setType("explosion");
    //     _packet.addData("damage", 2);
    //     for (auto &it : *_participants)
    //         it->deliver(_packet.getPacket());
    //     _player->setDirection("down");
    // }
}


float roundDecimal(float n)
{
    // Smaller multiple
    float a = (n / 10) * 10;

    // Larger multiple
    float b = a + 10;

    // Return of closest of two
    return (n - a > b - n) ? b : a;
}



void game::Game::fillEntitiesMap(const std::string map)
{
    float x = 0;
    float y = 0;

    for (auto &it : map) {
        switch (it) {
            case '1': {
                Block b;
                b.setPosition({x, 0, y});
                _EM.addEntity(b);
                break;
            }
            case '2': {
                BrittleBlock bB;
                bB.setPosition({x, 0, y});
                _EM.addEntity(bB);
                break;
            }
            case '\n':
                y += 10;
                x = 0;
            default:
                break;
        }
        x += 10;
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
    std::string map = _generation.genMap(10);

    fillEntitiesMap(map);
    return map;
}
