#include "Client/MenuEvent.hpp"

MenuEvent::MenuEvent(gui::IGUIEnvironment *env, video::IVideoDriver *driver, MODE &mode):
    _menu(env, driver),
    _mode(mode)
{
    _menu.changeMenu("client/config/MainMenu.json");
    _functions["startSolo"] = &MenuEvent::startSolo;
    _functions["host"] = &MenuEvent::host;
    _functions["startMulti"] = &MenuEvent::startMulti;
    _functions["optionMenu"] = &MenuEvent::menuOptions;
    _functions["quit"] = &MenuEvent::quit;
    _functions["help"] = &MenuEvent::menuHelp;
    _functions["returnMain"] = &MenuEvent::returnMain;
}

std::string MenuEvent::launchFunction(s32 id)
{
    if (id == -1)
        return "";
    return (this->*_functions[_menu[id]->getName()])(id);
}

std::string MenuEvent::startSolo(s32 id)
{
    (void)id;
    if (_mode == MAINMENU) {
        _mode = GAME;
        return "connectSolo";
    }
    return "";
}

std::string MenuEvent::host(s32 id)
{
    (void)id;
    if (_mode == MAINMENU) {
        _mode = GAME;
        return "connectHost";
    }
    return "";
}

std::string MenuEvent::startMulti(s32 id)
{
    (void)id;
    if (_mode == MAINMENU) {
        _mode = GAME;
        return "connect";
    }
    return "";
}

std::string MenuEvent::menuOptions(s32 id)
{
    (void)id;
    _menu.changeMenu("client/config/OptionsMenu.json");
    return "";
}

std::string MenuEvent::quit(s32 id)
{
    (void)id;
    return "quit";
}

std::string MenuEvent::menuHelp(s32 id)
{
    (void)id;
    _menu.changeMenu("client/config/helpMenu.json");
    return "";
}

std::string MenuEvent::returnMain(s32 id)
{
    (void)id;
    _menu.changeMenu("client/config/MainMenu.json");
    return "";
}