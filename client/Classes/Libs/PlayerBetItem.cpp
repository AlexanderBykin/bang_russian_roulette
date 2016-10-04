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

#include "PlayerBetItem.h"
#include "LanguageManager.h"
#include "GlobalProperties.h"

PlayerBetItem* PlayerBetItem::create(Vec2 startPoint, Vec2 destPoint, int amount, PlayerBetWinType winType) {
    PlayerBetItem *node = new (std::nothrow) PlayerBetItem();
    if(node && node->init(startPoint, destPoint, amount, winType)) {
        node->autorelease();
        return node;
    }
    CC_SAFE_DELETE(node);
    return nullptr;
}

bool PlayerBetItem::init(Vec2 startPoint, Vec2 destPoint, int amount, PlayerBetWinType winType) {
    if(!Layer::init()) {
        return false;
    }

    Size winSize = Director::getInstance()->getVisibleSize();

    _startPoint = startPoint;
    _destPoint = destPoint;
    _amount = amount;
    _winType = winType;
    _finishPoint = Vec2(0, winSize.height);
    
    std::string lbl = "";
    
    switch (_winType) {
        case PlayerBetWinType::pbwtWin:
            lbl = StringUtils::format("%s\n%i", LanguageManager::getString("DialogPlayerBetWinLabel").c_str(), amount); // TODO: need lowerCase
            break;
            
        case PlayerBetWinType::pbwtLose:
            lbl = StringUtils::format("%s\n%i", LanguageManager::getString("DialogPlayerBetLoseLabel").c_str(), amount); // TODO: need lowerCase
            break;
    }
    
    auto lblWin1 = Label::createWithTTF(lbl, GameFont, 24);
    lblWin1->setColor(Color3B::WHITE);
    this->addChild(lblWin1);
    
    this->setPosition(Vec2(_startPoint.x, _startPoint.y));
    
    return true;
}

void PlayerBetItem::animate() {
    this->runAction(Sequence::create(MoveTo::create(0.6, _destPoint),
                                     CallFunc::create(CC_CALLBACK_0(PlayerBetItem::didFinishAnimation1, this)),
                                     nullptr));
}

void PlayerBetItem::didFinishAnimation1() {
    this->stopAllActions();
    this->runAction(Sequence::create(DelayTime::create(0.3),
                                     MoveTo::create(0.6, _finishPoint),
                                     CallFunc::create(CC_CALLBACK_0(PlayerBetItem::didFinishAnimation2, this)),
                                     nullptr));
}

void PlayerBetItem::didFinishAnimation2() {
    this->stopAllActions();
    EventCustom event(PlayerBetItemDidFinishAnimationNotification);
    event.setUserData(this);
    _eventDispatcher->dispatchEvent(&event);
}

int PlayerBetItem::getAmount() {
    return _amount;
}