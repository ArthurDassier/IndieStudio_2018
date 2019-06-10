#include <iostream>
#include "module_tmp/toto.hpp"
#include "client/core.hpp"

#include <ctime>
#include <string>
#include <thread>
#include "server/server.hpp"

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

int main(int ac, char **av)
{
    if (ac != 2)
        return (84);
    std::string str(av[1]);
    if (str.compare("serv") == 0) {
        std::thread t1(run_server);
        client::Core all;
        all.startCore();
        t1.join();
    }
    else {
        client::Core all;
        all.startCore();
    }
}
