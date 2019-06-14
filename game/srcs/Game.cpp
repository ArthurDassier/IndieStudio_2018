/*
** EPITECH PROJECT, 2019
** IndieStudio_2018
** File description:
** Game.cpp
*/

#include "Game/BombUp.hpp"
#include "Game/Character.hpp"
#include "Game/Game.hpp"
#include "Game/Ground.hpp"
#include "Game/FireUp.hpp"
#include "Game/IEntity.hpp"
#include "Game/MovableEntity.hpp"
#include "Game/SpeedUp.hpp"
#include "Game/WallPass.hpp"

void game::Game::gameLoop()
{
    for (auto &it : *_participants) {
        refreshBomb();
        if (it->getId() != _player->getId())
            continue;
    }
}

void game::Game::sendPacket(const std::string packet)
{
    for (auto &it : *_participants)
        it->deliver(packet);
    _packet.clear();
}

void game::Game::updatePosition(const t_id id, const std::string direction)
{
    s_pos pos_player;

    for (auto &it : *_participants) {
        if (it->getId() == id) {
            pos_player = it->getPosition();
            it->setDirection(direction);
            if (direction.compare("up") == 0)
                it->getPosition().z += it->_speed;
            else if (direction.compare("down") == 0)
                it->getPosition().z -= it->_speed;
            else if (direction.compare("left") == 0)
                it->getPosition().x -= it->_speed;
            else if (direction.compare("right") == 0)
                it->getPosition().x += it->_speed;
            if (checkCollisions(it.get()) == false) {
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

void game::Game::destroyV(size_t power, s_pos pos)
{
    s_pos pos_block = pos;
    bool send = false;

    for (int i = 0; i != power + 1 && _EM.getEntityType(pos_block) != game::EntityType::block; i++) {
        _EM.deleteFromPos(pos_block.x, pos_block.z);
        pos_block.z += 10;
        _packet.addToVector<std::array<float, 2>>({pos.x, pos.z + i * 10});
        send = true;
        if (_packet.getVectorSize() == 3) {
            _packet.setType("destroy");
            _packet.addList("blocks", _packet.getVector());
            sendPacket(_packet.getPacket());
        }
        dropBonus(pos_block.x, pos_block.z);
    }
    if (send) {
        if (_packet.getVectorSize() != 0) {
            _packet.setType("destroy");
            _packet.addList("blocks", _packet.getVector());
            sendPacket(_packet.getPacket());
        }
        dropBonus(pos_block.x, pos_block.z);
    }

    pos_block = pos;
    send = false;
    for (int i = 0; i != power + 1 && _EM.getEntityType(pos_block) != game::EntityType::block; i++) {
        _EM.deleteFromPos(pos_block.x, pos_block.z);
        pos_block.z -= 10;
        _packet.addToVector<std::array<float, 2>>({pos.x, pos.z - i * 10});
        send = true;
        if (_packet.getVectorSize() == 3) {
            _packet.setType("destroy");
            _packet.addList("blocks", _packet.getVector());
            sendPacket(_packet.getPacket());
        }
    }
    if (send) {
        if (_packet.getVectorSize() != 0) {
            _packet.setType("destroy");
            _packet.addList("blocks", _packet.getVector());
            sendPacket(_packet.getPacket());
        }
        dropBonus(pos_block.x, pos_block.z);
    }
}

void game::Game::destroyH(size_t power, s_pos pos)
{
    s_pos pos_block = pos;
    bool send = false;

    for (int i = 0; i != power + 1 && _EM.getEntityType(pos_block) != game::EntityType::block; i++) {
        _EM.deleteFromPos(pos_block.x, pos_block.z);
        pos_block.x += 10;
        _packet.addToVector<std::array<float, 2>>({pos.x + i * 10, pos.z});
        send = true;
        if (_packet.getVectorSize() == 3) {
            _packet.setType("destroy");
            _packet.addList("blocks", _packet.getVector());
            sendPacket(_packet.getPacket());
        }
    }
    if (send) {
        if (_packet.getVectorSize() != 0) {
            _packet.setType("destroy");
            _packet.addList("blocks", _packet.getVector());
            sendPacket(_packet.getPacket());
        }
        dropBonus(pos_block.x, pos_block.z);
    }
    send = false;
    pos_block = pos;
    for (int i = 0; i != power + 1 && _EM.getEntityType(pos_block) != game::EntityType::block; i++) {
        _EM.deleteFromPos(pos_block.x, pos_block.z);
        pos_block.x -= 10;
        _packet.addToVector<std::array<float, 2>>({pos.x - i * 10, pos.z});
        send = true;
        if (_packet.getVectorSize() == 3) {
            _packet.setType("destroy");
            _packet.addList("blocks", _packet.getVector());
            sendPacket(_packet.getPacket());
        }
    }
    if (send) {
        if(_packet.getVectorSize() != 0) {
            _packet.setType("destroy");
            _packet.addList("blocks", _packet.getVector());
            sendPacket(_packet.getPacket());
        }
        dropBonus(pos_block.x, pos_block.z);
    }
}

void game::Game::destroyMap(size_t power, float x, float z)
{
    s_pos pos_block;
    pos_block.x = x;
    pos_block.z = z;
    bool send = false;

    destroyV(power, pos_block);
    destroyH(power, pos_block);
}

void game::Game::refreshBomb()
{
    for (int i = 0; i != _allBomb.size(); i++) {
        _allBomb[i].refresh();
        if (_allBomb[i].getAlive() == false) {
            _packet.setType("explosion");
            _packet.addData("x", _allBomb[i].getPosX());
            _packet.addData("z", _allBomb[i].getPosZ());
            _packet.addData("id", _allBomb.size() - 1);
            for (auto &it : *_participants)
                it->deliver(_packet.getPacket());
            _packet.clear();
            destroyMap(_allBomb[i].getPower(), _allBomb[i].getPosX(), _allBomb[i].getPosZ());
            _allBomb.erase(_allBomb.begin() + i);
            i--;
        }
    }
    // for (int i = 0; i != _allFire.size(); i++) {
    //     _allFire[i].refresh();
    //     if (_allFire[i].getAlive() == false) {
    //         _packet.setType("water");
    //         _packet.addData("x", _allFire[i].getPosX());
    //         _packet.addData("z", _allFire[i].getPosZ());
    //         _packet.addData("id", _allFire.size() - 1);
    //         for (auto &it : *_participants)
    //             it->deliver(_packet.getPacket());
    //         _packet.clear();
    //         _allFire.erase(_allFire.begin() + i);
    //         i--;
    //     }
    // }
}

float roundDecimal(int n)
{
    int a = (n / 10) * 10;
    int b = a + 10;
    return (n - a >= b - n) ? b : a;
}

game::s_pos game::Game::roundPos(int x, int z, std::string sens)
{
    s_pos pos_entity;
    if (sens.compare("up") == 0) {
        pos_entity.z = z - (z % 10);
        pos_entity.x = x - (x % 10);
    }
    else if (sens.compare("down") == 0) {
        pos_entity.z = z + 10 - (z % 10);
        pos_entity.x = x - (x % 10);
    }
    else if (sens.compare("right") == 0) {
        pos_entity.x = x - (x % 10);
        pos_entity.z = z - (z % 10);

    }
    else if (sens.compare("left") == 0) {
        pos_entity.x = x + 10 - (x % 10);
        pos_entity.z = z - (z % 10);
    }
    return pos_entity;
}


void game::Game::putBomb(t_id id)
{
    s_pos pos_bomb;
    bool send = false;

    for (auto &it : *_participants) {
        if (it->getId() == id) {
            if (static_cast<Character *>(it.get())->getCooldownBomb() >= 0.5) {
                pos_bomb = roundPos(it.get()->getPosition().x, it.get()->getPosition().z, it.get()->getDirection());
                _packet.setType("bomb");
                _packet.addData("x", pos_bomb.x);
                _packet.addData("z", pos_bomb.z);
                static_cast<Character *>(it.get())->setCooldownBomb();
                _allBomb.emplace_back(pos_bomb.x, pos_bomb.z, it.get()->getPower());
                send = true;
            }
        }
    }
    if (send == false)
        return;
    for (auto &it : *_participants)
        it->deliver(_packet.getPacket());
    _packet.clear();
}

bool game::Game::checkCollisions(t_entity::element_type* entity)
{
    s_pos pos_player = entity->getPosition();
    pos_player.z = roundDecimal(pos_player.z);
    pos_player.x = roundDecimal(pos_player.x);
    if (_EM.getEntityType(pos_player) == game::EntityType::block
    || _EM.getEntityType(pos_player) == game::EntityType::brittleBlock)
        return false;
    takeBonus(entity, entity->getPosition().x, entity->getPosition().z, entity->getDirection());
    return true;
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

void game::Game::dropBonus(float x, float z)
{
    s_pos pos_entity;
    pos_entity.x = x;
    pos_entity.y = 5;
    pos_entity.z = z;
    if (_EM.getEntityType(pos_entity) != game::EntityType::block && std::rand() % 8 != 1)
        return;

    int k = std::rand() % 4;
    _packet.setType("dropBonus");
    _packet.addData("x", x);
    _packet.addData("z", z);
    if (k == 0) {
        Bombup b;
        // b.setPosition({x, 5, y});
        // _EM.addEntity(b);
        // _packet.addData("bonusType", "BombUp");
    }
    // else if (k == 1) {
    //     SpeedUp b;
    //     b.setPosition({x, 5, y});
    //     _EM.addEntity(b);
    //     _packet.addData("bonusType", "SpeedUp");
    // }
    // else if (k == 2) {
    //     FireUp b;
    //     b.setPosition({x, 5, y});
    //     _EM.addEntity(b);
    //     _packet.addData("bonusType", "FireUp");
    // }
    // else if (k == 3) {
    //     WallPass b;
    //     b.setPosition({x, 5, y});
    //     _EM.addEntity(b);
    //     _packet.addData("bonusType", "WallPass");
    // }
    for (auto &it : *_participants)
        it->deliver(_packet.getPacket());
    _packet.clear();
}

void game::Game::takeBonus(t_entity::element_type* entity, float x, float z, std::string sens)
{
    s_pos pos_player = roundPos(x, z, sens);
    if (_EM.getEntityType(pos_player) == game::EntityType::SpeedUp)
        entity->_speed += 1;
    else if (_EM.getEntityType(pos_player) == game::EntityType::BombUp) {
    }
    else if (_EM.getEntityType(pos_player) == game::EntityType::FireUp) {
        entity->_power += 1;
    }
    else if (_EM.getEntityType(pos_player) == game::EntityType::WallPass) {
        entity->canWallPass = true;
    }
    else
        return;
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
