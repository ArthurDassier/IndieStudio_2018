/*
** EPITECH PROJECT, 2019
** session.hpp
** File description:
** session header
*/

#pragma once

#include <iostream>
#include <deque>
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/noncopyable.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/property_tree/json_parser.hpp>

#include "Game/Character.hpp"
#include "Server/Room.hpp"
#include "Error/Error.hpp"

namespace server
{
    class Session : public game::Character,
                    public boost::enable_shared_from_this<Session>
    {
        public:
            Session(boost::shared_ptr<boost::asio::ip::udp::socket> socket,
                    boost::asio::ip::udp::endpoint endpoint, Room &room);

            // Members
            void start();

            void deliver(std::string message);

            Room getRoom() noexcept;

        private:
            void sendTo();
            void handle_send(std::string, const boost::system::error_code &, std::size_t);
            t_id getId();
            player &get_playerdata();

            boost::shared_ptr<boost::asio::ip::udp::socket> _socket;
            boost::asio::ip::udp::endpoint _remote_endpoint;
            std::deque<std::string> _message_queue;
            player _player;
            Room &_room;
            int _skin;
    };
}; // namespace server