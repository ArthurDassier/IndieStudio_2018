#pragma once

#include "CustomMenu.hpp"

using elem_f = (*void)(int, std::string);

class MenuEvent : public IEventReceiver
{
public:
    MenuEvent(CustomMenu &menu);
    ~MenuEvent() = default;
    virtual bool OnEvent(const SEvent &event);
private:
    CustomMenu &_menu;
};