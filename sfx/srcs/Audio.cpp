/*
** EPITECH PROJECT, 2019
** IndieStudio_2018
** File description:
** SFX.cpp
*/

#include "SFX/Audio.hpp"

sfx::Audio::Audio(const std::string &name):
    _name(name)
{
}

std::string sfx::Audio::getName() const noexcept
{
    return _name;
}

sfx::Music::Music(const std::string &music, const std::string &file):
    Audio(music)
{
    _music = std::make_shared<sf::Music>();
    _music->openFromFile(file);
}

std::shared_ptr<sf::Music> sfx::Music::get() const noexcept
{
    return _music;
}

sfx::Sound::Sound(const std::string &sound, const std::string &file):
    Audio(sound)
{
    _buffer.loadFromFile(file);
    _sound = std::make_shared<sf::Sound>();
    _sound->setBuffer(_buffer);
}

std::shared_ptr<sf::Sound> sfx::Sound::get() const noexcept
{
    return _sound;
}