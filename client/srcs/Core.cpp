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
    _isHost(false)
{
}

void client::Core::startCore()
{
    std::string instruction = "";
    std::thread t1;

    _graph.addCamera();
    forever (42) {
        instruction = _menuEvent.launchFunction(_graph.getGuiID());
        if (instruction == "quit") {
            if (t1.joinable()) {
                _logicPause.buildJSON("quit");
                _logicPause.getClient().sendToServer(_logicPause.getData());
            }
            break;
        }
        if (instruction == "connectSolo" || instruction == "connectHost") {
            _isHost = true;
            t1 = std::thread(run_server);
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
        if (strStartWith(instruction, "connect")) {
            std::cout << "connection" << std::endl;
            _logicPause.getClient().connect();
            _logicPause.getClient().start_receive();
        }
        if (_graph.runGraph(_logicPause.getMode()) == 84) {
            if (t1.joinable()) {
                _logicPause.buildJSON("quit");
                _logicPause.getClient().sendToServer(_logicPause.getData());
            }
            break;
        }
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
    if (_isHost)
        t1.join();
}