#pragma once

#include <unordered_map>
#include "CustomMenu.hpp"

using elem_f = std::string (MenuEvent::*)(u32);

class MenuEvent : public IEventReceiver
{
public:
    MenuEvent(CustomMenu &menu);
    ~MenuEvent() = default;
    std::string startSolo(u32 id);
    std::string menuMulti(u32 id);
    std::string startMulti(u32 id);
    std::string menuOptions(u32 id);
    std::string soundVolume(u32 id);
    std::string musicVolume(u32 id);
private:
    std::unordered_map<std::string, elem_f> _functions;
    CustomMenu _menu;
};