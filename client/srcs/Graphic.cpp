/*
** EPITECH PROJECT, 2019
** irrlicht
** File description:
** Irrlicht
*/

#include "Client/Graphic.hpp"

client::EngineGraphic::EngineGraphic():
    _receiverGUI(),
    _receiverGame(),
    _device(
        irr::createDevice(
            video::EDT_OPENGL,
            core::dimension2d<u32>(1920, 1080),
            16,
            false,
            false,
            false,
            &_receiverGUI
        )
    ),
    _driver(_device->getVideoDriver()),
    _smgr(_device->getSceneManager()),
    _guienv(_device->getGUIEnvironment()),
    _driverType(video::EDT_OPENGL),
    _clock(),
    _oldMode(MAINMENU),
    _walk(0)
{
    _device->setResizable(true);
    _device->setWindowCaption(L"Bomberman");
    _loader.setSceneManager(_smgr);
    _loader.setVideoDriver(_driver);
    _loader.loadModels();
    _loader.loadTextures();
    _fMap.emplace(std::make_pair("move_other", std::bind(&EngineGraphic::move_other, this)));
    _fMap.emplace(std::make_pair("local_player", std::bind(&EngineGraphic::local_player, this)));
    _fMap.emplace(std::make_pair("new_player", std::bind(&EngineGraphic::new_player, this)));
    _fMap.emplace(std::make_pair("explosion", std::bind(&EngineGraphic::explosion, this)));
    _fMap.emplace(std::make_pair("death", std::bind(&EngineGraphic::death, this)));
    _fMap.emplace(std::make_pair("bomb", std::bind(&EngineGraphic::bomb, this)));
    _fMap.emplace(std::make_pair("destroy", std::bind(&EngineGraphic::destroy, this)));
    _fMap.emplace(std::make_pair("dropBonus", std::bind(&EngineGraphic::dropBonus, this)));
    _fMap.emplace(std::make_pair("removeBonus", std::bind(&EngineGraphic::removeBonus, this)));
}

client::EngineGraphic::~EngineGraphic()
{
}

int client::EngineGraphic::runGraph(const MODE &mode)
{
    if (mode != _oldMode) {
        if (mode == GAME) {
            _device->setEventReceiver(&_receiverGame);
        } else {
            _device->setEventReceiver(&_receiverGUI);
        }
        _oldMode = mode;
    }
    _clock.setElapsedTime();
    _clock.setElapsed();
    if (_device->run() == 0)
        return (84);
    _driver->beginScene(true, true, video::SColor(255,100,101,140));
    if (mode != MAINMENU)
        _smgr->drawAll();
    if (mode != GAME){
        _guienv->drawAll();
    }
    _driver->endScene();
    refreshFire();
    return (0);
}

EKEY_CODE client::EngineGraphic::input()
{
    if (_clock.getElapsed() >= _clock.getSecond()) {
        for (unsigned int i = KEY_LBUTTON; i < KEY_KEY_CODES_COUNT; i++)
            if (_receiverGame.IsKeyDown((EKEY_CODE)i))
                return (EKEY_CODE)i;
        _clock.getClock().stop();
        _clock.getClock().start();
    }
    return KEY_KEY_CODES_COUNT;
}

void client::EngineGraphic::matchQuery()
{
    try {
        std::string type = _root.get<std::string>("type");

        auto it =_fMap.find(type);
        if (it != _fMap.end())
            it->second();
    }
    catch (const std::exception &e)
    {
        throw(error::ClientError(e.what()));
    }
}

void client::EngineGraphic::addEntity(Character *player)
{
    scene::IAnimatedMesh *mesh = _loader.getModel("ninja");
    scene::IAnimatedMeshSceneNode *node = _smgr->addAnimatedMeshSceneNode(mesh);

    node->setMaterialTexture(0, _loader.getTexture(_skins[player->getSkin()]));
    node->setRotation(core::vector3df(0, 80, 0));
    node->setPosition(player->getPosition());
    node->setFrameLoop(0, 0);
    node->setScale(core::vector3df(2, 2, 2));
    node->setMaterialFlag(video::EMF_LIGHTING, false);
    player->setNode(node);
}

scene::ICameraSceneNode *client::EngineGraphic::addCamera()
{
    irr::core::array<irr::scene::ISceneNode *>	nodes;
    _smgr->loadScene("map.irr");
    _smgr->getSceneNodesFromType(irr::scene::ESNT_CUBE, nodes);
    return (_smgr->addCameraSceneNode(0, core::vector3df(43.8935,63.3423,-18.6599), core::vector3df(43.7971,4.3018,34.2673)));
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
}

void client::EngineGraphic::create_map(std::string map)
{
    int posi_x = 0;
    int posi_z = 0;

    for (auto &it : map) {
        switch (it) {
            case '0': {
                _map.push_back(createMapBlock("sand",
                    core::vector3df(posi_x, 0, posi_z))
                );
                posi_z += 10;
                break;
            }
            case '1': {
                _map.push_back(createMapBlock("wall",
                    core::vector3df(posi_x, 0, posi_z))
                );
                _map.push_back(createMapBlock("wall",
                    core::vector3df(posi_x, 10, posi_z))
                );
                posi_z += 10;
                break;
            }
            case '2': {
                _map.push_back(createMapBlock("sand",
                    core::vector3df(posi_x, 0, posi_z))
                );
                _map.push_back(createMapBlock("box",
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

scene::IMeshSceneNode *client::EngineGraphic::createMapBlock(const std::string texture, const core::vector3df pos)
{
    scene::IMeshSceneNode *tmp = _smgr->addCubeSceneNode();

    tmp->setMaterialTexture(0, _loader.getTexture(texture));
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
    std::cout << "Hey ça recoit" << std::endl;
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

scene::IParticleSystemSceneNode *client::EngineGraphic::fire(float x, float z)
{
    scene::IParticleSystemSceneNode *ps = _smgr->addParticleSystemSceneNode(false);
    scene::IParticleEmitter *em = ps->createBoxEmitter(
        core::aabbox3d<f32>(-10, 0, -10, 10, 1, 10),
        core::vector3df(0.0f, 0.02f, 0.0f),
        20, 50,
        video::SColor(0, 255, 255, 255),
        video::SColor(0, 255, 255, 255),
        300, 550, 0,
        core::dimension2df(3.f, 3.f),
        core::dimension2df(5.f, 5.f));

    ps->setEmitter(em);
    em->drop();
    scene::IParticleAffector *paf = ps->createFadeOutParticleAffector();

    ps->addAffector(paf);
    paf->drop();
    ps->setPosition(core::vector3df(x, 12, z));
    ps->setScale(core::vector3df(0.3, 0.3, 0.3));
    ps->setMaterialFlag(video::EMF_LIGHTING, false);
    ps->setMaterialFlag(video::EMF_ZWRITE_ENABLE, false);
    ps->setMaterialTexture(0,  _loader.getTexture("fire"));
    ps->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);
    return ps;
}

void client::EngineGraphic::explosion()
{
    try {
        float x = _root.get<float>("x");
        float y = _root.get<float>("z");
        size_t id = _root.get<size_t>("id");
        _nodeBomb.at(id)->remove();
        _nodeBomb.erase(_nodeBomb.begin() + id);
    } catch (const std::exception &e) {
        throw(error::ClientError(e.what()));
    }
}

void client::EngineGraphic::dropBonus()
{
    scene::IAnimatedMeshSceneNode *node;
    float x = _root.get<float>("x");
    float z = _root.get<float>("z");
    std::string bonusType = _root.get<std::string>("bonusType");
    core::vector3df pos(x, 5, z);

    if (bonusType.compare("SpeedUp") == 0) {
        node = _smgr->addAnimatedMeshSceneNode(_loader.getModel("SpeedUp"));
        node->setMaterialTexture(0, _loader.getTexture(_skins[4]));
        node->setScale(core::vector3df(2, 2, 2));

    }
    if (bonusType.compare("BombUp") == 0) {
        node = _smgr->addAnimatedMeshSceneNode(_loader.getModel("BombUp"));
        node->setScale(core::vector3df(1, 1, 1));

    }
    if (bonusType.compare("FireUp") == 0) {
        node = _smgr->addAnimatedMeshSceneNode(_loader.getModel("FireUp"));
        node->setScale(core::vector3df(0.5, 0.5, 0.5));

    }
    if (bonusType.compare("WallPass") == 0) {
        node = _smgr->addAnimatedMeshSceneNode(_loader.getModel("WallPass"));
        node->setScale(core::vector3df(2, 2, 2));
    }
    node->setRotation(core::vector3df(0, 80, 0));
    node->setPosition(pos);
    node->setFrameLoop(0, 0);
    node->setMaterialFlag(video::EMF_LIGHTING, false);
    _nodeBonus.push_back(node);
}

void client::EngineGraphic::removeBonus()
{
    float x = _root.get<float>("x");
    float z = _root.get<float>("z");
    int i = 0;
    for (; i != _nodeBonus.size(); i++)
        if (_nodeBonus[i]->getPosition().X == x && _nodeBonus[i]->getPosition().Z == z &&  _nodeBonus[i]->getPosition().Y == 5)
            break;
    if (i == _nodeBonus.size())
        return;
    _nodeBonus[i]->remove();
    _nodeBonus.erase(_nodeBonus.begin() + i);
}

void client::EngineGraphic::refreshFire()
{
    boost::timer::nanosecond_type five(1000000000LL);

    for (int i = 0; i != _listFire.size(); i++) {
        _listFire[i].second.setElapsedTime();
        _listFire[i].second.setElapsed();
        if (_listFire[i].second.getElapsed() > five) {
            for (int j = 0; j != _listFire[i].first.size(); j++) {
                _listFire[i].first[j]->clearParticles();
                _listFire[i].first[j]->remove();
            }
            _listFire.erase(_listFire.begin() + i);
            i--;
        }
    }
}

void client::EngineGraphic::destroy()
{
    std::vector<scene::IParticleSystemSceneNode *> flames;
    std::vector<std::vector<int>> getPos;
    int i = 0;

    try {
        for (pt::ptree::value_type &row : _root.get_child("blocks")) {
            std::vector<int> tmp;
            for (pt::ptree::value_type &cell : row.second)
                tmp.push_back(cell.second.get_value<int>());
            getPos.push_back(tmp);
        }
    } catch (const std::exception &e) {
        throw(error::ClientError("DESTROY"));
    }
    for (auto &it : getPos) {
        flames.push_back(fire(it.at(0), it.at(1)));
        for (; i != _map.size(); i++) {
            if (_map.at(i)->getPosition().X == it.at(0)
            &&_map.at(i)->getPosition().Z == it.at(1)
            &&_map.at(i)->getPosition().Y == 10)
                break;
        }
        if (i != _map.size()) {
            _map.at(i)->remove();
            _map.erase(_map.begin() + i);
        }
        i = 0;
    }
    _listFire.push_back(std::pair<std::vector<scene::IParticleSystemSceneNode *>, Clock>(flames, Clock()));
}

void client::EngineGraphic::death()
{
    exit(0);
    // std::size_t id = _root.get<std::size_t>("id");
    // float x = _root.get<float>("x");
    // float y = _root.get<float>("y");
    // float z = _root.get<float>("z");
    // core::vector3df pos = {x, y, z};
    //
    // for (auto &it : _charList) {
    //     if (it.getId() != id)
    //         continue;
    //     it.getNode()->setPosition(pos);
    //     if (it.getNode()->getEndFrame() != 13) {
    //         it.getNode()->setFrameLoop(0, 13);
    //         it.getNode()->setAnimationSpeed(15);
    //     }
    // }
}

void client::EngineGraphic::bomb()
{
    try {
        core::vector3df pos(_root.get<float>("x"), 5, _root.get<float>("z"));
        scene::IAnimatedMeshSceneNode *node = _smgr->addAnimatedMeshSceneNode(_loader.getModel("bomb"));

        node->setRotation(core::vector3df(0, 80, 0));
        node->setPosition(pos);
        node->setFrameLoop(0, 0);
        node->setScale(core::vector3df(30, 30, 30));
        node->setMaterialFlag(video::EMF_LIGHTING, false);
        _nodeBomb.push_back(node);
    } catch(const std::exception &e) {
        throw(error::ClientError("BOMB"));
    }
}

void client::EngineGraphic::setRoot(const boost::property_tree::ptree root)
{
    _root = root;
}

std::shared_ptr<std::map<std::string, std::function<void()>>> client::EngineGraphic::getFunctionMap() noexcept
{
    return std::make_shared<decltype(_fMap)>(_fMap);
}

video::IVideoDriver *client::EngineGraphic::getDriver() const
{
    return _driver;
}

gui::IGUIEnvironment *client::EngineGraphic::getGUIEnvironment() const
{
    return _guienv;
}

s32 client::EngineGraphic::getGuiID()
{
    return _receiverGUI.getID();
}
