/*
** EPITECH PROJECT, 2019
** client.hpp
** File description:
** client.hpp
*/

#pragma once

#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <memory>

namespace client
{
    class Client
    {
        public:
            Client();
            ~Client() = default;
            void connect(std::string ip_addr = "127.0.0.1", std::string port = "7777");
            void start_receive();
            void sendToServer(std::string msg);
            void handle_receive(const boost::system::error_code& error,
                std::size_t /*bytes_transferred*/);
            void handle_send(boost::shared_ptr<std::string> /*message*/,
                const boost::system::error_code& /*error*/,
                std::size_t /*bytes_transferred*/);
            boost::property_tree::ptree getRoot() const;
            void clearRoot();
            void call_poll_one();

        private:
            boost::asio::io_service _io_service;
            boost::asio::ip::udp::socket sock_;
            boost::asio::ip::udp::endpoint remote_endpoint_;
            boost::array<char, 256> recv_buffer_;
            boost::property_tree::ptree _root;
    };
}; // namespace client
