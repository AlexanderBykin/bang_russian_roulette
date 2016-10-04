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

#ifndef MYGAME_SCENEMANAGER_H
#define MYGAME_SCENEMANAGER_H

#include "cocos2d.h"

USING_NS_CC;

enum class BrrScenes {
    SceneIntro, SceneMain, SceneLobby, SceneShop, SceneRoom, SceneProfile, SceneTutorial, SceneAbout
};

class SceneManager : public Ref {
public:
    static SceneManager* getInstance();
    static void goNext(BrrScenes scene);
    static void goBack(BrrScenes scene);
    static void goWithNode(Node *node, bool isBackward);
    static Node *wrap(BrrScenes scene);
    ~SceneManager();
private:
    void eraseMemory(float value);
};


#endif //MYGAME_SCENEMANAGER_H
