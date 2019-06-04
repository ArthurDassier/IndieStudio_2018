/*
** EPITECH PROJECT, 2019
** Irrlicht.hpp
** File description:
** lib graph for bomberman
*/

#pragma once

#include "client.hpp"
#include "entity.hpp"
#include "../../../lib/includes/irrlicht.h"
#include "../../../lib/includes/driverChoice.h"
#include <list>
#include <vector>
#include <fstream>
using namespace irr;

class MyEventReceiver : public IEventReceiver
{
    public:
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

class EngineGraphic
{
    public:
        EngineGraphic();
        ~EngineGraphic();

        int runGraph();
        void dataMove(std::string);
        void input();
        std::string getData() const;
        void clearData();
        void manageRoot(boost::property_tree::ptree);
        void addEntity(Character *);
        scene::ICameraSceneNode *addCamera();
        void moveEntity(std::string sens, std::string id);
        void create_map(std::string map);

        // void create_map(std::ifstream &fd);
        // void settings();
        // void addEntity();
        // void Input();
        // void Move();
        // void Event();
        // void setCamera();
        // IrrlichtDevice *getDevice() const;
        // video::IVideoDriver *getDriver() const;
        // scene::ISceneManager *getSmgr() const;
        // gui::IGUIEnvironment *getGuienv() const;
        // std::list<scene::ISceneNode*> getMap() const;
        // MyEventReceiver getReceiver() const;
        // scene::IAnimatedMeshSceneNode *getNode() const;
        // void setNodePosition(core::vector3df);
        // core::vector3df getNodePosition() const;

    private:
        MyEventReceiver _receiver;
        IrrlichtDevice *_device;
        video::IVideoDriver *_driver;
        scene::ISceneManager *_smgr;
        gui::IGUIEnvironment *_guienv;
        video::E_DRIVER_TYPE _driverType;
        std::string _data;
        std::vector<Character> _charList;
        std::vector<Object> _objList;
        std::list<scene::ISceneNode*> _map;

        // std::list<scene::ISceneNode*> _map;
        // scene::IAnimatedMeshSceneNode *_node;
        // u32 then;
        // std::string _message;
        // std::string _idMove;
        // Client _client;
        // std::string _name;
        // core::vector3df _nodePosition;
        // std::string _id;
};
