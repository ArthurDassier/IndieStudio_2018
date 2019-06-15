/*
** EPITECH PROJECT, 2019
** logic for pause client for indi
** File description:
** LogicPause.cpp
*/

#include <iostream>
#include "Client/LogicPause.hpp"

LogicPause::LogicPause():
    _client(),
    _mode(MAINMENU),
    _key(KEY_KEY_CODES_COUNT),
    _lastKey(KEY_KEY_CODES_COUNT),
    _data("")
{
}

void LogicPause::setKey(EKEY_CODE key)
{
    _key = key;
}

void LogicPause::setMode(MODE mode)
{
    _mode = mode;
}

void LogicPause::dataMove(std::string move)
{
    boost::property_tree::ptree root;
    root.put("type", "movement");
    root.put("sens", move);
    std::ostringstream buff;
    boost::property_tree::write_json(buff, root, false);
    _data = buff.str();
}

void LogicPause::buildJSON(std::string type)
{
    boost::property_tree::ptree root;
    root.put("type", type);
    std::ostringstream buff;
    boost::property_tree::write_json(buff, root, false);
    _data = buff.str();
}

void LogicPause::manageKey()
{
    if (_key == KEY_KEY_CODES_COUNT) {
        _lastKey = _key;
        return;
    }
    if (_key == KEY_KEY_Z) {
        dataMove("up");
        _client.sendToServer(_data);
        _data.clear();
    }
    else if (_key == KEY_KEY_S) {
        dataMove("down");
        _client.sendToServer(_data);
        _data.clear();
    }
    else if (_key == KEY_KEY_Q) {
        dataMove("left");
        _client.sendToServer(_data);
        _data.clear();
    }
    else if (_key == KEY_KEY_D) {
        dataMove("right");
        _client.sendToServer(_data);
        _data.clear();
    } else if (_key == KEY_ESCAPE && _lastKey != KEY_ESCAPE) {
        buildJSON("pause");
        _client.sendToServer(_data);
        _mode = MENU;
    } else if (_key == KEY_SPACE && _lastKey != KEY_SPACE) {
        buildJSON("space");
        _client.sendToServer(_data);
        _data.clear();
    }
    _lastKey = _key;
    _key = KEY_KEY_CODES_COUNT;
}

client::Client &LogicPause::getClient()
{
    return _client;
}

MODE &LogicPause::getMode()
{
    return _mode;
}

std::string LogicPause::getData() const
{
    return _data;
}
