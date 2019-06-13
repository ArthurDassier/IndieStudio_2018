/*
** EPITECH PROJECT, 2019
** IndieStudio_2018
** File description:
** SFX.hpp
*/

#pragma once

#include <cassert>
#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>
#include <vector>
#include <boost/algorithm/string.hpp>

#include "Audio.hpp"
#include "ConfigManager.hpp"

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
        std::shared_ptr<Music> getMusic(const std::string &) const noexcept;

        void addSound(const std::string &, const std::string &);
        void addSound(const Sound &);
        std::shared_ptr<Sound> getSound(const std::string &) const noexcept;

        void playMusic(const std::string &);
        void playSound(const std::string &);

        void pauseMusic(const std::string &);
        void pauseSound(const std::string &);

        void stopMusic(const std::string &);
        void stopSound(const std::string &);

        void setGeneralVolume(const float &);
        float getGeneralVolume();

        void setMusicVolume(const float &);
        float getMusicVolume();

        void setSoundVolume(const float &);
        float getSoundVolume();

        float getVolume(const std::string &) const noexcept;
        void resetVolume();

    private:
        std::string _configPath;
        ConfigManager _config;
        std::vector<std::shared_ptr<Music>> _music;
        std::vector<std::shared_ptr<Sound>> _sound;
        std::unordered_map<std::string, float> _settings = {
            {"general_volume", 100},
            {"music_volume", 100},
            {"sound_volume", 100}
        };
        pt::ptree _defaultConfig;
};