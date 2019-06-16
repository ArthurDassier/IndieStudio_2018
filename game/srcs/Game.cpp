/*
** EPITECH PROJECT, 2019
** IndieStudio_2018
** File description:
** Game.cpp
*/

#include "Game/BombUp.hpp"
#include "Game/Character.hpp"
#include "Game/Game.hpp"
#include "Game/FireUp.hpp"
#include "Game/IEntity.hpp"
#include "Game/MovableEntity.hpp"
#include "Game/SpeedUp.hpp"
#include "Game/WallPass.hpp"
#include "Game/Bot.hpp"

void game::Game::gameLoop()
{
    if (_isSolo && !_botCreated) {
        std::cout << "new bot" << std::endl;
        iniNewBot();
        setBotActive(true);
        setBotCreated(true);
    }
    for (auto &it : *_participants) {
        refreshBomb();
        if (isBotActive())
            updateBot();
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
                it->getPosition().z += it->getSpeed();
            else if (direction.compare("down") == 0)
                it->getPosition().z -= it->getSpeed();
            else if (direction.compare("left") == 0)
                it->getPosition().x -= it->getSpeed();
            else if (direction.compare("right") == 0)
                it->getPosition().x += it->getSpeed();
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
    sendPacket(_packet.getPacket());
}

bool game::Game::updatePositionBot(const std::string direction)
{
    s_pos pos_player;

    pos_player = _bot.getPosition();
    _bot.setDirection(direction);
    if (direction.compare("up") == 0)
        _bot.getPosition().z += 2;
    else if (direction.compare("down") == 0)
        _bot.getPosition().z -= 2;
    else if (direction.compare("left") == 0)
        _bot.getPosition().x -= 2;
    else if (direction.compare("right") == 0)
        _bot.getPosition().x += 2;
    if (checkCollisions(&_bot) == false) {
        _bot.setPosition(pos_player);
        return true;
    }

    _packet.addData("id", _bot.getId());
    _packet.addData("sens", direction);
    _packet.setType("move_other");
    for (auto &it : *_participants) {
        it->deliver(_packet.getPacket());
    }
    _packet.clear();
    return false;
}

void game::Game::destroyV(size_t power, s_pos pos)
{
    s_pos pos_block = pos;

    for (int i = 0; i != power && _EM.getEntityType(pos_block) != game::EntityType::block; i++) {
        checkDeath(pos_block.x, pos_block.z);
        _packet.addToVector<std::array<float, 2>>({pos.x, pos.z + i * 10});
        if (_EM.getEntityType(pos_block) == game::EntityType::brittleBlock) {
            _EM.deleteFromPos(pos_block.x, pos_block.z);
            dropBonus(pos_block.x, pos_block.z);
            break;
        }
        _EM.deleteFromPos(pos_block.x, pos_block.z);
        pos_block.z += 10;
    }
    pos_block = pos;
    for (int i = 0; i != power && _EM.getEntityType(pos_block) != game::EntityType::block; i++) {
        checkDeath(pos_block.x, pos_block.z);
        _packet.addToVector<std::array<float, 2>>({pos.x, pos.z - i * 10});
        if (_EM.getEntityType(pos_block) == game::EntityType::brittleBlock) {
            _EM.deleteFromPos(pos_block.x, pos_block.z);
            dropBonus(pos_block.x, pos_block.z);
            break;
        }
        _EM.deleteFromPos(pos_block.x, pos_block.z);
        pos_block.z -= 10;
    }
}

void game::Game::destroyH(size_t power, s_pos pos)
{
    s_pos pos_block = pos;

    for (int i = 0; i != power && _EM.getEntityType(pos_block) != game::EntityType::block; i++) {
        checkDeath(pos_block.x, pos_block.z);
        _packet.addToVector<std::array<float, 2>>({pos.x + i * 10, pos.z});
        if (_EM.getEntityType(pos_block) == game::EntityType::brittleBlock) {
            _EM.deleteFromPos(pos_block.x, pos_block.z);
            dropBonus(pos_block.x, pos_block.z);
            break;
        }
        _EM.deleteFromPos(pos_block.x, pos_block.z);
        pos_block.x += 10;
    }
    pos_block = pos;
    for (int i = 0; i != power && _EM.getEntityType(pos_block) != game::EntityType::block; i++) {
        checkDeath(pos_block.x, pos_block.z);
        _packet.addToVector<std::array<float, 2>>({pos.x - i * 10, pos.z});
        if (_EM.getEntityType(pos_block) == game::EntityType::brittleBlock) {
            _EM.deleteFromPos(pos_block.x, pos_block.z);
            dropBonus(pos_block.x, pos_block.z);
            break;
        }
        _EM.deleteFromPos(pos_block.x, pos_block.z);
        pos_block.x -= 10;
    }
}

void game::Game::destroyMap(size_t power, float x, float z)
{
    s_pos pos_block;
    pos_block.x = x;
    pos_block.z = z;

    destroyV(power, pos_block);
    destroyH(power, pos_block);
    if (_packet.getVectorSize() != 0) {
        _packet.setType("destroy");
        _packet.addList("blocks", _packet.getVector());
        sendPacket(_packet.getPacket());
    }
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
            sendPacket(_packet.getPacket());
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
    sendPacket(_packet.getPacket());
}


void game::Game::putBombBot(t_id id)
{
    s_pos pos_bomb;
    bool send = false;

    if (_bot.getCooldownBomb() >= 0.5) {
        pos_bomb = roundPos(_bot.getPosition().x, _bot.getPosition().z, _bot.getDirection());
        _packet.setType("bomb");
        _packet.addData("x", pos_bomb.x);
        _packet.addData("z", pos_bomb.z);
        _bot.setCooldownBomb();
        _allBomb.emplace_back(pos_bomb.x, pos_bomb.z, _bot.getPower());
        send = true;
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

    for (auto &it : map) {
        if (it == '1') {
            Block b;
            b.setPosition({x, 5, y});
            _EM.addEntity(b);
        }
        else if (it == '2') {
            BrittleBlock bB;
            bB.setPosition({x, 0, y});
            _EM.addEntity(bB);
        }
        y+= 10;
        if (it == '\n') {
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
    if (_EM.getEntityType(pos_entity) != game::EntityType::brittleBlock)
        return;
    if (std::rand() % 8 != 1)
        return;
    int k = std::rand() % 4;
    _packet.setType("dropBonus");
    _packet.addData("x", x);
    _packet.addData("z", z);
    if (k == 0) {
        Bombup b;
        b.setPosition({x, 5, z});
        _EM.addEntity(b);
        _packet.addData("bonusType", "BombUp");
    }
    else if (k == 1) {
        Speedup b;
        b.setPosition({x, 5, z});
        _EM.addEntity(b);
        _packet.addData("bonusType", "SpeedUp");
    }
    else if (k == 2) {
        Fireup b;
        b.setPosition({x, 5, z});
        _EM.addEntity(b);
        _packet.addData("bonusType", "FireUp");
    }
    else if (k == 3) {
        Wallpass b;
        b.setPosition({x, 5, z});
        _EM.addEntity(b);
        _packet.addData("bonusType", "WallPass");
    }
    sendPacket(_packet.getPacket());
}

void game::Game::takeBonus(t_entity::element_type* entity, float x, float z, std::string sens)
{
    s_pos pos_player = roundPos(x, z, sens);
    if (_EM.getEntityType(pos_player) == game::EntityType::SpeedUp) {
        entity->getSpeed() += 1;
        _packet.setType("setSpeed");
        _packet.addData("speed", entity->getSpeed());
        sendPacket(_packet.getPacket());
    }
    else if (_EM.getEntityType(pos_player) == game::EntityType::BombUp)
    {
    }
    else if (_EM.getEntityType(pos_player) == game::EntityType::FireUp) {
        entity->getPower() += 1;
    }
    else if (_EM.getEntityType(pos_player) == game::EntityType::WallPass) {
        entity->canWallPass = true;
    }
    else
        return;
    _EM.deleteFromPos(pos_player.x, pos_player.z);
    _packet.setType("removeBonus");
    _packet.addData("x", pos_player.x);
    _packet.addData("z", pos_player.z);
    sendPacket(_packet.getPacket());
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
    game::s_pos pos;

    pos = {81, 5, 11};
    // _bot.setDirection("right");
    _bot.setPosition(pos);
    _bot.setSpawn(pos);
    _bot.setSkin(1);
    _EM.addEntity(_bot);

    _packet.setType("new_player");
    _packet.addData("id", _bot.getId());
    _packet.addData("x", _bot.getPosition().x);
    _packet.addData("y", _bot.getPosition().y);
    _packet.addData("z", _bot.getPosition().z);
    _packet.addData("skin", "1");
    for (auto &it : *_participants)
        it->deliver(_packet.getPacket());
    _packet.clear();
}

game::p_entity::pointer game::Game::getBot()
{
    return _EM.getBot();
}

void game::Game::updateBot()
{
    auto delay = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsed = delay - _cooldownMove;
    std::chrono::duration<double, std::milli> elapsed2 = delay - _cooldownBombBot;
    bool ret;

    if (elapsed.count() / 1000 >= 0.3) {
        _cooldownMove = std::chrono::high_resolution_clock::now();
        ret = updatePositionBot(std::string(sens[sens_bot]));
        sens_bot = ret ? (sens_bot + 1 > 3 ? 0 : sens_bot + 1) : sens_bot;
    }
    if (elapsed2.count() / 1000 >= 8) {
        _cooldownBombBot = std::chrono::high_resolution_clock::now();
        putBombBot(_bot.getId());
    }
}

void game::Game::checkDeath(float x, float z)
{
    s_pos pos_player;

    for (auto &it : *_participants) {
        pos_player = roundPos(it.get()->getPosition().x, it.get()->getPosition().z, it.get()->getDirection());
        if (pos_player.x == x && pos_player.z == z) {
            _packet.setType("death");
            it->deliver(_packet.getPacket());
            _packet.clear();
        }
    }
}

void game::Game::setSolo(bool solo)
{
    _isSolo = solo;
}

bool game::Game::isSolo()
{
    return _isSolo;
}

void game::Game::setBotCreated(bool bot)
{
    _botCreated = bot;
}