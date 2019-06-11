/*
** EPITECH PROJECT, 2019
** room.hpp
** File description:
** header for room
*/

#pragma once

#include <boost/bind.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <memory>

#include "../../../game/include/Character.hpp"
#include "../../../utils/include/utils/Packet.hpp"

using t_vector = std::vector<boost::shared_ptr<game::Character>>;

namespace server
{
    class Room
    {
        public:
            void join(boost::shared_ptr<game::Character>);
            void updatePosition(const t_id, std::string);

            void addParticipant(boost::shared_ptr<game::Character>, boost::shared_ptr<game::Character>);
            void addMap(boost::shared_ptr<game::Character>);

            void sendDeath(boost::shared_ptr<game::Character>);

            void startPosi(boost::shared_ptr<game::Character>);
            int nbParticipants();

            void setParticipants();
            std::shared_ptr<t_vector> getParticipants() const noexcept;
            void update_participants();

        private:
            utils::Packet _packet;
            t_vector _participants;
    };
}; // namespace server