/*
** EPITECH PROJECT, 2019
** IndieStudio_2018
** File description:
** GraphicLoader.hpp
*/

#pragma once

#include <map>

#include "irrlicht/irrlicht.h"
#include "Utils/ConfigManager.hpp"

using namespace irr;

namespace client
{
    class GraphicLoader
    {
        public:
            GraphicLoader();
            ~GraphicLoader() = default;

            void setSceneManager(scene::ISceneManager *);
            void setVideoDriver(video::IVideoDriver *);

            void loadModels();
            void loadTextures();

            scene::IAnimatedMesh *getModel(const std::string) const noexcept;
            irr::video::ITexture *getTexture(const std::string) const noexcept;

        private:
            utils::ConfigManager _config;
            scene::ISceneManager *_smgr;
            video::IVideoDriver *_driver;
            std::map<std::string, irr::video::ITexture *> _textures;
            std::map<std::string, scene::IAnimatedMesh *> _models;
    };
}; // namespace client