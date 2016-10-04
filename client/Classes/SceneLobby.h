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

#ifndef __BrrClient__SceneLobby__
#define __BrrClient__SceneLobby__

#include "cocos2d.h"
#include "ui/UIListView.h"
#include "ProtoMessageDelegate.h"
#include "MessageRequestRoomList.pb.h"
#include "DialogBase.h"

class SceneLobby : public cocos2d::Layer, public DialogDelegate, public ProtoMessageDelegate {
    int _lastSelectedBetItem = -1;
    int _lastSelectedRoomItem = -1;
public:
    bool init() override;
    void processProtoMessage(const eProtoMessageType messageType, const std::string &messageBody) override;
    CREATE_FUNC(SceneLobby);
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) override;
    void onDialogButtonTap(Ref* sender, int buttonIndex, std::map<std::string, std::string> userData) override;
private:
    enum SceneTags {
        _miBackTag = 100,
        _menuBetTag,
        _miBetTinyTag,
        _miBetSmallTag,
        _miBetMediumTag,
        _miBetBigTag,
        _listViewTag
    };
    DialogTypes _currentDialog;
    void onMenuCallback(cocos2d::Ref* ref);
    void onListViewSelectedItemEvent(cocos2d::Ref *sender, cocos2d::ui::ListView::EventType type);
    void onRoomItemTap(cocos2d::Ref *sender);
    void setEnableControls(bool value);
    void showDialog(DialogTypes dialogType);
    void hideDialog();
    // api calls
    void getRoomListWithBetType(MessageRequestRoomList_eBetType betType);
    // api callbacks
    void callbackRoomListWithBetType(const std::string &source);
};

#endif /* defined(__BrrClient__SceneLobby__) */
