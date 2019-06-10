/*
** EPITECH PROJECT, 2019
** IndieStudio_2018
** File description:
** ConfigManager.cpp
*/

#include "../include/utils/ConfigManager.hpp"

ConfigManager::ConfigManager(const std::string &file):
    _configFile(file),
    _node("")
{
    openConfigFile(file);
}

ConfigManager::ConfigManager():
    _configFile(""),
    _node("")
{
}

void ConfigManager::openConfigFile(const std::string &file)
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

void ConfigManager::setConfigFile(const std::string &file)
{
    _configFile = file;
    openConfigFile(file);
}

std::string ConfigManager::getConfigFile() const noexcept
{
    return _configFile;
}

void ConfigManager::setNode(const std::string &node)
{
    _node = node;
}

pt::ptree ConfigManager::getNode() const noexcept
{
    return _pt.get_child(_node);
}

pt::ptree ConfigManager::getNode(const std::string &node) const noexcept
{
    pt::ptree child = _pt.get_child(getNodePath(node));

    return child;
}

std::string ConfigManager::getNodePath(const std::string &node) const noexcept
{
    return _node + "." + node;
}

void ConfigManager::writeConfig(const pt::ptree &pt)
{
    write_json(getConfigFile(), pt);
}

void ConfigManager::writeConfig()
{
    write_json(getConfigFile(), _pt);
}

void ConfigManager::setPtree(const pt::ptree &pt)
{
    _pt = pt;
}

pt::ptree ConfigManager::getPtree() const noexcept
{
    return _pt;
}

void ConfigManager::split(const std::string &input, char del, std::vector<std::string> &elem)
{
    std::stringstream ss(input);
    std::string udrstr;

    while (std::getline(ss, udrstr, del))
        elem.push_back(udrstr);
}

std::vector<std::string> ConfigManager::split(const std::string &input, char del)
{
    std::vector<std::string> elem;

    split(input, del, elem);
    return elem;
}