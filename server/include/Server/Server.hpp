/*
** EPITECH PROJECT, 2019
** server.hpp
** File description:
** header for server
*/

#pragma once

#include <string>
#include <iostream>
#include <map>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/array.hpp>
#include <boost/make_shared.hpp>
#include <boost/noncopyable.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include "Server/Room.hpp"
#include "Server/Session.hpp"
#include "Game/Game.hpp"
#include "Error/Error.hpp"

using boost::asio::ip::udp;

#define forever while

namespace server
{
    class Server
    {
        public:
            Server();
            ~Server();

            // Members
            void run();
            void stop();
            bool getPause() const noexcept;

        private:
            void start_receive();
            void handle_receive(const boost::system::error_code &, std::size_t);
            void handle_send(boost::shared_ptr<std::string>, const boost::system::error_code &, std::size_t);

            void setHasReceived(const bool);
            bool getHasReceived() const noexcept;

            void setRoot(const boost::property_tree::ptree);
            boost::property_tree::ptree getRoot() const noexcept;

            void connection();
            void movement();
            void pause();
            void space();

            boost::asio::io_service _io_service;
            boost::shared_ptr<boost::asio::ip::udp::socket> _socket;
            boost::asio::ip::udp::endpoint _remote_endpoint;
            std::array<char, 1024> _recv_buffer = {0};
            boost::shared_ptr<Session> _session;
            boost::property_tree::ptree _root;
            std::map<std::string, std::function<void()>> _fMap;
            game::Game _game;
            Room _room;
            bool _pause;
            bool _hasReceived;
            bool _running;
    };
}; // namespace server
