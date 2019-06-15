/*
** EPITECH PROJECT, 2019
** main client for indi
** File description:
** main.cpp
*/

#include "Client/Core.hpp"

int run_server()
{
    try {
        std::cout << "starting a server" << std::endl;
        server::Server server;
        server.run();
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    return (0);
}

client::Core::Core():
    _graph(),
    _logicPause(),
    _menuEvent(_graph.getGUIEnvironment(), _graph.getDriver(), _logicPause.getMode()),
    _isHost(false),
    _isPause(false),
    _instruction("")
{
}

std::array<std::string, 2> getInfos(std::string str)
{
    std::array<std::string, 2> infos;
    size_t ip = str.find_first_of(':');
    size_t port = str.find_last_of(':');
    infos[0] = str.substr(ip, port);
    infos[1] = str.substr(port);
    return infos;
}

int client::Core::menuEvent()
{
    _instruction = _menuEvent.launchFunction(_graph.getGuiID());
    if (strStartWith(_instruction, "join")) {
            _infosConnect = getInfos(_instruction);
            _logicPause.getClient().connect(_infosConnect[0], _infosConnect[1]);
            _logicPause.getClient().start_receive();
        }
        if (_instruction == "quit") {
            if (_t1.joinable()) {
                _logicPause.buildJSON("quit");
                _logicPause.getClient().sendToServer(_logicPause.getData());
            }
            return (1);
        }
        if (_instruction == "endPause") {
            std::cout << "pause" << std::endl;
            _logicPause.buildJSON("pause");
            _logicPause.getClient().sendToServer(_logicPause.getData());
            _logicPause.setMode(GAME);
            _isPause = false;
        }
        if (_instruction == "connectSolo" || _instruction == "connectHost") {
            _isHost = true;
            _t1 = std::thread(run_server);
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
        if (strStartWith(_instruction, "connect")) {
            _logicPause.getClient().connect();
            _logicPause.getClient().start_receive();
        }
        return (0);
}

void client::Core::startCore()
{
    _graph.addCamera();
    while (2) {
        if (this->menuEvent() == 1)
            break;
        if (_graph.runGraph(_logicPause.getMode()) == 84) {
            if (_t1.joinable()) {
                _logicPause.buildJSON("quit");
                _logicPause.getClient().sendToServer(_logicPause.getData());
            }
            break;
        }
        _logicPause.setKey(_graph.input());
        _logicPause.manageKey();
        if (_logicPause.getMode() == MENU && !_isPause) {
            _menuEvent.startPause();
            _isPause = true;
        } else if (_logicPause.getMode() == GAME && _isPause) {
            _menuEvent.endPause(0);
            _isPause = false;
        }
        if (_logicPause.getClient().getRoot().empty() == false) {
            _graph.setRoot(_logicPause.getClient().getRoot());
            _graph.matchQuery();
            _logicPause.getClient().clearRoot();
        }
        if (_logicPause.getMode() != MAINMENU)
            _logicPause.getClient().call_poll_one();
    }
    if (_isHost)
        _t1.join();
}