#pragma once

#include <iostream>
#include <memory>
#include <vector>
#include <boost/property_tree/ptree.hpp>
#include "ConfigManager.hpp"
#include "irrlicht/irrlicht.h"
using namespace irr;

template<typename T>
using deleted_unique_ptr = std::unique_ptr<T,std::function<void(T*)>>;

class CustomMenu
{
public:
    CustomMenu(gui::IGUIEnvironment *env, video::IVideoDriver *driver);
    ~CustomMenu();
    void changeMenu(const std::string &configFile);
    void addElement(pt::ptree elem, const std::string name);
    gui::IGUIElement *operator[](s32 i);
    gui::IGUIEnvironment *operator->();
private:
    void addButton(pt::ptree elem, core::recti rect);
    void addScrollbar(pt::ptree elem, core::recti rect);
    void setSpriteBank(pt::ptree menu);
    ConfigManager _manager;
    gui::IGUIEnvironment *_env;
    std::vector<gui::IGUIElement *> _elems;
    gui::IGUISpriteBank *_bank;
    video::IVideoDriver *_driver;
};

bool strStartWith(std::string str1, const std::string str2);