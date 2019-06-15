/*
** EPITECH PROJECT, 2019
** IndieStudio_2018
** File description:
** Game.cpp
*/

#include "Game/Game.hpp"
#include "Game/Ground.hpp"
#include "Game/Character.hpp"
#include "Game/MovableEntity.hpp"
#include "Game/IEntity.hpp"
#include "Game/Bot.hpp"

void game::Game::gameLoop()
{
    for (auto &it : *_participants) {
        refreshBomb();
        if (isBotActive())
            _handleBot.updateBot(getBot());
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

void game::Game::destroyMap(size_t power, float x, float z)
{
    s_pos pos_block;
    pos_block.x = x;
    pos_block.z = z;

    for (int i = 0; i != power && _EM.getEntityType(pos_block) != game::EntityType::block; i++) {
        _packet.setType("destroy");
        _packet.addData("x", x);
        _EM.deleteFromPos(pos_block.x, pos_block.z);
        pos_block.z += 10;
        _packet.addData("z", z + i * 10);
        for (auto &it : *_participants)
            it->deliver(_packet.getPacket());
    }
    _packet.clear();
    pos_block.x = x;
    pos_block.z = z;
    for (int i = 0; i != power + 1 && _EM.getEntityType(pos_block) != game::EntityType::block; i++) {
        _packet.setType("destroy");
        _packet.addData("x", x + i * 10);
        _EM.deleteFromPos(pos_block.x, pos_block.z);
        pos_block.x += 10;
        _packet.addData("z", z);
        for (auto &it : *_participants)
            it->deliver(_packet.getPacket());
    }
    _packet.clear();
    pos_block.x = x;
    pos_block.z = z;

    for (int i = 0; i != power + 1 && _EM.getEntityType(pos_block) != game::EntityType::block; i++) {
        _packet.setType("destroy");
        _packet.addData("x", x - i * 10);
        _EM.deleteFromPos(pos_block.x, pos_block.z);
        pos_block.x -= 10;
        _packet.addData("z", z);
        for (auto &it : *_participants)
            it->deliver(_packet.getPacket());
    }
    for (int i = 0; i != power + 1 && _EM.getEntityType(pos_block) != game::EntityType::block; i++) {
        _packet.setType("destroy");
        _packet.addData("x", x);
        _EM.deleteFromPos(pos_block.x, pos_block.z);
        pos_block.z -= 10;
        _packet.addData("z", z - i * 10);
        for (auto &it : *_participants)
            it->deliver(_packet.getPacket());
    }
    _packet.clear();
}

void game::Game::refreshBomb()
{
    for (int i = 0; i != _allBomb.size(); i++) {
    // for (auto &it : _allBomb) {
        _allBomb[i].RefreshBomb();
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
}

float roundDecimal(int n)
{
    int a = (n / 10) * 10;
    int b = a + 10;
    return (n - a >= b - n) ? b : a;
}

game::s_pos game::Game::determineBombPos(int x, int z, std::string sens)
{
    s_pos pos_bomb;
    if (sens.compare("up") == 0) {
        pos_bomb.z = z - (z % 10);
        pos_bomb.x = x - (x % 10);
    }
    else if (sens.compare("down") == 0) {
        pos_bomb.z = z + 10 - (z % 10);
        pos_bomb.x = x - (x % 10);
    }
    else if (sens.compare("right") == 0) {
        pos_bomb.x = x - (x % 10);
        pos_bomb.z = z - (z % 10);
    }
    else if (sens.compare("left") == 0) {
        pos_bomb.x = x + 10 - (x % 10);
        pos_bomb.z = z - (z % 10);
    }
    return pos_bomb;
}


void game::Game::putBomb(t_id id)
{
    s_pos pos_bomb;

    for (auto &it : *_participants) {
        if (it->getId() == id) {
            if (static_cast<Character *>(it.get())->getCooldownBomb() >= 0.5) {
                pos_bomb = determineBombPos(it.get()->getPosition().x, it.get()->getPosition().z, it.get()->getDirection());
                _packet.setType("bomb");
                _packet.addData("x", pos_bomb.x);
                _packet.addData("z", pos_bomb.z);
                static_cast<Character *>(it.get())->setCooldownBomb();
                _allBomb.emplace_back(pos_bomb.x, pos_bomb.z, it.get()->getPower());
            }
        }
    }
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

void game::Game::iniNewBot()
{
    Bot bot;
    game::s_pos pos;
    
    pos = {81, 5, 11};
    bot.setPosition(pos);
    bot.setSpawn(pos);
    bot.setSkin(1);
    _EM.addEntity(bot);
}

game::p_entity::pointer game::Game::getBot()
{
    return _EM.getBot();
}
