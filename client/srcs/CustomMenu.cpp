#include <functional>
#include "Client/CustomMenu.hpp"


CustomMenu::CustomMenu(gui::IGUIEnvironment *env, video::IVideoDriver *driver) : _driver(driver)
{
    _env = env;
    _bank = _env->getSkin()->getSpriteBank();
    for (s32 i=0; i < irr::gui::EGDC_COUNT ; ++i)
	{
        video::SColor col = _env->getSkin()->getColor((gui::EGUI_DEFAULT_COLOR)i);
        col.setAlpha(255);
        _env->getSkin()->setColor((gui::EGUI_DEFAULT_COLOR)i, col);
        _env->getSkin()->setFont(_env->getBuiltInFont(), gui::EGDF_BUTTON);
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
    _env->addImage(_driver->getTexture("./client/res/menu_back.jpg"), core::position2d<s32>(0, 0));
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

void CustomMenu::addButton(pt::ptree elem, core::recti rect)
{
    gui::IGUIButton *newElem = _env->addButton(rect, 0, elem.get<int>("id"), L"Coucou", L"ok");
    newElem->setSpriteBank(_env->getSkin()->getSpriteBank());
    newElem->setSprite(gui::EGBS_BUTTON_FOCUSED, elem.get<s32>("texture"));
    newElem->setSprite(gui::EGBS_BUTTON_NOT_FOCUSED, elem.get<s32>("texture"));
    newElem->setName(elem.get<std::string>("name").c_str());
    _elems.push_back(newElem);
}

void CustomMenu::addScrollbar(pt::ptree elem, core::recti rect)
{
    gui::IGUIScrollBar *newElem = _env->addScrollBar(true, rect, 0, elem.get<int>("id"));

    newElem->setMax(100);
    newElem->setMin(0);
    newElem->setName(elem.get<std::string>("name").c_str());
    _elems.push_back(newElem);
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
    else
        exit(84);
}