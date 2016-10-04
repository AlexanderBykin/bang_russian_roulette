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

#include "SceneShop.h"
#include "Libs/SceneManager.h"
#include "Libs/ShopItem.h"
#include "Libs/LanguageManager.h"
#include "Libs/LabelShadow.h"
#include "Network/SocketThread.h"
#include "Libs/GlobalProperties.h"
#include "ProtoMessages/MessageRequestAuth.pb.h"
#include "ProtoMessages/MessageResponseAuth.pb.h"
#include "ProtoMessages/MessageResponseShopItemList.pb.h"
#include "ProtoMessages/MessageResponseMoney.pb.h"
#include "ProtoMessages/MessageResponseBuyShopItem.pb.h"
#include "ProtoMessages/MessageResponse.pb.h"
#include "ProtoMessages/MessageRequestWatchAd.pb.h"
#include "ProtoMessages/MessageResponseWatchAd.pb.h"
#include "ProtoMessages/AuthType.pb.h"
#include "PluginGoogleAnalytics/PluginGoogleAnalytics.h"
#include "Libs/Button9TextShadow.h"
#include "PluginIAP/PluginIAP.h"
#include "audio/include/AudioEngine.h"

bool SceneShop::init() {
    if(!Layer::init()) {
        return false;
    }

    sdkbox::PluginGoogleAnalytics::logScreen("SceneShop");
    
    sdkbox::IAP::setListener(this);
    sdkbox::IAP::init();
    //sdkbox::PluginVungle::setListener(this);
    //sdkbox::PluginVungle::init();
    
    auto winSize = Director::getInstance()->getVisibleSize();
    
    auto bg = Sprite::create("SceneProfile/SceneProfileBG.png");
    bg->setPosition(Vec2(winSize.width/2, winSize.height/2));
    this->addChild(bg, 0);
    
    
    auto sceneCaption = LabelShadow::create(LanguageManager::getString("ShopCaption"),
                                            GameFont,
                                            90,
                                            Color3B::WHITE,
                                            Color3B(51, 51, 51));
    sceneCaption->setAnchorPoint(Vec2::ANCHOR_MIDDLE_TOP);
    sceneCaption->setPosition(Vec2(winSize.width/2, winSize.height-10));
    sceneCaption->setShadowOffset(6);
    this->addChild(sceneCaption, 1);
    
    
    auto btnBack = Button9TextShadow::create("SceneProfile/btnSceneProfileBack.png", CC_CALLBACK_1(SceneShop::onMenuCallback, this));
    btnBack->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
    btnBack->setTag(_miBackTag);
    btnBack->setPosition(Vec2(10, winSize.height-15));
    this->addChild(btnBack, _miBackTag, _miBackTag);


    float btnWidth = winSize.width / 4 - 4 * 10;
    float btnHeight = 120.0f;
    auto listViewButton = ListView::create();
    listViewButton->setDirection(ui::ScrollView::Direction::HORIZONTAL);
    listViewButton->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
    listViewButton->setPosition(Vec2(60, winSize.height-230));
    listViewButton->setContentSize(Size(winSize.width-120, btnHeight*1.5));
    listViewButton->setScrollBarEnabled(false);
    listViewButton->setGravity(cocos2d::ui::ListView::Gravity::CENTER_HORIZONTAL);
    //listViewButton->setBackGroundColorType(cocos2d::ui::Layout::BackGroundColorType::SOLID);
    //listViewButton->setBackGroundColor(Color3B::GREEN);
    listViewButton->setItemsMargin(10);
    this->addChild(listViewButton, _menuShopItemTag, _menuShopItemTag);
    
    
    auto btnItems = Button9TextShadow::create("Dialog/btnDialogBaseBackNext.png",
                                                Size(btnWidth, btnHeight),
                                                LanguageManager::getString("ShopThingsButton"),
                                                GameFont,
                                                50,
                                                Color3B(51, 51, 51),
                                                Color3B(204, 204, 204),
                                                CC_CALLBACK_1(SceneShop::onMenuCallback, this));
    btnItems->setTag(_miItemsTypeTag);
    btnItems->setSelectedResources("SceneLobby/btnSceneLobbyBetBGSelected.png", Color3B(56, 37, 27), Color3B(255, 237, 105));
    btnItems->setPressedActionEnabled(false);
    btnItems->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    listViewButton->pushBackCustomItem(btnItems);
    
    
    auto btnCollections = Button9TextShadow::create("Dialog/btnDialogBaseBackNext.png",
                                                 Size(btnWidth, btnHeight),
                                                 LanguageManager::getString("ShopCollectionsButton"),
                                                 GameFont,
                                                 50,
                                                 Color3B(51, 51, 51),
                                                 Color3B(204, 204, 204),
                                                 CC_CALLBACK_1(SceneShop::onMenuCallback, this));
    btnCollections->setTag(_miCollectionTypeTag);
    btnCollections->setSelectedResources("SceneLobby/btnSceneLobbyBetBGSelected.png", Color3B(56, 37, 27), Color3B(255, 237, 105));
    btnCollections->setPressedActionEnabled(false);
    btnCollections->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    listViewButton->pushBackCustomItem(btnCollections);
    
    auto btnMoney = Button9TextShadow::create("Dialog/btnDialogBaseBackNext.png",
                                                  Size(btnWidth, btnHeight),
                                                  LanguageManager::getString("ShopMoneyButton"),
                                                  GameFont,
                                                  50,
                                                  Color3B(51, 51, 51),
                                                  Color3B(204, 204, 204),
                                                  CC_CALLBACK_1(SceneShop::onMenuCallback, this));
    btnMoney->setTag(_miMoneyTypeTag);
    btnMoney->setSelectedResources("SceneLobby/btnSceneLobbyBetBGSelected.png", Color3B(56, 37, 27), Color3B(255, 237, 105));
    btnMoney->setPressedActionEnabled(false);
    btnMoney->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    listViewButton->pushBackCustomItem(btnMoney);
    
    auto btnWatchAd = Button9TextShadow::create("Dialog/btnDialogBaseBackNext.png",
                                               Size(btnWidth, btnHeight),
                                               LanguageManager::getString("ShopWatchAdButton"),
                                               GameFont,
                                               50,
                                               Color3B(51, 51, 51),
                                               Color3B(204, 204, 204),
                                               CC_CALLBACK_1(SceneShop::onMenuCallback, this));
    btnWatchAd->setTag(_miWatchAdTag);
    btnWatchAd->setSelectedResources("SceneLobby/btnSceneLobbyBetBGSelected.png", Color3B(56, 37, 27), Color3B(255, 237, 105));
    btnWatchAd->setPressedActionEnabled(false);
    btnWatchAd->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    listViewButton->pushBackCustomItem(btnWatchAd);
    
    
    auto shelf = Sprite::create("SceneShop/SceneShopShelf.png");
    shelf->setPosition(Vec2(winSize.width/2, winSize.height/2));
    this->addChild(shelf, 1);
    
    
    ListView* listView = ListView::create();
    // set list view ex direction
    listView->setDirection(ui::ScrollView::Direction::HORIZONTAL);
    listView->setBounceEnabled(true);
    listView->setPosition(Vec2(0, winSize.height-620));
    listView->setContentSize(Size(winSize.width, 300));
    listView->setItemsMargin(20);
    //listView->setBackGroundColorType(cocos2d::ui::Layout::BackGroundColorType::SOLID);
    //listView->setBackGroundColor(Color3B::GREEN);
    listView->addEventListener((ui::ListView::ccListViewCallback)CC_CALLBACK_2(SceneShop::onListViewSelectedItemEvent, this));
    this->addChild(listView, _listViewItemsTag, _listViewItemsTag);
    
    
    auto lblMoney = Label::createWithTTF(LanguageManager::getString("ShopMoneyLabel"), GameFont, 38);
    lblMoney->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
    lblMoney->setPosition(Vec2(20, 350));
    lblMoney->setColor(Color3B(56, 37, 27));
    this->addChild(lblMoney);
    
    auto txtMoney = Label::createWithTTF("", GameFont, 38);
    txtMoney->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
    txtMoney->setPosition(Vec2(lblMoney->getPosition().x + lblMoney->getContentSize().width + 20, lblMoney->getPosition().y));
    txtMoney->setColor(Color3B(56, 37, 27));
    this->addChild(txtMoney, _txtMoneyTag, _txtMoneyTag);
    
    
    auto lblDesc = Label::createWithTTF(LanguageManager::getString("ShopDescriptionLabel"), GameFont, 38);
    lblDesc->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
    lblDesc->setPosition(Vec2(lblMoney->getPosition().x, lblMoney->getPosition().y - 40));
    lblDesc->setColor(Color3B(56, 37, 27));
    this->addChild(lblDesc);
    
    
    auto txtDescription = Label::createWithTTF("", GameFont, 30);
    txtDescription->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
    txtDescription->setDimensions(winSize.width/2+80, 160);
    txtDescription->setAlignment(TextHAlignment::LEFT, TextVAlignment::TOP);
    txtDescription->setPosition(Vec2(lblDesc->getPosition().x, lblDesc->getPosition().y - 20));
    txtDescription->setColor(Color3B(56, 37, 27));
    this->addChild(txtDescription, _txtDescriptionTag, _txtDescriptionTag);
    
    
    auto txtPriceForRealCash = Label::createWithTTF("", GameFont, 38);
    txtPriceForRealCash->setAnchorPoint(Vec2::ANCHOR_MIDDLE_RIGHT);
    txtPriceForRealCash->setPosition(Vec2(winSize.width - 360, 310));
    txtPriceForRealCash->setColor(Color3B(56, 37, 27));
    txtPriceForRealCash->setHorizontalAlignment(TextHAlignment::RIGHT);
    this->addChild(txtPriceForRealCash, _txtRealCashPriceTag, _txtRealCashPriceTag);
    
    
    auto txtPriceForGameCash = Label::createWithTTF("", GameFont, 38);
    txtPriceForGameCash->setAnchorPoint(Vec2::ANCHOR_MIDDLE_RIGHT);
    txtPriceForGameCash->setPosition(Vec2(winSize.width - 360, 175));
    txtPriceForGameCash->setColor(Color3B(56, 37, 27));
    txtPriceForGameCash->setHorizontalAlignment(TextHAlignment::RIGHT);
    this->addChild(txtPriceForGameCash, _txtInGameCashPriceTag, _txtInGameCashPriceTag);
    
    
    auto imgInGameCash = Sprite::create("SceneShop/SceneShopMoney.png");
    imgInGameCash->setAnchorPoint(Vec2::ANCHOR_MIDDLE_RIGHT);
    this->addChild(imgInGameCash, _imgInGameCashPriceTag, _imgInGameCashPriceTag);
    

    btnWidth = 300;
    auto listViewBuyButton = ListView::create();
    listViewBuyButton->setDirection(ui::ScrollView::Direction::VERTICAL);
    listViewBuyButton->setAnchorPoint(Vec2::ANCHOR_MIDDLE_RIGHT);
    listViewBuyButton->setPosition(Vec2(winSize.width-10, 240));
    listViewBuyButton->setContentSize(Size(btnWidth+20, btnHeight*2+2*15));
    listViewBuyButton->setScrollBarEnabled(false);
    listViewBuyButton->setGravity(cocos2d::ui::ListView::Gravity::CENTER_HORIZONTAL);
    //listViewBuyButton->setBackGroundColorType(cocos2d::ui::Layout::BackGroundColorType::SOLID);
    //listViewBuyButton->setBackGroundColor(Color3B::GREEN);
    listViewBuyButton->setItemsMargin(10);
    this->addChild(listViewBuyButton, _menuBuyButtonsTag, _menuBuyButtonsTag);

    auto btnBuyRealCash = Button9TextShadow::create("Dialog/btnDialogBaseBackNext.png",
                                                    Size(btnWidth, btnHeight),
                                                    LanguageManager::getString("ShopBuyButton"),
                                                    GameFont,
                                                    40,
                                                    Color3B(51, 51, 51),
                                                    Color3B(204, 204, 204),
                                                    CC_CALLBACK_1(SceneShop::onMenuCallback, this));
    btnBuyRealCash->setTag(_miRealCashTag);
    btnBuyRealCash->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    listViewBuyButton->pushBackCustomItem(btnBuyRealCash);

    auto btnBuyGameCash = Button9TextShadow::create("Dialog/btnDialogBaseBackNext.png",
                                                    Size(btnWidth, btnHeight),
                                                    LanguageManager::getString("ShopBuyButton"),
                                                    GameFont,
                                                    40,
                                                    Color3B(51, 51, 51),
                                                    Color3B(204, 204, 204),
                                                    CC_CALLBACK_1(SceneShop::onMenuCallback, this));
    btnBuyGameCash->setTag(_miInGameCashTag);
    btnBuyGameCash->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    listViewBuyButton->pushBackCustomItem(btnBuyGameCash);

    
    this->setMoney(0L);
    this->setPriceForRealMoney("0");
    this->setPriceForInGameCash(0);

    
    auto listener = EventListenerKeyboard::create();
    listener->onKeyReleased = CC_CALLBACK_2(SceneShop::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    this->scheduleOnce(CC_SCHEDULE_SELECTOR(SceneShop::delayInit), 0.5);


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

void SceneShop::delayInit(float value) {
    this->getMoney();
    auto listView = dynamic_cast<ListView*>(this->getChildByTag(_menuShopItemTag));
    this->onMenuCallback(listView->getItem(0));
}

void SceneShop::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event) {
    if(keyCode == EventKeyboard::KeyCode::KEY_BACK) {
        this->onMenuCallback(this->getChildByTag(_miBackTag));
    }
}

void SceneShop::onMenuCallback(cocos2d::Ref *ref) {
    auto item = dynamic_cast<Node*>(ref);
    auto listView = dynamic_cast<ListView*>(this->getChildByTag(_listViewItemsTag));
    experimental::AudioEngine::play2d("Sounds/btnmenu_click.mp3");
    switch ((SceneTags)item->getTag()) {
        case _miBackTag: {
            sdkbox::PluginGoogleAnalytics::logEvent("Button", "btnBack", "", 0);
            SceneManager::goBack(BrrScenes::SceneMain);
            break;
        }
            
        case _miItemsTypeTag:
        case _miCollectionTypeTag:
        case _miMoneyTypeTag:
        case _miWatchAdTag: {
            dynamic_cast<Label*>(this->getChildByTag(_txtDescriptionTag))->setString("");
            this->setPriceForInGameCash(0);
            auto listViewItems = dynamic_cast<ListView*>(this->getChildByTag(_menuShopItemTag));
            auto btn = dynamic_cast<Button9TextShadow*>(item);
            if(_lastSelectedShopItemIndex >= 0) {
                auto lastSelected = dynamic_cast<Button9TextShadow*>(listViewItems->getItem(_lastSelectedShopItemIndex));
                lastSelected->onPressStateChangedToNormal();
            }
            btn->onPressStateChangedToPressed();
            _lastSelectedShopItemIndex = (int)listViewItems->getIndex(btn);
            _lastSelectedShopItemType = btn->getTag();
            //SimpleAudioEngine::getInstance()->playEffect("btnmenu_click.mp3");

            switch ((SceneTags)item->getTag()) {
                case _miMoneyTypeTag:
                    sdkbox::PluginGoogleAnalytics::logEvent("Button", "btnItemTypeMoney", "", 0);
                    this->getShopItemByType(MessageRequestShopItemList_eShopItemType::MessageRequestShopItemList_eShopItemType_sitCOLLECTIONMONEY);
                    break;
                    
                case _miCollectionTypeTag:
                    sdkbox::PluginGoogleAnalytics::logEvent("Button", "btnItemTypeCollection", "", 0);
                    this->getShopItemByType(MessageRequestShopItemList_eShopItemType::MessageRequestShopItemList_eShopItemType_sitCOLLECTIONITEMS);
                    break;
                    
                case _miItemsTypeTag:
                    sdkbox::PluginGoogleAnalytics::logEvent("Button", "btnItemTypeItems", "", 0);
                    this->getShopItemByType(MessageRequestShopItemList_eShopItemType::MessageRequestShopItemList_eShopItemType_sitITEMS);
                    break;
                    
                case _miWatchAdTag:
                    sdkbox::PluginGoogleAnalytics::logEvent("Button", "btnItemTypeWatchAd", "", 0);
                    this->getShopItemByType(MessageRequestShopItemList_eShopItemType::MessageRequestShopItemList_eShopItemType_sitVIDEOAD);
                    break;
                    
                default:
                    break;
            }
            this->showBuyButtonsByShopItemType();

            _lastSelectedItem = -1;
            this->onListViewSelectedItemEvent(this->getChildByTag(_listViewItemsTag), ListView::EventType::ON_SELECTED_ITEM_END);
            break;
        }
            
        case _miRealCashTag: {
            sdkbox::PluginGoogleAnalytics::logEvent("Button", "btnRealCash", "", 0);
            if(auto selectedItem = dynamic_cast<ShopItem*>(listView->getItems().at(_lastSelectedItem))) {
                sdkbox::IAP::purchase(selectedItem->getItemName());
            }
            break;
        }
            
        case _miInGameCashTag: {
            if(_lastSelectedShopItemType == _miWatchAdTag) {
                //sdkbox::PluginGoogleAnalytics::logEvent("Button", "btnWatchAd", "", 0);
                //sdkbox::PluginVungle::show("video");
            } else {
                sdkbox::PluginGoogleAnalytics::logEvent("Button", "btnInGameCash", "", 0);
                //            SimpleAudioEngine::getInstance()->playEffect("btnmenu_click.mp3");
                if(listView->getItems().size() > 0) {
                    auto selectedItem = dynamic_cast<ShopItem*>(listView->getItems().at(_lastSelectedItem));
                    this->buyShopItemWithName(selectedItem->getItemName(), MessageRequestBuyShopItem_eBuyType::MessageRequestBuyShopItem_eBuyType_btInGameCash, "");
                    this->showDialog(DialogTypes::DialogTypeBase);
                    auto dialog = dynamic_cast<DialogBase*>(this->getChildByTag(DialogTypes::DialogTypeBase));
                    dialog->setCaption(LanguageManager::getString("ShopCaption"));
                    auto dialogMessage = LanguageManager::getString("ShopBuyItemWait");
                    auto winSize = Director::getInstance()->getVisibleSize();
                    auto lblDialogMessage = Label::createWithTTF(dialogMessage, GameFont, 47);
                    lblDialogMessage->setDimensions(dialog->getDialogRect().size.width-20, 100);
                    lblDialogMessage->setAlignment(TextHAlignment::CENTER, TextVAlignment::TOP);
                    lblDialogMessage->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
                    lblDialogMessage->setColor(Color3B(56, 37, 27));
                    dialog->addChild(lblDialogMessage);
                }
            }
            break;
        }
            
        default:
            break;
    }
}

void SceneShop::onListViewSelectedItemEvent(cocos2d::Ref *sender, cocos2d::ui::ListView::EventType type) {
    if(type == cocos2d::ui::ListView::EventType::ON_SELECTED_ITEM_END) {
        auto listView = dynamic_cast<ListView*>(sender);
        auto lastSelectedItemIndex = listView->getCurSelectedIndex();
        ShopItem* lastSelectedItem = nullptr;
        if (_lastSelectedItem >= 0) {
            if(auto shopItem = dynamic_cast<ShopItem*>(listView->getItem(_lastSelectedItem)))
                shopItem->setSelection(false);
        }
        if(lastSelectedItemIndex >= 0) {
            if(auto shopItem = dynamic_cast<ShopItem*>(listView->getItem(listView->getCurSelectedIndex()))) {
                shopItem->setSelection(true);
                // dynamic_cast<Label*>(this->getChildByTag(_txtDescriptionTag))->setString(shopItem->getItemDescription());
                this->setPriceForInGameCash(shopItem->getItemCost());
                lastSelectedItem = shopItem;
                sdkbox::PluginGoogleAnalytics::logEvent("SelectedItem", shopItem->getItemName(), "", 0);
            }
        }
        _lastSelectedItem = lastSelectedItemIndex;
        this->showBuyButtonsByShopItemType();

        bool isFound = false;
        
        if (!_inAppItems.empty() && lastSelectedItem != nullptr) {
            for (sdkbox::Product item : _inAppItems) {
                if (item.id.compare(lastSelectedItem->getItemName()) == 0) {
                    isFound = true;
                    this->setPriceForRealMoney(StringUtils::format("%.2f", item.priceValue));
                    break;
                }
            }
        }
        
        this->setRealCashIsVisible(isFound);
    }
}

void SceneShop::showBuyButtonsByShopItemType() {
    this->setGameCashIsVisible(false);
    this->setRealCashIsVisible(false);

    switch (_lastSelectedShopItemType) {
        case _miMoneyTypeTag:
            this->setRealCashIsVisible(true);
            break;
            
        case _miCollectionTypeTag:
            this->setGameCashIsVisible(true);
            this->setRealCashIsVisible(true);
            break;
            
        case _miItemsTypeTag:
            this->setGameCashIsVisible(true);
            break;
            
        case _miWatchAdTag:
            this->setWatchAdIsVisible(true);
            break;
            
        default:
            break;
    }
}

void SceneShop::setMoney(long long value) {
    if(auto txt = dynamic_cast<Label*>(this->getChildByTag(_txtMoneyTag))) {
        //txt->setString(StringUtils::format("%lli", value));
    }
}

void SceneShop::setPriceForRealMoney(const std::string& value) {
    if(auto txt = dynamic_cast<Label*>(this->getChildByTag(_txtRealCashPriceTag))) {
        //txt->setString(value);
    }
}

void SceneShop::setPriceForInGameCash(int value) {
    if(auto txt = dynamic_cast<Label*>(this->getChildByTag(_txtInGameCashPriceTag))) {
        //txt->setString(StringUtils::format("%i", value));
        this->getChildByTag(_imgInGameCashPriceTag)->setPosition(Vec2(txt->getPosition().x - txt->getContentSize().width - 20, txt->getPosition().y));
    }
}

void SceneShop::setRealCashIsVisible(bool value) {
    if (_inAppItems.empty() || !SocketThread::getInstance()->getSocket()->isConnected() || GlobalProperties::getPlayerId() <= 0L) {
        if (GlobalProperties::isDebug()) {
            cocos2d::log("setRealCashIsVisible _inAppItems=%lu", _inAppItems.size());
        }
        value = false;
    }
//    if(auto lv = dynamic_cast<ListView*>(this->getChildByTag(_menuBuyButtonsTag))){
//        if(auto btn = dynamic_cast<Button9TextShadow*>(lv->getItem(0))){
//            btn->setVisible(value);
//            btn->setText(LanguageManager::getString("ShopBuyButton"));
//            this->getChildByTag(_txtRealCashPriceTag)->setVisible(value);
//        }
//    }
}

void SceneShop::setGameCashIsVisible(bool value) {
    if(auto listView = dynamic_cast<ListView*>(this->getChildByTag(_listViewItemsTag))){
        if (listView->getItems().size() <= 0 || !SocketThread::getInstance()->getSocket()->isConnected() || GlobalProperties::getPlayerId() <= 0L) {
            value = false;
        }
    }
    
//    if(auto lv = dynamic_cast<ListView*>(this->getChildByTag(_menuBuyButtonsTag))){
//        if(auto btn = dynamic_cast<Button9TextShadow*>(lv->getItem(1))){
//            btn->setVisible(value);
//            btn->setText(LanguageManager::getString("ShopBuyButton"));
//            this->getChildByTag(_txtInGameCashPriceTag)->setVisible(value);
//            this->getChildByTag(_imgInGameCashPriceTag)->setVisible(value);
//        }
//    }
}

void SceneShop::setWatchAdIsVisible(bool value) {
    if(auto listView = dynamic_cast<ListView*>(this->getChildByTag(_listViewItemsTag))){
        if (listView->getItems().empty() || !SocketThread::getInstance()->getSocket()->isConnected() || GlobalProperties::getPlayerId() <= 0L) {
            value = false;
        }
    }

//    if(auto lv = dynamic_cast<ListView*>(this->getChildByTag(_menuBuyButtonsTag))){
//        if(auto btn = dynamic_cast<Button9TextShadow*>(lv->getItem(1))){
//            btn->setVisible(value);
//            btn->setText(LanguageManager::getString("ShopWatchAdButton"));
//            this->getChildByTag(_txtInGameCashPriceTag)->setVisible(false);
//            this->getChildByTag(_imgInGameCashPriceTag)->setVisible(false);
//        }
//    }
}

void SceneShop::showDialog(DialogTypes dialogType) {
    this->hideDialog();
    
    if (dialogType == DialogTypes::DialogTypeNone) {
        return;
    }
    
    this->setEnableControls(false);
    
    switch (dialogType) {
            /*case DialogTypeAuth: {
             DialogAuth *dialog = [[DialogAuth alloc] init];
             dialog.delegate = self;
             [self addChild:dialog z:999 tag:kDialogAuthTag];
             break;
             }*/
            
        case DialogTypes::DialogTypeBase: {
            sdkbox::PluginGoogleAnalytics::logEvent("ShowDialog", "Base", "", 0);
            auto dialog = DialogBase::create();
            dialog->setDelegate(this);
            this->addChild(dialog, dialogType, dialogType);
            break;
        }
            
        default:
            break;
    }
    
    _currentDialog = dialogType;
}

void SceneShop::hideDialog() {
    this->setEnableControls(true);
    
    if (_currentDialog == DialogTypes::DialogTypeNone) {
        return;
    }
    
    sdkbox::PluginGoogleAnalytics::logEvent("HideDialog", "Base", "", 0);

    this->removeChildByTag(_currentDialog);
    
    _currentDialog = DialogTypes::DialogTypeNone;
}

void SceneShop::onDialogButtonTap(Ref* sender, int buttonIndex, std::map<std::string, std::string> userData) {
    sdkbox::PluginGoogleAnalytics::logEvent("Dialog", StringUtils::format("ButtonIndex_%d", buttonIndex), "", 0);
    this->hideDialog();
}

void SceneShop::setEnableControls(bool value) {
    dynamic_cast<Button9TextShadow*>(this->getChildByTag(_miBackTag))->setEnabled(value);
    dynamic_cast<ListView*>(this->getChildByTag(_menuShopItemTag))->setEnabled(value);
    dynamic_cast<ListView*>(this->getChildByTag(_listViewItemsTag))->setEnabled(value);
    dynamic_cast<ListView*>(this->getChildByTag(_menuBuyButtonsTag))->setEnabled(value);
}

// api calls

void SceneShop::authPlayer() {
    if(GlobalProperties::getLogin().empty() || GlobalProperties::getPassword().empty()) {
        return;
    }
    
    sdkbox::PluginGoogleAnalytics::logEvent("ApiCall", "AuthPlayer", "GooglePlay", 0);
    
    MessageRequestAuth msg;
    msg.set_authtype(eAuthType::atEmail);
    msg.set_login(GlobalProperties::getLogin());
    msg.set_password(GlobalProperties::getPassword());
    SocketThread::getInstance()->getSocket()->Send(this->wrapMessage(eProtoMessageType::cmtAuth, msg));
}

void SceneShop::getShopItemByType(MessageRequestShopItemList_eShopItemType shopItemType) {
    sdkbox::PluginGoogleAnalytics::logEvent("ApiCall", "getShopItemByType", StringUtils::format("ItemType_%d", shopItemType), 0);
    auto listView = dynamic_cast<ListView*>(this->getChildByTag(_listViewItemsTag));
    listView->removeAllItems();
    MessageRequestShopItemList msg;
    msg.set_shopitemtype(shopItemType);
    msg.set_lang(GlobalProperties::getCurrentLanguageAsString());
    SocketThread::getInstance()->getSocket()->Send(this->wrapMessage(eProtoMessageType::cmtGetShopItems, msg));
}

void SceneShop::getMoney() {
    sdkbox::PluginGoogleAnalytics::logEvent("ApiCall", "getMoney", "", 0);
    SocketThread::getInstance()->getSocket()->Send(this->wrapMessage(eProtoMessageType::cmtGetMoney));
}

void SceneShop::buyShopItemWithName(const std::string& shopItemName, MessageRequestBuyShopItem_eBuyType buyType, const char *receipt) {
    auto itemType = (_lastSelectedShopItemType == _miCollectionTypeTag ||
                     _lastSelectedShopItemType == _miMoneyTypeTag)
    ? MessageRequestBuyShopItem_eItemType::MessageRequestBuyShopItem_eItemType_itItemCollection
    : MessageRequestBuyShopItem_eItemType::MessageRequestBuyShopItem_eItemType_itItem;

    sdkbox::PluginGoogleAnalytics::logEvent("ApiCall", "buyShopItem", StringUtils::format("ItemName_%s_BuyType_%d_ItemType_%d", shopItemName.c_str(), buyType, itemType), 0);

    MessageRequestBuyShopItem msg;
    msg.set_markettype(MessageRequestBuyShopItem_eMarketType_atGoogle);
    msg.set_shopitemname(shopItemName);
    msg.set_buytype(buyType);
    msg.set_receipt(receipt);
    msg.set_itemtype(itemType);
    SocketThread::getInstance()->getSocket()->Send(this->wrapMessage(eProtoMessageType::cmtBuyShopItem, msg));
}

// api callbacks

void SceneShop::processProtoMessage(const eProtoMessageType messageType, const std::string &messageBody) {
    switch (messageType) {
        case eProtoMessageType::cmtGetShopItems: {
            this->callbackShopItems(messageBody);
            break;
        }
            
        case eProtoMessageType::cmtNeedAuth: {
            this->callbackNeedAuth(messageBody);
            break;
        }
            
        case eProtoMessageType::cmtAuth: {
            this->callbackAuth(messageBody);
            break;
        }
            
        case eProtoMessageType::cmtGetMoney: {
            this->callbackGetMoney(messageBody);
            break;
        }
            
        case eProtoMessageType::cmtBuyShopItem: {
            this->callbackBuyShopItem(messageBody);
            break;
        }
            
        case eProtoMessageType::cmtWatchAd: {
            this->callbackWatchAd(messageBody);
            break;
        }
            
        default:
            break;
    }
}

void SceneShop::callbackNeedAuth(const std::string &source) {
    sdkbox::PluginGoogleAnalytics::logEvent("ApiCallback", "callbackNeedAuth", "", 0);
    
    this->authPlayer();
}

void SceneShop::callbackAuth(const std::string &source) {
    sdkbox::PluginGoogleAnalytics::logEvent("ApiCallback", "callbackAuth", "", 0);
    if (source.empty())
        return;
    
    MessageResponseAuth msg;
    msg.ParseFromString(source);
    
    auto authErrorType = msg.errortype();
    
    if (authErrorType == MessageResponseAuth_eAuthErrorType::MessageResponseAuth_eAuthErrorType_aetNone) {
        GlobalProperties::setPlayerId(msg.playerid());
        
        if (GlobalProperties::getPlayerId() > 0) {
            this->getMoney();
        }
    }
    else {
        GlobalProperties::setPlayerId(-1);
    }
}

void SceneShop::callbackShopItems(const std::string &source) {
    sdkbox::PluginGoogleAnalytics::logEvent("ApiCallback", "callbackShopItems", "", 0);
    if (source.empty())
        return;
    
    MessageResponseShopItemList msg;
    msg.ParseFromString(source);
    
    auto listView = dynamic_cast<ListView*>(this->getChildByTag(_listViewItemsTag));
    listView->removeAllItems();
    
    for(auto item : msg.shopitemlist()) {
        listView->pushBackCustomItem(ShopItem::create(StringUtils::format("ShopItem/%s", item.imagename().c_str()), item.name(), item.description(), item.amount(), item.cost()));
    }
    
    listView->setCurSelectedIndex(0);
    
    if (GlobalProperties::isDebug()) {
        cocos2d::log("callbackShopItems itemsSource=%lu", listView->getItems().size());
    }
}

void SceneShop::callbackGetMoney(const std::string &source) {
    sdkbox::PluginGoogleAnalytics::logEvent("ApiCallback", "callbackGetMoney", "", 0);
    if (source.empty())
        return;
    
    MessageResponseMoney msg;
    msg.ParseFromString(source);
    
    this->setMoney(msg.money());
}

void SceneShop::callbackBuyShopItem(const std::string &source) {
    sdkbox::PluginGoogleAnalytics::logEvent("ApiCallback", "callbackBuyShopItem", "", 0);
    if (source.empty())
        return;
    
    MessageResponseBuyShopItem msg;
    msg.ParseFromString(source);
    
    auto buyErrorType = msg.buyerrortype();
    
    this->showDialog(DialogTypes::DialogTypeBase);
    auto dialog = dynamic_cast<DialogBase*>(this->getChildByTag(DialogTypes::DialogTypeBase));
    dialog->setDelegate(this);
    dialog->setCaption(LanguageManager::getString("ShopCaption"));
    dialog->addDoneButton(LanguageManager::getString("DialogBaseDoneButton"));
    
    std::string dialogMessage = "";
    
    sdkbox::PluginGoogleAnalytics::logEvent("ApiCallback", "callbackBuyShopItem", StringUtils::format("BuyResult_%d", buyErrorType), 0);

    switch (buyErrorType) {
        case MessageResponseBuyShopItem_eBuyErrorType::MessageResponseBuyShopItem_eBuyErrorType_betNone: {
            this->getMoney();
            dialogMessage = LanguageManager::getString("ShopBuyItemSuccess");
            break;
        }
            
        case MessageResponseBuyShopItem_eBuyErrorType::MessageResponseBuyShopItem_eBuyErrorType_betMoneyLessThenNeed: {
            dialogMessage = LanguageManager::getString("ShopBuyItemFailMoneyLessThenNeed");
            break;
        }
            
        case MessageResponseBuyShopItem_eBuyErrorType::MessageResponseBuyShopItem_eBuyErrorType_betInternalError: {
            dialogMessage = LanguageManager::getString("ShopBuyItemFailInternal");
            break;
        }
            
        case MessageResponseBuyShopItem_eBuyErrorType::MessageResponseBuyShopItem_eBuyErrorType_betReceiptError: {
            dialogMessage = LanguageManager::getString("ShopBuyItemFailReceipt");
            break;
        }
            
        default:
            break;
    }
    
    auto lblDialogMessage = Label::createWithTTF(dialogMessage, GameFont, 47);
    lblDialogMessage->setDimensions(dialog->getDialogRect().size.width-20, 100);
    lblDialogMessage->setAlignment(TextHAlignment::CENTER, TextVAlignment::TOP);
    lblDialogMessage->setPosition(Vec2(dialog->getDialogRect().origin.x + dialog->getDialogRect().size.width / 2,
                                       dialog->getDialogRect().origin.y + dialog->getDialogRect().size.height / 2));
    lblDialogMessage->setColor(Color3B(56, 37, 27));
    dialog->addChild(lblDialogMessage);
}

void SceneShop::callbackWatchAd(const std::string &source) {
    sdkbox::PluginGoogleAnalytics::logEvent("ApiCallback", "callbackWatchAd", "", 0);
    if(source.empty()) {
        return;
    }
    
    MessageResponseWatchAd msg;
    msg.ParseFromString(source);
    
    // open dialog with award notification
    
    this->getMoney();
}

// SDKBOX AIP

void SceneShop::onInitialized(bool ok) {
}

void SceneShop::onSuccess(const sdkbox::Product& p) {
    sdkbox::PluginGoogleAnalytics::logEvent("IAP", "onSuccess", p.name, 0);

    this->hideDialog();

    auto listView = dynamic_cast<ListView*>(this->getChildByTag(_listViewItemsTag));

    if(auto shopItem = dynamic_cast<ShopItem*>(listView->getItem(listView->getCurSelectedIndex()))) {
        if (SocketThread::getInstance()->getSocket()->isConnected()) {
            this->buyShopItemWithName(shopItem->getItemName(), MessageRequestBuyShopItem_eBuyType_btRealMoney, "");
            this->showDialog(DialogTypeBase);
            auto dialog = dynamic_cast<DialogBase*>(this->getChildByTag(DialogTypeBase));
            dialog->setDelegate(this);
            dialog->setCaption(LanguageManager::getString("ShopCaption"));
            dialog->addDoneButton(LanguageManager::getString("DialogBaseDoneButton"));
            
            auto lblDialogMessage = Label::createWithTTF(LanguageManager::getString("ShopBuyItemSuccess"), GameFont, 47);
            lblDialogMessage->setDimensions(dialog->getDialogRect().size.width-20, 100);
            lblDialogMessage->setAlignment(TextHAlignment::CENTER, TextVAlignment::TOP);
            lblDialogMessage->setPosition(Vec2(dialog->getDialogRect().origin.x + dialog->getDialogRect().size.width / 2,
                                               dialog->getDialogRect().origin.y + dialog->getDialogRect().size.height / 2));
            lblDialogMessage->setColor(Color3B(56, 37, 27));
            dialog->addChild(lblDialogMessage);
        }
    }
}

void SceneShop::onFailure(const sdkbox::Product& p, const std::string& msg) {
    sdkbox::PluginGoogleAnalytics::logEvent("IAP", "onFailure", p.name, 0);

    this->hideDialog();
    this->showDialog(DialogTypeBase);

    auto dialog = dynamic_cast<DialogBase*>(this->getChildByTag(DialogTypeBase));
    dialog->setDelegate(this);
    dialog->setCaption(LanguageManager::getString("ShopCaption"));
    dialog->addDoneButton(LanguageManager::getString("DialogBaseDoneButton"));
    
    auto lblDialogMessage = Label::createWithTTF(msg, GameFont, 47);
    lblDialogMessage->setDimensions(dialog->getDialogRect().size.width-20, 100);
    lblDialogMessage->setAlignment(TextHAlignment::CENTER, TextVAlignment::TOP);
    lblDialogMessage->setPosition(Vec2(dialog->getDialogRect().origin.x + dialog->getDialogRect().size.width/2,
                                       dialog->getDialogRect().origin.y + dialog->getDialogRect().size.height/2));
    lblDialogMessage->setColor(Color3B(56, 37, 27));
    dialog->addChild(lblDialogMessage);
}

void SceneShop::onCanceled(const sdkbox::Product& p) {
    sdkbox::PluginGoogleAnalytics::logEvent("IAP", "onCanceled", p.name, 0);
    this->hideDialog();
}

void SceneShop::onRestored(const sdkbox::Product& p) {
    sdkbox::PluginGoogleAnalytics::logEvent("IAP", "onRestored", p.name, 0);
}

void SceneShop::onProductRequestSuccess(const std::vector<sdkbox::Product>& products) {
    sdkbox::PluginGoogleAnalytics::logEvent("IAP", "onProductRequest", "Success", 0);
    _inAppItems = products;
}

void SceneShop::onProductRequestFailure(const std::string& msg) {
    sdkbox::PluginGoogleAnalytics::logEvent("IAP", "onProductRequest", "Failure", 0);
    _inAppItems.clear();
}

void SceneShop::onRestoreComplete(bool ok, const std::string &msg) {
    sdkbox::PluginGoogleAnalytics::logEvent("IAP", "onRestore", "Complete", 0);
}

// SDKBOX VUNGLE

//void SceneShop::onVungleCacheAvailable() {
//
//}
//
//void SceneShop::onVungleStarted() {
//    sdkbox::PluginGoogleAnalytics::logEvent("VideoAd", "Vungle", "onVungleStarted", 0);
//}
//
//void SceneShop::onVungleFinished() {
//    sdkbox::PluginGoogleAnalytics::logEvent("VideoAd", "Vungle", "onVungleFinished", 0);
//}
//
//void SceneShop::onVungleAdViewed(bool isComplete) {
//    sdkbox::PluginGoogleAnalytics::logEvent("VideoAd", "Vungle", "onVungleAdViewed", 0);
//    if(isComplete && SocketThread::getInstance()->getSocket()->isConnected()) {
//        MessageRequestWatchAd msg;
//        msg.set_adtype(MessageRequestWatchAd_eAdType_atVungle);
//        SocketThread::getInstance()->getSocket()->Send(this->wrapMessage(eProtoMessageType::cmtWatchAd, msg));
//    }
//}
//
//void SceneShop::onVungleAdReward(const std::string& name) {
//
//}
//
