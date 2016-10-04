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

#ifndef __BrrClient__DialogUseItem__
#define __BrrClient__DialogUseItem__

#include "cocos2d.h"
#include "DialogBase.h"
#include "extensions/cocos-ext.h"
#include "ui/UIListView.h"
#include "ProtoMessageDelegate.h"
#include "MessageResponseShopItem.pb.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace ui;

class DialogUseItem : public DialogBase, public ProtoMessageDelegate {
    int _lastSelectedItemType = -1;
public:
    bool init() override;
    void processProtoMessage(const eProtoMessageType messageType, const std::string &messageBody) override;
    CREATE_FUNC(DialogUseItem);
private:
    enum SceneTags {
        itemTypeAllTag = 100,
        itemTypeMeTag,
        itemTypeEnemyTag,
        menuItemTypeTag,
        listViewItemsTag
    };
    std::vector<MessageResponseShopItem> _items;
    std::map<std::string, std::string> _itemsForUsage;
    void onMenuCallback(Ref* sender);
    void setItemTypeButtonSelection(int itemType);
    void getShopItems();
    void onListViewSelectedItemEvent(Ref *sender, ListView::EventType type);
    void showItemsByType();
    void callbackGetShopItems(const std::string &source);
};

#endif /* defined(__BrrClient__DialogUseItem__) */
