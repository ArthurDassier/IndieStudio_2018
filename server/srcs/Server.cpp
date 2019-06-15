/*
** EPITECH PROJECT, 2019
** server.hpp
** File description:
** server
*/

#include "Server/Server.hpp"

server::Server::Server() :
    _io_service(),
    _socket(boost::make_shared<boost::asio::ip::udp::socket>(
        _io_service,
        udp::endpoint(udp::v4(), 7777)
        )
    ),
    _pause(false),
    _hasReceived(false),
    _running(true)
{
    _fMap.emplace(std::make_pair("connection", std::bind(&Server::connection, this)));
    _fMap.emplace(std::make_pair("movement", std::bind(&Server::movement, this)));
    _fMap.emplace(std::make_pair("pause", std::bind(&Server::pause, this)));
    _fMap.emplace(std::make_pair("space", std::bind(&Server::space, this)));
    _fMap.emplace(std::make_pair("quit", std::bind(&Server::stop, this)));
    _room.setMap(_game.getMap());
    start_receive();
}

server::Server::~Server()
{
    std::cout << "Server successfully exited" << std::endl;
}

void server::Server::run()
{
    forever (_running) {
        _io_service.poll();
        if (getHasReceived()) {
            _game.updateParticipants(_session->getRoom().getParticipants());
            _game.gameLoop();
        }
    }
}

void server::Server::stop()
{
    _io_service.stop();
    _running = false;
}

void server::Server::start_receive()
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

void server::Server::handle_receive(const boost::system::error_code &error,
std::size_t bytes_transferred)
{
    if (!error || error == boost::asio::error::message_size) {
        std::string receive_json = std::string(_recv_buffer.begin(), _recv_buffer.begin() + bytes_transferred);
        std::stringstream ss;

        ss << receive_json;
        try {
            boost::property_tree::read_json(ss, _root);
        } catch (std::exception &e) {
            throw(error::ServerError(e.what()));
        }
        _fMap.find(_root.get<std::string>("type"))->second();
        start_receive();
    }
}

void server::Server::handle_send(boost::shared_ptr<std::string> message,
const boost::system::error_code &error, std::size_t bytes_transferred)
{
    if (!error)
        std::cout << *message << " was sent" << std::endl;
    else
        std::cout << error.message() << std::endl;
}

void server::Server::connection()
{
    if (_room.nbParticipants() == 4)
        return;
    _pause = false;
    _session.reset(new Session(_socket, _remote_endpoint, _room));
    _session->start();
    setHasReceived(true);
    

    if (_room.nbParticipants() == 1) {
        // _game.setBotActive(true);
        _game.setPlayer(_room.getParticipants()->front());
    }
    // else
        // _game.setBotActive(false);
}

void server::Server::movement()
{
    if (!_pause) {
        std::string sens = _root.get<std::string>("sens");
        _game.updatePosition(boost::lexical_cast<t_id>(_remote_endpoint.port()), sens);
    }
}

void server::Server::space()
{
    if (!_pause)
        _game.putBomb(boost::lexical_cast<t_id>(_remote_endpoint.port()));
}

void server::Server::pause()
{
    if (_room.nbParticipants() == 1)
        _pause = !_pause;
}

bool server::Server::getPause() const noexcept
{
    return (_pause);
}

void server::Server::setHasReceived(const bool hasReceived)
{
    _hasReceived = hasReceived;
}

bool server::Server::getHasReceived() const noexcept
{
    return _hasReceived;
}

void server::Server::setRoot(const boost::property_tree::ptree root)
{
    _root = root;
}

boost::property_tree::ptree server::Server::getRoot() const noexcept
{
    return _root;
}
