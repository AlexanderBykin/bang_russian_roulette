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

#include "SceneLobby.h"
#include "SceneManager.h"
#include "LabelShadow.h"
#include "LanguageManager.h"
#include "extensions/cocos-ext.h"
#include "RoomItem.h"
#include "MessageResponseRoomInfo.pb.h"
#include "ProtoMessageType.pb.h"
#include "MessageResponseRoomList.pb.h"
#include "MessageResponseRoomInfo.pb.h"
#include "SocketThread.h"
#include "SceneRoom.h"
#include "GlobalProperties.h"
#include "PluginGoogleAnalytics/PluginGoogleAnalytics.h"
#include "audio/include/AudioEngine.h"
#include "Button9TextShadow.h"

USING_NS_CC;
using namespace ui;

bool SceneLobby::init() {
    if(!Layer::init()) {
        return false;
    }
    
    sdkbox::PluginGoogleAnalytics::logScreen("SceneLobby");
    
    auto winSize = Director::getInstance()->getVisibleSize();
    
    auto bg = Sprite::create("SceneLobby/SceneLobbyBG.png");
    bg->setPosition(Vec2(winSize.width/2, winSize.height/2));
    this->addChild(bg, 0);
    
    auto sceneCaption = LabelShadow::create(LanguageManager::getString("LobbyCaption"),
                                            GameFont,
                                            90,
                                            Color3B::WHITE,
                                            Color3B(51, 51, 51));
    sceneCaption->setAnchorPoint(Vec2::ANCHOR_MIDDLE_TOP);
    sceneCaption->setPosition(Vec2(winSize.width/2, winSize.height-10));
    sceneCaption->setShadowOffset(6);
    this->addChild(sceneCaption, 1);
    

    auto btnBack = Button9TextShadow::create("SceneLobby/btnSceneLobbyBack.png", CC_CALLBACK_1(SceneLobby::onMenuCallback, this));
    btnBack->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
    btnBack->setTag(_miBackTag);
    btnBack->setPosition(Vec2(10, winSize.height-15));
    this->addChild(btnBack, _miBackTag, _miBackTag);
   
    
    int btnWidth = winSize.width/4-4*10;
    int btnHeight = 120;
    auto listViewBet = ListView::create();
    listViewBet->setDirection(ui::ScrollView::Direction::HORIZONTAL);
    listViewBet->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
    listViewBet->setPosition(Vec2(60, winSize.height-230));
    listViewBet->setContentSize(Size(winSize.width-120, btnHeight*1.5));
    listViewBet->setScrollBarEnabled(false);
    listViewBet->setGravity(cocos2d::ui::ListView::Gravity::CENTER_HORIZONTAL);
    //listViewBet->setBackGroundColorType(cocos2d::ui::Layout::BackGroundColorType::SOLID);
    //listViewBet->setBackGroundColor(Color3B::GREEN);
    listViewBet->setItemsMargin(10);
    this->addChild(listViewBet, _menuBetTag, _menuBetTag);
    
    
    auto btnBetTiny = Button9TextShadow::create("Dialog/btnDialogBaseBackNext.png",
                                                Size(btnWidth, btnHeight),
                                                LanguageManager::getString("LobbyBetTypeTinyButton"),
                                                GameFont,
                                                50,
                                                Color3B(51, 51, 51),
                                                Color3B(204, 204, 204),
                                                CC_CALLBACK_1(SceneLobby::onMenuCallback, this));
    btnBetTiny->setTag(_miBetTinyTag);
    btnBetTiny->setSelectedResources("SceneLobby/btnSceneLobbyBetBGSelected.png", Color3B(56, 37, 27), Color3B(255, 237, 105));
    btnBetTiny->setPressedActionEnabled(false);
    btnBetTiny->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    listViewBet->pushBackCustomItem(btnBetTiny);
    
    
    auto btnBetSmall = Button9TextShadow::create("Dialog/btnDialogBaseBackNext.png",
                                                 Size(btnWidth, btnHeight),
                                                 LanguageManager::getString("LobbyBetTypeSmallButton"),
                                                 GameFont,
                                                 50,
                                                 Color3B(51, 51, 51),
                                                 Color3B(204, 204, 204),
                                                 CC_CALLBACK_1(SceneLobby::onMenuCallback, this));
    btnBetSmall->setTag(_miBetSmallTag);
    btnBetSmall->setSelectedResources("SceneLobby/btnSceneLobbyBetBGSelected.png", Color3B(56, 37, 27), Color3B(255, 237, 105));
    btnBetSmall->setPressedActionEnabled(false);
    btnBetSmall->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    listViewBet->pushBackCustomItem(btnBetSmall);
    
    auto btnBetMedium = Button9TextShadow::create("Dialog/btnDialogBaseBackNext.png",
                                                  Size(btnWidth, btnHeight),
                                                  LanguageManager::getString("LobbyBetTypeMediumButton"),
                                                  GameFont,
                                                  50,
                                                  Color3B(51, 51, 51),
                                                  Color3B(204, 204, 204),
                                                  CC_CALLBACK_1(SceneLobby::onMenuCallback, this));
    btnBetMedium->setTag(_miBetMediumTag);
    btnBetMedium->setSelectedResources("SceneLobby/btnSceneLobbyBetBGSelected.png", Color3B(56, 37, 27), Color3B(255, 237, 105));
    btnBetMedium->setPressedActionEnabled(false);
    btnBetMedium->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    listViewBet->pushBackCustomItem(btnBetMedium);
    
    auto btnBetBig = Button9TextShadow::create("Dialog/btnDialogBaseBackNext.png",
                                               Size(btnWidth, btnHeight),
                                               LanguageManager::getString("LobbyBetTypeBigButton"),
                                               GameFont,
                                               50,
                                               Color3B(51, 51, 51),
                                               Color3B(204, 204, 204),
                                               CC_CALLBACK_1(SceneLobby::onMenuCallback, this));
    btnBetBig->setTag(_miBetBigTag);
    btnBetBig->setSelectedResources("SceneLobby/btnSceneLobbyBetBGSelected.png", Color3B(56, 37, 27), Color3B(255, 237, 105));
    btnBetBig->setPressedActionEnabled(false);
    btnBetBig->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    listViewBet->pushBackCustomItem(btnBetBig);
    
    
    ListView* listView = ListView::create();
    // set list view ex direction
    listView->setDirection(ui::ScrollView::Direction::VERTICAL);
    listView->setBounceEnabled(true);
    listView->setPosition(Vec2(60, 60));
    listView->setContentSize(Size(winSize.width-listView->getPosition().x*2, winSize.height-300-listView->getPosition().y*2));
    //    listView->setBackGroundColorType(cocos2d::ui::Layout::BackGroundColorType::SOLID);
    //    listView->setBackGroundColor(Color3B::GREEN);
    listView->addEventListener((ui::ListView::ccListViewCallback)CC_CALLBACK_2(SceneLobby::onListViewSelectedItemEvent, this));
    this->addChild(listView, 1, SceneTags::_listViewTag);
    
    //    for (int i=0; i<20; i++)  {
    //        MessageResponseRoomInfo *itemResponse;
    //        itemResponse->set_roomid(i + 1);
    //        itemResponse->set_shootdirection((i % 2 == 0) ? RoomShootDirection::rsdLEFT : RoomShootDirection::rsdRIGHT);
    //        itemResponse->set_playerbank((i + 1) * 20);
    //        itemResponse->set_investorbank((i + 1) * 20);
    //        itemResponse->set_amountplayers(i + 1);
    //        itemResponse->set_maxplayers(i + 1);
    //        itemResponse->set_currentround(i + 1);
    //        itemResponse->set_maxrounds(i + 1);
    //        itemResponse->set_isgamestarted(false);
    //        auto roomItem = RoomItem::create(itemResponse, winSize.width-listView->getPosition().x*2, 60);
    //        listView->pushBackCustomItem(roomItem);
    //    }
    
    
    auto tableLabel = Label::createWithTTF(LanguageManager::getString("LobbyRoomsLabel"), GameFont, 36);
    tableLabel->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
    tableLabel->setPosition(Vec2(60, winSize.height - 275));
    tableLabel->setColor(Color3B(151, 239, 187));
    this->addChild(tableLabel);
    
    int headerAvgPos = (int) (winSize.width / 5);
    
    auto gridHeader = LayerColor::create(Color4B(0, 0, 0, 125), winSize.width - 120, 60);
    gridHeader->setPosition(Vec2(60, winSize.height - 360));
    this->addChild(gridHeader);
    
    auto separatorLine = LayerColor::create(Color4B(39, 137, 82, 255), winSize.width - 120, 6);
    gridHeader->addChild(separatorLine);
    
    auto numberField = Label::createWithTTF("#", GameFont, 32);
    numberField->setPosition(Vec2(40, gridHeader->getContentSize().height / 2));
    numberField->setColor(Color3B(22, 178, 84));
    gridHeader->addChild(numberField);
    
    auto betField = Label::createWithTTF(LanguageManager::getString("LobbyBetLabel"), GameFont, 32);
    betField->setPosition(Vec2(headerAvgPos - 10, gridHeader->getContentSize().height / 2));
    betField->setColor(Color3B(22, 178, 84));
    gridHeader->addChild(betField);
    
    auto playerField = Label::createWithTTF(LanguageManager::getString("LobbyPlayersLabel"), GameFont, 32);
    playerField->setPosition(Vec2(headerAvgPos * 2 - 10, gridHeader->getContentSize().height / 2));
    playerField->setColor(Color3B(22, 178, 84));
    gridHeader->addChild(playerField);
    
    auto roundField = Label::createWithTTF(LanguageManager::getString("LobbyRoundLabel"), GameFont, 32);
    roundField->setPosition(Vec2(headerAvgPos * 3 - 20, gridHeader->getContentSize().height / 2));
    roundField->setColor(Color3B(22, 178, 84));
    gridHeader->addChild(roundField);
    
    auto bankField = Label::createWithTTF(LanguageManager::getString("LobbyBankLabel"), GameFont, 32);
    bankField->setPosition(Vec2(headerAvgPos * 4 - 50, gridHeader->getContentSize().height / 2));
    bankField->setColor(Color3B(22, 178, 84));
    gridHeader->addChild(bankField);
    
    
    this->onMenuCallback(btnBetTiny);
    
    
    auto listener = EventListenerKeyboard::create();
    listener->onKeyReleased = CC_CALLBACK_2(SceneLobby::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    
    if (GlobalProperties::isDebug()) {
        auto lblTest = Label::createWithTTF("Только для тестирования\n(с) Шниперсон Александр", GameFont, 100);
        lblTest->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
        lblTest->setPosition(winSize.width/2, winSize.height/2);
        lblTest->setRotation(-45);
        lblTest->setOpacity(100);
        this->addChild(lblTest, 9999, 9999);
    }
    
    return true;
}

void SceneLobby::onMenuCallback(cocos2d::Ref *ref) {
    auto item = dynamic_cast<Node*>(ref);
    experimental::AudioEngine::play2d("Sounds/btnmenu_click.mp3");
    switch (item->getTag()) {
        case _miBackTag: {
            sdkbox::PluginGoogleAnalytics::logEvent("Button", "btnBack", "", 0);
            SceneManager::goBack(BrrScenes::SceneMain);
            break;
        }
            
        case _miBetTinyTag:
        case _miBetSmallTag:
        case _miBetMediumTag:
        case _miBetBigTag: {
            auto listViewBet = dynamic_cast<ListView*>(this->getChildByTag(SceneTags::_menuBetTag));
            if(_lastSelectedBetItem >= 0) {
                auto lastSelected = dynamic_cast<Button9TextShadow*>(listViewBet->getItem(_lastSelectedBetItem));
                lastSelected->onPressStateChangedToNormal();
            }
            auto btnBet = dynamic_cast<Button9TextShadow*>(ref);
            btnBet->onPressStateChangedToPressed();
            _lastSelectedBetItem = listViewBet->getIndex(btnBet);
            switch ((SceneTags)btnBet->getTag()) {
                case SceneTags::_miBetTinyTag:
                    sdkbox::PluginGoogleAnalytics::logEvent("Button", "btnBetTiny", "", 0);
                    this->getRoomListWithBetType(MessageRequestRoomList_eBetType::MessageRequestRoomList_eBetType_btTINY);
                    break;
                    
                case SceneTags::_miBetSmallTag:
                    sdkbox::PluginGoogleAnalytics::logEvent("Button", "btnBetSmall", "", 0);
                    this->getRoomListWithBetType(MessageRequestRoomList_eBetType::MessageRequestRoomList_eBetType_btSMALL);
                    break;
                    
                case SceneTags::_miBetMediumTag:
                    sdkbox::PluginGoogleAnalytics::logEvent("Button", "btnBetMedium", "", 0);
                    this->getRoomListWithBetType(MessageRequestRoomList_eBetType::MessageRequestRoomList_eBetType_btMEDIUM);
                    break;
                    
                case SceneTags::_miBetBigTag:
                    sdkbox::PluginGoogleAnalytics::logEvent("Button", "btnBetBig", "", 0);
                    this->getRoomListWithBetType(MessageRequestRoomList_eBetType::MessageRequestRoomList_eBetType_btBIG);
                    break;
                    
                default:
                    break;
            }
            break;
        }
            
        default:
            break;
    }
}

void SceneLobby::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event) {
    if(keyCode == EventKeyboard::KeyCode::KEY_BACK) {
        this->onMenuCallback(this->getChildByTag(_miBackTag));
    }
}

void SceneLobby::onListViewSelectedItemEvent(cocos2d::Ref *sender, cocos2d::ui::ListView::EventType type) {
    if(type == cocos2d::ui::ListView::EventType::ON_SELECTED_ITEM_END){
        auto listView = dynamic_cast<ListView*>(sender);
        auto lastSelectedItemIndex = listView->getCurSelectedIndex();
        auto selectedItem = dynamic_cast<RoomItem*>(listView->getItem(lastSelectedItemIndex));
        sdkbox::PluginGoogleAnalytics::logEvent("SelectedItem", "x1", "", 0);
        if (lastSelectedItemIndex == _lastSelectedRoomItem) {
            sdkbox::PluginGoogleAnalytics::logEvent("SelectedItem", "x2", "", 0);
            SceneManager::goWithNode(SceneRoom::create(selectedItem->getRoomId()), false);
        } else {
            if (_lastSelectedRoomItem >= 0)
                dynamic_cast<RoomItem*>(listView->getItem(_lastSelectedRoomItem))->setSelection(false);
            if(lastSelectedItemIndex >= 0)
                selectedItem->setSelection(true);
        }
        _lastSelectedRoomItem = lastSelectedItemIndex;
    }
}

void SceneLobby::showDialog(DialogTypes dialogType) {
    this->hideDialog();
    
    if (dialogType == DialogTypeNone) {
        return;
    }
    
    this->setEnableControls(false);
    
    switch (dialogType) {
        case DialogTypeBase: {
            auto dialog = DialogBase::create();
            dialog->setDelegate(this);
            this->addChild(dialog, DialogTypeBase, DialogTypeBase);
            break;
        }
            
        default:
            break;
    }
    
    _currentDialog = dialogType;
}

void SceneLobby::hideDialog() {
    this->setEnableControls(true);
    
    if (_currentDialog == DialogTypeNone) {
        return;
    }
    
    this->removeChildByTag(_currentDialog);
    
    _currentDialog = DialogTypeNone;
}

void SceneLobby::setEnableControls(bool value) {
    dynamic_cast<Button9TextShadow*>(this->getChildByTag(_miBackTag))->setEnabled(value);
    dynamic_cast<Menu*>(this->getChildByTag(_menuBetTag))->setEnabled(value);
    dynamic_cast<ListView*>(this->getChildByTag(_listViewTag))->setEnabled(value);
}

void SceneLobby::onDialogButtonTap(Ref* sender, int buttonIndex, std::map<std::string, std::string> userData) {
    sdkbox::PluginGoogleAnalytics::logEvent("Dialog", StringUtils::format("ButtonIndex_%d", buttonIndex), "", 0);
    this->hideDialog();
}

// api calls

void SceneLobby::getRoomListWithBetType(MessageRequestRoomList_eBetType betType) {
    sdkbox::PluginGoogleAnalytics::logEvent("ApiCall", "getRoomListWithBetType", StringUtils::format("betType_%d", betType), 0);
    if(!SocketThread::getInstance()->getSocket()->isConnected()) {
        return;
    }
    
    auto listView = dynamic_cast<ListView*>(this->getChildByTag(SceneTags::_listViewTag));
    listView->removeAllItems();
    MessageRequestRoomList msg;
    msg.set_bettype(betType);
    
    SocketThread::getInstance()->getSocket()->Send(this->wrapMessage(eProtoMessageType::cmtGetRoomList, msg));
}

// api callbacks

void SceneLobby::processProtoMessage(const eProtoMessageType messageType, const std::string &messageBody) {
    switch (messageType) {
        case eProtoMessageType::cmtGetRoomList: {
            this->callbackRoomListWithBetType(messageBody);
            break;
        }
            
        default:
            break;
    }
}

void SceneLobby::callbackRoomListWithBetType(const std::string &source) {
    sdkbox::PluginGoogleAnalytics::logEvent("ApiCallback", "callbackRoomListWithBetType", "", 0);
    if (source.empty())
        return;
    
    MessageResponseRoomList msg;
    msg.ParseFromString(source);
    
    auto winSize = Director::getInstance()->getVisibleSize();
    auto listView = dynamic_cast<ListView*>(this->getChildByTag(SceneTags::_listViewTag));
    for(auto item : msg.roomlist()) {
        auto roomItem = RoomItem::create(&item, winSize.width-listView->getPosition().x*2, 60);
        listView->pushBackCustomItem(roomItem);
    }
}
