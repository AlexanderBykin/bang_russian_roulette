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

#include "SceneProfile.h"
#include "SceneManager.h"
#include "LanguageManager.h"
#include "LabelShadow.h"
#include "GlobalProperties.h"
#include "PluginGoogleAnalytics/PluginGoogleAnalytics.h"
#include "audio/include/AudioEngine.h"
#include "SocketThread.h"
#include "ui/UIListView.h"
#include "ShopItem.h"
#include "MessageRequestAuth.pb.h"
#include "MessageResponseAuth.pb.h"
#include "MessageRequestShopItemList.pb.h"
#include "MessageResponseShopItemList.pb.h"
#include "MessageResponsePlayerProfile.pb.h"
#include "MessageRequestRegistration.pb.h"
#include "AuthType.pb.h"
#include "DialogAuth.h"
#include "MessageRequestForgotPassword.pb.h"
#include "Button9TextShadow.h"
#include "PluginSdkboxPlay/PluginSdkboxPlay.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace ui;

bool SceneProfile::init() {
    if(!Layer::init()) {
        return false;
    }
    
    sdkbox::PluginGoogleAnalytics::logScreen("SceneProfile");
    
    auto winSize = Director::getInstance()->getVisibleSize();
    
    auto bg = Sprite::create("SceneProfile/SceneProfileBG.png");
    bg->setPosition(Vec2(winSize.width/2, winSize.height/2));
    this->addChild(bg, 0);
    
    auto sceneCaption = LabelShadow::create(LanguageManager::getString("ProfileCaption"),
                                            GameFont,
                                            90,
                                            Color3B::WHITE,
                                            Color3B(51, 51, 51));
    sceneCaption->setAnchorPoint(Vec2::ANCHOR_MIDDLE_TOP);
    sceneCaption->setPosition(Vec2(winSize.width/2, winSize.height-10));
    sceneCaption->setShadowOffset(6);
    this->addChild(sceneCaption, 1);


    auto btnBack = Button9TextShadow::create("SceneProfile/btnSceneProfileBack.png", CC_CALLBACK_1(SceneProfile::onMenuCallback, this));
    btnBack->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
    btnBack->setTag(miBackTag);
    btnBack->setPosition(Vec2(10, winSize.height-15));
    this->addChild(btnBack, miBackTag, miBackTag);


    auto btnLogin = Button9TextShadow::create("SceneRoom/btnSceneRoomBackBG.png",
                                             Size(300, 120),
                                             LanguageManager::getString("ProfileLoginButton"),
                                             GameFont,
                                             47,
                                             Color3B(66, 158, 97),
                                             Color3B(0, 51, 14),
                                             CC_CALLBACK_1(SceneProfile::onMenuCallback, this));
    btnLogin->setTag(miLoginTag);
    btnLogin->setAnchorPoint(Vec2::ANCHOR_TOP_RIGHT);
    btnLogin->setPosition(Vec2(winSize.width-10, winSize.height-15));
    this->addChild(btnLogin, miLoginTag, miLoginTag);


    auto lblLanguage = Label::createWithTTF(LanguageManager::getString("ProfileCurrentLanguageLabel"),
                                            GameFont,
                                            50);
    lblLanguage->setAnchorPoint(Vec2::ANCHOR_MIDDLE_RIGHT);
    lblLanguage->setColor(Color3B(56, 37, 27));
    lblLanguage->setPosition(Vec2(300, 260));
    this->addChild(lblLanguage, 1);

    
    auto btnLanguageText = Label::createWithTTF(this->getSelectedLanguage(),
                                            GameFont,
                                            50);
    btnLanguageText->setColor(Color3B(255, 255, 255));
    auto miLanguage = MenuItemLabel::create(btnLanguageText, CC_CALLBACK_1(SceneProfile::onMenuCallback, this));
    miLanguage->setTag(miLanguageTag);
    auto mLanguage = Menu::create(miLanguage, nullptr);
    mLanguage->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    mLanguage->setPosition(Vec2(lblLanguage->getPosition().x+500, lblLanguage->getPosition().y));
    this->addChild(mLanguage, menuLanguageTag, menuLanguageTag);

    auto lblMusic = Label::createWithTTF(LanguageManager::getString("ProfileMusicLabel"),
                                         GameFont,
                                         50);
    lblMusic->setColor(Color3B(56, 37, 27));
    lblMusic->setAnchorPoint(Vec2::ANCHOR_MIDDLE_RIGHT);
    lblMusic->setPosition(Vec2(lblLanguage->getPosition().x, mLanguage->getPosition().y-90));
    this->addChild(lblMusic, 1);

    auto btnMusic = ControlSwitch::create(Sprite::create("Switch/SwitchMask.png"),
                                          Sprite::create("Switch/SwitchOn.png"),
                                          Sprite::create("Switch/SwitchOff.png"),
                                          Sprite::create("Switch/SwitchThumb.png"),
                                          Label::createWithTTF(LanguageManager::getString("ProfileSwitchOn"), GameFont, 36),
                                          Label::createWithTTF(LanguageManager::getString("ProfileSwitchOff"), GameFont, 36));
    btnMusic->setOn(GlobalProperties::getIsMusicOn());
    btnMusic->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    btnMusic->setPosition(Vec2(lblMusic->getPosition().x+500, lblMusic->getPosition().y));
    btnMusic->setTag(btnMusicTag);
    btnMusic->addTargetWithActionForControlEvents(this, cccontrol_selector(SceneProfile::onSwitchChanged), Control::EventType::VALUE_CHANGED);
    this->addChild(btnMusic, 1);

    auto lblEffects = Label::createWithTTF(LanguageManager::getString("ProfileEffectsLabel"),
                                           GameFont,
                                           50);
    lblEffects->setAnchorPoint(Vec2::ANCHOR_MIDDLE_RIGHT);
    lblEffects->setColor(Color3B(56, 37, 27));
    lblEffects->setPosition(Vec2(lblLanguage->getPosition().x, lblMusic->getPosition().y-110));
    this->addChild(lblEffects, 1);

    auto btnEffects = ControlSwitch::create(Sprite::create("Switch/SwitchMask.png"),
                                            Sprite::create("Switch/SwitchOn.png"),
                                            Sprite::create("Switch/SwitchOff.png"),
                                            Sprite::create("Switch/SwitchThumb.png"),
                                            Label::createWithTTF(LanguageManager::getString("ProfileSwitchOn"), GameFont, 36),
                                            Label::createWithTTF(LanguageManager::getString("ProfileSwitchOff"), GameFont, 36));
    btnEffects->setOn(GlobalProperties::getIsEffectsOn());
    btnEffects->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    btnEffects->setPosition(Vec2(lblEffects->getPosition().x+500, lblEffects->getPosition().y));
    btnEffects->setTag(btnEffectsTag);
    btnEffects->addTargetWithActionForControlEvents(this, cccontrol_selector(SceneProfile::onSwitchChanged), Control::EventType::VALUE_CHANGED);
    this->addChild(btnEffects, 1);

    
    auto listView = ListView::create();
    // set list view ex direction
    listView->setDirection(ui::ScrollView::Direction::HORIZONTAL);
    listView->setBounceEnabled(true);
    listView->setPosition(Vec2(0, winSize.height-700));
    listView->setContentSize(Size(winSize.width, 300));
    listView->setItemsMargin(20);
    //listView->setBackGroundColorType(cocos2d::ui::Layout::BackGroundColorType::SOLID);
    //listView->setBackGroundColor(Color3B::GREEN);
    this->addChild(listView, listViewTag, listViewTag);
    
    
    auto avatar = Sprite::create("SceneRoom/SceneRoomPlayerNoAvatarMan.png");
    avatar->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
    avatar->setPosition(Vec2(20, btnBack->getPosition().y - btnBack->getContentSize().height - 10));
    this->addChild(avatar);
    
    
    auto lblPlayerName = Label::createWithTTF(LanguageManager::getString("DialogPlayerInfoNameLabel"), GameFont, 35);
    lblPlayerName->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
    lblPlayerName->setPosition(Vec2(avatar->getPosition().x + avatar->getContentSize().width+40, avatar->getPosition().y));
    this->addChild(lblPlayerName, lblPlayerNameTag, lblPlayerNameTag);

    auto lblPlayerMoney = Label::createWithTTF(LanguageManager::getString("ShopMoneyLabel") + " 0", GameFont, 35);
    lblPlayerMoney->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
    lblPlayerMoney->setPosition(Vec2(lblPlayerName->getPosition().x, lblPlayerName->getPosition().y-40));
    this->addChild(lblPlayerMoney, lblPlayerMoneyTag, lblPlayerMoneyTag);
    
    auto lblPlayerWins = Label::createWithTTF(LanguageManager::getString("DialogPlayerInfoWinsLabel") + " 0", GameFont, 35);
    lblPlayerWins->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
    lblPlayerWins->setPosition(Vec2(lblPlayerMoney->getPosition().x, lblPlayerMoney->getPosition().y-40));
    this->addChild(lblPlayerWins, lblPlayerWinsTag, lblPlayerWinsTag);

    auto lblPlayerLoses = Label::createWithTTF(LanguageManager::getString("DialogPlayerInfoLosesLabel") + " 0", GameFont, 35);
    lblPlayerLoses->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
    lblPlayerLoses->setPosition(Vec2(lblPlayerWins->getPosition().x, lblPlayerWins->getPosition().y-40));
    this->addChild(lblPlayerLoses, lblPlayerLosesTag, lblPlayerLosesTag);

    auto lblPlayerRating = Label::createWithTTF(LanguageManager::getString("DialogPlayerInfoRatingLabel") + " 0", GameFont, 35);
    lblPlayerRating->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
    lblPlayerRating->setPosition(Vec2(lblPlayerLoses->getPosition().x, lblPlayerLoses->getPosition().y-40));
    this->addChild(lblPlayerRating, lblPlayerRatingTag, lblPlayerRatingTag);

    
    auto shelf = Sprite::create("SceneShop/SceneShopShelf.png");
    shelf->setPosition(Vec2(winSize.width/2, winSize.height/2-80));
    this->addChild(shelf, 1);

    
    auto listener = EventListenerKeyboard::create();
    listener->onKeyReleased = CC_CALLBACK_2(SceneProfile::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    
    this->getPlayerProfile();
    this->updateLoginButtonStatus();
    
    
    if (GlobalProperties::isDebug()) {
        auto lblTest = Label::createWithTTF("Только для тестирования\n(с) Шниперсон Александр", GameFont, 100);
        lblTest->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
        lblTest->setPosition(winSize.width/2, winSize.height/2);
        lblTest->setRotation(-45);
        lblTest->setOpacity(100);
        this->addChild(lblTest, 9999, 9999);
    }
    
    if(sdkbox::PluginSdkboxPlay::isSignedIn()) {
        GlobalProperties::setLogin(sdkbox::PluginSdkboxPlay::getPlayerId());
        GlobalProperties::setPassword("GOOGLEPLAY");
        this->authPlayer();
    }

    return true;
}

const std::string SceneProfile::getSelectedLanguage() {
    auto res = StringUtils::format("ProfileLanguage_%d", (int)GlobalProperties::getCurrentLanguage()).c_str();
    return LanguageManager::getString(res);
}

void SceneProfile::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event) {
    if(keyCode == EventKeyboard::KeyCode::KEY_BACK) {
        this->onMenuCallback(this->getChildByTag(miBackTag));
    }
}

void SceneProfile::onMenuCallback(cocos2d::Ref *ref) {
    experimental::AudioEngine::play2d("Sounds/btnmenu_click.mp3");
    switch (dynamic_cast<Node*>(ref)->getTag()) {
        case miBackTag: {
            sdkbox::PluginGoogleAnalytics::logEvent("Button", "btnBack", "", 0);
            SceneManager::goBack(BrrScenes::SceneMain);
            break;
        }
            
        case miLanguageTag: {
            if (GlobalProperties::getCurrentLanguage() == LanguageType::ENGLISH) {
                GlobalProperties::setCurrentLanguage(LanguageType::RUSSIAN);
            } else {
                GlobalProperties::setCurrentLanguage(LanguageType::ENGLISH);
            }
            sdkbox::PluginGoogleAnalytics::logEvent("Button", "btnChangeLanguage", GlobalProperties::getCurrentLanguageAsString(), 1);
            dynamic_cast<MenuItemLabel*>(ref)->setString(this->getSelectedLanguage());
            LanguageManager::initLanguage();
            break;
        }
            
        case miLoginTag: {
            if(GlobalProperties::getLogin().empty() || GlobalProperties::getPassword().empty()) {
                // this->showDialog(DialogTypeAuth);
                if(sdkbox::PluginSdkboxPlay::isSignedIn()) {
                    GlobalProperties::setLogin(sdkbox::PluginSdkboxPlay::getPlayerId());
                    GlobalProperties::setPassword("GOOGLEPLAY");
                    this->authPlayer();
                } else {
                    sdkbox::PluginSdkboxPlay::signin();
                    onMenuCallback(ref); // can be a infinite loop in case of error
                }
            } else {
                GlobalProperties::setLogin("");
                GlobalProperties::setPassword("");
                GlobalProperties::setPlayerId(-1);
                dynamic_cast<ListView*>(this->getChildByTag(listViewTag))->getItems().clear();
            }
            this->updateLoginButtonStatus();
            break;
        }
            
        default:
            break;
    }
}

void SceneProfile::onSwitchChanged(cocos2d::Ref *sender, cocos2d::extension::Control::EventType controlEvent) {
    auto btnSwitch = dynamic_cast<ControlSwitch*>(sender);
    experimental::AudioEngine::play2d("Sounds/switch_click.mp3");
    switch (btnSwitch->getTag()) {
        case btnMusicTag:
            sdkbox::PluginGoogleAnalytics::logEvent("Button", "btnMusic", "", 0);
            GlobalProperties::setIsMusicOn(btnSwitch->isOn());
            break;

        case btnEffectsTag:
            sdkbox::PluginGoogleAnalytics::logEvent("Button", "btnEffects", "", 0);
            GlobalProperties::setIsEffectsOn(btnSwitch->isOn());
            break;
            
        default:
            break;
    }
}

void SceneProfile::showDialog(DialogTypes dialogType) {
    this->hideDialog();
    
    if (dialogType == DialogTypes::DialogTypeNone) {
        return;
    }
    
    this->setEnableControls(false);
    
    switch (dialogType) {
        case DialogTypes::DialogTypeAuth: {
            auto dialog = DialogAuth::create(DialogAuth::DialogAuthMode::Auth);
            dialog->setDelegate(this);
            this->addChild(dialog, dialogType, dialogType);
            break;
        }
            
        case DialogTypes::DialogTypeRegister: {
            auto dialog = DialogAuth::create(DialogAuth::DialogAuthMode::Register);
            dialog->setDelegate(this);
            this->addChild(dialog, dialogType, dialogType);
            break;
        }
            
        case DialogTypes::DialogTypeForgotPassword: {
            auto dialog = DialogAuth::create(DialogAuth::DialogAuthMode::ForgotPassword);
            dialog->setDelegate(this);
            this->addChild(dialog, dialogType, dialogType);
            break;
        }
            
        case DialogTypes::DialogTypeVerifyEmail: {
            auto dialog = DialogAuth::create(DialogAuth::DialogAuthMode::VerifyEmail);
            dialog->setDelegate(this);
            this->addChild(dialog, dialogType, dialogType);
            break;
        }
            
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

void SceneProfile::hideDialog() {
    this->setEnableControls(true);
    
    if (_currentDialog == DialogTypes::DialogTypeNone) {
        return;
    }
    
    sdkbox::PluginGoogleAnalytics::logEvent("HideDialog", "Base", "", 0);
    
    this->removeChildByTag(_currentDialog);
    
    _currentDialog = DialogTypes::DialogTypeNone;
}

void SceneProfile::onDialogButtonTap(Ref* sender, int buttonIndex, std::map<std::string, std::string> userData) {
    sdkbox::PluginGoogleAnalytics::logEvent("Dialog", StringUtils::format("ButtonIndex_%d", buttonIndex), "", 0);
    DialogTypes curDialog = _currentDialog;
    this->hideDialog();
    
    switch (curDialog) {
        case DialogTypeAuth: {
            switch (buttonIndex) {
                case DialogBase::DialogBaseButtons::btnDoneTag: {
                    if(userData.at("email").empty() || userData.at("password").empty()) {
                        this->showMessageDialog(LanguageManager::getString("DialogAuthCaption"), LanguageManager::getString("DialogAuthNotAllRequiredFields"));
                        return;
                    }
                    GlobalProperties::setLogin(userData.at("email"));
                    GlobalProperties::setPassword(userData.at("password"));
                    this->authPlayer();
                    break;
                }
                    
                case DialogBase::DialogBaseButtons::btnDoneTag+1: {
                    this->showDialog(DialogTypeRegister);
                    break;
                }
                    
                default:
                    break;
            }
            break;
        }
            
        case DialogTypeRegister: {
            switch (buttonIndex) {
                case DialogBase::DialogBaseButtons::btnDoneTag: {
                    if(userData.at("email").empty() || userData.at("password").empty() || userData.at("name").empty()) {
                        this->showMessageDialog(LanguageManager::getString("DialogAuthCaption"), LanguageManager::getString("DialogAuthNotAllRequiredFields"));
                        return;
                    }
                    GlobalProperties::setLogin(userData.at("email"));
                    GlobalProperties::setPassword(userData.at("password"));
                    this->registerPlayer(GlobalProperties::getLogin(), GlobalProperties::getPassword(), userData.at("name"));
                    break;
                }
                    
                case DialogBase::DialogBaseButtons::btnDoneTag+1: {
                    this->showDialog(DialogTypeForgotPassword);
                    break;
                }
                    
                default:
                    break;
            }
            break;
        }

        case DialogTypeForgotPassword: {
            switch (buttonIndex) {
                case DialogBase::DialogBaseButtons::btnDoneTag: {
                    if(userData.at("email").empty()) {
                        this->showMessageDialog(LanguageManager::getString("DialogAuthCaption"), LanguageManager::getString("DialogAuthNotAllRequiredFields"));
                        return;
                    }
                    this->forgotPassword(userData.at("email"));
                    break;
                }
                    
                default:
                    break;
            }
            break;
        }
            
        case DialogTypeVerifyEmail: {
            if (buttonIndex == DialogBase::DialogBaseButtons::btnDoneTag) {
                this->verifyEmail(userData.at("email"), userData.at("verify"));
            }
            break;
        }
            
        default:
            break;
    }
}

void SceneProfile::showMessageDialog(const std::string &caption, const std::string &message) {
    this->showDialog(DialogTypes::DialogTypeBase);
    auto dialog = dynamic_cast<DialogBase*>(this->getChildByTag(DialogTypeBase));
    dialog->setCaption(caption);
    dialog->addDoneButton(LanguageManager::getString("DialogBaseDoneButton"));
    
    auto lblDialogMessage = Label::createWithTTF(message, GameFont, 35);
    lblDialogMessage->setDimensions(dialog->getDialogRect().size.width, dialog->getDialogRect().size.height/2);
    lblDialogMessage->setAlignment(cocos2d::TextHAlignment::CENTER);
    lblDialogMessage->setPosition(Vec2(dialog->getDialogRect().origin.x + dialog->getDialogRect().size.width/2,
                                       dialog->getDialogRect().origin.y + dialog->getDialogRect().size.height/2));
    lblDialogMessage->setColor(Color3B(56, 37, 27));
    dialog->addChild(lblDialogMessage);
}

void SceneProfile::setEnableControls(bool value) {
    dynamic_cast<Button9TextShadow*>(this->getChildByTag(miBackTag))->setEnabled(value);
    dynamic_cast<ListView*>(this->getChildByTag(listViewTag))->setEnabled(value);
    dynamic_cast<Menu*>(this->getChildByTag(menuLanguageTag))->setEnabled(value);
    dynamic_cast<Button9TextShadow*>(this->getChildByTag(miLoginTag))->setEnabled(value);
    dynamic_cast<ControlSwitch*>(this->getChildByTag(btnMusicTag))->setEnabled(value);
    dynamic_cast<ControlSwitch*>(this->getChildByTag(btnEffectsTag))->setEnabled(value);
}

void SceneProfile::updateLoginButtonStatus() {
    auto btn = dynamic_cast<Button9TextShadow*>(this->getChildByTag(miLoginTag));
    if(GlobalProperties::getLogin().empty() || GlobalProperties::getPassword().empty() || GlobalProperties::getPlayerId() <= 0) {
        btn->setText(LanguageManager::getString("ProfileLoginButton"));
    } else {
        btn->setText(LanguageManager::getString("ProfileLogOutButton"));
    }
}

// api calls

void SceneProfile::getPlayerProfile() {
    SocketThread::getInstance()->getSocket()->Send(this->wrapMessage(eProtoMessageType::cmtGetPlayerProfile));
}

void SceneProfile::authPlayer() {
    if (GlobalProperties::isDebug()) {
        log(">>> SceneProfile L(%s) P(%s)", GlobalProperties::getLogin().c_str(), GlobalProperties::getPassword().c_str());
    }
    if(GlobalProperties::getLogin().empty() || GlobalProperties::getPassword().empty()) {
        return;
    }
    
    sdkbox::PluginGoogleAnalytics::logEvent("ApiCall", "AuthPlayer_GooglePlay", "", 0);
    
    MessageRequestAuth msg;
    msg.set_authtype(eAuthType::atGooglePlay);
    msg.set_login(GlobalProperties::getLogin());
    msg.set_password(GlobalProperties::getPassword());
    SocketThread::getInstance()->getSocket()->Send(this->wrapMessage(eProtoMessageType::cmtAuth, msg));
}

void SceneProfile::verifyEmail(const std::string &email, const std::string &verifyCode) {
    if(email.empty() || verifyCode.empty()) {
        return;
    }
    
    sdkbox::PluginGoogleAnalytics::logEvent("ApiCall", "AuthPlayer_Email", "", 0);
    
    MessageRequestAuth msg;
    msg.set_authtype(eAuthType::atEmail);
    msg.set_login(email);
    msg.set_verifycode(verifyCode);
    SocketThread::getInstance()->getSocket()->Send(this->wrapMessage(eProtoMessageType::cmtAuth, msg));
}

void SceneProfile::registerPlayer(const std::string &login, const std::string &password, const std::string &name) {
    if (GlobalProperties::isDebug()) {
        log(">>> SceneProfile L(%s) P(%s) N(%s)", login.c_str(), password.c_str(), name.c_str());
    }
    
    if(login.empty() || password.empty() || name.empty()) {
        return;
    }
    
    sdkbox::PluginGoogleAnalytics::logEvent("ApiCall", "AuthPlayer_GooglePlay", "", 0);
   
    MessageRequestRegistration msg;
    msg.set_authtype(eAuthType::atGooglePlay);
    msg.set_login(login);
    msg.set_password(password);
    msg.set_displayname(name);
    SocketThread::getInstance()->getSocket()->Send(this->wrapMessage(eProtoMessageType::cmtRegister, msg));
}

void SceneProfile::forgotPassword(const std::string &email) {
    if(email.empty()) {
        return;
    }
    
    sdkbox::PluginGoogleAnalytics::logEvent("ApiCall", "ForgotPassword", "", 0);
    
    MessageRequestForgotPassword msg;
    msg.set_email(email);
    SocketThread::getInstance()->getSocket()->Send(this->wrapMessage(eProtoMessageType::cmtForgotPassword, msg));
}

void SceneProfile::getShopItems() {
    sdkbox::PluginGoogleAnalytics::logEvent("ApiCall", "getShopItems", "", 0);
    MessageRequestShopItemList msg;
    msg.set_shopitemtype(MessageRequestShopItemList_eShopItemType::MessageRequestShopItemList_eShopItemType_sitINVENTORYWITHSHOP);
    msg.set_lang(GlobalProperties::getCurrentLanguageAsString());
    SocketThread::getInstance()->getSocket()->Send(this->wrapMessage(eProtoMessageType::cmtGetShopItems, msg));
}


// api callbacks

void SceneProfile::processProtoMessage(const eProtoMessageType messageType, const std::string &messageBody) {
    switch (messageType) {
        case eProtoMessageType::cmtNeedAuth: {
            this->callbackNeedAuth(messageBody);
            break;
        }
            
        case eProtoMessageType::cmtAuth: {
            this->callbackAuth(messageBody);
            break;
        }
            
        case eProtoMessageType::cmtGetPlayerProfile: {
            this->callbackGetPlayerProfile(messageBody);
            break;
        }
            
        case eProtoMessageType::cmtGetShopItems: {
            this->callbackGetShopItems(messageBody);
            break;
        }
            
        default:
            break;
    }
}

void SceneProfile::callbackNeedAuth(const std::string &source) {
    sdkbox::PluginGoogleAnalytics::logEvent("ApiCallback", "callbackNeedAuth", "", 0);
    
    this->authPlayer();
}

void SceneProfile::callbackAuth(const std::string &source) {
    if (source.empty())
        return;
    
    sdkbox::PluginGoogleAnalytics::logEvent("ApiCallback", "callbackAuth", "", 0);

    MessageResponseAuth msg;
    msg.ParseFromString(source);

    GlobalProperties::setPlayerId(-1);

    switch (msg.errortype()) {
        case MessageResponseAuth::eAuthErrorType::MessageResponseAuth_eAuthErrorType_aetNone: {
            GlobalProperties::setPlayerId(msg.playerid());
            if (GlobalProperties::getPlayerId() > 0) {
                this->getPlayerProfile();
            }
            break;
        }

        case MessageResponseAuth::eAuthErrorType::MessageResponseAuth_eAuthErrorType_aetBadUID: {
            //this->showMessageDialog(LanguageManager::getString("DialogAuthCaption"), LanguageManager::getString("DialogAuthBadUID"));
            this->registerPlayer(GlobalProperties::getLogin(), GlobalProperties::getPassword(), sdkbox::PluginSdkboxPlay::getPlayerAccountField("display_name"));
            break;
        }

        /*case MessageResponseAuth::eAuthErrorType::MessageResponseAuth_eAuthErrorType_aetBadVerify: {
            this->showMessageDialog(LanguageManager::getString("DialogAuthCaption"), LanguageManager::getString("DialogAuthBadVerify"));
            break;
        }
            
        case MessageResponseAuth::eAuthErrorType::MessageResponseAuth_eAuthErrorType_aetBlocked: {
            this->showMessageDialog(LanguageManager::getString("DialogAuthCaption"), LanguageManager::getString("DialogAuthBlocked"));
            break;
        }
            
        case MessageResponseAuth::eAuthErrorType::MessageResponseAuth_eAuthErrorType_aetNeedVerify: {
            this->showDialog(DialogTypeVerifyEmail);
            break;
        }
            
        case MessageResponseAuth::eAuthErrorType::MessageResponseAuth_eAuthErrorType_aetNoPassOrVerify: {
            this->showMessageDialog(LanguageManager::getString("DialogAuthCaption"), LanguageManager::getString("DialogAuthNoPassOrVerify"));
            break;
        }
            
        case MessageResponseAuth::eAuthErrorType::MessageResponseAuth_eAuthErrorType_aetNotAllRequiredFields: {
            this->showMessageDialog(LanguageManager::getString("DialogAuthCaption"), LanguageManager::getString("DialogAuthNotAllRequiredFields"));
            break;
        }
            
        case MessageResponseAuth::eAuthErrorType::MessageResponseAuth_eAuthErrorType_aetUsedUID: {
            this->showMessageDialog(LanguageManager::getString("DialogAuthCaption"), LanguageManager::getString("DialogAuthUsedUID"));
            break;
        }
            
        case MessageResponseAuth::eAuthErrorType::MessageResponseAuth_eAuthErrorType_aetPasswordChanged: {
            this->showMessageDialog(LanguageManager::getString("DialogAuthCaption"), LanguageManager::getString("DialogAuthPasswordChanged"));
            break;
        }*/
            
        default:
            break;
    }
    
    this->updateLoginButtonStatus();
}

void SceneProfile::callbackGetShopItems(const std::string &source) {
    if (source.empty()) {
        return;
    }
    
    sdkbox::PluginGoogleAnalytics::logEvent("ApiCallback", "callbackGetShopItems", "", 0);
    
    MessageResponseShopItemList msg;
    msg.ParseFromString(source);
    
    auto listView = dynamic_cast<ListView*>(this->getChildByTag(listViewTag));
    listView->getItems().clear();
    
    for(auto item : msg.shopitemlist()) {
        auto shopItem = ShopItem::create("ShopItem/" + item.imagename(), item.name(), item.description(), item.amount(), 0);
        shopItem->setAmountVisible(true);
        listView->pushBackCustomItem(shopItem);
    }
}

void SceneProfile::callbackGetPlayerProfile(const std::string &source) {
    if (source.empty()) {
        return;
    }
    
    sdkbox::PluginGoogleAnalytics::logEvent("ApiCallback", "callbackGetPlayerProfile", "", 0);
    
    MessageResponsePlayerProfile msg;
    msg.ParseFromString(source);
    
    auto lblPlayerName = dynamic_cast<Label*>(this->getChildByTag(lblPlayerNameTag));
    auto lblPlayerMoney = dynamic_cast<Label*>(this->getChildByTag(lblPlayerMoneyTag));
    auto lblPlayerWins = dynamic_cast<Label*>(this->getChildByTag(lblPlayerWinsTag));
    auto lblPlayerLoses = dynamic_cast<Label*>(this->getChildByTag(lblPlayerLosesTag));
    auto lblPlayerRating = dynamic_cast<Label*>(this->getChildByTag(lblPlayerRatingTag));
    
    lblPlayerName->setString(StringUtils::format("%s %s", LanguageManager::getString("DialogPlayerInfoNameLabel").c_str(), msg.playername().c_str()));
    lblPlayerMoney->setString(StringUtils::format("%s %lli", LanguageManager::getString("ShopMoneyLabel").c_str(), msg.playermoney()));
    lblPlayerWins->setString(StringUtils::format("%s %i", LanguageManager::getString("DialogPlayerInfoWinsLabel").c_str(), msg.playerwins()));
    lblPlayerLoses->setString(StringUtils::format("%s %i", LanguageManager::getString("DialogPlayerInfoLosesLabel").c_str(), msg.playerloses()));
    lblPlayerRating->setString(StringUtils::format("%s %i", LanguageManager::getString("DialogPlayerInfoRatingLabel").c_str(), msg.playerrating()));

    this->getShopItems();
}

// SdkboxPlay

