/*
** EPITECH PROJECT, 2019
** IndieStudio_2018
** File description:
** Packet.hpp
*/

#pragma once

#include <ostream>
#include <sstream>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

namespace utils
{
    class Packet
    {
        public:
            Packet() = default;
            ~Packet() = default;

            std::string const getPacket() noexcept;

            void setType(const std::string);

            template <typename T>
            void addData(const std::string name, const T data)
            {
                root.put(name, data);
            }

            // void addList(const std::string name)
            // {
            //     root.add_child("name");
            // }

            template <typename T>
            void addPairToList(const std::string name1, const std::string name2, T elem1, T elem2)
            {
                boost::property_tree::ptree f;
                boost::property_tree::ptree s;

                // list.push_back(std::make_pair)

                f.put(name1, elem1);
                f.put(name2, elem2);

                list.push_back(std::make_pair("", f));
                // list.put("block", std::make_pair("", f));
            }

            template <typename T>
            void addDataToList(const std::string name, const T data)
            {
                list.put(name, data);
            }

            template <typename T>
            void addList(const std::string name, std::vector<T> data)
            {
                boost::property_tree::ptree matrix_node;

                for (auto &it : data) {
                    boost::property_tree::ptree row;
                    for (auto &it_c : it) {
                        boost::property_tree::ptree cell;
                        cell.put_value(it_c);
                        row.push_back(std::make_pair("", cell));
                    }
                    matrix_node.push_back(std::make_pair("", row));
                }
                root.add_child(name, matrix_node);
            }

            void clear();

        private:
            boost::property_tree::ptree root;
            boost::property_tree::ptree list;
    };
}; // namespace utils