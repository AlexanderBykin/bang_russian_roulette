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

#include "DialogUseItem.h"
#include "LanguageManager.h"
#include "GlobalProperties.h"
#include "SocketThread.h"
#include "MessageRequestShopItemList.pb.h"
#include "MessageResponseShopItemList.pb.h"
#include "ShopItem.h"
#include "PluginGoogleAnalytics/PluginGoogleAnalytics.h"
#include "audio/include/AudioEngine.h"
#include "Button9TextShadow.h"

bool DialogUseItem::init() {
    if(!DialogBase::init()) {
        return false;
    }
    
    sdkbox::PluginGoogleAnalytics::logScreen("DialogUseItem");
    
    this->setCaption(LanguageManager::getString("DialogUseItemsCaption"));

    int btnWidth = _dialogRect.size.width/3-2*18;
    int btnHeight = 120;
    auto listViewType = ListView::create();
    listViewType->setDirection(ui::ScrollView::Direction::HORIZONTAL);
    listViewType->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
    listViewType->setPosition(Vec2(_dialogRect.origin.x + 40, _dialogRect.origin.y + _dialogRect.size.height - 80));
    listViewType->setContentSize(Size(_dialogRect.size.width, btnHeight*1.5));
    listViewType->setScrollBarEnabled(false);
    listViewType->setGravity(cocos2d::ui::ListView::Gravity::CENTER_HORIZONTAL);
    //listViewType->setBackGroundColorType(cocos2d::ui::Layout::BackGroundColorType::SOLID);
    //listViewType->setBackGroundColor(Color3B::GREEN);
    listViewType->setItemsMargin(18);
    this->addChild(listViewType, menuItemTypeTag, menuItemTypeTag);
    
    
    auto btnItemTypeAll = Button9TextShadow::create("Dialog/btnDialogBaseBackNext.png",
                                                Size(btnWidth, btnHeight),
                                                LanguageManager::getString("DialogUseItemsAllButton"),
                                                GameFont,
                                                50,
                                                Color3B(51, 51, 51),
                                                Color3B(204, 204, 204),
                                                CC_CALLBACK_1(DialogUseItem::onMenuCallback, this));
    btnItemTypeAll->setTag(itemTypeAllTag);
    btnItemTypeAll->setSelectedResources("SceneLobby/btnSceneLobbyBetBGSelected.png", Color3B(56, 37, 27), Color3B(255, 237, 105));
    btnItemTypeAll->setPressedActionEnabled(false);
    btnItemTypeAll->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    listViewType->pushBackCustomItem(btnItemTypeAll);
    
    
    auto btnItemMe = Button9TextShadow::create("Dialog/btnDialogBaseBackNext.png",
                                                 Size(btnWidth, btnHeight),
                                                 LanguageManager::getString("DialogUseItemsMeButton"),
                                                 GameFont,
                                                 50,
                                                 Color3B(51, 51, 51),
                                                 Color3B(204, 204, 204),
                                                 CC_CALLBACK_1(DialogUseItem::onMenuCallback, this));
    btnItemMe->setTag(itemTypeMeTag);
    btnItemMe->setSelectedResources("SceneLobby/btnSceneLobbyBetBGSelected.png", Color3B(56, 37, 27), Color3B(255, 237, 105));
    btnItemMe->setPressedActionEnabled(false);
    btnItemMe->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    listViewType->pushBackCustomItem(btnItemMe);
    
    auto btnItemEnemy = Button9TextShadow::create("Dialog/btnDialogBaseBackNext.png",
                                                  Size(btnWidth, btnHeight),
                                                  LanguageManager::getString("DialogUseItemsEnemyButton"),
                                                  GameFont,
                                                  50,
                                                  Color3B(51, 51, 51),
                                                  Color3B(204, 204, 204),
                                                  CC_CALLBACK_1(DialogUseItem::onMenuCallback, this));
    btnItemEnemy->setTag(itemTypeEnemyTag);
    btnItemEnemy->setSelectedResources("SceneLobby/btnSceneLobbyBetBGSelected.png", Color3B(56, 37, 27), Color3B(255, 237, 105));
    btnItemEnemy->setPressedActionEnabled(false);
    btnItemEnemy->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    listViewType->pushBackCustomItem(btnItemEnemy);
    
    
    ListView* listView = ListView::create();
    // set list view ex direction
    listView->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
    listView->setDirection(ui::ScrollView::Direction::HORIZONTAL);
    listView->setBounceEnabled(true);
    listView->setPosition(Vec2(_dialogRect.origin.x, _dialogRect.origin.y + _dialogRect.size.height / 2));
    listView->setContentSize(Size(_dialogRect.size.width, 300));
    listView->setItemsMargin(20);
    //listView->setBackGroundColorType(cocos2d::ui::Layout::BackGroundColorType::SOLID);
    //listView->setBackGroundColor(Color3B::GREEN);
    listView->addEventListener((ListView::ccListViewCallback)CC_CALLBACK_2(DialogUseItem::onListViewSelectedItemEvent, this));
    this->addChild(listView, listViewItemsTag, SceneTags::listViewItemsTag);
    
    
    this->addCancelButton(LanguageManager::getString("DialogUseItemsBackButton"));
    this->addDoneButton(LanguageManager::getString("DialogUseItemsNextButton"), CC_CALLBACK_1(DialogUseItem::onMenuCallback, this));
    
    
    this->setItemTypeButtonSelection(SceneTags::itemTypeAllTag);
    this->getShopItems();
    
    
//    auto item1 = new MessageResponseShopItem();
//    item1->set_amount(10);
//    item1->set_cost(100);
//    item1->set_description("asdasd");
//    item1->set_imagename("ShopItemArmoredBullet.png");
//    item1->set_name("brr_armored_bullet");
//    item1->set_usagetype(MessageResponseShopItem_eUsageType_utPlayer);
//    _items.push_back(item1);
//    
//    auto item2 = new MessageResponseShopItem();
//    item2->set_amount(10);
//    item2->set_cost(100);
//    item2->set_description("asdasd");
//    item2->set_imagename("ShopItemBrokenBullet.png");
//    item2->set_name("brr_broken_bullet");
//    item2->set_usagetype(MessageResponseShopItem_eUsageType_utEnemy);
//    _items.push_back(item2);
//    
//    auto item3 = new MessageResponseShopItem();
//    item3->set_amount(10);
//    item3->set_cost(100);
//    item3->set_description("asdasd");
//    item3->set_imagename("ShopItemHelmet.png");
//    item3->set_name("brr_helmet");
//    item3->set_usagetype(MessageResponseShopItem_eUsageType_utPlayer);
//    _items.push_back(item3);
//    
//    auto item4 = new MessageResponseShopItem();
//    item4->set_amount(10);
//    item4->set_cost(100);
//    item4->set_description("asdasd");
//    item4->set_imagename("ShopItemChangeShootDirection.png");
//    item4->set_name("brr_change_shoot_direction");
//    item4->set_usagetype(MessageResponseShopItem_eUsageType_utBoth);
//    _items.push_back(item4);
//    
//    this->showItemsByType();
    
    
    return true;
}

void DialogUseItem::onMenuCallback(cocos2d::Ref *sender) {
    auto node = dynamic_cast<Node*>(sender);
    experimental::AudioEngine::play2d("Sounds/btnmenu_click.mp3");
    switch (node->getTag()) {
        case DialogBaseButtons::btnDoneTag: {
            if(_delegate) {
                _delegate->onDialogButtonTap(this, DialogBaseButtons::btnDoneTag, _itemsForUsage);
            }
            break;
        }
            
        case SceneTags::itemTypeAllTag:
        case SceneTags::itemTypeMeTag:
        case SceneTags::itemTypeEnemyTag: {
            this->setItemTypeButtonSelection(node->getTag());
            break;
        }
            
        default:
            break;
    }
}

void DialogUseItem::setItemTypeButtonSelection(int itemType) {
    sdkbox::PluginGoogleAnalytics::logEvent("Button", StringUtils::format("setItemTypeButtonSelection_%d", itemType), "", 0);
    
    auto lv = dynamic_cast<ListView*>(this->getChildByTag(SceneTags::menuItemTypeTag));
    Button9TextShadow* lastItem = nullptr;
    Button9TextShadow* curItem = nullptr;
    for (auto node : lv->getItems()) {
        if(node->getTag() == _lastSelectedItemType) lastItem = dynamic_cast<Button9TextShadow*>(node);
        if(node->getTag() == itemType) curItem = dynamic_cast<Button9TextShadow*>(node);
    }
    if(lastItem) {
        lastItem->onPressStateChangedToNormal();
    }
    if(curItem) {
        curItem->onPressStateChangedToPressed();
    }
    _lastSelectedItemType = itemType;
    this->showItemsByType();
}

void DialogUseItem::getShopItems() {
    sdkbox::PluginGoogleAnalytics::logEvent("ApiCall", "getShopItems", "", 0);
    MessageRequestShopItemList msg;
    msg.set_shopitemtype(MessageRequestShopItemList_eShopItemType::MessageRequestShopItemList_eShopItemType_sitINVENTORYWITHSHOP);
    msg.set_lang(GlobalProperties::getCurrentLanguageAsString());
    SocketThread::getInstance()->getSocket()->Send(this->wrapMessage(eProtoMessageType::cmtGetShopItems, msg));
}

void DialogUseItem::onListViewSelectedItemEvent(Ref *sender, ListView::EventType type) {
    if(type == cocos2d::ui::ListView::EventType::ON_SELECTED_ITEM_END){
        auto listView = dynamic_cast<ListView*>(sender);
        auto selectedItem = dynamic_cast<ShopItem*>(listView->getItem(listView->getCurSelectedIndex()));
        sdkbox::PluginGoogleAnalytics::logEvent("SelectedItem", selectedItem->getItemName(), "", 0);
        if(_itemsForUsage.find(selectedItem->getItemName()) == _itemsForUsage.end()) {
            _itemsForUsage.insert(std::pair<std::string, std::string>(selectedItem->getItemName(), "1"));
            selectedItem->setSelection(true);
        } else {
            _itemsForUsage.erase(selectedItem->getItemName());
            selectedItem->setSelection(false);
        }
    }
}

void DialogUseItem::showItemsByType() {
    auto listView = dynamic_cast<ListView*>(this->getChildByTag(SceneTags::listViewItemsTag));
    listView->removeAllItems();
    switch (_lastSelectedItemType) {
        case SceneTags::itemTypeAllTag: {
            sdkbox::PluginGoogleAnalytics::logEvent("Button", "itemTypeAll", "", 0);
            for(auto item : _items) {
                auto shopItem = ShopItem::create("ShopItem/" + item.imagename(), item.name(), item.description(), item.amount(), 0);
                shopItem->setAmountVisible(true);
                listView->pushBackCustomItem(shopItem);
            }
            break;
        }
            
        case SceneTags::itemTypeMeTag: {
            sdkbox::PluginGoogleAnalytics::logEvent("Button", "itemTypeMe", "", 0);
            for(auto item : _items) {
                if(item.usagetype() == MessageResponseShopItem_eUsageType_utPlayer || item.usagetype() == MessageResponseShopItem_eUsageType_utBoth) {
                    auto shopItem = ShopItem::create("ShopItem/" + item.imagename(), item.name(), item.description(), item.amount(), 0);
                    shopItem->setAmountVisible(true);
                    listView->pushBackCustomItem(shopItem);
                }
            }
            break;
        }
            
        case SceneTags::itemTypeEnemyTag: {
            sdkbox::PluginGoogleAnalytics::logEvent("Button", "itemTypeEnemy", "", 0);
            for(auto item : _items) {
                if(item.usagetype() == MessageResponseShopItem_eUsageType_utEnemy || item.usagetype() == MessageResponseShopItem_eUsageType_utBoth) {
                    auto shopItem = ShopItem::create("ShopItem/" + item.imagename(), item.name(), item.description(), item.amount(), 0);
                    shopItem->setAmountVisible(true);
                    listView->pushBackCustomItem(shopItem);
                }
            }
            break;
        }
            
        default:
            break;
    }
}

void DialogUseItem::processProtoMessage(const eProtoMessageType messageType, const std::string &messageBody) {
    switch (messageType) {
        case eProtoMessageType::cmtGetShopItems: {
            this->callbackGetShopItems(messageBody);
            break;
        }
            
        default: {
            break;
        }
    }
}

void DialogUseItem::callbackGetShopItems(const std::string &source) {
    sdkbox::PluginGoogleAnalytics::logEvent("ApiCallback", "callbackGetShopItems", "", 0);

    if (source.size() == 0) {
        return;
    }
    
    MessageResponseShopItemList msg;
    msg.ParseFromString(source);
    
    for(auto item : msg.shopitemlist()) {
        _items.push_back(item);
    }
    
    this->showItemsByType();
}

