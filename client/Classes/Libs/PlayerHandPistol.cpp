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

#include "PlayerHandPistol.h"
#include "PlayerShootDirection.pb.h"
#include "Utils.h"
#include "RotateRadian.h"

PlayerHandPistol* PlayerHandPistol::create(RoomPlayer *player) {
    PlayerHandPistol *node = new (std::nothrow) PlayerHandPistol();
    if(node && node->init(player)) {
        node->autorelease();
        return node;
    }
    CC_SAFE_DELETE(node);
    return nullptr;
}

bool PlayerHandPistol::init(RoomPlayer *player) {
    _listenerPlayerEntityChangeShootDirection = EventListenerCustom::create(PlayerEntityChangeShootDirectionNotification, CC_CALLBACK_1(PlayerHandPistol::onPlayerEntityDidChangeShootDirection, this));
    _listenerPlayerEntityChangeRadian = EventListenerCustom::create(PlayerEntityChangeCurrentRadianNotification, CC_CALLBACK_1(PlayerHandPistol::onPlayerEntityDidChangeCurrentRadian, this));
    _eventDispatcher->addEventListenerWithFixedPriority(_listenerPlayerEntityChangeShootDirection, 1);
    _eventDispatcher->addEventListenerWithFixedPriority(_listenerPlayerEntityChangeRadian, 1);
    
    Size winSize = Director::getInstance()->getVisibleSize();

    _player = player;
    _isClockWise = (_player->getShootDirection() == PlayerShootDirection::psdRIGHT);
    this->setHandPistolState(PlayerHandPistolStateHand);
    
    _center = Vec2(winSize.width / 2, winSize.height / 2);
    _radius = Utils::getQuadraticSizes(winSize) / 2 - Utils::getQuadraticSizes(this->getContentSize()) / 2 - 80;
    
    this->updatePosition();
    
    return true;
}

PlayerHandPistol::~PlayerHandPistol() {
    _eventDispatcher->removeEventListener(_listenerPlayerEntityChangeShootDirection);
    _eventDispatcher->removeEventListener(_listenerPlayerEntityChangeRadian);
}

void PlayerHandPistol::onPlayerEntityDidChangeShootDirection(EventCustom *event) {
    long long playerId = *((long long*)(event->getUserData()));
    if (playerId != _player->getPlayerId()) {
        return;
    }
    
    _isClockWise = (_player->getShootDirection() == PlayerShootDirection::psdRIGHT);
    
    this->updatePosition();
}

void PlayerHandPistol::onPlayerEntityDidChangeCurrentRadian(EventCustom *event) {
    long long playerId = *((long long*)(event->getUserData()));
    if (playerId != _player->getPlayerId()) {
        return;
    }
    
    this->updatePosition();
}

void PlayerHandPistol::setHandPistolState(PlayerHandPistolState value) {
    _handPistolState = value;
    
    this->removeChildByTag(pistol1Tag);
    
    Sprite *_pistol1Sprite = nullptr;
    
    switch (_handPistolState) {
        case PlayerHandPistolStateHand: {
            _pistol1Sprite = Sprite::create("SceneRoom/SceneRoomHandPistolRight.png");
            break;
        }
            
        case PlayerHandPistolStateKilled: {
            _pistol1Sprite = Sprite::create("SceneRoom/SceneRoomBangKillRight.png");
            break;
        }
            
        case PlayerHandPistolStateNotKilled: {
            _pistol1Sprite = Sprite::create("SceneRoom/SceneRoomBangNotKillRight.png");
            break;
        }
    }
    
    this->addChild(_pistol1Sprite, pistol1Tag, pistol1Tag);
    this->updatePosition();
}

void PlayerHandPistol::updatePosition() {
    double offsetRadian = 0.40;
    
    if (_isClockWise) {
        offsetRadian *= -1;
    }
    
    dynamic_cast<Sprite*>(this->getChildByTag(pistol1Tag))->setFlippedX(!_isClockWise);
    
    Vec2 xyPos = Utils::getCenteredXYPositionByCircle(_radius, _player->getRadian() + offsetRadian, _center);
    
    this->updateRotation();
    this->setPosition(Vec2(xyPos.x, xyPos.y));
}

void PlayerHandPistol::updateRotation() {
    double angle = -CC_RADIANS_TO_DEGREES(_player->getRadian()) + 90;
    
    auto _pistol1Sprite = dynamic_cast<Sprite*>(this->getChildByTag(pistol1Tag));
    
    switch (_player->getPlayerAmount()) {
        case 6:
            if (_isClockWise)
                angle += 30;
                else
                    angle -= 30;
                    break;
            
        case 5:
            if (_isClockWise)
                angle += 40;
                else
                    angle -= 40;
                    break;
            
        case 4:
            if (_isClockWise)
                angle += 50;
                else
                    angle -= 50;
                    break;
            
        case 3:
            if (_isClockWise)
                angle += 60;
                else
                    angle -= 60;
                    break;
            
        default:
            break;
    }
    
    _pistol1Sprite->setRotation(angle);
}

void PlayerHandPistol::showAnimated() {
    _isClockWise = (_player->getShootDirection() == PlayerShootDirection::psdRIGHT);
    
    double offsetRadian = 0.40;
    
    if (_isClockWise) {
        offsetRadian *= -1;
    }
    
    double sourceRadian = _player->getRadian();
    double destRadian = (_isClockWise) ? _player->getRadian() - offsetRadian : _player->getRadian() + offsetRadian;
    
    this->runAction(RotateRadian::create(1, sourceRadian, destRadian, false, false, this));
}

void PlayerHandPistol::setRadian(double value) {
    auto _pistol1Sprite = dynamic_cast<Sprite*>(this->getChildByTag(pistol1Tag));

    _pistol1Sprite->setFlippedX(!_isClockWise);
    
    Vec2 xyPos = Utils::getCenteredXYPositionByCircle(_radius, value, _center);
    
    _pistol1Sprite->setRotation(CC_RADIANS_TO_DEGREES(value) * (-1) + 90);
    this->setPosition(Vec2(xyPos.x, xyPos.y));
}

RoomPlayer* PlayerHandPistol::getPlayer() {
    return _player;
}