/*
** EPITECH PROJECT, 2019
** server.hpp
** File description:
** header for server
*/

#pragma once

#include <string>
#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/array.hpp>
#include <boost/make_shared.hpp>
#include <boost/noncopyable.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <map>

#include "room.hpp"
#include "session.hpp"

using boost::asio::ip::udp;

class Server
{
    public:
        Server();

        // Members
        void run();
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

        boost::asio::io_service _io_service;
        boost::shared_ptr<boost::asio::ip::udp::socket> _socket;
        boost::asio::ip::udp::endpoint _remote_endpoint;
        boost::array<char, 128> _recv_buffer;
        boost::shared_ptr<Session> new_session;
        boost::property_tree::ptree _root;
        std::map<std::string, std::function<void()>> _fMap;
        Room _room;
        bool _pause;
        bool _hasReceived;
};