#include <vector>
#include <iostream>
#include <cstdlib>
#include <iostream>
#include <ctime>

#include "Game/Generation.hpp"

bool game::Generation::isBlockNext(std::vector<std::string> map, int j, int k)
{
    if (j == 0 || k == 0)
        return false;
    if (map[j][k - 1] == '1'
    || map[j][k + 1] == '1'
    || map[j - 1][k] == '1'
    || map[j - 1][k - 1] == '1'
    || map[j - 1][k + 1] == '1'
    || map[j + 1][k] == '1'
    || map[j + 1][k - 1] == '1'
    || map[j + 1][k + 1] == '1')
        return false;
    return true;
}

std::string game::Generation::getResult(std::vector<std::string> &map)
{
    std::string result = "";

    for (int i = 0; i != map.size(); i++) {
        result += map[i] + "\n";
        std::cout << map[i] + '\n';
    }
    return result;
}

std::string const game::Generation::genMap(const std::size_t len)
{
    std::srand(std::time(nullptr));
    std::vector<std::string> map;
    int k = 0;
    map.push_back("1111111111");
    map.push_back("1002222001");
    map.push_back("1022222201");
    for (int i = 0; i != len - 4; i++)
        map.push_back("1222222221");
    for (size_t j = 1; j != map.size() - 2; j++) {
        k = std::rand() % (len - 2);
        for (; k != map[k].size() - 2; k++) {
            if (isBlockNext(map, j, k) == true) {
                map[j][k] = '1';
                break;
            }
        }
    }
    map[map.size() - 2] = "1002222201";
    map[map.size() - 1] = "1022222001";
    map.push_back("1111111111");
    std::cout << "size: " << map.size() << "\n";

    return (getResult(map));
}
