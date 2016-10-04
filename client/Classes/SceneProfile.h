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

#ifndef __BrrClient__SceneProfile__
#define __BrrClient__SceneProfile__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "ProtoMessageDelegate.h"
#include "DialogBase.h"

class SceneProfile: public cocos2d::Layer, public ProtoMessageDelegate, public DialogDelegate {
public:
    bool init() override;
    void onMenuCallback(cocos2d::Ref* ref);
    const std::string getSelectedLanguage();
    void onSwitchChanged(cocos2d::Ref* sender, cocos2d::extension::Control::EventType controlEvent);
    CREATE_FUNC(SceneProfile);
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) override;
    void processProtoMessage(const eProtoMessageType messageType, const std::string &messageBody) override;
private:
    enum SceneTags {
        miBackTag = 100,
        miLoginTag,
        miLanguageTag,
        menuLanguageTag,
        btnMusicTag,
        btnEffectsTag,
        listViewTag,
        lblPlayerNameTag,
        lblPlayerMoneyTag,
        lblPlayerWinsTag,
        lblPlayerLosesTag,
        lblPlayerRatingTag
    };
    DialogTypes _currentDialog;
    void showDialog(DialogTypes dialogType);
    void showMessageDialog(const std::string &caption, const std::string &message);
    void hideDialog();
    void onDialogButtonTap(Ref* sender, int buttonIndex, std::map<std::string, std::string> userData) override;
    void setEnableControls(bool value);
    void updateLoginButtonStatus();
    // api calls
    void getPlayerProfile();
    void verifyEmail(const std::string &email, const std::string &verifyCode);
    void authPlayer();
    void registerPlayer(const std::string &login, const std::string &password, const std::string &name);
    void forgotPassword(const std::string &email);
    void getShopItems();
    // api callbacks
    void callbackNeedAuth(const std::string &source);
    void callbackAuth(const std::string &source);
    void callbackGetPlayerProfile(const std::string &source);
    void callbackGetShopItems(const std::string &source);
};

#endif 
