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

#include "RoomPlayer.h"
#include "Utils.h"
#include "LanguageManager.h"
#include "GlobalProperties.h"
#include "RotateRadian.h"

RoomPlayer* RoomPlayer::create(long long playerId, const std::string &playerName, int playerPosition, const std::string &avatar, PlayerShootDirection shootDirection, double radian, RoomPlayerStateTypes playerState) {
    RoomPlayer *node = new (std::nothrow) RoomPlayer();
    if(node && node->init(playerId, playerName, playerPosition, avatar, shootDirection, radian, playerState)) {
        node->autorelease();
        return node;
    }
    CC_SAFE_DELETE(node);
    return nullptr;
}

bool RoomPlayer::init(long long playerId, const std::string &playerName, int playerPosition, const std::string &avatar, PlayerShootDirection shootDirection, double radian, RoomPlayerStateTypes playerState) {
    if(!Layer::init()) {
        return false;
    }
    
    Size winSize = Director::getInstance()->getVisibleSize();
    
    _playerAmount = 0;
    _playerName = playerName;
    this->setTouchEnable(true);
    this->setPlayerState(playerState);
    this->setPlayerId(playerId);
    this->setPlayerPosition(playerPosition);
    this->setAvatar(avatar);
    this->setRadian(radian);
    this->setShootDirection(shootDirection);
    
    _center = Vec2(winSize.width / 2, winSize.height / 2);
    _radius = Utils::getQuadraticSizes(winSize) / 2 - Utils::getQuadraticSizes(this->getContentSize()) / 2;
    
    this->updatePosition();
    
    return true;
}

long long RoomPlayer::getPlayerId() {
    return _playerId;
}

int RoomPlayer::getPlayerPosition() {
    return _playerPosition;
}

void RoomPlayer::setPlayerPosition(int value) {
    _playerPosition = value;
}

void RoomPlayer::setPlayerName(const std::string &value) {
    _playerName = value;
}

const std::string& RoomPlayer::getAvatar() {
    return _avatar;
}

double RoomPlayer::getRadian() {
    return _currentRadian;
}

void RoomPlayer::setRadian(double value) {
    _currentRadian = value;
    EventCustom event(PlayerEntityChangeCurrentRadianNotification);
    event.setUserData(new long long(_playerId));
    _eventDispatcher->dispatchEvent(&event);
    this->updatePosition();
}

void RoomPlayer::setPlayerState(RoomPlayerStateTypes playerState) {
    _playerState = playerState;
    
    this->removeChildByTag(SceneTags::bgTag);
    
    Sprite *playerBGSprite;
    
    switch (_playerState) {
        case RoomPlayerStateTypeDefault: {
            playerBGSprite = Sprite::create("SceneRoom/SceneRoomPlayerNone.png");
            break;
        }
            
        case RoomPlayerStateTypeCurrent: {
            playerBGSprite = Sprite::create("SceneRoom/SceneRoomPlayerGreen.png");
            break;
        }
            
        case RoomPlayerStateTypeSelected: {
            playerBGSprite = Sprite::create("SceneRoom/SceneRoomPlayerGold.png");
            break;
        }
            
        case RoomPlayerStateTypeEnemy: {
            playerBGSprite = Sprite::create("SceneRoom/SceneRoomPlayerGray.png");
            break;
        }
            
        case RoomPlayerStateTypeKilled: {
            playerBGSprite = Sprite::create("SceneRoom/SceneRoomPlayerRed.png");
            break;
        }
            
        default:
            break;
    }
    
    this->setContentSize(playerBGSprite->getContentSize());
    this->addChild(playerBGSprite, 1, bgTag);
}

void RoomPlayer::setAvatar(const std::string &value) {
    _avatar = value;
    
    this->removeChildByTag(avatarTag);
    
    Sprite *playerAvatarSprite = NULL;
    
    if (_playerId <= 0) {
        playerAvatarSprite = Sprite::create();
        auto lbl = Label::createWithTTF(LanguageManager::getString("RoomPlayerStayHereLabel"), GameFont, 24);
        lbl->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
        lbl->setColor(Color3B(66, 158, 97));
        //lbl->setPosition(Vec2(this->getContentSize().width / 2, this->getContentSize().height / 2));
        this->addChild(lbl);
    }
    else {
        if (_avatar.empty()) {
            playerAvatarSprite = Sprite::create("SceneRoom/SceneRoomPlayerNoAvatarMan.png");
        }
        else {
            auto texture = new Texture2D();
            texture->initWithData(&_avatar, _avatar.size(), Texture2D::PixelFormat::DEFAULT, 150, 150, Size(150, 150));
            playerAvatarSprite = Sprite::createWithTexture(texture);
        }
    }
    
    //double playerAvatarSize = 150;
    //playerAvatarSprite->setContentSize(Size(playerAvatarSize, playerAvatarSize));
    playerAvatarSprite->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    //playerAvatarSprite->setPosition(Vec2(1, 1));
    this->addChild(playerAvatarSprite, 2, avatarTag);
    
    if (GlobalProperties::isDebug()) {
        auto lblPos = Label::createWithTTF(StringUtils::format("%i", _playerPosition), GameFont, 24);
        lblPos->setColor(Color3B::WHITE);
        this->addChild(lblPos, 3, lblPosTag);
    }
    
    auto lblPlayerName = Label::createWithTTF(_playerName, GameFont, 24);
    lblPlayerName->setColor(Color3B::WHITE);
    this->addChild(lblPlayerName, 4);
    
    EventCustom event(PlayerEntityChangeAvatarNotification);
    event.setUserData(new long long(_playerId));
    _eventDispatcher->dispatchEvent(&event);
}

void RoomPlayer::setPlayerId(long long playerId) {
    _playerId = playerId;
    
    if (_playerId <= 0L) {
        this->setPlayerState(RoomPlayerStateTypeDefault);
    }
    else {
        if (GlobalProperties::getPlayerId() > 0 && GlobalProperties::getPlayerId() == _playerId) {
            this->setPlayerState(RoomPlayerStateTypeCurrent);
        }
        else {
            this->setPlayerState(RoomPlayerStateTypeEnemy);
        }
    }
}

int RoomPlayer::getPlayerAmount() {
    return _playerAmount;
}

void RoomPlayer::setPlayerAmount(int value) {
    _playerAmount = value;
}

void RoomPlayer::animateRotationWithPlayerId(long long destPlayerId, bool roomClockWise, bool withRoomClockWise, int playerAmount) {
    _playerAmount = playerAmount;
    auto _currentAction = this->getActionByTag(animationTag);
    if (_currentAction && !_currentAction->isDone()) {
        if (_playerId == destPlayerId) {
            this->setPlayerState(RoomPlayerStateTypeSelected);
        }
        
        return;
    }
    
    _prevPlayerState = _playerState;
    
    if (_playerId == destPlayerId) {
        this->setPlayerState(RoomPlayerStateTypeSelected);
    }
    
    _destRadian = _currentRadian + (2 * M_PI);
    
    auto newAction = Sequence::create(EaseExponentialOut::create(RotateRadian::create(2, _currentRadian, _destRadian, roomClockWise, withRoomClockWise, this)),
                                      CallFunc::create(CC_CALLBACK_0(RoomPlayer::animationRotationDidFinish, this)), nullptr);
    newAction->setTag(animationTag);
    this->runAction(newAction);
}

void RoomPlayer::animationRotationDidFinish() {
    this->setPlayerState(_prevPlayerState);
}

void RoomPlayer::animateRotationToRadian(double radian, bool roomClockWise, bool withRoomClockWise, int playerAmount) {
    _playerAmount = playerAmount;
    
    _destRadian = radian;
    
    auto newAction = EaseOut::create(RotateRadian::create(2, _currentRadian, _destRadian, roomClockWise, withRoomClockWise, this),
                                     1.8);
    newAction->setTag(animationTag);
    this->runAction(newAction);
}

PlayerShootDirection RoomPlayer::getShootDirection() {
    return _shootDirection;
}

void RoomPlayer::setShootDirection(PlayerShootDirection shootDirection) {
    _shootDirection = shootDirection;
    
    EventCustom event(PlayerEntityChangeShootDirectionNotification);
    event.setUserData(new long long(_playerId));
    _eventDispatcher->dispatchEvent(&event);
}

void RoomPlayer::setOpacity(GLubyte value) {
    for (auto child : this->getChildren()) {
        child->setOpacity(value);
    }
}

void RoomPlayer::fadeOut(bool withCallback) {
    _sendCallbackAfterAnimation = withCallback;
    auto newAction = Sequence::create(FadeOut::create(1.0), CallFunc::create(CC_CALLBACK_0(RoomPlayer::didFinishFadeOut, this)), nullptr);
    newAction->setTag(animationTag);
    this->runAction(newAction);
}

void RoomPlayer::didFinishFadeOut() {
    this->stopAllActions();
    
    if (_sendCallbackAfterAnimation) {
        EventCustom event(RoomPlayerFadeOutCompleteNotification);
        event.setUserData(new int(_playerPosition));
        _eventDispatcher->dispatchEvent(&event);
    }
}

void RoomPlayer::updatePosition() {
    this->setPosition(Utils::getCenteredXYPositionByCircle(_radius, _currentRadian, _center));
}

bool RoomPlayer::onTouchBegan(Touch *touch, Event *event) {
    Point location = touch->getLocationInView();
    location = Director::getInstance()->convertToGL(location);
    
    auto rect = Rect(this->getPosition().x - this->getContentSize().width / 2, this->getPosition().y - this->getContentSize().height / 2, this->getContentSize().width, this->getContentSize().height);
    
    return rect.containsPoint(location);
}

void RoomPlayer::onTouchEnded(Touch *touch, Event *event) {
    EventCustom cuEvent(RoomPlayerTapNotification);
    cuEvent.setUserData(this);
    _eventDispatcher->dispatchEvent(&cuEvent);
}

void RoomPlayer::setTouchEnable(bool value) {
    _eventDispatcher->removeEventListener(_touchListener);
    if(value) {
        _touchListener = EventListenerTouchOneByOne::create();
        _touchListener->onTouchBegan = CC_CALLBACK_2(RoomPlayer::onTouchBegan, this);
        _touchListener->onTouchEnded = CC_CALLBACK_2(RoomPlayer::onTouchEnded, this);
        _eventDispatcher->addEventListenerWithSceneGraphPriority(_touchListener, this);
    }
}
