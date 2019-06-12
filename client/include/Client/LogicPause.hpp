/*
** EPITECH PROJECT, 2019
** LogicPause.hpp
** File description:
** lib graph for bomberman
*/

#pragma once

#include <fstream>
#include "Client/Client.hpp"
#include "irrlicht/irrlicht.h"

using namespace irr;

enum MODE {
    MENU,
    GAME
};

class LogicPause
{
    public:
        LogicPause();
        ~LogicPause() = default;

        void setKey(EKEY_CODE key);
        void setData(std::string data);
        std::string getData() const;
        void manageKey();

        client::Client &getClient();

        void dataMove(std::string move);
        void sendEscape();
        void sendSpace();

    private:
        client::Client _client;
        MODE _mode;
        EKEY_CODE _lastKey;
        std::string _data;
        boost::property_tree::ptree _message;
};
