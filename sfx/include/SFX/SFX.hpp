/*
** EPITECH PROJECT, 2019
** IndieStudio_2018
** File description:
** SFX.hpp
*/

#pragma once

#include <boost/algorithm/string.hpp>
#include <cassert>
#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>
#include <vector>

#include "Audio.hpp"
#include "Error/Error.hpp"
#include "Utils/ConfigManager.hpp"

namespace sfx
{
    class SFX
    {
        public:
            
            SFX(const std::string &);

            void loadConfig();
            void loadConfig(const std::string &);
            void setConfig();
            void updateConfig();

            void loadAudioSettings();
            void loadMusic();
            void loadSound();

            void addMusic(const std::string &, const std::string &);
            void addMusic(const Music &);
            std::shared_ptr<sf::Music> getMusic(const std::string &) const;

            void addSound(const std::string &, const std::string &);
            void addSound(const Sound &);
            std::shared_ptr<sf::Sound> getSound(const std::string &) const;

            void playMusic(const std::string &);
            void playSound(const std::string &);

            void pauseMusic(const std::string &);
            void pauseSound(const std::string &);

            void stopMusic(const std::string &);
            void stopSound(const std::string &);

            void setGeneralVolume(const int &);
            int getGeneralVolume();

            void setMusicVolume(const int &);
            int getMusicVolume();

            void setSoundVolume(const int &);
            int getSoundVolume();

            int getVolume(const std::string &) const noexcept;
            void resetVolume();

        private:
            std::string _configPath;
            utils::ConfigManager _config;
            std::vector<std::shared_ptr<Music>> _music;
            std::vector<std::shared_ptr<Sound>> _sound;
            std::unordered_map<std::string, int> _settings = {
                {"general_volume", 100},
                {"music_volume", 100},
                {"sound_volume", 100}
            };
            pt::ptree _defaultConfig;
    };
}; // namespace sfx