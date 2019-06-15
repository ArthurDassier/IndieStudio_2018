/*
** EPITECH PROJECT, 2019
** IndieStudio_2018
** File description:
** CustomMenu.cpp
*/

#include <functional>
#include "Client/CustomMenu.hpp"

CustomMenu::CustomMenu(gui::IGUIEnvironment *env, video::IVideoDriver *driver):
    _driver(driver),
    _env(env),
    _bank(_env->getSkin()->getSpriteBank()),
    _lastMenu("")
{
    gui::IGUIFont *font = _env->getFont("./client/res/font.bmp");
    for (s32 i=0; i < irr::gui::EGDC_COUNT ; ++i)
	{
        video::SColor col = _env->getSkin()->getColor((gui::EGUI_DEFAULT_COLOR)i);
        col.setAlpha(255);
        _env->getSkin()->setColor((gui::EGUI_DEFAULT_COLOR)i, col);
        _env->getSkin()->setFont(font);
	}
}

CustomMenu::~CustomMenu()
{}

gui::IGUIElement *CustomMenu::operator[](s32 i)
{
    return _elems.at(i);
}

gui::IGUIEnvironment *CustomMenu::operator->()
{
    return _env;
}

void CustomMenu::setSpriteBank(pt::ptree menu)
{
    _bank->clear();
    for (auto &it : menu.get_child("textures")) {
        _bank->addTextureAsSprite(_driver->getTexture(it.second.get_value<std::string>().c_str()));
    }
}

void CustomMenu::changeMenu(const std::string &configFile)
{
    if (!_elems.empty())
        _elems.clear();
    _env->clear();
    if (_lastMenu == "")
        _lastMenu = configFile;
    else
        _lastMenu = _manager.getConfigFile();
    _manager.setConfigFile(configFile);
    for (auto &it : _manager.getPtree()) {
        if (it.first == "textures")
            this->setSpriteBank(_manager.getPtree());
        else if (it.first == "font")
            _env->getSkin()->setFont(_env->getFont(it.second.get_value<char *>()));
        else
            this->addElement(_manager.getNode(it.first), it.first);
    }
}

void CustomMenu::addImage(pt::ptree elem)
{
    gui::IGUIImage *img = _env->addImage(_bank->getTexture(elem.get<int>("texture")), core::position2d<s32>(0, 0));
    img->setID(elem.get<int>("id"));
    img->setScaleImage(true);
    _elems.push_back(img);
}

void CustomMenu::addButton(pt::ptree elem, core::recti rect)
{
    std::string txt = elem.get<std::string>("text");
    std::wstring wtxt(txt.length(), L' ');
    std::copy(txt.begin(), txt.end(), wtxt.begin());
    gui::IGUIButton *newElem = _env->addButton(rect, 0, elem.get<int>("id"), wtxt.c_str());
    newElem->setSpriteBank(_env->getSkin()->getSpriteBank());
    newElem->setSprite(gui::EGBS_BUTTON_UP, elem.get<s32>("texture"));
    newElem->setName(elem.get<std::string>("name").c_str());
    _elems.push_back(newElem);
}

void CustomMenu::addScrollbar(pt::ptree elem, core::recti rect)
{
    std::string txt = elem.get<std::string>("text");
    std::wstring wtxt(txt.length(), L' ');
    std::copy(txt.begin(), txt.end(), wtxt.begin());
    gui::IGUIScrollBar *newElem = _env->addScrollBar(true, rect, 0, elem.get<int>("id"));

    newElem->setMax(100);
    newElem->setMin(0);
    newElem->setName(elem.get<std::string>("name").c_str());
    newElem->setText(wtxt.c_str());
    _elems.push_back(newElem);
}

void CustomMenu::addText(pt::ptree elem, core::recti rect)
{
    std::string txt = elem.get<std::string>("text");
    std::wstring wtxt(txt.length(), L' ');
    std::copy(txt.begin(), txt.end(), wtxt.begin());
    gui::IGUIStaticText *text =  _env->addStaticText(wtxt.c_str(), rect, false, true, 0, elem.get<int>("id"));
    _elems.push_back(text);
}

void CustomMenu::addEditBox(pt::ptree elem, core::recti rect)
{
    std::string txt = elem.get<std::string>("text");
    std::wstring wtxt(txt.length(), L' ');
    std::copy(txt.begin(), txt.end(), wtxt.begin());
    gui::IGUIEditBox *box = _env->addEditBox(wtxt.c_str(), rect, true, 0, elem.get<int>("id"));
    _elems.push_back(box);
}

bool strStartWith(std::string str1, const std::string str2)
{
    return str1.substr(0, str2.size()) == str2;
}

void CustomMenu::addElement(pt::ptree elem, const std::string name)
{
    std::vector<int> pos;

    for (auto &it : elem.get_child("pos"))
        pos.push_back(it.second.get_value<int>());
    if (strStartWith(name, "button"))
        this->addButton(elem, core::recti(pos[0], pos[1], pos[2], pos[3]));
    else if (strStartWith(name, "scrollBar"))
        this->addScrollbar(elem, core::recti(pos[0], pos[1], pos[2], pos[3]));
    else if (strStartWith(name, "image"))
        this->addImage(elem);
    else if (strStartWith(name, "editBox"))
        this->addEditBox(elem, core::recti(pos[0], pos[1], pos[2], pos[3]));
    else if (strStartWith(name, "text"))
        this->addText(elem, core::recti(pos[0], pos[1], pos[2], pos[3]));
    else
        exit(84);
}

std::string CustomMenu::getLastMenu() const
{
    return _lastMenu;
}