/*
** EPITECH PROJECT, 2019
** server.hpp
** File description:
** server
*/

#include "../include/server/server.hpp"

Server::Server() :
    _io_service(),
    _socket(boost::make_shared<boost::asio::ip::udp::socket>(
        _io_service,
        udp::endpoint(udp::v4(), 7777)
        )
    )
{
    start_receive();
}

void Server::run()
{
    _io_service.run();
}

void Server::start_receive()
{
    _socket->async_receive_from(
        boost::asio::buffer(_recv_buffer),
        _remote_endpoint,
        boost::bind(
            &Server::handle_receive,
            this,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
}

void Server::handle_receive(const boost::system::error_code &error,
std::size_t bytes_transferred)
{
    if (!error || error == boost::asio::error::message_size) {
        std::string receive_json = std::string(_recv_buffer.begin(), _recv_buffer.begin() + bytes_transferred);
        boost::property_tree::ptree root;
        std::stringstream ss;

        std::cout << receive_json << std::endl;
        ss << receive_json;
        try {
            boost::property_tree::read_json(ss, root);
        } catch (std::exception &e) {
            std::cout << "Error: " << e.what() << std::endl;
        }
        std::string type = root.get<std::string>("type");
        if (type == "connection") {
            new_session.reset(new Session(_socket, _remote_endpoint, _room));
            new_session->start();
        } else if (type == "move") {
            std::string sens = root.get<std::string>("sens");
            _room.updatePosition(boost::lexical_cast<std::string>(_remote_endpoint.port()), sens);
        } else {
            // Eventuellement d'autres messages
        }
        start_receive();
    }
}

void Server::handle_send(boost::shared_ptr<std::string> message,
const boost::system::error_code &error, __attribute__((unused)) std::size_t bytes_transferred)
{
    if (!error)
        std::cout << *message << " was sent" << std::endl;
    else
        std::cout << error.message() << std::endl;
}
