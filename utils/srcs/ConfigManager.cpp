/*
** EPITECH PROJECT, 2019
** IndieStudio_2018
** File description:
** ConfigManager.cpp
*/

#include "Utils/ConfigManager.hpp"

utils::ConfigManager::ConfigManager(const std::string &file):
    _configFile(file),
    _node("")
{
    openConfigFile(file);
}

utils::ConfigManager::ConfigManager():
    _configFile(""),
    _node("")
{
}

void utils::ConfigManager::openConfigFile(const std::string &file)
{
    std::ifstream ifs(file);
    std::fstream fs;

    if (ifs.good())
        read_json(file, _pt);
    else {
        fs.open(file, std::fstream::out);
        fs.close();
        // throw error
    }
}

void utils::ConfigManager::setConfigFile(const std::string &file)
{
    _configFile = file;
    openConfigFile(file);
}

std::string utils::ConfigManager::getConfigFile() const noexcept
{
    return _configFile;
}

void utils::ConfigManager::setNode(const std::string &node)
{
    _node = node;
}

pt::ptree utils::ConfigManager::getNode() const noexcept
{
    return _pt.get_child(_node);
}

pt::ptree utils::ConfigManager::getNode(const std::string &node) const noexcept
{
    pt::ptree child = _pt.get_child(getNodePath(node));

    return child;
}

std::string utils::ConfigManager::getNodePath(const std::string &node) const noexcept
{
    return (_node == "") ? node : (_node + "." + node);
}

void utils::ConfigManager::writeConfig(const pt::ptree &pt)
{
    write_json(getConfigFile(), pt);
}

void utils::ConfigManager::writeConfig()
{
    write_json(getConfigFile(), _pt);
}

void utils::ConfigManager::setPtree(const pt::ptree &pt)
{
    _pt = pt;
}

pt::ptree utils::ConfigManager::getPtree() const noexcept
{
    return _pt;
}

void utils::ConfigManager::split(const std::string &input, char del, std::vector<std::string> &elem)
{
    std::stringstream ss(input);
    std::string udrstr;

    while (std::getline(ss, udrstr, del))
        elem.push_back(udrstr);
}

std::vector<std::string> utils::ConfigManager::split(const std::string &input, char del)
{
    std::vector<std::string> elem;

    split(input, del, elem);
    return elem;
}