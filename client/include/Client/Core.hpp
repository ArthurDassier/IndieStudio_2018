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

#define forever while (42)

namespace client
{
    class Core
    {
        public:
            Core();
            ~Core() = default;

            void startCore();
            int menuEvent();
            bool isHost() const;

        private:
            EngineGraphic _graph;
            LogicPause _logicPause;
            MenuEvent _menuEvent;
            bool _isHost;
            bool _isPause;
            std::string _instruction;
            std::thread _t1;
            std::array<std::string, 2> _infosConnect;
    };
};
