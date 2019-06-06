/*
** EPITECH PROJECT, 2019
** IndieStudio_2018
** File description:
** main.cpp
*/

#include <algorithm>
#include <iostream>
#include <memory>
#include <vector>
#include "Entity.hpp"
#include "EntityManager.hpp"

int main()
{
    std::vector<std::shared_ptr<game::Entity>> entities;
    // game::Bomb bomb({32, 3, 0});
    game::Bomb bomb;
    bomb.setPosition({32, 3, 0});
    game::EntityManager EM;

    EM.addEntity(game::Character());
    EM.addEntity(game::Character());
    EM.addEntity(bomb);
    EM.addEntity(game::Character());
    // EM.addEntity(game::Character({10, 3, 0}));
    // EM.addEntity(game::Character({12, 4, 0}));
    // EM.addEntity(bomb);
    // EM.addEntity(game::Character({27, 2, 0}));

    auto r = EM.getEntity({32, 3, 0});
    std::cout << "r(" << r->id << ")-> r.x = " << r->getPosition().x << std::endl;

    for (auto &it : EM.getEntities())
        std::cout << it->id << "-> " << it->getPosition().x << std::endl;

    EM.removeEntity(r);

    std::cout << "=====>" << std::endl;

    for (auto &it : EM.getEntities())
        std::cout << it->id << "-> " << it->getPosition().x << std::endl;
    return 0;
}