/*
** EPITECH PROJECT, 2019
** IndieStudio_2018
** File description:
** Game.cpp
*/

#include "Game/Game.hpp"
#include "Game/Ground.hpp"

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
        if (it->getId() != _player->getId())
            continue;
    }
}

void game::Game::updatePosition(const t_id id, const std::string direction)
{
    s_pos pos_player;

    for (auto &it : *_participants) {
        if (it->getId() == id) {
            pos_player = it->getPosition();
            it->setDirection(direction);
            if (direction.compare("up") == 0)
                it->getPosition().z += 2;
            else if (direction.compare("down") == 0)
                it->getPosition().z -= 2;
            else if (direction.compare("left") == 0)
                it->getPosition().x -= 2;
            else if (direction.compare("right") == 0)
                it->getPosition().x += 2;
            if (checkCollisions() == false) {
                it->setPosition(pos_player);
                return;
            }
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

float roundDecimal(int n)
{
    int a = (n / 10) * 10;
    int b = a + 10;
    return (n - a >= b - n) ? b : a;
}

bool game::Game::checkCollisions()
{
    s_pos pos_player = _player->getPosition();

    if (_player->getDirection().compare("up") == 0) {
        pos_player.z = roundDecimal(pos_player.z);
        pos_player.x = roundDecimal(pos_player.x);
    }
    else if (_player->getDirection().compare("down") == 0) {
        pos_player.z = roundDecimal(pos_player.z);
        pos_player.x = roundDecimal(pos_player.x);
    }
    else if (_player->getDirection().compare("left") == 0) {
        pos_player.x = roundDecimal(pos_player.x);
        pos_player.z = roundDecimal(pos_player.z);
    }
    else if (_player->getDirection().compare("right") == 0) {
        pos_player.x = roundDecimal(pos_player.x);
        pos_player.z = roundDecimal(pos_player.z);
    }
    if (_EM.getEntityType(pos_player) == game::EntityType::block
    || _EM.getEntityType(pos_player) == game::EntityType::brittleBlock) {
        return false;
    }
    return true;
    //     _packet.setType("explosion");
    //     _packet.addData("damage", 2);
    //     for (auto &it : *_participants)
    //         it->deliver(_packet.getPacket());
    //     _player->setDirection("down");
    // }
}

void game::Game::fillEntitiesMap(const std::string map)
{
    float x = 0;
    float y = 0;

    for (int i = 0; i != map.size(); i++) {
        if (map[i] == '0') {
            Ground g;
            g.setPosition({x, 0, y});
            _EM.addEntity(g);
        }
        else if (map[i] == '1') {
            Block b;
            b.setPosition({x, 0, y});
            _EM.addEntity(b);
        }
        else if (map[i] == '2') {
            BrittleBlock bB;
            bB.setPosition({x, 0, y});
            _EM.addEntity(bB);
        }
        y+= 10;
        if (map[i] == '\n') {
            x += 10;
            y = 0;
        }
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
