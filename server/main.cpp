#include <ctime>
#include <iostream>
#include <string>
#include "server.hpp"

int main()
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
