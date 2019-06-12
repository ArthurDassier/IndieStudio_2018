/*
** EPITECH PROJECT, 2019
** main client for indi
** File description:
** main.cpp
*/

#include "Client/Core.hpp"

client::Core::Core():
    _graph(),
    _logicPause(),
    _menuEvent(_graph.getGUIEnvironment(), _graph.getDriver(), _logicPause.getMode())
{
}

void client::Core::startCore()
{
    std::string instruction = "";

    _graph.addCamera();
    while (2) {
        instruction = _menuEvent.launchFunction(_graph.getGuiID());
        if (instruction == "connect") {
            _logicPause.getClient().connect();
            _logicPause.getClient().start_receive();
        }
        if (_graph.runGraph(_logicPause.getMode()) == 84)
            break;
        _logicPause.setKey(_graph.input());
        _logicPause.manageKey();
        if (_logicPause.getClient().getRoot().empty() == false) {
            _graph.setRoot(_logicPause.getClient().getRoot());
            _graph.matchQuery();
            _logicPause.getClient().clearRoot();
        }
        if (_logicPause.getMode() != MAINMENU)
            _logicPause.getClient().call_poll_one();
    }
}
