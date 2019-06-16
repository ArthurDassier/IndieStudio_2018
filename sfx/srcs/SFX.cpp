/*
** EPITECH PROJECT, 2019
** IndieStudio_2018
** File description:
** SFX.cpp
*/

#include "SFX/SFX.hpp"

sfx::SFX::SFX(const std::string &config):
    _configPath(config)
{
    _config.setConfigFile(config);
    _config.openConfigFile(config);
    _config.setNode("audio");
}

void sfx::SFX::updateConfig()
{
    _config.setConfig("music.volume", _settings["music_volume"]);
    _config.setConfig("sound.volume", _settings["sound_volume"]);
    _config.writeConfig();
}

void sfx::SFX::loadConfig()
{
    loadAudioSettings();
    loadMusic();
    loadSound();
}

void sfx::SFX::loadAudioSettings()
{
    _settings["general_volume"] = getGeneralVolume();
    _settings["music_volume"] = getMusicVolume();
    _settings["sound_volume"] = getSoundVolume();
}

void sfx::SFX::loadMusic()
{
    pt::ptree node = _config.getNode("music");

    for (auto &it : _config.getConfigList<std::string>(node, "musics"))
        addMusic(it.first, it.second);
}

void sfx::SFX::loadSound()
{
    pt::ptree node = _config.getNode("sound");

    for (auto &it: _config.getConfigList<std::string>(node, "sounds"))
        addSound(it.first, it.second);
}

void sfx::SFX::addMusic(const std::string &music, const std::string &file)
{
    _music.push_back(std::make_unique<Music>(music, file));
    _music.back()->get()->setVolume(getMusicVolume());
}

void sfx::SFX::addMusic(const Music &music)
{
    _music.push_back(std::make_unique<Music>(music));
    _music.back()->get()->setVolume(getMusicVolume());
}

std::shared_ptr<sf::Music> sfx::SFX::getMusic(const std::string &music) const
{
    auto it = std::find_if(_music.begin(), _music.end(),
                            [&](const std::shared_ptr<Music> i) {
                                return (boost::iequals(music, i->getName()));
                            });
    if (it == _music.end())
        throw(error::SFXError("Failed to find a music"));
    return it->get()->get();
}

void sfx::SFX::addSound(const std::string &sound, const std::string &file)
{
    _sound.push_back(std::make_unique<Sound>(sound, file));
    _sound.back()->get()->setVolume(getSoundVolume());
}

void sfx::SFX::addSound(const Sound &sound)
{
    _sound.push_back(std::make_unique<Sound>(sound));
    _sound.back()->get()->setVolume(getSoundVolume());
}

std::shared_ptr<sf::Sound> sfx::SFX::getSound(const std::string &sound) const
{
    auto it = std::find_if(_sound.begin(), _sound.end(),
                            [&](const std::shared_ptr<Sound> i) {
                                return (boost::iequals(sound, i->getName()));
                            });
    if (it == _sound.end())
        throw(error::SFXError("Failed to find a sound"));
    return it->get()->get();
}

void sfx::SFX::playMusic(const std::string &music)
{
    auto m = getMusic(music);

    if (m->getStatus() != sf::SoundSource::Status::Playing)
        m->play();
}

void sfx::SFX::playSound(const std::string &sound)
{
    getSound(sound)->play();
}

void sfx::SFX::pauseMusic(const std::string &music)
{
    getMusic(music)->pause();
}

void sfx::SFX::pauseSound(const std::string &sound)
{
    getSound(sound)->pause();
}

void sfx::SFX::stopMusic(const std::string &music)
{
    getMusic(music)->stop();
}

void sfx::SFX::stopSound(const std::string &sound)
{
    getSound(sound)->stop();
}

void sfx::SFX::setGeneralVolume(const int &volume)
{
    _settings["general_volume"] = volume;
    setMusicVolume(volume);
    setSoundVolume(volume);
}

int sfx::SFX::getGeneralVolume()
{
    return _config.getConfig<int>("volume");
}

void sfx::SFX::setMusicVolume(const int &volume)
{
    _settings["music_volume"] = volume;
    for (auto &it : _music)
        it->get()->setVolume(volume);
}

int sfx::SFX::getMusicVolume()
{
    return _config.getConfig<int>("music.volume");
}

void sfx::SFX::setSoundVolume(const int &volume)
{
    _settings["sound_volume"] = volume;
    for (auto &it : _sound)
        it->get()->setVolume(volume);
}

int sfx::SFX::getSoundVolume()
{
    return _config.getConfig<int>("sound.volume");
}

int sfx::SFX::getVolume(const std::string &setting) const noexcept
{
    return _settings.find(setting)->second;
}

void sfx::SFX::resetVolume()
{
    setMusicVolume(getMusicVolume());
    setSoundVolume(getSoundVolume());
}