#include "Client/MenuEvent.hpp"

MenuEvent::MenuEvent(gui::IGUIEnvironment *env, video::IVideoDriver *driver, MODE &mode):
    _sfx("client/config/audio.json"),
    _menu(env, driver),
    _mode(mode)
{
    _sfx.loadConfig();
    _sfx.playMusic("menu");
    _sfx.getMusic("menu")->setLoop(true);
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
    _functions["sound"] = &MenuEvent::soundVolume;
    _functions["music"] = &MenuEvent::musicVolume;
    _functions["saveOption"] = &MenuEvent::saveOptions;
    _functions["returnOptions"] = &MenuEvent::returnFromOptions;
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
    _sfx.playSound("play");
    if (_mode == MAINMENU) {
        _mode = GAME;
        _sfx.pauseMusic("menu");
        _sfx.playMusic("game");
        _sfx.getMusic("game")->setLoop(true);
        return "connectSolo";
    }
    return "";
}

std::string MenuEvent::host(s32 id)
{
    (void)id;
    _sfx.playSound("play");
    if (_mode == MAINMENU) {
        _mode = GAME;
        _sfx.pauseMusic("menu");
        _sfx.playMusic("game");
        _sfx.getMusic("game")->setLoop(true);
    }
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
    ((gui::IGUIScrollBar *)_menu[1])->setPos(_sfx.getSoundVolume());
    _menu[2]->setText(std::to_wstring(_sfx.getSoundVolume()).c_str());
    ((gui::IGUIScrollBar *)_menu[3])->setPos(_sfx.getMusicVolume());
    _menu[4]->setText(std::to_wstring(_sfx.getMusicVolume()).c_str());
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

std::string MenuEvent::soundVolume(s32 id)
{
    int volume = ((gui::IGUIScrollBar *)_menu[id])->getPos();
    _sfx.setSoundVolume(volume);
    _menu[id + 1]->setText(std::to_wstring(volume).c_str());
    return "";
}

std::string MenuEvent::musicVolume(s32 id)
{
    int volume = ((gui::IGUIScrollBar *)_menu[id])->getPos();
    _sfx.setMusicVolume(volume);
    _menu[id + 1]->setText(std::to_wstring(volume).c_str());
    return "";
}

std::string MenuEvent::saveOptions(s32 id)
{
    _sfx.playSound("button");
    _sfx.updateConfig();
    _menu.changeMenu(_menu.getLastMenu());
    return "";
}

std::string MenuEvent::returnFromOptions(s32 id)
{
    _sfx.resetVolume();
    _sfx.playSound("button");
    _menu.changeMenu(_menu.getLastMenu());
    return "";
}