/*
** EPITECH PROJECT, 2019
** client.cpp
** File description:
** client.cpp
*/

#include <thread>
#include <iostream>
#include "client/Client.hpp"

Client::Client(boost::asio::io_service &io_service):
    sock_(io_service)
{
    try {
        boost::asio::ip::udp::resolver resolver(io_service);
        boost::asio::ip::udp::resolver::query query("127.0.0.1", "7777");
        remote_endpoint_ = *resolver.resolve(query);
        boost::property_tree::ptree root;

        root.put("type", "connection");
        std::ostringstream buf;
        boost::property_tree::write_json(buf, root, false);
        std::string data = buf.str();

        sock_.open(boost::asio::ip::udp::v4());
        sock_.send_to(boost::asio::buffer(data), remote_endpoint_);
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}

Client::~Client()
{

}

void Client::start_receive()
{
    //initialize the rmoete_endpoint_
    boost::asio::ip::udp::endpoint sender_endpoint;
    sock_.async_receive_from(
        boost::asio::buffer(recv_buffer_),
        sender_endpoint,
        boost::bind(
            &Client::handle_receive,
            this,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
}

void Client::sendToServer(std::string msg)
{
    sock_.send_to(boost::asio::buffer(msg), remote_endpoint_);
}

void Client::handle_receive(const boost::system::error_code& error,
    std::size_t bytes_transferred)
{
    if (!error || error == boost::asio::error::message_size) {
        std::string receive_json = std::string(recv_buffer_.begin(),
        recv_buffer_.begin() + bytes_transferred);
        boost::property_tree::ptree root;
        std::stringstream ss;

        ss << receive_json;
        try {
            boost::property_tree::read_json(ss, root);
        } catch (std::exception &e) {
            std::cout << "Error: " << e.what() << std::endl;
        }
        // manageType(root);
        _root = root;
        start_receive();
    } else
        std::cout << "je passe la" << error.message() << std::endl;
}

boost::property_tree::ptree Client::getRoot() const
{
    return (_root);
}

void Client::clearRoot()
{
    _root.clear();
}
