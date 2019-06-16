#pragma once

#include <unordered_map>
#include "Client/LogicPause.hpp"
#include "Client/CustomMenu.hpp"
#include "SFX/SFX.hpp"

class MenuEvent
{
    public:
        typedef std::string (MenuEvent::*elem_f)(s32);
        MenuEvent(gui::IGUIEnvironment *env, video::IVideoDriver *driver, MODE &mode);
        ~MenuEvent() = default;
        std::string launchFunction(s32 id);
        void startPause();
        std::string endPause(s32 id);
        // std::string menuMulti(S32 id);
    private:
        sfx::SFX _sfx;
        std::string saveOptions(s32 id);
        std::string soundVolume(s32 id);
        std::string musicVolume(s32 id);
        std::string startSolo(s32 id);
        std::string host(s32 id);
        std::string menuMulti(s32 id);
        std::string menuOptions(s32 id);
        std::string quit(s32 id);
        std::string menuHelp(s32 id);
        std::string returnMain(s32 id);
        std::string returnLastMenu(s32 id);
        std::string joinServer(s32 id);
        std::string returnFromOptions(s32 id);
        std::unordered_map<std::string, elem_f> _functions;
        CustomMenu _menu;
        MODE &_mode;
        bool _isHost;
};