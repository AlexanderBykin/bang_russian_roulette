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

#include "ShopItemUsed.h"
#include "Utils.h"
#include "RotateRadian.h"

ShopItemUsed* ShopItemUsed::create(std::string shopItemName, double sourcePlayerRadian, double destPlayerRadian, long long destPlayerId) {
    ShopItemUsed *node = new (std::nothrow) ShopItemUsed();
    if(node && node->init(shopItemName, sourcePlayerRadian, destPlayerRadian, destPlayerId)) {
        node->autorelease();
        return node;
    }
    CC_SAFE_DELETE(node);
    return nullptr;
}

bool ShopItemUsed::init(std::string shopItemName, double sourcePlayerRadian, double destPlayerRadian, long long destPlayerId) {
    if(!Layer::init()) {
        return false;
    }
    
    Size winSize = Director::getInstance()->getVisibleSize();
    
    _shopItemName = shopItemName;
    _destPlayerId = destPlayerId;
    _sourcePlayerRadian = sourcePlayerRadian;
    _destPlayerRadian = destPlayerRadian;
    _currentRadian = _sourcePlayerRadian;
    //        _isClockWise = (sourcePlayerRadian < destPlayerRadian);
    
    Sprite *itemSprite = nullptr;
    
    if (shopItemName.compare("brr_broken_bullet") == 0) {
        itemSprite = Sprite::create("ShopItem/ShopItemUsedBrokenBullet.png");
    }
    else if (shopItemName.compare("brr_armored_bullet") == 0) {
        itemSprite = Sprite::create("ShopItem/ShopItemUsedArmoredBullet.png");
    }
    else if (shopItemName.compare("brr_helmet") == 0) {
        itemSprite = Sprite::create("ShopItem/ShopItemUsedHelmet.png");
    }
    else if (shopItemName.compare("brr_change_shoot_direction") == 0) {
        itemSprite = Sprite::create("ShopItem/ShopItemUsedChangeShootDirection.png");
    }
    
    itemSprite->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    this->addChild(itemSprite, bgTag, bgTag);
    this->setContentSize(itemSprite->getContentSize());
    
    _center = Vec2(winSize.width / 2, winSize.height / 2);
    _radius = Utils::getQuadraticSizes(winSize) / 2 - Utils::getQuadraticSizes(this->getContentSize()) + 10;
    
    this->updatePosition();
    
    return true;
}

void ShopItemUsed::animate() {
    this->runAction(Sequence::create(EaseOut::create(RotateRadian::create(1.3, _currentRadian, _destPlayerRadian, false, false, this), 1),
                                     FadeOut::create(1.0),
                                     CallFunc::create(CC_CALLBACK_0(ShopItemUsed::didFinishAnimation, this)), nullptr));
}

void ShopItemUsed::didFinishAnimation() {
    EventCustom event(ShopItemUsedDidFinishAnimationNotification);
    event.setUserData(this);
    _eventDispatcher->dispatchEvent(&event);
}

void ShopItemUsed::updatePosition() {
    this->setPosition(Utils::getCenteredXYPositionByCircle(_radius,_currentRadian, _center));
}

void ShopItemUsed::setRadian(double value) {
    _currentRadian = value;
    this->updatePosition();
}

void ShopItemUsed::setOpacity(GLubyte value) {
    this->getChildByTag(bgTag)->setOpacity(value);
}

const std::string ShopItemUsed::getShopItemName() {
    return _shopItemName;
}

long long ShopItemUsed::getDestPlayerId() {
    return _destPlayerId;
}