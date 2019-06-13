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
#include "Client/Client.hpp"
#include "Client/Entity.hpp"
#include "Client/Clock.hpp"
#include "Game/Character.hpp"

using namespace irr;

namespace client
{
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
            bool KeyIsDown[KEY_KEY_CODES_COUNT];
    };

    class EngineGraphic
    {
        public:
            EngineGraphic();
            ~EngineGraphic();

            int runGraph();
            void dataMove(std::string);
            EKEY_CODE input();
            void matchQuery();

            void setRoot(const boost::property_tree::ptree);

            void move_other();
            void local_player();
            void new_player();
            void new_power_up();
            void new_bomb();
            void explosion();
            void death();
            void bomb();
            void destroy();

            std::shared_ptr<std::map<std::string, std::function<void()>>> getFunctionMap() noexcept;

            Character createCharacter();
            void addEntity(Character *);

            scene::ICameraSceneNode *addCamera();
            void moveEntity(std::string sens, std::string id);

            void updateEntity(std::vector<Character>::iterator &, const core::vector3df, const core::vector3df);
            void create_map(std::string map);
            void sendEscape();
            void sendSpace();
            scene::IMeshSceneNode *createMapBlock(const io::path &, const core::vector3df);

            void setKey(std::string);
        private:
            MyEventReceiver _receiver;
            IrrlichtDevice *_device;
            video::IVideoDriver *_driver;
            scene::ISceneManager *_smgr;
            gui::IGUIEnvironment *_guienv;
            video::E_DRIVER_TYPE _driverType;
            std::vector<Character> _charList;
            std::vector<scene::ISceneNode*> _map;
            Clock _clock;
            boost::property_tree::ptree _root;
            std::map<std::string, std::function<void()>> _fMap;
            std::vector<scene::IAnimatedMeshSceneNode *> _nodeBomb;

            std::map<int, const irr::io::path> _skins = {
                {0, "client/res/nskinrd.jpg"},
                {1, "client/res/nskinbl.jpg"},
                {2, "client/res/nskingr.jpg"},
                {3, "client/res/nskinpu.jpg"}
            };
    };
}; // namespace client
