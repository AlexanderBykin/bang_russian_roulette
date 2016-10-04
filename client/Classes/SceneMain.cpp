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

#include "SceneMain.h"
#include "SceneManager.h"
#include "LanguageManager.h"
#include "GlobalProperties.h"
#include "MessageRequestCheckApi.pb.h"
#include "MessageResponseCheckApi.pb.h"
#include "SocketThread.h"
#include "PluginGoogleAnalytics/PluginGoogleAnalytics.h"
#include "PluginSdkboxPlay/PluginSdkboxPlay.h"
#include "audio/include/AudioEngine.h"
#include "ui/UIListView.h"
#include "DemoListViewItem.h"
#include "MessageRequestAuth.pb.h"
#include "MessageResponseAuth.pb.h"
#include "Button9TextShadow.h"

USING_NS_CC;
using namespace ui;

bool SceneMain::init() {
    if(!Layer::init()) {
        return false;
    }
    
    sdkbox::PluginGoogleAnalytics::logScreen("SceneMain");
    
    auto director = Director::getInstance();
    Size winSize = director->getVisibleSize();
    
    auto bg = Sprite::create("SceneMain/SceneMainBG.png");
    bg->setPosition(Vec2(winSize.width/2, winSize.height/2));
    this->addChild(bg);
    
    
    auto btnLogo = Button9TextShadow::create("SceneMain/logo.png", CC_CALLBACK_1(SceneMain::onMenuCallback, this));
    btnLogo->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
    btnLogo->setTag(miLogoTag);
    btnLogo->setPosition(Vec2(10, winSize.height-10));
    this->addChild(btnLogo, miLogoTag, miLogoTag);

    
    int btnHeight = 130;
    auto listView = ListView::create();
    // set list view ex direction
    listView->setDirection(ui::ScrollView::Direction::VERTICAL);
    listView->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    listView->setPosition(Vec2(winSize.width/2, winSize.height/2-60));
    listView->setContentSize(Size(winSize.width/2, btnHeight*5+20*4));
    listView->setScrollBarEnabled(false);
    listView->setGravity(cocos2d::ui::ListView::Gravity::CENTER_HORIZONTAL);
    //listView->setBackGroundColorType(cocos2d::ui::Layout::BackGroundColorType::SOLID);
    //listView->setBackGroundColor(Color3B::GREEN);
    listView->setItemsMargin(10);
    this->addChild(listView, menuMainTag, menuMainTag);


    auto btnPlay = Button9TextShadow::create("SceneMain/btnSceneMainBG.png",
                                            Size(winSize.width/2.3, btnHeight),
                                            LanguageManager::getString("MainPlayButton"),
                                            GameFont,
                                            60,
                                            Color3B(57, 37, 27),
                                            Color3B(255, 237, 105),
                                            CC_CALLBACK_1(SceneMain::onMenuCallback, this));
    btnPlay->setTag(miPlayTag);
    btnPlay->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    auto btnPlayLogo = Sprite::create("SceneMain/btnSceneMainPlayLogo.png");
    btnPlayLogo->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
    btnPlayLogo->setPosition(Vec2(50, btnHeight/2+6));
    btnPlay->addContentChild(btnPlayLogo);
    listView->pushBackCustomItem(btnPlay);

    auto btnShop = Button9TextShadow::create("SceneMain/btnSceneMainBG.png",
                                             Size(winSize.width/2.3, btnHeight),
                                             LanguageManager::getString("MainShopButton"),
                                             GameFont,
                                             60,
                                             Color3B(57, 37, 27),
                                             Color3B(255, 237, 105),
                                             CC_CALLBACK_1(SceneMain::onMenuCallback, this));
    btnShop->setTag(miShopTag);
    btnShop->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    auto btnShopLogo = Sprite::create("SceneMain/btnSceneMainShopLogo.png");
    btnShopLogo->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
    btnShopLogo->setPosition(Vec2(50, btnHeight/2+6));
    btnShop->addContentChild(btnShopLogo);
    listView->pushBackCustomItem(btnShop);

    auto btnProfile = Button9TextShadow::create("SceneMain/btnSceneMainBG.png",
                                             Size(winSize.width/2.3, btnHeight),
                                             LanguageManager::getString("MainProfileButton"),
                                             GameFont,
                                             60,
                                             Color3B(57, 37, 27),
                                             Color3B(255, 237, 105),
                                             CC_CALLBACK_1(SceneMain::onMenuCallback, this));
    btnProfile->setTag(miProfileTag);
    btnProfile->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    auto btnProfileLogo = Sprite::create("SceneMain/btnSceneMainProfileLogo.png");
    btnProfileLogo->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
    btnProfileLogo->setPosition(Vec2(50, btnHeight/2+6));
    btnProfile->addContentChild(btnProfileLogo);
    listView->pushBackCustomItem(btnProfile);

    auto btnTutorial = Button9TextShadow::create("SceneMain/btnSceneMainBG.png",
                                                Size(winSize.width/2.3, btnHeight),
                                                LanguageManager::getString("MainTutorialButton"),
                                                GameFont,
                                                60,
                                                Color3B(57, 37, 27),
                                                Color3B(255, 237, 105),
                                                CC_CALLBACK_1(SceneMain::onMenuCallback, this));
    btnTutorial->setTag(miTutorialTag);
    btnTutorial->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    auto btnTutorialLogo = Sprite::create("SceneMain/btnSceneMainTutorialLogo.png");
    btnTutorialLogo->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
    btnTutorialLogo->setPosition(Vec2(50, btnHeight/2+6));
    btnTutorial->addContentChild(btnTutorialLogo);
    listView->pushBackCustomItem(btnTutorial);

    auto btnAbout = Button9TextShadow::create("SceneMain/btnSceneMainBG.png",
                                                 Size(winSize.width/2.3, btnHeight),
                                                 LanguageManager::getString("MainAboutButton"),
                                                 GameFont,
                                                 60,
                                                 Color3B(57, 37, 27),
                                                 Color3B(255, 237, 105),
                                                 CC_CALLBACK_1(SceneMain::onMenuCallback, this));
    btnAbout->setTag(miAboutTag);
    btnAbout->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    auto btnAboutLogo = Sprite::create("SceneMain/btnSceneMainAboutLogo.png");
    btnAboutLogo->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
    btnAboutLogo->setPosition(Vec2(50, btnHeight/2+6));
    btnAbout->addContentChild(btnAboutLogo);
    listView->pushBackCustomItem(btnAbout);

    auto listener = EventListenerKeyboard::create();
    listener->onKeyReleased = CC_CALLBACK_2(SceneMain::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    if (!SocketThread::getInstance()->getSocket()->isConnected()) {
        SocketThread::getInstance()->start();
    }
    
    this->scheduleOnce(CC_SCHEDULE_SELECTOR(SceneMain::delayInit), 0.5);
    
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

void SceneMain::delayInit(float value) {
    this->checkApiVersion();
}

void SceneMain::onMenuCallback(Ref* sender) {
    auto item = dynamic_cast<Node*>(sender);
    experimental::AudioEngine::play2d("Sounds/btnmenu_click.mp3");
    switch ((SceneTags)item->getTag()) {
        case miLogoTag: {
            sdkbox::PluginGoogleAnalytics::logEvent("Button", "btnLogo", "", 0);
            Application::getInstance()->openURL("http://www.orionlab.net/?brr");
            break;
        }
            
        case miPlayTag: {
            if(!this->checkConnection())
                return;
            sdkbox::PluginGoogleAnalytics::logEvent("Button", "btnPlay", "", 1);
            SceneManager::goNext(BrrScenes::SceneLobby);
            break;
        }
            
        case miShopTag: {
            if(!this->checkConnection())
                return;
            sdkbox::PluginGoogleAnalytics::logEvent("Button", "btnShop", "", 1);
            SceneManager::goNext(BrrScenes::SceneShop);
            break;
        }
            
        case miProfileTag: {
            sdkbox::PluginGoogleAnalytics::logEvent("Button", "btnSettings", "", 1);
            SceneManager::goNext(BrrScenes::SceneProfile);
            break;
        }
            
        case miTutorialTag: {
            sdkbox::PluginGoogleAnalytics::logEvent("Button", "btnTutorial", "", 1);
            this->showTutorial();
            break;
        }
            
        case miAboutTag: {
            sdkbox::PluginGoogleAnalytics::logEvent("Button", "btnAbout", "", 1);
            SceneManager::goNext(BrrScenes::SceneAbout);
            break;
        }
            
        default:
            break;
    }
}

bool SceneMain::checkConnection() {
    Size winSize = Director::getInstance()->getVisibleSize();
    if (!SocketThread::getInstance()->getSocket()->hasInternetConnection("www.google.com", 80)) {
        this->showDialog(DialogTypeBase);
        auto dialog = dynamic_cast<DialogBase*>(this->getChildByTag(DialogTypeBase));
        dialog->setCaption(LanguageManager::getString("NetworkConnectionCaption"));
        dialog->addDoneButton(LanguageManager::getString("DialogBaseDoneButton"));
        
        
        auto lblDialogMessage = Label::createWithTTF(LanguageManager::getString("NetworkConnectionText"), GameFont, 35);
        lblDialogMessage->setDimensions(dialog->getDialogRect().size.width, dialog->getDialogRect().size.height/2);
        lblDialogMessage->setAlignment(cocos2d::TextHAlignment::CENTER);
        lblDialogMessage->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
        lblDialogMessage->setColor(Color3B(56, 37, 27));
        dialog->addChild(lblDialogMessage);
        return false;
    }
    
    if (!SocketThread::getInstance()->getSocket()->isConnected()) {
        this->showDialog(DialogTypeBase);
        auto dialog = dynamic_cast<DialogBase*>(this->getChildByTag(DialogTypeBase));
        dialog->setCaption(LanguageManager::getString("ServerMaintenanceCaption"));
        dialog->addDoneButton(LanguageManager::getString("DialogBaseDoneButton"));
        
        auto lblDialogMessage = Label::createWithTTF(LanguageManager::getString("ServerMaintenanceText"), GameFont, 35);
        lblDialogMessage->setDimensions(dialog->getDialogRect().size.width, dialog->getDialogRect().size.height/2);
        lblDialogMessage->setAlignment(cocos2d::TextHAlignment::CENTER);
        lblDialogMessage->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
        lblDialogMessage->setColor(Color3B(56, 37, 27));
        dialog->addChild(lblDialogMessage);
        return false;
    }
    
    return true;
}

void SceneMain::onDialogButtonTap(Ref* sender, int buttonIndex, std::map<std::string, std::string> userData) {
    sdkbox::PluginGoogleAnalytics::logEvent("Dialog", StringUtils::format("ButtonIndex_%d", buttonIndex), "", 0);
    this->hideDialog();
}

void SceneMain::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event) {
    if(keyCode == EventKeyboard::KeyCode::KEY_BACK) {
        Director::getInstance()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        exit(0);
#endif
    }
}

void SceneMain::showDialog(DialogTypes dialogType) {
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

void SceneMain::hideDialog() {
    this->setEnableControls(true);
    
    if (_currentDialog == DialogTypeNone) {
        return;
    }
    
    this->removeChildByTag(_currentDialog);
    
    _currentDialog = DialogTypeNone;
}

void SceneMain::setEnableControls(bool value) {
    dynamic_cast<ListView*>(this->getChildByTag(menuMainTag))->setEnabled(value);
    dynamic_cast<Button9TextShadow*>(this->getChildByTag(miLogoTag))->setEnabled(value);
}

void SceneMain::showTutorial() {
    this->showDialog(DialogTypes::DialogTypeBase);
    auto dialog = dynamic_cast<DialogBase*>(this->getChildByTag(DialogTypeBase));
    dialog->setCaption(LanguageManager::getString("MainTutorialButton"));
    dialog->addDoneButton(LanguageManager::getString("MenuDemoNextButton"));
    ListView* listView = ListView::create();
    listView->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
    listView->setDirection(ui::ScrollView::Direction::VERTICAL);
    listView->setBounceEnabled(true);
    listView->setPosition(Vec2(dialog->getDialogRect().origin.x + 40, dialog->getDialogRect().origin.y + dialog->getDialogRect().size.height / 2 + 40));
    listView->setContentSize(Size(dialog->getDialogRect().size.width - 80, 480));
    //listView->setBackGroundColorType(cocos2d::ui::Layout::BackGroundColorType::SOLID);
    //listView->setBackGroundColor(Color3B::GREEN);
    listView->setItemsMargin(10);
    dialog->addChild(listView);
    listView->pushBackCustomItem(DemoListViewItem::create(LanguageManager::getString("DialogTutorialLine1"), listView->getContentSize().width, TextHAlignment::CENTER));
    listView->pushBackCustomItem(DemoListViewItem::create(LanguageManager::getString("DialogTutorialLine2"), listView->getContentSize().width, TextHAlignment::CENTER));
    listView->pushBackCustomItem(DemoListViewItem::create(LanguageManager::getString("DialogTutorialLine3"), listView->getContentSize().width, TextHAlignment::LEFT));
    listView->pushBackCustomItem(DemoListViewItem::create(LanguageManager::getString("DialogTutorialLine4"), listView->getContentSize().width, TextHAlignment::LEFT));
    listView->pushBackCustomItem(DemoListViewItem::create(LanguageManager::getString("DialogTutorialLine5"), listView->getContentSize().width, TextHAlignment::LEFT));
    listView->pushBackCustomItem(DemoListViewItem::create(LanguageManager::getString("DialogTutorialLine6"), listView->getContentSize().width, TextHAlignment::LEFT));
    listView->pushBackCustomItem(DemoListViewItem::create(LanguageManager::getString("DialogTutorialLine7"), listView->getContentSize().width, TextHAlignment::LEFT));
    listView->pushBackCustomItem(DemoListViewItem::create(LanguageManager::getString("DialogTutorialLine8"), listView->getContentSize().width, TextHAlignment::LEFT));
    listView->pushBackCustomItem(DemoListViewItem::create(LanguageManager::getString("DialogTutorialLine9"), listView->getContentSize().width, TextHAlignment::LEFT));
    listView->pushBackCustomItem(DemoListViewItem::create(LanguageManager::getString("DialogTutorialLine10"), listView->getContentSize().width, TextHAlignment::LEFT));
    listView->pushBackCustomItem(DemoListViewItem::create(LanguageManager::getString("DialogTutorialLine11"), listView->getContentSize().width, TextHAlignment::LEFT));
    listView->pushBackCustomItem(DemoListViewItem::create(LanguageManager::getString("DialogTutorialLine12"), listView->getContentSize().width, TextHAlignment::LEFT));
    listView->pushBackCustomItem(DemoListViewItem::create(LanguageManager::getString("DialogTutorialLine13"), listView->getContentSize().width, TextHAlignment::LEFT));
    listView->pushBackCustomItem(DemoListViewItem::create(LanguageManager::getString("DialogTutorialLine14"), listView->getContentSize().width, TextHAlignment::LEFT));
    listView->pushBackCustomItem(DemoListViewItem::create(LanguageManager::getString("DialogTutorialLine15"), listView->getContentSize().width, TextHAlignment::LEFT));
    listView->pushBackCustomItem(DemoListViewItem::create(LanguageManager::getString("DialogTutorialLine16"), listView->getContentSize().width, TextHAlignment::LEFT));
    listView->pushBackCustomItem(DemoListViewItem::create(LanguageManager::getString("DialogTutorialLine17"), listView->getContentSize().width, TextHAlignment::LEFT));
    listView->pushBackCustomItem(DemoListViewItem::create(LanguageManager::getString("DialogTutorialLine18"), listView->getContentSize().width, TextHAlignment::LEFT));
    listView->pushBackCustomItem(DemoListViewItem::create(LanguageManager::getString("DialogTutorialLine19"), listView->getContentSize().width, TextHAlignment::LEFT));
    listView->pushBackCustomItem(DemoListViewItem::create(LanguageManager::getString("DialogTutorialLine20"), listView->getContentSize().width, TextHAlignment::LEFT));
    listView->pushBackCustomItem(DemoListViewItem::create(LanguageManager::getString("DialogTutorialLine21"), listView->getContentSize().width, TextHAlignment::LEFT));
    listView->pushBackCustomItem(DemoListViewItem::create(LanguageManager::getString("DialogTutorialLine22"), listView->getContentSize().width, TextHAlignment::LEFT));
    listView->pushBackCustomItem(DemoListViewItem::create(LanguageManager::getString("DialogTutorialLine23"), listView->getContentSize().width, TextHAlignment::LEFT));
    listView->pushBackCustomItem(DemoListViewItem::create(LanguageManager::getString("DialogTutorialLine24"), listView->getContentSize().width, TextHAlignment::LEFT));
    listView->pushBackCustomItem(DemoListViewItem::create(LanguageManager::getString("DialogTutorialLine25"), listView->getContentSize().width, TextHAlignment::LEFT));
}

// api call

void SceneMain::checkApiVersion() {
    MessageRequestCheckApi msg;
    msg.set_version("1.14");
    SocketThread::getInstance()->getSocket()->Send(this->wrapMessage(eProtoMessageType::cmtCheckAPIVersion, msg));
}

void SceneMain::authPlayer() {
    if (GlobalProperties::isDebug()) {
        log(">>> SceneMain L(%s) P(%s)", GlobalProperties::getLogin().c_str(), GlobalProperties::getPassword().c_str());
    }
    if (sdkbox::PluginSdkboxPlay::isSignedIn()) {
        sdkbox::PluginGoogleAnalytics::logEvent("ApiCall", "AuthPlayer_GooglePlay", "", 0);
        
        MessageRequestAuth msg;
        msg.set_authtype(eAuthType::atGooglePlay);
        msg.set_login(GlobalProperties::getLogin());
        msg.set_password(GlobalProperties::getPassword());
        SocketThread::getInstance()->getSocket()->Send(this->wrapMessage(eProtoMessageType::cmtAuth, msg));
    } else {
        sdkbox::PluginSdkboxPlay::signin();
    }
}

// api callback

void SceneMain::processProtoMessage(const eProtoMessageType messageType, const std::string &messageBody) {
    switch (messageType) {
        case eProtoMessageType::cmtCheckAPIVersion: {
            this->callbackCheckApiVersion(messageBody);
            break;
        }
            
        case eProtoMessageType::cmtAuth: {
            this->callbackAuth(messageBody);
            break;
        }
            
        default:
            break;
    }
}

void SceneMain::callbackCheckApiVersion(const std::string &source) {
    bool isApiValid = false;
    
    if(!source.empty()) {
        MessageResponseCheckApi msg;
        msg.ParseFromString(source);
        isApiValid = msg.status() == MessageResponseCheckApi_eCheckApiStatus_casSUCCESS;
    }
    
    if(!isApiValid) {
        this->hideDialog();
        this->showDialog(DialogTypeBase);
        auto dialog = dynamic_cast<DialogBase*>(this->getChildByTag(DialogTypeBase));
        dialog->setCaption(LanguageManager::getString("AppNeedUpdateCaption"));
        dialog->addDoneButton(LanguageManager::getString("DialogBaseDoneButton"));
        
        auto lblDialogMessage = Label::createWithTTF(LanguageManager::getString("AppNeedUpdateText"), GameFont, 35);
        lblDialogMessage->setDimensions(dialog->getDialogRect().size.width, dialog->getDialogRect().size.height/2);
        lblDialogMessage->setAlignment(cocos2d::TextHAlignment::CENTER);
        lblDialogMessage->setPosition(Vec2(dialog->getDialogRect().origin.x + dialog->getDialogRect().size.width/2,
                                           dialog->getDialogRect().origin.y + dialog->getDialogRect().size.height/2));
        lblDialogMessage->setColor(Color3B(56, 37, 27));
        dialog->addChild(lblDialogMessage);
    } else {
        this->authPlayer();
    }
}

void SceneMain::callbackAuth(const std::string &source) {
    sdkbox::PluginGoogleAnalytics::logEvent("ApiCallback", "callbackAuth", "", 0);
    if (source.empty())
        return;
    
    MessageResponseAuth msg;
    msg.ParseFromString(source);
    
    GlobalProperties::setPlayerId(-1);
    
    switch (msg.errortype()) {
        case MessageResponseAuth::eAuthErrorType::MessageResponseAuth_eAuthErrorType_aetNone: {
            GlobalProperties::setPlayerId(msg.playerid());
            break;
        }
            
        default:
            break;
    }
}
