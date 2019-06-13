#pragma once

#include <unordered_map>
#include "Client/LogicPause.hpp"
#include "Client/CustomMenu.hpp"

class MenuEvent
{
    public:
        typedef std::string (MenuEvent::*elem_f)(s32);
        MenuEvent(gui::IGUIEnvironment *env, video::IVideoDriver *driver, MODE &mode);
        ~MenuEvent() = default;
        std::string launchFunction(s32 id);
        std::string startSolo(s32 id);
        std::string host(s32 id);
        std::string startMulti(s32 id);
        std::string menuOptions(s32 id);
        std::string quit(s32 id);
        std::string menuHelp(s32 id);
        std::string returnMain(s32 id);
        // std::string menuMulti(S32 id);
        // std::string soundVolume(S32 id);
        // std::string musicVolume(S32 id);
    private:
        std::unordered_map<std::string, elem_f> _functions;
        CustomMenu _menu;
        MODE &_mode;
        bool _isHost;
};