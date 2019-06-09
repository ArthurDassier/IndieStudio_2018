#include <vector>
#include <iostream>
#include <cstdlib>
#include <iostream>
#include <ctime>

bool isBlockNext(std::vector<std::string> map, int j, int k)
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

std::string getResult(std::vector<std::string> &map)
{
    std::string result = "";
    for (int i = 0; i != map.size(); i++) {
        result += map[i] + "\n";
        std::cout << result;
    }
    return (result);
}

std::string genMap(size_t len)
{
    std::srand(std::time(nullptr));
    std::vector<std::string> map;
    int k = 0;
    map.push_back("1111111111");
    for (int i = 0; i != len - 2; i++)
        map.push_back("1000000001");
    map.push_back("1111111111");
    for (size_t j = 1; j != map.size() - 1; j++) {
        k = std::rand() % (len - 2);
        for (; k != map[k].size() - 1; k++) {
            if (isBlockNext(map, j, k) == true) {
                map[j][k] = '1';
                break;
            }
        }
    }
    return (getResult(map));
}
