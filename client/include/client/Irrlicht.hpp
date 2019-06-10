/*
** EPITECH PROJECT, 2019
** Irrlicht.hpp
** File description:
** lib graph for bomberman
*/

#pragma once

#include <list>
#include <unordered_map>
#include <vector>
#include <fstream>
#include "irrlicht/irrlicht.h"
#include "irrlicht/driverChoice.h"
#include "client/client.hpp"
#include "client/entity.hpp"
#include "client/clock.hpp"
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

        void updateEntity(std::vector<Character>::iterator &, const core::vector3df, const core::vector3df);
        void create_map(std::string map);
        void sendEscape();
        scene::IMeshSceneNode *createMapBlock(const io::path &, const core::vector3df);

    private:
        MyEventReceiver _receiver;
        IrrlichtDevice *_device;
        video::IVideoDriver *_driver;
        scene::ISceneManager *_smgr;
        gui::IGUIEnvironment *_guienv;
        video::E_DRIVER_TYPE _driverType;
        std::string _data;
        std::vector<Character> _charList;
        std::list<scene::ISceneNode*> _map;
        Clock _clock;

        std::unordered_map<int, const irr::io::path> _skins = {
            {0, "client/res/nskinrd.jpg"},
            {1, "client/res/nskinbl.jpg"},
            {2, "client/res/nskingr.jpg"},
            {3, "client/res/nskinpu.jpg"}
        };
};
