/*
** EPITECH PROJECT, 2019
** IndieStudio
** File description:
** test
*/

#include <array>
#include <boost/program_options.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

namespace pt = boost::property_tree;

int main()
{
    pt::ptree root;
    int matrix[3][3];
    std::vector<std::array<int, 3>> pos = {
        {10, 0, 20},
        {20, 0, 10},
        {0, 10, 20}
    };
    std::vector<std::vector<int>> getPos;

    pt::ptree matrix_node;
    for (auto &it : pos) {
        pt::ptree row;
        for (auto &it_c : it) {
            pt::ptree cell;
            cell.put_value(it_c);
            row.push_back(std::make_pair("", cell));
        }
        matrix_node.push_back(std::make_pair("", row));
    }
    root.add_child("matrix", matrix_node);
    pt::write_json("test2.json", root);



    for (pt::ptree::value_type &row : root.get_child("matrix")) {
        std::vector<int> tmp;
        for (pt::ptree::value_type &cell : row.second) {
            tmp.push_back(cell.second.get_value<int>());
        }
        getPos.push_back(tmp);
    }
    for (auto &it : getPos) {
        std::cout << "{ ";
        for (auto &it_c : it)
            std::cout << it_c << " ";
        std::cout << "}" << std::endl;
    }
    return 0;
}