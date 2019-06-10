/*
** EPITECH PROJECT, 2019
** irrlicht
** File description:
** Irrlicht
*/

#include "client/Graphic.hpp"

EngineGraphic::EngineGraphic():
    _receiver(),
    _device(irr::createDevice(video::EDT_SOFTWARE,
    core::dimension2d<u32>(640, 480), 16, false, false, false, &_receiver)),
    _driver(_device->getVideoDriver()),
    _smgr(_device->getSceneManager()),
    _guienv(_device->getGUIEnvironment()),
    _driverType (video::EDT_OPENGL),
    _clock()
{
    // _client.start_receive();
}

EngineGraphic::~EngineGraphic()
{
    _device->drop();
}

int EngineGraphic::runGraph()
{
    _clock.setElapsedTime();
    _clock.setElapsed();
    if (_device->run() == 0)
        return (84);
    if (_clock.getElapsed() >= _clock.getSecond()) {
        input();
        _clock.getClock().stop();
        _clock.getClock().start();
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
    root.put("type", "movement");
    root.put("sens", move);
    std::ostringstream buff;
    boost::property_tree::write_json(buff, root, false);
    _data = buff.str();
}

void EngineGraphic::sendEscape()
{
    boost::property_tree::ptree root;
    root.put("type", "pause");
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
    else if (_receiver.IsKeyDown(irr::KEY_KEY_P))
        sendEscape();
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

    if (type.compare("move_other") == 0)
        moveEntity(root.get<std::string>("sens"), root.get<std::string>("id"));
    else if (type.compare("local_player") == 0) {
        std::size_t id = root.get<std::size_t>("id");
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
    else if (type.compare("new_player") == 0) {
        std::size_t id = root.get<std::size_t>("id");
        Character player;
        float x = root.get<float>("x");
        float y = root.get<float>("y");
        float z = root.get<float>("z");
        int skin = root.get<int>("skin");

        player.setId(id);
        player.setPosition(core::vector3df(x, y, z));
        player.setSkin(skin);
        addEntity(&player);
        _charList.push_back(player);
    }
}

void EngineGraphic::addEntity(Character *player)
{
    scene::IAnimatedMesh* mesh = _smgr->getMesh("client/ninja.b3d");
    scene::IAnimatedMeshSceneNode *node = _smgr->addAnimatedMeshSceneNode(mesh);

    node->setMaterialTexture(0, _driver->getTexture(_skins[player->getSkin()]));
    node->setRotation(core::vector3df(0, 80, 0));
    node->setPosition(player->getPosition());
    node->setFrameLoop(0, 0);
    node->setScale(core::vector3df(2, 2, 2));
    node->setMaterialFlag(video::EMF_LIGHTING, false);
    player->setNode(node);
}

scene::ICameraSceneNode *EngineGraphic::addCamera()
{
    return (_smgr->addCameraSceneNode(0, core::vector3df(22,71,-30), core::vector3df(22.5,35,10)));
}

void EngineGraphic::moveEntity(std::string sens, std::string id)
{
    scene::IAnimatedMeshSceneNode *tmp;
    auto it = _charList.begin();
    core::vector3df posi;

    for (; it != _charList.end(); it++)
        if (it->getId() == std::stol(id))
            break;
    posi = it->getNode()->getPosition();
    if (sens.compare("up") == 0) {
        posi.Z += 2;
        updateEntity(it, posi, core::vector3df(0, 0, 0));
    } else if (sens.compare("down") == 0) {
        posi.Z -= 2;
        updateEntity(it, posi, core::vector3df(0, 160, 0));
    } else if (sens.compare("left") == 0) {
        posi.X -= 2;
        updateEntity(it, posi, core::vector3df(0, -80, 0));
    } else if (sens.compare("right") == 0) {
        posi.X += 2;
        updateEntity(it, posi, core::vector3df(0, 80, 0));
    }
}

void EngineGraphic::updateEntity(std::vector<Character>::iterator &it,
const core::vector3df pos, const core::vector3df rotation)
{
    it->getNode()->setPosition(pos);
    it->getNode()->setRotation(rotation);
    if (it->getNode()->getEndFrame() != 13) {
        it->getNode()->setFrameLoop(0, 13);
        it->getNode()->setAnimationSpeed(15);
    }
}

void EngineGraphic::create_map(std::string map)
{
    int posi_x = 0;
    int posi_z = 0;

    for (auto &it : map) {
        switch (it) {
            case '0': {
                _map.push_back(createMapBlock("client/brick.png",
                    core::vector3df(posi_x, 0, posi_z))
                );
                posi_z += 10;
                break;
            }
            case '1': {
                _map.push_back(createMapBlock("client/brick.png",
                    core::vector3df(posi_x, 0, posi_z))
                );
                _map.push_back(createMapBlock("client/brick.png",
                    core::vector3df(posi_x, 10, posi_z))
                );
                posi_z += 10;
                break;
            }
            case '\n':
                posi_x += 10;
                posi_z = 0;
                break;
            case EOF:
                return;
            default:
                exit(84);
                break;
        }
    }
}

scene::IMeshSceneNode *EngineGraphic::createMapBlock(const io::path &filename, const core::vector3df pos)
{
    scene::IMeshSceneNode *tmp = _smgr->addCubeSceneNode();

    tmp->setMaterialTexture(0, _driver->getTexture(filename));
    tmp->setMaterialFlag(video::EMF_LIGHTING, false);
    tmp->setPosition(pos);
    return tmp;
}
