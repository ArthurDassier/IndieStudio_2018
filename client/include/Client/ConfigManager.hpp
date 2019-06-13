// /*
// ** EPITECH PROJECT, 2019
// ** IndieStudio_2018
// ** File description:
// ** ConfigManager.hpp
// */

// #pragma once

// #include <fstream>
// #include <iostream>
// #include <string>
// #include <vector>
// #include <boost/program_options.hpp>
// #include <boost/property_tree/json_parser.hpp>
// #include <boost/property_tree/ptree.hpp>

// namespace pt = boost::property_tree;

// class ConfigManager
// {
// 	public:
//         ConfigManager(const std::string &);
//         ConfigManager();
//         ~ConfigManager() = default;

//         void openConfigFile(const std::string &);
//         void setConfigFile(const std::string &);
//         std::string getConfigFile() const noexcept;

//         void setNode(const std::string &);
//         pt::ptree getNode() const noexcept;
//         pt::ptree getNode(const std::string &) const noexcept;
//         std::string getNodePath(const std::string &) const noexcept;

//         template <typename T>
//         void setConfig(const std::string &node, const T &value)
//         {
//             _pt.put(getNodePath(node), value);
//         }

//         template <typename T>
//         void writeConfig(const std::string &node, const T &value)
//         {
//             _pt.put(getNodePath(node), value);
//             write_json(_configFile, _pt);
//         }
        
//         void writeConfig(const pt::ptree &);
//         void writeConfig();

//         template <typename T>
//         T getConfig(const pt::ptree::key_type &key)
//         {
//             std::vector<std::string> vec = split(getNodePath(key), '.');
//             pt::ptree pt_tmp = _pt;

//             for (auto &it : vec)
//                 pt_tmp = pt_tmp.get_child(it);
//             return pt_tmp.get_value<T>();
//         }

//         template <typename T>
//         T getConfig(const pt::ptree &pt, const pt::ptree::key_type &key)
//         {
//             std::vector<std::string> vec = split(getNodePath(key), '.');
//             pt::ptree pt_tmp = pt;

//             for (auto &it : vec)
//                 pt_tmp = pt_tmp.get_child(it);
//             return pt_tmp.get_value<T>();
//         }

//         template <typename T>
//         std::unordered_map<std::string, T> getConfigList(const pt::ptree::key_type &key)
//         {
//             std::unordered_map<std::string, T> um;

//             for (auto &it : _pt.get_child(getNodePath(key)))
//                 um[it.first] = it.second.get_value<T>();
//             return um;
//         }

//         template <typename T>
//         std::unordered_map<std::string, T> getConfigList(const pt::ptree &pt, const pt::ptree::key_type &key)
//         {
//             std::unordered_map<std::string, T> um;

//             for (auto &it : pt.get_child(key))
//                 um[it.first] = it.second.get_value<T>();
//             return um;
//         }

//         void setPtree(const pt::ptree &);
//         pt::ptree getPtree() const noexcept;

//     private:
//         void split(const std::string &, char, std::vector<std::string> &);
//         std::vector<std::string> split(const std::string &, char);

//         std::string _configFile;
//         std::string _node;
//         pt::ptree _pt;
// };