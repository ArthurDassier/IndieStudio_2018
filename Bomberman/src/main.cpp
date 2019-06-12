#include <iostream>
#include <ctime>
#include <string>
#include "Client/Core.hpp"

int main(int ac, char **av, char **env)
{
    if (env[0] == nullptr)
        return (84);
    client::Core all;
    all.startCore();
}
