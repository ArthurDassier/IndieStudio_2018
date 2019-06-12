/*
** EPITECH PROJECT, 2019
** IndieStudio_2018
** File description:
** IndieStudioError.hpp
*/

#pragma once

#include <exception>
#include <iostream>
#include <string>

namespace error
{
    class Error : public std::exception
    {
        public:
            Error(const std::string &message,
                  const std::string &component = "Unknown") throw();

            virtual const char *what() const throw()
            {
                return _message.data();
            }

        private:
            std::string _message;
    };

    class ClientError : public Error
    {
        public:
            ClientError(const std::string &message);
    };

    class GameError : public Error
    {
        public:
            GameError(const std::string &message);
    };

    class ServerError : public Error
    {
        public:
            ServerError(const std::string &message);
    };

    class SFXError : public Error
    {
        public:
            SFXError(const std::string &message);
    };

    class UtilsError : public Error
    {
        public:
            UtilsError(const std::string &message);
    };
}; // namespace error