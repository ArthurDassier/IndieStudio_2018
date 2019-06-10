/*
** EPITECH PROJECT, 2019
** main client for indi
** File description:
** main.cpp
*/

#include "client/core.hpp"

Core::Core():
    _io_service(),
    _client(_io_service),
    _graph()
{
}

Core::~Core()
{
}

void Core::startCore()
{
    _client.start_receive();
    _graph.addCamera();
    while (2) {
        if (_graph.runGraph() == 84)
            break;
        if (_graph.getData().empty() == false) {
            _client.sendToServer(_graph.getData());
            _graph.clearData();
        }
        if (_client.getRoot().empty() == false) {
            _graph.manageRoot(_client.getRoot());
            _client.clearRoot();
        }
        _io_service.poll_one();
    }
}
