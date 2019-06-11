/*
** EPITECH PROJECT, 2019
** main client for indi
** File description:
** main.cpp
*/

#include "Client/Core.hpp"

client::Core::Core():
    // _io_service(),
    // _client(_io_service),
    _graph(),
    _logicPause()
{
}

void client::Core::startCore()
{
    // _client.start_receive();
    _logicPause.getClient().connect();
    _logicPause.getClient().start_receive();
    _graph.addCamera();
    while (2) {
        if (_graph.runGraph() == 84)
            break;
        _logicPause.setKey(_graph.input());
        _logicPause.manageKey();
        // if (_graph.getData().empty() == false) {
        //     _client.sendToServer(_graph.getData());
        //     _graph.clearData();
        // }
        if (_logicPause.getClient().getRoot().empty() == false) {
            _graph.setRoot(_logicPause.getClient().getRoot());
            _graph.matchQuery();
            _logicPause.getClient().clearRoot();
        }
        _logicPause.getClient().call_poll_one();
    }
}
