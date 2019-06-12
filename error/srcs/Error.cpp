/*
** EPITECH PROJECT, 2019
** IndieStudio_2018
** File description:
** Error.cpp
*/

#include "Error/Error.hpp"

error::Error::Error(const std::string &message, const std::string &component) throw():
    _message("\033[1;31m" + component + ": " + message + "\033[0m")
{
}

error::ClientError::ClientError(const std::string &message):
    Error(message, "Client")
{
}

error::GameError::GameError(const std::string &message):
    Error(message, "Game")
{
}

error::ServerError::ServerError(const std::string &message):
    Error(message, "Server")
{
}

error::SFXError::SFXError(const std::string &message):
    Error(message, "SFX")
{
}

error::UtilsError::UtilsError(const std::string &message):
    Error(message, "Utils")
{
}