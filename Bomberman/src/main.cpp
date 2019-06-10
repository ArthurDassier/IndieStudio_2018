#include <iostream>
#include <ctime>
#include <string>
#include <thread>
#include "client/core.hpp"
#include "server/server.hpp"

int server()
{
    try {
        std::cout << "starting a server" << std::endl;
        Server server;
        server.run();
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    return (0);
}

int main(int ac, char **av)
{
    if (ac != 2)
        return (84);
    std::string str(av[1]);
    if (str.compare("serv") == 0) {
        std::thread t1(server);
        Core all;
        all.startCore();
        t1.join();
    }
    else {
        Core all;
        all.startCore();
    }
}
