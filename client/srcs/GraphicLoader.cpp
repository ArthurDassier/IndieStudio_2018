/*
** EPITECH PROJECT, 2019
** IndieStudio_2018
** File description:
** GraphicLoader.cpp
*/

#include "Client/GraphicLoader.hpp"

client::GraphicLoader::GraphicLoader()
{
    _config.setConfigFile("client/config/graphic.json");
}

void client::GraphicLoader::setSceneManager(scene::ISceneManager *smgr)
{
    _smgr = smgr;
}

void client::GraphicLoader::setVideoDriver(video::IVideoDriver *driver)
{
    _driver = driver;
}

void client::GraphicLoader::loadModels()
{
    for (auto &it : _config.getConfigList<std::string>("models"))
        _models.emplace(std::make_pair(it.first, _smgr->getMesh(it.second.c_str())));
}

void client::GraphicLoader::loadTextures()
{
    for (auto &it : _config.getConfigList<std::string>("textures"))
        _textures.emplace(std::make_pair(it.first, _driver->getTexture(it.second.c_str())));
}

scene::IAnimatedMesh *client::GraphicLoader::getModel(const std::string index) const noexcept
{
    auto tmp = _models.at(index);
    return _models.at(index);
}

irr::video::ITexture *client::GraphicLoader::getTexture(const std::string index) const noexcept
{
    return _textures.at(index);
}