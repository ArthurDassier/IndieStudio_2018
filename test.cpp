/*
** EPITECH PROJECT, 2019
** test.cpp
** File description:
** test.cpp
*/

#include "lib/includes/irrlicht.h"
#include "lib/includes/driverChoice.h"
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

int main(void)
{
    MyEventReceiver receiver;
    IrrlichtDevice *device = irr::createDevice(video::EDT_SOFTWARE, dimension2d<u32>(640, 480), 16, false, false, false, &receiver);
    IVideoDriver* driver;
    ISceneManager* smgr;
    IGUIEnvironment* guienv;
    video::E_DRIVER_TYPE driverType = EDT_OPENGL;

    if (!device) {
        printf("Fail device\n");
        exit(84);
    }
    driver = device->getVideoDriver();
    smgr = device->getSceneManager();
    guienv = device->getGUIEnvironment();

    IAnimatedMesh* mesh = smgr->getMesh("faerie.md2");
    if (!mesh) {
        device->drop();
        exit(84);
    }
    IAnimatedMeshSceneNode* node = smgr->addAnimatedMeshSceneNode(mesh);
    if (node) {
        node->setMaterialFlag(EMF_LIGHTING, false);
        node->setMD2Animation(scene::EMAT_STAND);
        node->setMaterialTexture(0, driver->getTexture("Faerie5.BMP"));
    }
    smgr->addCameraSceneNode(0, vector3df(50,0,-20), vector3df(0,0,0));

    u32 then = device->getTimer()->getTime();
    const f32 MOVEMENT_SPEED = 5.f;


    while (device->run()) {
        const u32 now = device->getTimer()->getTime();
		const f32 frameDeltaTime = (f32)(now - then) / 1000.f;
		then = now;
        core::vector3df nodePosition = node->getPosition();
        if (receiver.IsKeyDown(irr::KEY_KEY_Z)) {
            nodePosition.X+= MOVEMENT_SPEED * frameDeltaTime;
        }
        if (receiver.IsKeyDown(irr::KEY_KEY_S))
            nodePosition.X-= MOVEMENT_SPEED * frameDeltaTime;
        if (receiver.IsKeyDown(irr::KEY_KEY_Q))
            nodePosition.Y+= MOVEMENT_SPEED * frameDeltaTime;
        if (receiver.IsKeyDown(irr::KEY_KEY_D))
            nodePosition.Y-= MOVEMENT_SPEED * frameDeltaTime;
        node->setPosition(nodePosition);
        driver->beginScene(true, true, SColor(255,100,101,140));
        smgr->drawAll();
        guienv->drawAll();
        driver->endScene();
    }
    device->drop();

    // video::E_DRIVER_TYPE driverType = EDT_OPENGL;
    // if (driverType == video::EDT_COUNT)
    //     return 84;

    // MyEventReceiver receiver;
    // IrrlichtDevice* device = createDevice(driverType,
    //                 core::dimension2d<u32>(640, 480), 16, false, false, false, &receiver);
    // if (device == 0)
    //     return 84;
    // video::IVideoDriver* driver = device->getVideoDriver();
    // scene::ISceneManager* smgr = device->getSceneManager();
    // IAnimatedMesh* mesh = smgr->getMesh("faerie.md2");
    // if (!mesh) {
    //     device->drop();
    //     exit(84);
    // }
    // IAnimatedMeshSceneNode* node = smgr->addAnimatedMeshSceneNode(mesh);
    // if (node) {
    //     node->setMaterialFlag(EMF_LIGHTING, false);
    //     node->setMD2Animation(scene::EMAT_STAND);
    //     node->setMaterialTexture(0, driver->getTexture("Faerie5.BMP"));
    // }
    // if (node) {
    //     scene::ISceneNodeAnimator* anim =
    //         smgr->createFlyStraightAnimator(core::vector3df(30,-100,0),
    //         core::vector3df(0,70,0), 3500, true);
    //     if (anim) {
    //         node->addAnimator(anim);
    //         anim->drop();
    //     }
    // }
    // smgr->addCameraSceneNode(0, vector3df(50,0,-20), vector3df(0,0,0));
    // while (device->run()) {
    //     driver->beginScene(true, true, SColor(255,100,101,140));
    //     smgr->drawAll();
    //     driver->endScene();
    // }
    // device->drop();
    // return (0);
}