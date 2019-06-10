#pragma once

#include <string>

std::string genMap(size_t len);
std::string getResult(std::vector<std::string> &map);
bool isBlockNext(std::vector<std::string> map, int j, int k);
