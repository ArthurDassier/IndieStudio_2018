#include "Client/MenuEvent.hpp"

MenuEvent::MenuEvent(CustomMenu &menu): _menu(menu)
{}

bool MenuEvent::OnEvent(const SEvent &event)
{
    if (event.EventType == EET_GUI_EVENT) {
        s32 id = event.GUIEvent.Caller->getID();
        return true;
    }
    return false;
}