/*
** EPITECH PROJECT, 2019
** IndieStudio_2018
** File description:
** SFX.hpp
*/

#pragma once

#include <memory>
#include <SFML/Audio.hpp>
#include <vector>

namespace sfx
{
    class Audio
    {
        public:
            Audio(const std::string &);

            std::string getName() const noexcept;

        protected:
            std::string _name;
    };

    class Music : public Audio
    {
        public:
            Music(const std::string &, const std::string &);

            // void set(const std::string &);
            std::shared_ptr<sf::Music> get() const noexcept;

        private:
            std::shared_ptr<sf::Music> _music;
    };

    class Sound : public Audio
    {
        public:
            Sound(const std::string &, const std::string &);

            // void set(const std::string &);
            std::shared_ptr<sf::Sound> get() const noexcept;

        private:
            sf::SoundBuffer _buffer;
            std::shared_ptr<sf::Sound> _sound;
    };
}; // namespace sfx