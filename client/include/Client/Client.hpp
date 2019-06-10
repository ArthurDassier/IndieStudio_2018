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

class Client
{
    public:
        Client(boost::asio::io_service& io_service);
        ~Client();
        void start_receive();
        void sendToServer(std::string msg);
        void handle_receive(const boost::system::error_code& error,
            std::size_t /*bytes_transferred*/);
        void handle_send(boost::shared_ptr<std::string> /*message*/,
            const boost::system::error_code& /*error*/,
            std::size_t /*bytes_transferred*/);
        boost::property_tree::ptree getRoot() const;
        void clearRoot();

    private:
        boost::asio::ip::udp::endpoint remote_endpoint_;
        boost::array<char, 256> recv_buffer_;
        boost::asio::ip::udp::socket sock_;
        boost::property_tree::ptree _root;
};
