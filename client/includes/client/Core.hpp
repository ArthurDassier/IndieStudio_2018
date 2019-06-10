/*
** EPITECH PROJECT, 2019
** core
** File description:
** core
*/

#pragma once

#include "client/Client.hpp"
#include "client/Graphic.hpp"

class Core
{
    public:
        Core();
        ~Core();
        void startCore();
    private:
        boost::asio::io_service _io_service;
        Client _client;
        EngineGraphic _graph;
};
