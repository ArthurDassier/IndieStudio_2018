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

void game::Game::gameLoop()
{
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
            // std::cout << it->getId() << "\n";
            std::cout << it->getPosition().x << "\n";
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

void game::Game::refreshBomb()
{
    for (int i = 0; i != _allBomb.size(); i++) {
        if (_allBomb[i].checkTimeExplosion() >= 1.5) {
            _packet.setType("explosion");
            _packet.addData("x", _allBomb[i].getPosX());
            _packet.addData("z", _allBomb[i].getPosZ());
            for (auto &it : *_participants)
                it->deliver(_packet.getPacket());
            _packet.clear();
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

void game::Game::putBomb(t_id id)
{
    for (auto &it : *_participants) {
        if (it->getId() == id) {
            if (static_cast<Character *>(it.get())->getCooldownBomb() >= 5) {
                _packet.setType("bomb");
                _packet.addData("x", it.get()->getPosition().x);
                _packet.addData("z", it.get()->getPosition().z);
                static_cast<Character *>(it.get())->setCooldownBomb();
                // _allBomb.emplace_back(it.get()->getPosition().x, it.get()->getPosition().z, it.get()->getPower());
            }
        }
    }
    for (auto &it : *_participants)
        it->deliver(_packet.getPacket());
    _packet.clear();
}

bool game::Game::checkCollisions(t_entity::element_type* entity)//Entity& entity)
{
    std::cout << entity->getPosition().x << std::endl;
    s_pos pos_player = entity->getPosition();
    std::cout << pos_player.x << ", " << pos_player.z << "\n";
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
