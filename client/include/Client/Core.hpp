/*
** EPITECH PROJECT, 2019
** core
** File description:
** core
*/

#pragma once

#include <thread>
#include <chrono>

#include "Client/Client.hpp"
#include "Client/Graphic.hpp"
#include "Client/LogicPause.hpp"
#include "Client/MenuEvent.hpp"
#include "Server/Server.hpp"

namespace client
{
    class Core
    {
        public:
            Core();
            ~Core() = default;

            void startCore();
            bool isHost() const;

        private:
            EngineGraphic _graph;
            LogicPause _logicPause;
            MenuEvent _menuEvent;
            bool _isHost;
    };
};
