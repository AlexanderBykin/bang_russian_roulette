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

#include "DialogPlayerInfo.h"
#include "LanguageManager.h"
#include "SocketThread.h"
#include "MessageRequestPlayerInfo.pb.h"
#include "ProtoMessageType.pb.h"
#include "MessageResponsePlayerInfo.pb.h"
#include "GlobalProperties.h"

USING_NS_CC;

DialogPlayerInfo* DialogPlayerInfo::create(long long playerId) {
    DialogPlayerInfo *node = new (std::nothrow) DialogPlayerInfo();
    if(node && node->init(playerId)) {
        node->autorelease();
        return node;
    }
    CC_SAFE_DELETE(node);
    return nullptr;
}

bool DialogPlayerInfo::init(long long playerId) {
    if(!DialogBase::init()) {
        return false;
    }
    
    this->setCaption(LanguageManager::getString("DialogPlayerInfoCaption"));
    
    
    auto lblName = Label::createWithTTF(LanguageManager::getString("DialogPlayerInfoNameLabel"), GameFont, 34);
    lblName->setColor(Color3B(56, 37, 27));
    lblName->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
    lblName->setPosition(Vec2(_dialogRect.origin.x + 20, _dialogRect.origin.y + _dialogRect.size.height - 120));
    this->addChild(lblName, txtNameTag, txtNameTag);
    
    auto lblWins = Label::createWithTTF(LanguageManager::getString("DialogPlayerInfoWinsLabel"), GameFont, 34);
    lblWins->setColor(Color3B(56, 37, 27));
    lblWins->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
    lblWins->setPosition(Vec2(_dialogRect.origin.x + 20, lblName->getPosition().y - 40));
    this->addChild(lblWins, txtWinsTag, txtWinsTag);
    
    auto lblLoses = Label::createWithTTF(LanguageManager::getString("DialogPlayerInfoLosesLabel"), GameFont, 34);
    lblLoses->setColor(Color3B(56, 37, 27));
    lblLoses->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
    lblLoses->setPosition(Vec2(_dialogRect.origin.x + 20, lblWins->getPosition().y - 40));
    this->addChild(lblLoses, txtLosesTag, txtLosesTag);
    
    //_lblRating = [CCLabelTTF labelWithString:[LanguageManager localizedString:@"DialogPlayerInfoRatingLabel"] fontName:GameFontBold fontSize:[BRRUtilities getValueByInterfaceIdiomPhone:12 orPad:24]];
    //_lblRating.color = ccc3(56, 37, 27);
    //_lblRating.anchorPoint = ccp(0, 0.5);
    //_lblRating.position = ccp(super.dialogRect.origin.x + [BRRUtilities getValueByInterfaceIdiomPhone:10 orPad:20], _lblLoses.position.y - [BRRUtilities getValueByInterfaceIdiomPhone:20 orPad:40]);
    //[self addChild:_lblRating];
    
    this->addDoneButton(LanguageManager::getString("DialogPlayerInfoNextButton"));
    
    this->getPlayerInfo(playerId);
    
    return true;
}

void DialogPlayerInfo::getPlayerInfo(long long playerId) {
    MessageRequestPlayerInfo msg;
    msg.set_playerid(playerId);
    SocketThread::getInstance()->getSocket()->Send(this->wrapMessage(eProtoMessageType::cmtGetPlayerInfo, msg));
}

void DialogPlayerInfo::processProtoMessage(const eProtoMessageType messageType, const std::string &messageBody) {
    switch (messageType) {
        case eProtoMessageType::cmtGetPlayerInfo: {
            this->callbackGetPlayerInfo(messageBody);
            break;
        }
            
        default:
            break;
    }
}

void DialogPlayerInfo::callbackGetPlayerInfo(const std::string &source) {
    if (source.size() == 0)
        return;
    
    MessageResponsePlayerInfo msg;
    msg.ParseFromString(source);
    
    dynamic_cast<Label*>(this->getChildByTag(txtNameTag))->setString(StringUtils::format("%s %s",
                                                                                         LanguageManager::getString("DialogPlayerInfoNameLabel").c_str(),
                                                                                         msg.playername().c_str()));
    dynamic_cast<Label*>(this->getChildByTag(txtWinsTag))->setString(StringUtils::format("%s %d",
                                                                                         LanguageManager::getString("DialogPlayerInfoWinsLabel").c_str(),
                                                                                         msg.playerwins()));
    dynamic_cast<Label*>(this->getChildByTag(txtLosesTag))->setString(StringUtils::format("%s %d",
                                                                                          LanguageManager::getString("DialogPlayerInfoLosesLabel").c_str(),
                                                                                          msg.playerloses()));
}

