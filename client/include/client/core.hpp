/*
** EPITECH PROJECT, 2019
** core
** File description:
** core
*/

#pragma once

#include "client.hpp"
#include "Irrlicht.hpp"

namespace client
{
    class Core
    {
        public:
            Core();
            ~Core() = default;

            void startCore();

        private:
            boost::asio::io_service _io_service;
            Client _client;
            EngineGraphic _graph;
    };
}; // namespace client