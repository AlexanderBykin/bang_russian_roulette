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

#include "RoomItem.h"
#include "GlobalProperties.h"

RoomItem* RoomItem::create(MessageResponseRoomInfo *roomItem, float width, float height) {
    RoomItem *node = new (std::nothrow) RoomItem();
    if(node && node->init(roomItem, width, height)) {
        node->autorelease();
        return node;
    }
    CC_SAFE_DELETE(node);
    return nullptr;
}

bool RoomItem::init(MessageResponseRoomInfo *roomItem, float width, float height) {
    if(!Widget::init()) {
        return false;
    }

    _roomId = roomItem->roomid();
    
    this->setContentSize(Size(width, height));
    this->setTouchEnabled(true);

    auto winSize = Director::getInstance()->getVisibleSize();

    auto bgColor = LayerColor::create(_bgColor, width, height);
    bgColor->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    this->addChild(bgColor, 0, _bgColorTag);

    auto fieldsAvg = winSize.width / 5;
    
    auto separatorLine = LayerColor::create(Color4B(39, 137, 82, 255), width, 2);
    separatorLine->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    separatorLine->setPosition(Vec2(0, 0));
    this->addChild(separatorLine);
    
    auto lblId = Label::createWithTTF(StringUtils::format("%lli", roomItem->roomid()), GameFont, 22);
    lblId->setPosition(Vec2(60, this->getContentSize().height / 2));
    lblId->setColor(Color3B(151, 239, 187));
    this->addChild(lblId);
    
    auto lblBet = Label::createWithTTF(StringUtils::format("%i", roomItem->bet()), GameFont, 22);
    lblBet->setPosition(Vec2(fieldsAvg - 10, this->getContentSize().height / 2));
    lblBet->setColor(Color3B(151, 239, 187));
    this->addChild(lblBet);
    
    auto lblPlayer = Label::createWithTTF(StringUtils::format("%i / %i", roomItem->amountplayers(), roomItem->maxplayers()), GameFont, 22);
    lblPlayer->setPosition(Vec2(fieldsAvg * 2 - 10, this->getContentSize().height / 2));
    lblPlayer->setColor(Color3B(151, 239, 187));
    this->addChild(lblPlayer);
    
    auto lblRound = Label::createWithTTF(StringUtils::format("%i / %i", roomItem->currentround(), roomItem->maxrounds()), GameFont, 22);
    lblRound->setPosition(Vec2(fieldsAvg * 3 - 20, this->getContentSize().height / 2));
    lblRound->setColor(Color3B(151, 239, 187));
    this->addChild(lblRound);
    
    auto lblBank = Label::createWithTTF(StringUtils::format("$ %lli", roomItem->playerbank()), GameFont, 22);
    lblBank->setPosition(Vec2(fieldsAvg * 4 - 50, this->getContentSize().height / 2));
    lblBank->setColor(Color3B(151, 239, 187));
    this->addChild(lblBank);
    

    return true;
}

void RoomItem::setSelection(bool value) {
    Color3B textColor = _textColor;
    Color4B bgColor = _bgColor;
    if (value) {
        bgColor = _bgSelectedColor;
        textColor = _textSelectedColor;
    }
    else {
        bgColor = _bgColor;
        textColor = _textColor;
    }
    auto bgColorNode = dynamic_cast<LayerColor*>(this->getChildByTag(_bgColorTag));
    bgColorNode->setColor(Color3B(bgColor.r, bgColor.g, bgColor.b));
    bgColorNode->setOpacity(bgColor.a);
    for(auto child : this->getChildren())
    {
        if (auto label = dynamic_cast<Label*>(child)) {
            label->setColor(textColor);
        }
    }
}

long long RoomItem::getRoomId() {
    return _roomId;
}