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
    _mode(GAME),
    _lastKey(KEY_KEY_CODES_COUNT),
    _data("")
{
}

void LogicPause::setKey(EKEY_CODE key)
{
    _lastKey = key;
}

void LogicPause::setData(std::string data)
{
    _data = data;
}

std::string LogicPause::getData() const
{
    return _data;
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

void LogicPause::sendEscape()
{
    boost::property_tree::ptree root;
    root.put("type", "pause");
    std::ostringstream buff;
    boost::property_tree::write_json(buff, root, false);
    _data = buff.str();
}

void LogicPause::manageKey()
{
    if (_lastKey == KEY_KEY_CODES_COUNT)
        return;
    if (_mode == GAME) {
        if (_lastKey == KEY_KEY_Z) {
            dataMove("up");
            _client.sendToServer(_data);
            _data.clear();
        }
        else if (_lastKey == KEY_KEY_S) {
            dataMove("down");
            _client.sendToServer(_data);
            _data.clear();
        }
        else if (_lastKey == KEY_KEY_Q) {
            dataMove("left");
            _client.sendToServer(_data);
            _data.clear();
        }
        else if (_lastKey == KEY_KEY_D) {
            dataMove("right");
            _client.sendToServer(_data);
            _data.clear();
        }
        else if (_lastKey == KEY_ESCAPE) {
            sendEscape();
            _client.sendToServer(_data);
            _mode = MENU;
        }
    }
    _lastKey = KEY_KEY_CODES_COUNT;
}

client::Client &LogicPause::getClient()
{
    return _client;
}