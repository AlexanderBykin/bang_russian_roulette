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

#ifndef __BrrClient__SceneMain__
#define __BrrClient__SceneMain__

#include "cocos2d.h"
#include "DialogBase.h"
#include "ProtoMessageDelegate.h"

class SceneMain:public cocos2d::Layer, public DialogDelegate, public ProtoMessageDelegate {
public:
    bool init() override;
    void onMenuCallback(cocos2d::Ref* sender);
    void onDialogButtonTap(Ref* sender, int buttonIndex, std::map<std::string, std::string> userData) override;
    CREATE_FUNC(SceneMain);
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) override;
    void processProtoMessage(const eProtoMessageType messageType, const std::string &messageBody) override;
private:
    enum SceneTags {
        miLogoTag = 100,
        miPlayTag,
        miShopTag,
        miProfileTag,
        miTutorialTag,
        miAboutTag,
        menuMainTag
    };
    DialogTypes _currentDialog;
    void delayInit(float value);
    void showDialog(DialogTypes dialogType);
    void hideDialog();
    void setEnableControls(bool value);
    bool checkConnection();
    void showTutorial();
    // api call
    void checkApiVersion();
    void authPlayer();
    // api callback
    void callbackCheckApiVersion(const std::string &source);
    void callbackAuth(const std::string &source);
};

#endif 