/*
** EPITECH PROJECT, 2019
** test.cpp
** File description:
** test.cpp
*/

#include "lib/includes/irrlicht.h"
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;


int main(void)
{
    IrrlichtDevice *device = irr::createDevice(video::EDT_SOFTWARE, dimension2d<u32>(640, 480), 16, false, false, false, 0);

    device->setWindowCaption(L"Hello World! - Irrlicht Engine Demo");
}