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

#include "DialogAuth.h"
#include "LanguageManager.h"
#include "GlobalProperties.h"

DialogAuth* DialogAuth::create(const DialogAuth::DialogAuthMode &mode) {
    DialogAuth *node = new (std::nothrow) DialogAuth();
    if(node && node->init(mode)) {
        node->autorelease();
        return node;
    }
    CC_SAFE_DELETE(node);
    return nullptr;
}

bool DialogAuth::init(const DialogAuthMode &mode) {
    if(!DialogBase::init()) {
        return false;
    }
    
    _dialogMode = mode;
    
    switch(_dialogMode) {
        case DialogAuthMode::Auth: {
            this->setCaption(LanguageManager::getString("DialogAuthCaption"));
            auto lblEmail = Label::createWithTTF(LanguageManager::getString("DialogAuthEmailLabel"), GameFont, 40);
            lblEmail->setAnchorPoint(Vec2::ANCHOR_MIDDLE_RIGHT);
            lblEmail->setPosition(Vec2(this->getDialogRect().origin.x + 250,
                                       this->getDialogRect().origin.y + this->getDialogRect().size.height /2 + 140));
            this->addChild(lblEmail);
            
            auto ebEmail = EditBox::create(Size(900, 90), "Dialog/DialogBaseTextField.png");
            ebEmail->setFontName(GameFont);
            ebEmail->setFontColor(Color3B::BLACK);
            ebEmail->setFontSize(35);
            ebEmail->setInputMode(EditBox::InputMode::EMAIL_ADDRESS);
            ebEmail->setInputFlag(cocos2d::ui::EditBox::InputFlag::SENSITIVE);
            ebEmail->setReturnType(ui::EditBox::KeyboardReturnType::DONE);
            ebEmail->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
            ebEmail->setPosition(Vec2(lblEmail->getPosition().x + 20, lblEmail->getPosition().y));
            ebEmail->setPlaceHolder(LanguageManager::getString("DialogAuthEnterTextLabel").c_str());
            ebEmail->setPlaceholderFontColor(Color3B::WHITE);
            ebEmail->setMaxLength(32);
            ebEmail->setDelegate(this);
            ebEmail->setText(GlobalProperties::getLogin().c_str());
            this->addChild(ebEmail, edEmailTag, edEmailTag);
            
            auto lblPassword = Label::createWithTTF(LanguageManager::getString("DialogAuthPasswordLabel"), GameFont, 40);
            lblPassword->setAnchorPoint(Vec2::ANCHOR_MIDDLE_RIGHT);
            lblPassword->setPosition(Vec2(lblEmail->getPosition().x, lblEmail->getPosition().y - 140));
            this->addChild(lblPassword);
            
            auto ebPassword = EditBox::create(Size(900, 90), "Dialog/DialogBaseTextField.png");
            ebPassword->setFontName(GameFont);
            ebPassword->setFontColor(Color3B::BLACK);
            ebPassword->setFontSize(35);
            ebPassword->setInputMode(EditBox::InputMode::SINGLE_LINE);
            ebPassword->setInputFlag(cocos2d::ui::EditBox::InputFlag::PASSWORD);
            ebPassword->setReturnType(ui::EditBox::KeyboardReturnType::DONE);
            ebPassword->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
            ebPassword->setPosition(Vec2(lblPassword->getPosition().x + 20, lblPassword->getPosition().y));
            ebPassword->setPlaceHolder(LanguageManager::getString("DialogAuthEnterTextLabel").c_str());
            ebPassword->setPlaceholderFontColor(Color3B::WHITE);
            ebPassword->setMaxLength(32);
            ebPassword->setDelegate(this);
            this->addChild(ebPassword, edPasswordTag, edPasswordTag);

            this->addCustomButton(LanguageManager::getString("DialogAuthRegisterButton"),
                                  Vec2(this->getDialogRect().origin.x + this->getDialogRect().size.width/2, this->getDialogRect().origin.y + 20),
                                  DialogBaseButtons::btnDoneTag+1);
            break;
        }
            
        case DialogAuthMode::Register: {
            this->setCaption(LanguageManager::getString("DialogAuthRegisterCaption"));
            auto lblEmail = Label::createWithTTF(LanguageManager::getString("DialogAuthEmailLabel"), GameFont, 40);
            lblEmail->setAnchorPoint(Vec2::ANCHOR_MIDDLE_RIGHT);
            lblEmail->setPosition(Vec2(this->getDialogRect().origin.x + 250,
                                       this->getDialogRect().origin.y + this->getDialogRect().size.height /2 + 180));
            this->addChild(lblEmail);
            
            auto ebEmail = EditBox::create(Size(900, 90), "Dialog/DialogBaseTextField.png");
            ebEmail->setFontName(GameFont);
            ebEmail->setFontColor(Color3B::BLACK);
            ebEmail->setFontSize(35);
            ebEmail->setInputMode(EditBox::InputMode::EMAIL_ADDRESS);
            ebEmail->setInputFlag(cocos2d::ui::EditBox::InputFlag::SENSITIVE);
            ebEmail->setReturnType(ui::EditBox::KeyboardReturnType::DONE);
            ebEmail->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
            ebEmail->setPosition(Vec2(lblEmail->getPosition().x + 20, lblEmail->getPosition().y));
            ebEmail->setPlaceHolder(LanguageManager::getString("DialogAuthEnterTextLabel").c_str());
            ebEmail->setPlaceholderFontColor(Color3B::WHITE);
            ebEmail->setMaxLength(32);
            ebEmail->setDelegate(this);
            this->addChild(ebEmail, edEmailTag, edEmailTag);
            
            auto lblPassword = Label::createWithTTF(LanguageManager::getString("DialogAuthPasswordLabel"), GameFont, 40);
            lblPassword->setAnchorPoint(Vec2::ANCHOR_MIDDLE_RIGHT);
            lblPassword->setPosition(Vec2(lblEmail->getPosition().x, lblEmail->getPosition().y - 140));
            this->addChild(lblPassword);
            
            auto ebPassword = EditBox::create(Size(900, 90), "Dialog/DialogBaseTextField.png");
            ebPassword->setFontName(GameFont);
            ebPassword->setFontColor(Color3B::BLACK);
            ebPassword->setFontSize(35);
            ebPassword->setInputMode(EditBox::InputMode::SINGLE_LINE);
            ebPassword->setInputFlag(cocos2d::ui::EditBox::InputFlag::PASSWORD);
            ebPassword->setReturnType(ui::EditBox::KeyboardReturnType::DONE);
            ebPassword->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
            ebPassword->setPosition(Vec2(lblPassword->getPosition().x + 20, lblPassword->getPosition().y));
            ebPassword->setPlaceHolder(LanguageManager::getString("DialogAuthEnterTextLabel").c_str());
            ebPassword->setPlaceholderFontColor(Color3B::WHITE);
            ebPassword->setMaxLength(32);
            ebPassword->setDelegate(this);
            this->addChild(ebPassword, edPasswordTag, edPasswordTag);
            
            auto lblName = Label::createWithTTF(LanguageManager::getString("DialogAuthNameLabel"), GameFont, 40);
            lblName->setAnchorPoint(Vec2::ANCHOR_MIDDLE_RIGHT);
            lblName->setPosition(Vec2(lblPassword->getPosition().x, lblPassword->getPosition().y - 140));
            this->addChild(lblName);
            
            auto ebName = EditBox::create(Size(900, 90), "Dialog/DialogBaseTextField.png");
            ebName->setFontName(GameFont);
            ebName->setFontColor(Color3B::BLACK);
            ebName->setFontSize(35);
            ebName->setInputMode(EditBox::InputMode::SINGLE_LINE);
            ebName->setInputFlag(cocos2d::ui::EditBox::InputFlag::SENSITIVE);
            ebName->setReturnType(ui::EditBox::KeyboardReturnType::DONE);
            ebName->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
            ebName->setPosition(Vec2(lblName->getPosition().x + 20, lblName->getPosition().y));
            ebName->setPlaceHolder(LanguageManager::getString("DialogAuthEnterTextLabel").c_str());
            ebName->setPlaceholderFontColor(Color3B::WHITE);
            ebName->setMaxLength(32);
            ebName->setDelegate(this);
            this->addChild(ebName, edNameTag, edNameTag);

            this->addCustomButton(LanguageManager::getString("DialogAuthForgotButton"),
                                  Vec2(this->getDialogRect().origin.x + this->getDialogRect().size.width/2, this->getDialogRect().origin.y + 20),
                                  DialogBaseButtons::btnDoneTag+1);
            break;
        }
            
        case DialogAuthMode::ForgotPassword: {
            this->setCaption(LanguageManager::getString("DialogAuthForgotCaption"));
            auto lblEmail = Label::createWithTTF(LanguageManager::getString("DialogAuthEmailLabel"), GameFont, 40);
            lblEmail->setAnchorPoint(Vec2::ANCHOR_MIDDLE_RIGHT);
            lblEmail->setPosition(Vec2(this->getDialogRect().origin.x + 250,
                                       this->getDialogRect().origin.y + this->getDialogRect().size.height /2));
            this->addChild(lblEmail);
            
            auto ebEmail = EditBox::create(Size(900, 90), "Dialog/DialogBaseTextField.png");
            ebEmail->setFontName(GameFont);
            ebEmail->setFontColor(Color3B::BLACK);
            ebEmail->setFontSize(35);
            ebEmail->setInputMode(EditBox::InputMode::EMAIL_ADDRESS);
            ebEmail->setInputFlag(cocos2d::ui::EditBox::InputFlag::SENSITIVE);
            ebEmail->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
            ebEmail->setPosition(Vec2(lblEmail->getPosition().x + 20, lblEmail->getPosition().y));
            ebEmail->setPlaceHolder(LanguageManager::getString("DialogAuthEnterTextLabel").c_str());
            ebEmail->setPlaceholderFontColor(Color3B::WHITE);
            ebEmail->setMaxLength(32);
            ebEmail->setReturnType(ui::EditBox::KeyboardReturnType::DONE);
            ebEmail->setDelegate(this);
            ebEmail->setText(GlobalProperties::getLogin().c_str());
            this->addChild(ebEmail, edEmailTag, edEmailTag);
            break;
        }
            
        case DialogAuthMode::VerifyEmail: {
            this->setCaption(LanguageManager::getString("DialogAuthVerifyCaption"));
            auto lblEmail = Label::createWithTTF(LanguageManager::getString("DialogAuthEmailLabel"), GameFont, 40);
            lblEmail->setAnchorPoint(Vec2::ANCHOR_MIDDLE_RIGHT);
            lblEmail->setPosition(Vec2(this->getDialogRect().origin.x + 250,
                                       this->getDialogRect().origin.y + this->getDialogRect().size.height /2 + 140));
            this->addChild(lblEmail);
            
            auto ebEmail = EditBox::create(Size(900, 90), "Dialog/DialogBaseTextField.png");
            ebEmail->setFontName(GameFont);
            ebEmail->setFontColor(Color3B::BLACK);
            ebEmail->setFontSize(35);
            ebEmail->setInputMode(EditBox::InputMode::EMAIL_ADDRESS);
            ebEmail->setInputFlag(cocos2d::ui::EditBox::InputFlag::SENSITIVE);
            ebEmail->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
            ebEmail->setPosition(Vec2(lblEmail->getPosition().x + 20, lblEmail->getPosition().y));
            ebEmail->setPlaceHolder(LanguageManager::getString("DialogAuthEnterTextLabel").c_str());
            ebEmail->setPlaceholderFontColor(Color3B::WHITE);
            ebEmail->setMaxLength(32);
            ebEmail->setReturnType(ui::EditBox::KeyboardReturnType::DONE);
            ebEmail->setDelegate(this);
            ebEmail->setText(GlobalProperties::getLogin().c_str());
            this->addChild(ebEmail, edEmailTag, edEmailTag);
            
            auto lblVerify = Label::createWithTTF(LanguageManager::getString("DialogAuthVerifyLabel"), GameFont, 40);
            lblVerify->setAnchorPoint(Vec2::ANCHOR_MIDDLE_RIGHT);
            lblVerify->setPosition(Vec2(lblEmail->getPosition().x, lblEmail->getPosition().y - 140));
            this->addChild(lblVerify);
            
            auto ebVerify = EditBox::create(Size(900, 90), "Dialog/DialogBaseTextField.png");
            ebVerify->setFontName(GameFont);
            ebVerify->setFontColor(Color3B::BLACK);
            ebVerify->setFontSize(35);
            ebVerify->setInputMode(EditBox::InputMode::SINGLE_LINE);
            ebVerify->setInputFlag(cocos2d::ui::EditBox::InputFlag::SENSITIVE);
            ebVerify->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
            ebVerify->setPosition(Vec2(lblVerify->getPosition().x + 20, lblVerify->getPosition().y));
            ebVerify->setPlaceHolder(LanguageManager::getString("DialogAuthEnterTextLabel").c_str());
            ebVerify->setPlaceholderFontColor(Color3B::WHITE);
            ebVerify->setMaxLength(32);
            ebVerify->setReturnType(ui::EditBox::KeyboardReturnType::DONE);
            ebVerify->setDelegate(this);
            this->addChild(ebVerify, edVerifyTag, edVerifyTag);
            break;
        }
    }
    
    this->addCancelButton(LanguageManager::getString("DialogAuthBackButton"));
    this->addDoneButton(LanguageManager::getString("DialogAuthNextButton"), CC_CALLBACK_1(DialogAuth::onMenuCallback, this));
    
    return true;
}

void DialogAuth::onMenuCallback(cocos2d::Ref *sender) {
    std::string email = "";
    std::string password = "";
    std::string name = "";
    std::string verify = "";

    if(auto ctrl = dynamic_cast<EditBox*>(this->getChildByTag(edEmailTag))) {
        email = ctrl->getText();
    }
    
    if(auto ctrl = dynamic_cast<EditBox*>(this->getChildByTag(edPasswordTag))) {
        password = ctrl->getText();
    }

    if(auto ctrl = dynamic_cast<EditBox*>(this->getChildByTag(edNameTag))) {
        name = ctrl->getText();
    }

    if(auto ctrl = dynamic_cast<EditBox*>(this->getChildByTag(edVerifyTag))) {
        verify = ctrl->getText();
    }
    
    if(_delegate) {
        switch (_dialogMode) {
            case DialogAuthMode::Auth: {
                _delegate->onDialogButtonTap(this, DialogBase::DialogBaseButtons::btnDoneTag,
                                             {
                                                 {"email", email},
                                                 {"password", password}
                                             });
                break;
            }
                
            case DialogAuthMode::Register: {
                _delegate->onDialogButtonTap(this, DialogBase::DialogBaseButtons::btnDoneTag,
                                             {
                                                 {"email", email},
                                                 {"password", password},
                                                 {"name", name}
                                             });
                break;
            }
                
            case DialogAuthMode::ForgotPassword: {
                _delegate->onDialogButtonTap(this, DialogBase::DialogBaseButtons::btnDoneTag,
                                             {
                                                 {"email", email}
                                             });
                break;
            }
                
            case DialogAuthMode::VerifyEmail: {
                _delegate->onDialogButtonTap(this, DialogBase::DialogBaseButtons::btnDoneTag,
                                             {
                                                 {"email", email},
                                                 {"verify", verify}
                                             });
                break;
            }
                
            default:
                break;
        }
    }
}

void DialogAuth::editBoxEditingDidBegin(EditBox* editBox) {
}

void DialogAuth::editBoxEditingDidEnd(EditBox* editBox) {
}

void DialogAuth::editBoxTextChanged(EditBox* editBox, const std::string& text) {
}

void DialogAuth::editBoxReturn(EditBox* editBox) {
}

