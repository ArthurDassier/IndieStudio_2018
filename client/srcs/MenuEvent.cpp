#include "Client/MenuEvent.hpp"

MenuEvent::MenuEvent(gui::IGUIEnvironment *env, video::IVideoDriver *driver, MODE &mode):
    _sfx("client/config/audio.json"),
    _menu(env, driver),
    _mode(mode)
{
    _sfx.loadConfig();
    _sfx.playMusic("menu");
    _menu.changeMenu("client/config/MainMenu.json");
    _functions["startSolo"] = &MenuEvent::startSolo;
    _functions["host"] = &MenuEvent::host;
    _functions["startMulti"] = &MenuEvent::menuMulti;
    _functions["optionMenu"] = &MenuEvent::menuOptions;
    _functions["quit"] = &MenuEvent::quit;
    _functions["help"] = &MenuEvent::menuHelp;
    _functions["returnMain"] = &MenuEvent::returnMain;
    _functions["resumeGame"] = &MenuEvent::endPause;
    _functions["return"] = &MenuEvent::returnLastMenu;
    _functions["joinServer"] = &MenuEvent::joinServer;
}

std::string MenuEvent::launchFunction(s32 id)
{
    if (id == -1)
        return "";
    return (this->*_functions[_menu[id]->getName()])(id);
}

void MenuEvent::startPause()
{
    _sfx.pauseMusic("game");
    _menu.changeMenu("./client/config/PauseMenu.json");
}

std::string MenuEvent::endPause(s32 id)
{
    (void)id;
    _mode = GAME;
    _sfx.playMusic("game");
    return "endPause";
}

std::string MenuEvent::startSolo(s32 id)
{
    (void)id;
    _sfx.playSound("button");
    if (_mode == MAINMENU) {
        _mode = GAME;
        _sfx.pauseMusic("menu");
        _sfx.playMusic("game");
        return "connectSolo";
    }
    return "";
}

std::string MenuEvent::host(s32 id)
{
    (void)id;
    _sfx.playSound("button");
    if (_mode == MAINMENU) {
        _mode = GAME;
        _sfx.pauseMusic("menu");
        _sfx.playMusic("game");
        return "connectHost";
    }
    return "";
}

std::string MenuEvent::menuMulti(s32 id)
{
    (void)id;
    _sfx.playSound("button");
    _menu.changeMenu("client/config/JoinServerMenu.json");
    return "";
}

std::string MenuEvent::menuOptions(s32 id)
{
    (void)id;
    _sfx.playSound("button");
    _menu.changeMenu("client/config/OptionsMenu.json");
    return "";
}

std::string MenuEvent::quit(s32 id)
{
    (void)id;
    _sfx.playSound("button");
    return "quit";
}

std::string MenuEvent::menuHelp(s32 id)
{
    (void)id;
    _sfx.playSound("button");
    _menu.changeMenu("client/config/helpMenu.json");
    return "";
}

std::string MenuEvent::returnMain(s32 id)
{
    (void)id;
    _sfx.playSound("button");
    _menu.changeMenu("client/config/MainMenu.json");
    return "";
}

std::string MenuEvent::returnLastMenu(s32 id)
{
    (void)id;
    _sfx.playSound("button");
    _menu.changeMenu(_menu.getLastMenu());
    return "";
}

std::string MenuEvent::joinServer(s32 id)
{
    _sfx.playSound("button");
    std::wstring ipAndPort = L"join:";
    ipAndPort += _menu[3]->getText();
    ipAndPort += L":";
    ipAndPort += _menu[4]->getText();
    std::string txt(ipAndPort.length(), ' ');
    std::copy(ipAndPort.begin(), ipAndPort.end(), txt.begin());
    return txt;
}