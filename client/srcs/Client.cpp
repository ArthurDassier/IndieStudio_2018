/*
** EPITECH PROJECT, 2019
** client.cpp
** File description:
** client.cpp
*/

#include <thread>
#include <iostream>
#include "Client/Client.hpp"

client::Client::Client():
    _io_service(),
    _sock(_io_service)
{
}

void client::Client::call_poll_one()
{
    _io_service.poll_one();
}

void client::Client::connect(std::string ip_addr, std::string port)
{
    try {
        boost::asio::ip::udp::resolver resolver(_io_service);
        boost::asio::ip::udp::resolver::query query(ip_addr, port);
        _remote_endpoint = *resolver.resolve(query);
        boost::property_tree::ptree root;

        root.put("type", "connection");
        std::ostringstream buf;
        boost::property_tree::write_json(buf, root, false);
        std::string data = buf.str();

        _sock.open(boost::asio::ip::udp::v4());
        _sock.send_to(boost::asio::buffer(data), _remote_endpoint);
    } catch (std::exception& e) {
        throw(error::ClientError(e.what()));
    }
}

void client::Client::start_receive()
{
    //initialize the rmoete_endpoint_
    boost::asio::ip::udp::endpoint sender_endpoint;
    _sock.async_receive_from(
        boost::asio::buffer(_recv_buffer),
        sender_endpoint,
        boost::bind(
            &Client::handle_receive,
            this,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
}

void client::Client::sendToServer(std::string msg)
{
    _sock.send_to(boost::asio::buffer(msg), _remote_endpoint);
}

void client::Client::handle_receive(const boost::system::error_code& error,
    std::size_t bytes_transferred)
{
    if (!error || error == boost::asio::error::message_size) {
        std::string receive_json = std::string(_recv_buffer.begin(),
        _recv_buffer.begin() + bytes_transferred);
        boost::property_tree::ptree root;
        std::stringstream ss;

        ss << receive_json;
        try {
            boost::property_tree::read_json(ss, root);
        } catch (std::exception &e) {
            throw(error::ClientError(e.what()));
        }
        // manageType(root);
        _root = root;
        start_receive();
    } else
        std::cout << "je passe la" << error.message() << std::endl;
}

boost::property_tree::ptree client::Client::getRoot() const
{
    return (_root);
}

void client::Client::clearRoot()
{
    _root.clear();
}
