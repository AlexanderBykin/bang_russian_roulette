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

#include "ShootDirection.h"
#include "PlayerShootDirection.pb.h"
#include "Utils.h"
#include "GlobalProperties.h"

ShootDirection* ShootDirection::create(RoomPlayer* player) {
    ShootDirection *node = new (std::nothrow) ShootDirection();
    if(node && node->init(player)) {
        node->autorelease();
        return node;
    }
    CC_SAFE_DELETE(node);
    return nullptr;
}

bool ShootDirection::init(RoomPlayer *player) {
    if(!Layer::init()) {
        return false;
    }
    _listenerPlayerEntityChangeShootDirection = EventListenerCustom::create(PlayerEntityChangeShootDirectionNotification, CC_CALLBACK_1(ShootDirection::onPlayerEntityDidChangeShootDirection, this));
    _listenerPlayerEntityChangeRadian = EventListenerCustom::create(PlayerEntityChangeCurrentRadianNotification, CC_CALLBACK_1(ShootDirection::onPlayerEntityDidChangeCurrentRadian, this));
    _eventDispatcher->addEventListenerWithFixedPriority(_listenerPlayerEntityChangeShootDirection, 1);
    _eventDispatcher->addEventListenerWithFixedPriority(_listenerPlayerEntityChangeRadian, 1);
    
    _player = player;
    _isClockWise = (_player->getShootDirection() == PlayerShootDirection::psdRIGHT);
    
    Size winSize = Director::getInstance()->getVisibleSize();
    _center = Vec2(winSize.width / 2, winSize.height / 2);
    _radius = Utils::getQuadraticSizes(winSize) / 5.5;
    
    if (GlobalProperties::isDebug()) {
        auto lblPos = Label::createWithTTF(StringUtils::format("%i", _player->getPlayerPosition()), GameFont, 24);
        lblPos->setColor(Color3B::WHITE);
        this->addChild(lblPos, lblPosTag, lblPosTag);
    }
    
    this->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    this->updateShootDirection();
    this->updatePosition();
    
    _isAnimationEnabled = false;
    
    return true;
}

ShootDirection::~ShootDirection() {
    _eventDispatcher->removeEventListener(_listenerPlayerEntityChangeRadian);
    _eventDispatcher->removeEventListener(_listenerPlayerEntityChangeShootDirection);
}

void ShootDirection::onPlayerEntityDidChangeShootDirection(EventCustom *event) {
    long long playerId = *((long long*)(event->getUserData()));
    if (playerId != _player->getPlayerId()) {
        return;
    }

    _isClockWise = (_player->getShootDirection() == PlayerShootDirection::psdRIGHT);
    
    this->updateShootDirection();
}

void ShootDirection::onPlayerEntityDidChangeCurrentRadian(EventCustom *event) {
    long long playerId = *((long long*)(event->getUserData()));
    if (playerId != _player->getPlayerId()) {
        return;
    }
    
    this->updatePosition();
}

void ShootDirection::updateShootDirection() {
    this->removeChildByTag(bgTag);
    
    Sprite *bgSprite = NULL;
    
    if (_player->getShootDirection() == PlayerShootDirection::psdDOUBLE) {
        bgSprite = Sprite::create("SceneRoom/SceneRoomArrowDouble.png");
    }
    else {
        bgSprite = Sprite::create("SceneRoom/SceneRoomArrow.png");
    }
    
    bgSprite->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    this->addChild(bgSprite, bgTag, bgTag);
    this->setContentSize(bgSprite->getContentSize());
    
    if (_player->getShootDirection() != PlayerShootDirection::psdDOUBLE) {
        bgSprite->setFlippedX(!_isClockWise);
    }
    
    this->updatePosition();
}

void ShootDirection::updatePosition() {
    if (auto bgSprite = dynamic_cast<Sprite*>(this->getChildByTag(bgTag))) {
        bgSprite->setRotation(CC_RADIANS_TO_DEGREES(_player->getRadian()) * (-1) + 90);
    }
    this->setPosition(Utils::getCenteredXYPositionByCircle(_radius, _player->getRadian(), _center));
}

void ShootDirection::setOpacity(GLubyte value) {
    this->getChildByTag(bgTag)->setOpacity(value);
}

void ShootDirection::fadeOut(bool withCallback) {
    _sendCallbackAfterAnimation = withCallback;
    this->runAction(Sequence::create(FadeOut::create(1.0), CallFunc::create(CC_CALLBACK_0(ShootDirection::didFinishFadeOut, this)), nullptr));
}

void ShootDirection::didFinishFadeOut() {
    this->stopAllActions();
    
    if (_sendCallbackAfterAnimation) {
        EventCustom event(ShootDirectionFadeOutCompleteNotification);
        event.setUserData(new int(_player->getPlayerPosition()));
        _eventDispatcher->dispatchEvent(&event);
    }
}

RoomPlayer* ShootDirection::getPlayer() {
    return _player;
}