/*
** EPITECH PROJECT, 2019
** irrlicht
** File description:
** Irrlicht
*/

#include "Client/Graphic.hpp"

client::EngineGraphic::EngineGraphic():
    _receiver(),
    _device(
        irr::createDevice(
            video::EDT_SOFTWARE,
            core::dimension2d<u32>(640, 480),
            16,
            false,
            false,
            false,
            &_receiver
        )
    ),
    _driver(_device->getVideoDriver()),
    _smgr(_device->getSceneManager()),
    _guienv(_device->getGUIEnvironment()),
    _driverType(video::EDT_OPENGL),
    _clock()
{
    _fMap.emplace(std::make_pair("move_other", std::bind(&EngineGraphic::move_other, this)));
    _fMap.emplace(std::make_pair("local_player", std::bind(&EngineGraphic::local_player, this)));
    _fMap.emplace(std::make_pair("new_player", std::bind(&EngineGraphic::new_player, this)));
    _fMap.emplace(std::make_pair("explosion", std::bind(&EngineGraphic::explosion, this)));
    _fMap.emplace(std::make_pair("death", std::bind(&EngineGraphic::death, this)));
    _fMap.emplace(std::make_pair("bomb", std::bind(&EngineGraphic::bomb, this)));
    _fMap.emplace(std::make_pair("destroy", std::bind(&EngineGraphic::destroy, this)));
    _fMap.emplace(std::make_pair("dropBonus", std::bind(&EngineGraphic::dropBonus, this)));
}

client::EngineGraphic::~EngineGraphic()
{
}

int client::EngineGraphic::runGraph()
{
    _clock.setElapsedTime();
    _clock.setElapsed();
    if (_device->run() == 0)
        return (84);
    _driver->beginScene(true, true, video::SColor(255,100,101,140));
    _smgr->drawAll();
    _guienv->drawAll();
    _driver->endScene();
    return (0);
}

EKEY_CODE client::EngineGraphic::input()
{
    if (_clock.getElapsed() >= _clock.getSecond()) {
        for (unsigned int i = KEY_LBUTTON; i < KEY_KEY_CODES_COUNT; i++)
            if (_receiver.IsKeyDown((EKEY_CODE)i))
                return (EKEY_CODE)i;
        _clock.getClock().stop();
        _clock.getClock().start();
    }
    return KEY_KEY_CODES_COUNT;
}

void client::EngineGraphic::matchQuery()
{
    std::string type = _root.get<std::string>("type");

    _fMap.find(type)->second();
}

void client::EngineGraphic::addEntity(Character *player)
{
    scene::IAnimatedMesh* mesh = _smgr->getMesh("client/res/ninja.b3d");
    scene::IAnimatedMeshSceneNode *node = _smgr->addAnimatedMeshSceneNode(mesh);

    node->setMaterialTexture(0, _driver->getTexture(_skins[player->getSkin()]));
    node->setRotation(core::vector3df(0, 80, 0));
    node->setPosition(player->getPosition());
    node->setFrameLoop(0, 0);
    node->setScale(core::vector3df(2, 2, 2));
    node->setMaterialFlag(video::EMF_LIGHTING, false);
    player->setNode(node);
}

scene::ICameraSceneNode *client::EngineGraphic::addCamera()
{
    return (_smgr->addCameraSceneNode(0, core::vector3df(22,71,-20), core::vector3df(35,25,10)));
}

void client::EngineGraphic::moveEntity(std::string sens, std::string id)
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

void client::EngineGraphic::updateEntity(std::vector<Character>::iterator &it,
const core::vector3df pos, const core::vector3df rotation)
{
    it->getNode()->setPosition(pos);
    it->getNode()->setRotation(rotation);
    if (it->getNode()->getEndFrame() != 13) {
        it->getNode()->setFrameLoop(0, 13);
        it->getNode()->setAnimationSpeed(15);
    }
}

void client::EngineGraphic::create_map(std::string map)
{
    int posi_x = 0;
    int posi_z = 0;

    for (auto &it : map) {
        switch (it) {
            case '0': {
                _map.push_back(createMapBlock("client/res/sand_sol.jpg",
                    core::vector3df(posi_x, 0, posi_z))
                );
                posi_z += 10;
                break;
            }
            case '1': {
                _map.push_back(createMapBlock("client/res/wall_2.jpg",
                    core::vector3df(posi_x, 0, posi_z))
                );
                _map.push_back(createMapBlock("client/res/wall_2.jpg",
                    core::vector3df(posi_x, 10, posi_z))
                );
                posi_z += 10;
                break;
            }
            case '2': {
                _map.push_back(createMapBlock("client/res/sand_sol.jpg",
                    core::vector3df(posi_x, 0, posi_z))
                );
                _map.push_back(createMapBlock("client/res/box.jpg",
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

scene::IMeshSceneNode *client::EngineGraphic::createMapBlock(const io::path &filename, const core::vector3df pos)
{
    scene::IMeshSceneNode *tmp = _smgr->addCubeSceneNode();

    tmp->setMaterialTexture(0, _driver->getTexture(filename));
    tmp->setMaterialFlag(video::EMF_LIGHTING, false);
    tmp->setPosition(pos);
    return tmp;
}

client::Character client::EngineGraphic::createCharacter()
{
    std::size_t id = _root.get<std::size_t>("id");
    float x = _root.get<float>("x");
    float y = _root.get<float>("y");
    float z = _root.get<float>("z");
    int skin = _root.get<int>("skin");
    client::Character player;

    player.setId(id);
    player.setPosition(core::vector3df(x, y, z));
    player.setSkin(skin);
    return player;
}

void client::EngineGraphic::move_other()
{
    moveEntity(_root.get<std::string>("sens"), _root.get<std::string>("id"));
}

void client::EngineGraphic::local_player()
{
    client::Character player = createCharacter();

    addEntity(&player);
    _charList.push_back(player);
    create_map(_root.get<std::string>("diagram"));
}

void client::EngineGraphic::new_player()
{
    client::Character player = createCharacter();

    addEntity(&player);
    _charList.push_back(player);
}

void client::EngineGraphic::explosion()
{
    float x = _root.get<float>("x");
    float y = _root.get<float>("z");
    _nodeBomb[_root.get<size_t>("id")]->remove();
    _nodeBomb.erase(_nodeBomb.begin());
}

void client::EngineGraphic::dropBonus()
{
    core::vector3df pos(_root.get<float>("x"), 5, _root.get<float>("z"));
    scene::IAnimatedMesh* mesh = _smgr->getMesh("client/res/Bomb.3ds");
    scene::IAnimatedMeshSceneNode *node = _smgr->addAnimatedMeshSceneNode(mesh);

    node->setMaterialTexture(0, _driver->getTexture("client/res/Albedo.png"));
    node->setRotation(core::vector3df(0, 80, 0));
    node->setPosition(pos);
    node->setFrameLoop(0, 0);
    node->setScale(core::vector3df(30, 30, 30));
    node->setMaterialFlag(video::EMF_LIGHTING, false);
    _nodeBomb.push_back(node);
}

void client::EngineGraphic::destroy()
{
    float x = _root.get<float>("x");
    float z = _root.get<float>("z");
    int i = 0;
    for (;i != _map.size(); i++) {
        if (_map[i]->getPosition().X == x && _map[i]->getPosition().Z == z & _map[i]->getPosition().Y == 10) {
            break;
        }
    }
    if (i != _map.size()) {
        _map[i]->remove();
        _map.erase(_map.begin() + i);
    }
}

void client::EngineGraphic::death()
{
    std::size_t id = _root.get<std::size_t>("id");
    float x = _root.get<float>("x");
    float y = _root.get<float>("y");
    float z = _root.get<float>("z");
    core::vector3df pos = {x, y, z};

    std::cout << "position = {" << x << ", " << y << ", " << z << "}" << std::endl;
    for (auto &it : _charList) {
        if (it.getId() != id)
            continue;
        it.getNode()->setPosition(pos);
        if (it.getNode()->getEndFrame() != 13) {
            it.getNode()->setFrameLoop(0, 13);
            it.getNode()->setAnimationSpeed(15);
        }
    }
}

void client::EngineGraphic::bomb()
{
    core::vector3df pos(_root.get<float>("x"), 5, _root.get<float>("z"));
    scene::IAnimatedMesh* mesh = _smgr->getMesh("client/res/Bomb.3ds");
    scene::IAnimatedMeshSceneNode *node = _smgr->addAnimatedMeshSceneNode(mesh);

    node->setMaterialTexture(0, _driver->getTexture("client/res/Albedo.png"));
    node->setRotation(core::vector3df(0, 80, 0));
    node->setPosition(pos);
    node->setFrameLoop(0, 0);
    node->setScale(core::vector3df(30, 30, 30));
    node->setMaterialFlag(video::EMF_LIGHTING, false);
    _nodeBomb.push_back(node);
}

void client::EngineGraphic::setRoot(const boost::property_tree::ptree root)
{
    _root = root;
}

std::shared_ptr<std::map<std::string, std::function<void()>>> client::EngineGraphic::getFunctionMap() noexcept
{
    return std::make_shared<decltype(_fMap)>(_fMap);
}
