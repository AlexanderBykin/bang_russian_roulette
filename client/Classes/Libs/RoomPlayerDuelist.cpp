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

#include "RoomPlayerDuelist.h"
#include "GlobalProperties.h"

bool RoomPlayerDuelist::init() {
    if(!Layer::init()) {
        return false;
    }
    
    _touchListener = EventListenerTouchOneByOne::create();
    _touchListener->onTouchBegan = CC_CALLBACK_2(RoomPlayerDuelist::onTouchBegan, this);
    _touchListener->onTouchEnded = CC_CALLBACK_2(RoomPlayerDuelist::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(_touchListener, this);
    
    this->setPlayerDuelState(RoomPlayerDuelist::RoomPlayerDuelistDuelStateTypes::stDefault);
    
    return true;
}

PlayerDuelistEntity *RoomPlayerDuelist::getPlayerDuelistEntity() {
    return _playerDuelistEntity;
}

void RoomPlayerDuelist::setPlayerDuelistEntity(PlayerDuelistEntity *value) {
    _playerDuelistEntity = value;
    _playerDuelistEntity->retain();
}

void RoomPlayerDuelist::updateState() {
    if (!_player) {
        return;
    }
    
    auto state = (_playerDuelistEntity->getIsDuelist()) ? RoomPlayerDuelistDuelStateTypes::stIsDuelist : RoomPlayerDuelistDuelStateTypes::stIsNotDuelist;
    this->setPlayerDuelState(state);
}

void RoomPlayerDuelist::setPlayerDuelState(RoomPlayerDuelistDuelStateTypes value) {
    _playerDuelState = value;
    
    this->removeChildByTag(SceneTags::bgTag);
    
    Sprite *bgSprite = nullptr;
    
    switch (_playerDuelState) {
        case stDefault: {
            bgSprite = Sprite::create("Dialog/btnDialogDuelFoil.png");
            break;
        }
            
        case stIsDuelist: {
            bgSprite = Sprite::create("Dialog/btnDialogDuelBlackBall.png");
            break;
        }
            
        case stIsNotDuelist: {
            bgSprite = Sprite::create("Dialog/btnDialogDuelWhiteBall.png");
            break;
        }
    }
    
    bgSprite->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    this->addChild(bgSprite, 1, bgTag);
    this->setContentSize(bgSprite->getContentSize());
}

void RoomPlayerDuelist::setPlayer(RoomPlayer *player) {
    _player = player;
    
    if (!_player || _player->getPlayerId() <= 0) {
        return;
    }
    
    this->scheduleOnce(CC_SCHEDULE_SELECTOR(RoomPlayerDuelist::onUpdateAfterDelay), 0.6);
}

void RoomPlayerDuelist::onUpdateAfterDelay(float value) {
    this->removeChildByTag(bgTag);
    this->removeChildByTag(avatarTag);
    
    Sprite *bgSprite = nullptr;
    
    if (_player->getPlayerId() == GlobalProperties::getPlayerId()) {
        bgSprite = Sprite::create("SceneRoom/SceneRoomPlayerGreen.png");
    } else {
        bgSprite = Sprite::create("SceneRoom/SceneRoomPlayerGray.png");
    }
    
    bgSprite->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    //    this->setContentSize(bgSprite->getContentSize());
    this->addChild(bgSprite, 1, bgTag);
    
    Sprite *playerAvatarSprite = nullptr;
    
    if (_player->getAvatar().empty()) {
        playerAvatarSprite = Sprite::create("SceneRoom/SceneRoomPlayerNoAvatarMan.png");
    }
    else {
        auto texture = new Texture2D();
        texture->initWithData(&_player->getAvatar(), _player->getAvatar().size(), Texture2D::PixelFormat::DEFAULT, 200, 200, Size(200, 200));
        playerAvatarSprite = Sprite::createWithTexture(texture);
    }
    
    Sprite *smallBall = nullptr;
    
    switch (_playerDuelState) {
        case stIsDuelist: {
            smallBall = Sprite::create("Dialog/DialogDuelBlackBallSmall.png");
            break;
        }
            
        case stIsNotDuelist: {
            smallBall = Sprite::create("Dialog/DialogDuelWhiteBallSmall.png");
            break;
        }
            
        default:
            break;
    }
    
    //int playerAvatarSize = 150;
    //playerAvatarSprite->setContentSize(Size(playerAvatarSize, playerAvatarSize));
    playerAvatarSprite->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    //playerAvatarSprite->setPosition(Vec2(1, 1));
    
    smallBall->setPosition(Vec2(playerAvatarSprite->getContentSize().width - smallBall->getContentSize().width / 2, smallBall->getContentSize().height / 2));
    playerAvatarSprite->addChild(smallBall);
    this->addChild(playerAvatarSprite, 2, avatarTag);
    
    if (!_playerDuelistEntity->getIsDuelist()) {
        auto lblWinAmount = Label::createWithTTF(StringUtils::format("%i", _playerDuelistEntity->getWinAmount()), GameFont, 28);
        lblWinAmount->setColor(Color3B::WHITE);
        //    lblWinAmount.position = ccp(self.contentSize.width / 2, self.contentSize.height / 2);
        this->addChild(lblWinAmount, 3, winAmountTag);
    }
    
    _eventDispatcher->removeEventListener(_touchListener);
}

bool RoomPlayerDuelist::onTouchBegan(Touch *touch, Event *event) {
    Point location = touch->getLocationInView();
    location = Director::getInstance()->convertToGL(location);
    
    Rect _glRect = Rect(this->getPosition().x - this->getContentSize().width / 2,
                        this->getPosition().y - this->getContentSize().height / 2,
                        this->getContentSize().width,
                        this->getContentSize().height);
    
    return _glRect.containsPoint(location);
}

void RoomPlayerDuelist::onTouchEnded(Touch *touch, Event *event) {
    if (GlobalProperties::getPlayerId() <= 0) {
        return;
    }
    
    EventCustom cuEvent(RoomPlayerDuelistTapNotification);
    cuEvent.setUserData(new int(_playerDuelistEntity->getPosition()));
    _eventDispatcher->dispatchEvent(&cuEvent);
}