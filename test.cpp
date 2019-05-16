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
    IVideoDriver* driver;
    ISceneManager* smgr;
    IGUIEnvironment* guienv;

    if (!device) {
        printf("Fail device\n");
        exit(84);
    }
    driver = device->getVideoDriver();
    smgr = device->getSceneManager();
    guienv = device->getGUIEnvironment();

    device->setWindowCaption(L"Hello World! - Irrlicht Engine Demo");
    guienv->addStaticText(L"Hello World! This is the Irrlicht Software renderer!", rect<s32>(10,10,260,22), true);
    IAnimatedMesh* mesh = smgr->getMesh("ninja.b3d");
    if (!mesh) {
        device->drop();
        exit(84);
    }
    IAnimatedMeshSceneNode* node = smgr->addAnimatedMeshSceneNode(mesh);
    if (node) {
        node->setMaterialFlag(EMF_LIGHTING, false);
        node->setMD2Animation(scene::EMAT_STAND);
        node->setMaterialTexture(0, driver->getTexture("nskinrd.jpg"));
    }
    smgr->addCameraSceneNode(0, vector3df(0,30,-50), vector3df(0,5,0));
    while (device->run()) {
        driver->beginScene(true, true, SColor(255,100,101,140));
        smgr->drawAll();
        guienv->drawAll();
        driver->endScene();
    }
    device->drop();
    return (0);
}