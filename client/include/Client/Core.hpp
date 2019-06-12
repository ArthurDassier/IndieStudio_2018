/*
** EPITECH PROJECT, 2019
** core
** File description:
** core
*/

#pragma once

#include "Client/Client.hpp"
#include "Client/Graphic.hpp"
#include "Client/LogicPause.hpp"

namespace client
{
    class Core
    {
        public:
            Core();
            ~Core() = default;

            void startCore();

        private:
            EngineGraphic _graph;
            LogicPause _logicPause;
    };
};
