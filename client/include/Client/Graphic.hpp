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
#include "Client/Clock.hpp"
#include "Client/Entity.hpp"
#include "Client/GraphicLoader.hpp"
#include "Client/LogicPause.hpp"
#include "Game/Character.hpp"

using namespace irr;

namespace client
{
    class ReceiverGame : public IEventReceiver
    {
        public:
            virtual bool OnEvent(const SEvent &event) {
                for (u32 i=0; i<KEY_KEY_CODES_COUNT; ++i)
                    KeyIsDown[i] = false;
                if (event.EventType == irr::EET_KEY_INPUT_EVENT) {
                        KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
                        return true;
                    }
                return false;
            }

            virtual bool IsKeyDown(EKEY_CODE keyCode) const
            {
                return KeyIsDown[keyCode];
            }

            ReceiverGame()
            {
                for (u32 i=0; i<KEY_KEY_CODES_COUNT; ++i)
                    KeyIsDown[i] = false;
            }
        private:
            bool KeyIsDown[KEY_KEY_CODES_COUNT];
    };

    class ReceiverGUI : public IEventReceiver
    {
        public:
            virtual bool OnEvent(const SEvent& event)
            {
                if (event.EventType == EET_GUI_EVENT) {
                    if (event.GUIEvent.EventType == gui::EGET_BUTTON_CLICKED || event.GUIEvent.EventType == gui::EGET_SCROLL_BAR_CHANGED) {
                        _guiID = event.GUIEvent.Caller->getID();
                        return true;
                    }
                }
                _guiID = -1;
                return false;
            }

            s32 getID()
            {
                s32 tmp = _guiID;
                _guiID = -1;
                return tmp;
            }

            ReceiverGUI():
                _guiID(-1)
            {
            }

        private:
            s32 _guiID;
    };

    class EngineGraphic
    {
        public:
            EngineGraphic();
            ~EngineGraphic();

            int runGraph(const MODE &mode);
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
            void dropBonus();
            void removeBonus();

            scene::IParticleSystemSceneNode *fire(float, float);
            std::shared_ptr<std::map<std::string, std::function<void()>>> getFunctionMap() noexcept;

            Character createCharacter();
            void addEntity(Character *);

            scene::ICameraSceneNode *addCamera();
            void moveEntity(std::string sens, std::string id);

            void updateEntity(std::vector<Character>::iterator &, const core::vector3df, const core::vector3df);
            void create_map(std::string map);
            void sendEscape();
            void sendSpace();
            void refreshFire();
            scene::IMeshSceneNode *createMapBlock(const std::string, const core::vector3df);

            void setKey(std::string);

            video::IVideoDriver *getDriver() const;
            gui::IGUIEnvironment *getGUIEnvironment() const;
            s32 getGuiID();

        private:
            ReceiverGUI _receiverGUI;
            ReceiverGame _receiverGame;
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
            std::vector<std::pair<std::vector<scene::IParticleSystemSceneNode *>, Clock>> _listFire;

            std::vector<scene::IAnimatedMeshSceneNode *> _nodeBonus;
            GraphicLoader _loader;
            utils::ConfigManager _config;
            std::map<int, const std::string> _skins = {
                {0, "nskinrd"},
                {1, "nskinbl"},
                {2, "nskingr"},
                {3, "nskinpu"}};

            std::map<int, const scene::IAnimatedMesh *> _models;
            MODE _oldMode;
            float _walk;
    };
}; // namespace client
