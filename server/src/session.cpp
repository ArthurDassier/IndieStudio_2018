/*
** EPITECH PROJECT, 2019
** session.cpp
** File description:
** session
*/

#include "../include/server/session.hpp"

Session::Session(boost::shared_ptr<boost::asio::ip::udp::socket> socket,
boost::asio::ip::udp::endpoint endpoint, Room &room) :
    _socket(socket),
    _room(room),
    _remote_endpoint(endpoint),
    _player(get_id())
{
}

void Session::start()
{
    _room.join(shared_from_this());
}

boost::asio::ip::udp::socket &Session::socket()
{
    return *_socket;
}

void Session::deliver(std::string message)
{
    bool write_in_progress = !_message_queue.empty();

    _message_queue.push_back(message);
    if (!write_in_progress) {
        _socket->async_send_to(
            boost::asio::buffer(_message_queue.front()),
            _remote_endpoint,
            boost::bind(
                &Session::handle_send,
                this,
                _message_queue.front(),
                boost::asio::placeholders::error,
                boost::asio::placeholders::bytes_transferred));
    }
}

void Session::handle_send(__attribute__((unused)) std::string message,
const boost::system::error_code &error, __attribute__((unused)) std::size_t bytes_transferre)
{
    if (!error) {
        if (!_message_queue.empty()) {
            _message_queue.pop_front();
            if (!_message_queue.empty()) {
                _socket->async_send_to(
                    boost::asio::buffer(_message_queue.front()),
                    _remote_endpoint,
                    boost::bind(
                        &Session::handle_send,
                        this,
                        _message_queue.front(),
                        boost::asio::placeholders::error,
                        boost::asio::placeholders::bytes_transferred));
            }
        }
    }
}

std::string Session::get_id()
{
    return boost::lexical_cast<std::string>(_remote_endpoint.port());
}

player &Session::get_playerdata()
{
    return _player;
}
