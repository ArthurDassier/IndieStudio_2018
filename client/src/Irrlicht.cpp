/*
** EPITECH PROJECT, 2019
** irrlicht
** File description:
** Irrlicht
*/

#include "boost/timer/timer.hpp"
#include "../include/client/Irrlicht.hpp"

EngineGraphic::EngineGraphic():
    _receiver(),
    _device(irr::createDevice(video::EDT_SOFTWARE,
    core::dimension2d<u32>(640, 480), 16, false, false, false, &_receiver)),
    _driver(_device->getVideoDriver()),
    _smgr(_device->getSceneManager()),
    _guienv(_device->getGUIEnvironment()),
    _driverType (video::EDT_OPENGL)
{
    // _client.start_receive();
}

EngineGraphic::~EngineGraphic()
{
    _device->drop();
}

int EngineGraphic::runGraph()
{
    static boost::timer::cpu_timer clock;
    static auto start = clock.elapsed();
    static boost::timer::nanosecond_type second(70000000LL);
    boost::timer::cpu_times elapsed_times(clock.elapsed());
    boost::timer::nanosecond_type elapsed(elapsed_times.system + elapsed_times.user);

    if (_device->run() == 0)
        return (84);
    if (elapsed >= second) {
        input();
        clock.stop();
        clock.start();
    }
    _driver->beginScene(true, true, video::SColor(255,100,101,140));
    _smgr->drawAll();
    _guienv->drawAll();
    _driver->endScene();
    return (0);
}

void EngineGraphic::dataMove(std::string move)
{
    boost::property_tree::ptree root;
    root.put("type", "move");
    root.put("sens", move);
    std::ostringstream buff;
    boost::property_tree::write_json(buff, root, false);
    _data = buff.str();

}

void EngineGraphic::input()
{
    if (_receiver.IsKeyDown(irr::KEY_KEY_Z))
        dataMove("up");
    else if (_receiver.IsKeyDown(irr::KEY_KEY_S))
        dataMove("down");
    else if (_receiver.IsKeyDown(irr::KEY_KEY_Q))
        dataMove("left");
    else if (_receiver.IsKeyDown(irr::KEY_KEY_D))
        dataMove("right");
}

std::string EngineGraphic::getData() const
{
    return (_data);
}

void EngineGraphic::clearData()
{
    _data.clear();
}

void EngineGraphic::manageRoot(boost::property_tree::ptree root)
{
    std::string type = root.get<std::string>("type");

    if (type.compare("moveother") == 0)
        moveEntity(root.get<std::string>("sens"), root.get<std::string>("id"));
    if (type.compare("you") == 0) {
        std::string id = root.get<std::string>("id");
        float x = root.get<float>("x");
        float y = root.get<float>("y");
        float z = root.get<float>("z");
        int skin = root.get<int>("skin");
        Character player;

        player.setId(id);
        player.setPosition(core::vector3df(x, y, z));
        player.setSkin(skin);
        addEntity(&player);
        _charList.push_back(player);
        create_map(root.get<std::string>("diagram"));
    }
    if (type.compare("newplayer") == 0) {
        std::string id = root.get<std::string>("id");
        Character player;
        float x = root.get<float>("x");
        float y = root.get<float>("y");
        float z = root.get<float>("z");
        int skin = root.get<int>("skin");


        player.setId(id);
        player.setPosition(core::vector3df(x, y, z));
        player.setSkin(1);
        addEntity(&player);
        _charList.push_back(player);
    }
}

void EngineGraphic::addEntity(Character *player)
{
    scene::IAnimatedMesh* mesh;// = _smgr->getMesh("client/ninja.b3d");
    scene::IAnimatedMeshSceneNode *node;// = _smgr->addAnimatedMeshSceneNode(mesh);

    switch (player->getSkin()) {
        case 0:
            mesh = _smgr->getMesh("client/ninja.b3d");
            break;
        case 1:
            mesh = _smgr->getMesh("client/ninja.b3d");
            break;
        case 2:
            mesh = _smgr->getMesh("client/ninja.b3d");
            break;
        case 3:
            mesh = _smgr->getMesh("client/ninja.b3d");
            break;
        default:
            mesh = _smgr->getMesh("client/ninja.b3d");
            break;
    }
    node = _smgr->addAnimatedMeshSceneNode(mesh);
    node->setMaterialTexture(0, _driver->getTexture("client/nskinrd.jpg"));
    node->setRotation(core::vector3df(0, 80, 0));
    node->setPosition(player->getPosition());
    node->setFrameLoop(0, 0);
    node->setScale(core::vector3df(2, 2, 2));
    node->setMaterialFlag(video::EMF_LIGHTING, false);
    player->setNode(node);
}

scene::ICameraSceneNode *EngineGraphic::addCamera()
{
    return ( _smgr->addCameraSceneNode(0, core::vector3df(22,71,-30), core::vector3df(22.5,35,10)));
    
    // _device->getCursorControl()->setVisible(false);
}

void EngineGraphic::moveEntity(std::string sens, std::string id)
{
    scene::IAnimatedMeshSceneNode *tmp;
    auto it = _charList.begin();
    core::vector3df posi;

    for (; it != _charList.end(); it++)
        if (it->getId().compare(id) == 0)
            break;
    posi = it->getNode()->getPosition();
    if (sens.compare("up") == 0) {
        posi.Z += 2;
        std::cout << posi.Z << std::endl;
        it->getNode()->setPosition(posi);
        it->getNode()->setRotation(core::vector3df(0, 0, 0));
        if (it->getNode()->getEndFrame() != 13) {
            it->getNode()->setFrameLoop(0, 13); //move ninja
            it->getNode()->setAnimationSpeed(15);
        }
    }
    if (sens.compare("down") == 0) {
        posi.Z -= 2;
        it->getNode()->setPosition(posi);
        it->getNode()->setRotation(core::vector3df(0, 160, 0));
        if (it->getNode()->getEndFrame() != 13) {
            it->getNode()->setFrameLoop(0, 13); //move ninja
            it->getNode()->setAnimationSpeed(15);
        }
    }
    if (sens.compare("left") == 0) {
        posi.X -= 2;
        it->getNode()->setPosition(posi);
        it->getNode()->setRotation(core::vector3df(0, -80, 0));
        if (it->getNode()->getEndFrame() != 13) {
            it->getNode()->setFrameLoop(0, 13); //move ninja
            it->getNode()->setAnimationSpeed(15);
        }
    }
    if (sens.compare("right") == 0) {
        posi.X += 2;
        it->getNode()->setPosition(posi);
        it->getNode()->setRotation(core::vector3df(0, 80, 0));
        if (it->getNode()->getEndFrame() != 13) {
            it->getNode()->setFrameLoop(0, 13); //move ninja
            it->getNode()->setAnimationSpeed(15);
        }
    }
}

void EngineGraphic::create_map(std::string map)
{
    int posi_x = 0;
    int posi_z = 0;
    int stop = 0;
    auto it = map.begin();

    for (; it != map.end(); it++) {
        switch (*it) {
            case '0': {
                scene::IMeshSceneNode* tmp = _smgr->addCubeSceneNode();
                tmp->setMaterialTexture(0, _driver->getTexture("client/brick.png"));
                tmp->setMaterialFlag(video::EMF_LIGHTING, false);
                tmp->setPosition(core::vector3df(posi_x, 0, posi_z));
                _map.push_back(tmp);
                posi_z += 10;
                break;
            }
            case '1': {
                scene::IMeshSceneNode* tmp1 = _smgr->addCubeSceneNode();
                tmp1->setMaterialTexture(0, _driver->getTexture("client/brick.png"));
                tmp1->setMaterialFlag(video::EMF_LIGHTING, false);
                tmp1->setPosition(core::vector3df(posi_x, 0, posi_z));
                _map.push_back(tmp1);
                scene::IMeshSceneNode* tmp2 = _smgr->addCubeSceneNode();
                tmp2->setMaterialTexture(0, _driver->getTexture("client/brick.png"));
                tmp2->setMaterialFlag(video::EMF_LIGHTING, false);
                tmp2->setPosition(core::vector3df(posi_x, 10, posi_z));
                _map.push_back(tmp2);
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
            default: exit(84);
                break;
        }
        if (stop == 1)
            break;
    }
}

// void EngineGraphic::addEntity()
// {
//     scene::IAnimatedMesh* mesh = getSmgr()->getMesh("ninja.b3d");
//     _node = getSmgr()->addAnimatedMeshSceneNode(mesh);
//     _node->setMD2Animation(scene::EMAT_STAND);
//     _node->setMaterialTexture(0, getDriver()->getTexture("nskinrd.jpg"));
//     _node->setPosition(core::vector3df(40, 10, 40));
//     _node->setRotation(core::vector3df(0, 80, 0));
//     _node->setFrameLoop(0, 0);
//     _node->setAnimationSpeed(15);
//     _node->setScale(core::vector3df(2, 2, 2));
//     _node->setMaterialFlag(video::EMF_LIGHTING, false);
// }

// void EngineGraphic::Input()
// {
//     static boost::timer::cpu_timer clock;
//     static auto start = clock.elapsed();
//     static boost::timer::nanosecond_type second(50000000LL);
//     bool is_send = false;
//     boost::property_tree::ptree root;
//     static std::string data;

//     // const u32 now = getDevice()->getTimer()->getTime();
//     // const f32 frameDeltaTime = (f32)(now - then) / 1000.f;
//     // then = now;
//     // core::vector3df nodePosition = _node->getPosition();
//     // const f32 MOVEMENT_SPEED = 60.f;

//     root.put("type", "move");
//     if (getReceiver().IsKeyDown(irr::KEY_KEY_Z)) {
//         root.put("sens", "up");
//         std::ostringstream buff;
//         boost::property_tree::write_json(buff, root, false);
//         data = buff.str();
//         is_send = true;
//         // nodePosition.Z+= 1;
//         // // node->setRotation(vector3df(0, -80, 0)); //faeries
//         // _node->setRotation(core::vector3df(0, 0, 0));
//         if (_node->getEndFrame() != 13) {
//             _node->setFrameLoop(0, 13); //move ninja
//             _node->setAnimationSpeed(15);
//         }
//     }
//     else if (getReceiver().IsKeyDown(irr::KEY_KEY_S)) {
//         root.put("sens", "down");
//         std::ostringstream buff;
//         boost::property_tree::write_json(buff, root, false);
//         data = buff.str();
//         is_send = true;
//         // // node->setRotation(vector3df(0, 80, 0)); //faeries
//         // _node->setRotation(core::vector3df(0, 160, 0));
//         if (_node->getEndFrame() != 13) {
//             _node->setFrameLoop(0, 13); //move ninja
//             _node->setAnimationSpeed(15);
//         }
//     }
//     else if (getReceiver().IsKeyDown(irr::KEY_KEY_Q)) {
//         root.put("sens", "left");
//         std::ostringstream buff;
//         boost::property_tree::write_json(buff, root, false);
//         data = buff.str();
//         is_send = true;
//         // // node->setRotation(vector3df(0, 80, 0)); //faeries
//         // _node->setRotation(core::vector3df(0, 160, 0));
//         if (_node->getEndFrame() != 13) {
//             _node->setFrameLoop(0, 13); //move ninja
//             _node->setAnimationSpeed(15);
//         }
//     }
//     else if (getReceiver().IsKeyDown(irr::KEY_KEY_D)) {
//         root.put("sens", "right");
//         std::ostringstream buff;
//         boost::property_tree::write_json(buff, root, false);
//         data = buff.str();
//         is_send = true;
//         // // node->setRotation(vector3df(0, 0, 0)); //faeries
//         // _node->setRotation(core::vector3df(0, 80, 0));
//         if (_node->getEndFrame() != 13) {
//             _node->setFrameLoop(0, 13); //move ninja
//             _node->setAnimationSpeed(15);
//         }
//     }

//     boost::timer::cpu_times elapsed_times(clock.elapsed());
//     boost::timer::nanosecond_type elapsed(elapsed_times.system + elapsed_times.user);
//     if (elapsed >= second && is_send) {
//         _client.sendToServer(data);
//         clock.stop();
//         clock.start();
//     }
//     // } else {
//     //     _node->setFrameLoop(_node->getFrameNr(), _node->getFrameNr());
//     // }
// }

// void EngineGraphic::Move()
// {
//     if (_client.getMessage().empty() == true) {
//         _node->setFrameLoop(_node->getFrameNr(), _node->getFrameNr());
//         return;
//     }
//     if (_id.compare(_client.getIdMove()) != 0)
//         return;
//     if (_client.getMessage().compare("up") == 0) {
//         _nodePosition.Z+= 2;
//         _node->setRotation(core::vector3df(0, 0, 0));
//         if (_node->getEndFrame() != 13) {
//             _node->setFrameLoop(0, 13); //move ninja
//             _node->setAnimationSpeed(15);
//         }
//         _client.clearMessage();
//     }
//     else if (_client.getMessage().compare("down") == 0) {
//         _nodePosition.Z-= 2;
//         _node->setRotation(core::vector3df(0, 160, 0));
//         if (_node->getEndFrame() != 13) {
//             _node->setFrameLoop(0, 13); //move ninja
//             _node->setAnimationSpeed(15);
//         }
//         _client.clearMessage();
//     }
//     else if (_client.getMessage().compare("left") == 0) {
//         _nodePosition.X-= 2;
//         _node->setRotation(core::vector3df(0, -80, 0));
//         if (_node->getEndFrame() != 13) {
//             _node->setFrameLoop(0, 13); //move ninja
//             _node->setAnimationSpeed(15);
//         }
//         _client.clearMessage();
//     }
//     else if (_client.getMessage().compare("right") == 0) {
//         _nodePosition.X+= 2;
//         _node->setRotation(core::vector3df(0, 80, 0));
//         if (_node->getEndFrame() != 13) {
//             _node->setFrameLoop(0, 13); //move ninja
//             _node->setAnimationSpeed(15);
//         }
//         _client.clearMessage();
//     }
//     else {
//         _node->setFrameLoop(_node->getFrameNr(), _node->getFrameNr());
//         _client.getMessage().clear();
//     }
//     _node->setPosition(_nodePosition);
// }

// void EngineGraphic::Event()
// {
//     static int lock = 0;

//     if (lock != 0)
//         return;
//     if (_client.getId().empty() == true)
//         return;
//     lock++;
//     _id = _client.getId();
//     std::cout << "Event " << _id << std::endl;
// }

// void EngineGraphic::setCamera()
// {
//     scene::ICameraSceneNode* camera = getSmgr()->addCameraSceneNodeFPS();
//     getDevice()->getCursorControl()->setVisible(false);
// }

// void EngineGraphic::create_map(std::ifstream &fd)
// {
//     int posi_x = 0;
//     int posi_z = 0;
//     int stop = 0;

//     for (;;) {
//         char c = fd.get();
//         _message.push_back(c);
//         switch (c) {
//             case '0': {
//                 scene::IMeshSceneNode* tmp = _smgr->addCubeSceneNode();
//                 tmp->setMaterialTexture(0, _driver->getTexture("brick.png"));
//                 tmp->setMaterialFlag(video::EMF_LIGHTING, false);
//                 tmp->setPosition(core::vector3df(posi_x, 0, posi_z));
//                 _map.push_back(tmp);
//                 posi_z += 10;
//                 break;
//             }
//             case '1': {
//                 scene::IMeshSceneNode* tmp1 = _smgr->addCubeSceneNode();
//                 tmp1->setMaterialTexture(0, _driver->getTexture("brick.png"));
//                 tmp1->setMaterialFlag(video::EMF_LIGHTING, false);
//                 tmp1->setPosition(core::vector3df(posi_x, 0, posi_z));
//                 _map.push_back(tmp1);
//                 scene::IMeshSceneNode* tmp2 = _smgr->addCubeSceneNode();
//                 tmp2->setMaterialTexture(0, _driver->getTexture("brick.png"));
//                 tmp2->setMaterialFlag(video::EMF_LIGHTING, false);
//                 tmp2->setPosition(core::vector3df(posi_x, 10, posi_z));
//                 _map.push_back(tmp2);
//                 posi_z += 10;
//                 break;
//             }
//             case '\n': {
//                 posi_x += 10;
//                 posi_z = 0;
//                 break;
//             }
//             case EOF: {
//                 stop = 1;
//                 break;
//             }
//             default: exit(84);
//                 break;
//         }
//         if (stop == 1)
//             break;
//     }
//     _message.pop_back();
// }

// IrrlichtDevice *EngineGraphic::getDevice() const
// {
//     return (_device);
// }

// video::IVideoDriver *EngineGraphic::getDriver() const
// {
//     return (_driver);
// }

// scene::ISceneManager *EngineGraphic::getSmgr() const
// {
//     return (_smgr);
// }

// gui::IGUIEnvironment *EngineGraphic::getGuienv() const
// {
//     return (_guienv);
// }

// std::list<scene::ISceneNode*> EngineGraphic::getMap() const
// {
//     return (_map);
// }

// MyEventReceiver EngineGraphic::getReceiver() const
// {
//     return (_receiver);
// }

// scene::IAnimatedMeshSceneNode *EngineGraphic::getNode() const
// {
//     return (_node);
// }

// void EngineGraphic::setNodePosition(core::vector3df posi)
// {
//     _nodePosition = posi;
// }

// core::vector3df EngineGraphic::getNodePosition() const
// {
//     return (_nodePosition);
// }
