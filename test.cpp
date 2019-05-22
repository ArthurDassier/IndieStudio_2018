/*
** EPITECH PROJECT, 2019
** test.cpp
** File description:
** test.cpp
*/

#include "lib/includes/irrlicht.h"
#include "lib/includes/driverChoice.h"
#include <list>
#include <fstream>
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class MyEventReceiver : public IEventReceiver
{
public:
	// This is the one method that we have to implement
	virtual bool OnEvent(const SEvent& event)
	{
		// Remember whether each key is down or up
		if (event.EventType == irr::EET_KEY_INPUT_EVENT)
			KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
		return false;
	}

	// This is used to check whether a key is being held down
	virtual bool IsKeyDown(EKEY_CODE keyCode) const
	{
		return KeyIsDown[keyCode];
	}

	MyEventReceiver()
	{
		for (u32 i=0; i<KEY_KEY_CODES_COUNT; ++i)
			KeyIsDown[i] = false;
	}

private:
	// We use this array to store the current state of each key
	bool KeyIsDown[KEY_KEY_CODES_COUNT];
};


int main(int argc, char **argv)
{
    if (argc != 2) {
        printf("Met une map sinon je me lance pas\n");
        exit(84);
    }
    std::ifstream fd(argv[1], std::ifstream::in);

    MyEventReceiver receiver;
    IrrlichtDevice *device = irr::createDevice(video::EDT_SOFTWARE, dimension2d<u32>(640, 480), 16, false, false, false, &receiver);
    IVideoDriver* driver;
    ISceneManager* smgr;
    IGUIEnvironment* guienv;
    video::E_DRIVER_TYPE driverType = EDT_OPENGL;

    driver = device->getVideoDriver();
    smgr = device->getSceneManager();
    guienv = device->getGUIEnvironment();

    std::list<ISceneNode*> map;
    int posi_x = 0;
    int posi_z = 0;

    // for (int i = 0; i < 11; i++) {
    //     ISceneNode* tmp = smgr->addCubeSceneNode();
    //     tmp->setMaterialTexture(0, driver->getTexture("Carrelage/Carrelage043.jpg"));
    //     tmp->setMaterialFlag(video::EMF_LIGHTING, false);
    //     tmp->setPosition(vector3df(posi_x, 0, 0));
    //     map.push_back(tmp);
    //     for (int a = 0; a < 11; a++) {
    //         ISceneNode* tmp2 = smgr->addCubeSceneNode();
    //         tmp2->setMaterialTexture(0, driver->getTexture("Carrelage/Carrelage043.jpg"));
    //         tmp2->setMaterialFlag(video::EMF_LIGHTING, false);
    //         tmp2->setPosition(vector3df(posi_x, 0, posi_z));
    //         map.push_back(tmp2);
    //         posi_z += 10;
    //     }
    //     posi_z = 0;
    //     posi_x += 10;
    // }

    int stop = 0;

    for (;;) {
        char c = fd.get();
        switch (c) {
            case '0': {
                ISceneNode* tmp = smgr->addCubeSceneNode();
                tmp->setMaterialTexture(0, driver->getTexture("Carrelage/Carrelage043.jpg"));
                tmp->setMaterialFlag(video::EMF_LIGHTING, false);
                tmp->setPosition(vector3df(posi_x, 0, posi_z));
                map.push_back(tmp);
                posi_z += 10;
                break;
            }
            case '1': {
                ISceneNode* tmp1 = smgr->addCubeSceneNode();
                tmp1->setMaterialTexture(0, driver->getTexture("Carrelage/Carrelage043.jpg"));
                tmp1->setMaterialFlag(video::EMF_LIGHTING, false);
                tmp1->setPosition(vector3df(posi_x, 0, posi_z));
                map.push_back(tmp1);
                ISceneNode* tmp2 = smgr->addCubeSceneNode();
                tmp2->setMaterialTexture(0, driver->getTexture("Carrelage/Carrelage040.jpg"));
                tmp2->setMaterialFlag(video::EMF_LIGHTING, false);
                tmp2->setPosition(vector3df(posi_x, 10, posi_z));
                map.push_back(tmp2);
                posi_z += 10;
                break;
            }
            case '\n': {
                posi_x += 10;
                posi_z = 0;
                break;
            }
            case EOF: {
                stop = 1;
                break;
            }
            default:
                break;
        }
        if (stop == 1)
            break;
    }

    smgr->addCameraSceneNodeFPS();
    device->getCursorControl()->setVisible(false);

    u32 then = device->getTimer()->getTime();
    const f32 MOVEMENT_SPEED = 30.f;

    while (device->run()) {
        driver->beginScene(true, true, SColor(255,100,101,140));
        smgr->drawAll();
        guienv->drawAll();
        driver->endScene();
    }
    device->drop();

    // MyEventReceiver receiver;
    // IrrlichtDevice *device = irr::createDevice(video::EDT_SOFTWARE, dimension2d<u32>(640, 480), 16, false, false, false, &receiver);
    // IVideoDriver* driver;
    // ISceneManager* smgr;
    // IGUIEnvironment* guienv;
    // video::E_DRIVER_TYPE driverType = EDT_OPENGL;

    // if (!device) {
    //     printf("Fail device\n");
    //     exit(84);
    // }
    // driver = device->getVideoDriver();
    // smgr = device->getSceneManager();
    // guienv = device->getGUIEnvironment();

    // IAnimatedMesh* mesh = smgr->getMesh("faerie.md2");
    // if (!mesh) {
    //     device->drop();
    //     exit(84);
    // }
    // IAnimatedMeshSceneNode* node = smgr->addAnimatedMeshSceneNode(mesh);
    // if (node) {
    //     // node->setMaterialFlag(EMF_LIGHTING, false);
    //     node->setMD2Animation(scene::EMAT_STAND);
    //     node->setMaterialTexture(0, driver->getTexture("Faerie5.BMP"));
    // }
    // smgr->addCameraSceneNode(0, vector3df(50,0,-20), vector3df(0,0,0));

    // u32 then = device->getTimer()->getTime();
    // const f32 MOVEMENT_SPEED = 30.f;


    // while (device->run()) {
    //     const u32 now = device->getTimer()->getTime();
	// 	const f32 frameDeltaTime = (f32)(now - then) / 1000.f;
	// 	then = now;
    //     core::vector3df nodePosition = node->getPosition();
    //     if (receiver.IsKeyDown(irr::KEY_KEY_Z)) {
    //         nodePosition.X+= MOVEMENT_SPEED * frameDeltaTime;
    //     }
    //     if (receiver.IsKeyDown(irr::KEY_KEY_S))
    //         nodePosition.X-= MOVEMENT_SPEED * frameDeltaTime;
    //     if (receiver.IsKeyDown(irr::KEY_KEY_Q))
    //         nodePosition.Y+= MOVEMENT_SPEED * frameDeltaTime;
    //     if (receiver.IsKeyDown(irr::KEY_KEY_D))
    //         nodePosition.Y-= MOVEMENT_SPEED * frameDeltaTime;
    //     node->setPosition(nodePosition);
    //     driver->beginScene(true, true, SColor(255,100,101,140));
    //     smgr->drawAll();
    //     guienv->drawAll();
    //     driver->endScene();
    // }
    // device->drop();



}
