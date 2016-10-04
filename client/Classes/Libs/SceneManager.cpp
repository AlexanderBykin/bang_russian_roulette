/*
 Bang Russian Roulette (client) - This is real online and multiplayer game published at Google Play.
 Copyright (C) 2016  Alexander Shniperson
 Email: alex.shniperson@gmail.com
 
 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "SceneManager.h"
#include "SceneIntro.h"
#include "SceneMain.h"
#include "SceneLobby.h"
#include "SceneShop.h"
#include "SceneRoom.h"
#include "SceneProfile.h"
#include "SceneAbout.h"
#include "ProtoMessageDelegate.h"

static SceneManager* _instance = nullptr;

SceneManager* SceneManager::getInstance() {
    if(_instance == nullptr) {
        _instance = new (std::nothrow) SceneManager();
    }
    return _instance;
}

SceneManager::~SceneManager() {
    if(_instance != nullptr) {
        delete _instance;
    }
}

void SceneManager::goNext(BrrScenes scene) {
    goWithNode(wrap(scene), false);
}

void SceneManager::goBack(BrrScenes scene) {
    goWithNode(wrap(scene), true);
}

void SceneManager::goWithNode(Node *node, bool isBackward) {
    SceneManager::getInstance();
    auto director = Director::getInstance();
    auto newScene = Scene::create();
    newScene->addChild(node, ProtoMessageDelegate::ProtoMessageSceneID, ProtoMessageDelegate::ProtoMessageSceneID);

    if (director->getRunningScene() != nullptr) {
        if (isBackward) {
            director->replaceScene(TransitionSlideInL::create(1.0, newScene));
            director->getScheduler()->schedule(static_cast<cocos2d::SEL_SCHEDULE>(&SceneManager::eraseMemory), _instance, 2.0, 0, 0, false);
        } else {
            director->replaceScene(TransitionSlideInR::create(1.0, newScene));
            director->getScheduler()->schedule(static_cast<cocos2d::SEL_SCHEDULE>(&SceneManager::eraseMemory), _instance, 2.0, 0, 0, false);
        }
    }
    else {
        director->runWithScene(newScene);
    }
}

Node* SceneManager::wrap(BrrScenes scene) {
    switch (scene) {
        case BrrScenes::SceneIntro:
            return SceneIntro::create();

        case BrrScenes::SceneMain:
            return SceneMain::create();

        case BrrScenes::SceneLobby:
            return SceneLobby::create();
        
        case BrrScenes::SceneShop:
            return SceneShop::create();

        case BrrScenes::SceneProfile:
            return SceneProfile::create();
        
        case BrrScenes::SceneAbout:
            return SceneAbout::create();
        
        default:
            return SceneMain::create();
    }
}

void SceneManager::eraseMemory(float value) {
    SpriteFrameCache::getInstance()->removeUnusedSpriteFrames();
    Director::getInstance()->getTextureCache()->removeUnusedTextures();
    Director::getInstance()->purgeCachedData();
}
