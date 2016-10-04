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

#include "ShopItem.h"
#include "GlobalProperties.h"

ShopItem* ShopItem::create(const std::string &itemImage, const std::string &itemName, const std::string &itemDescription, int amount, int cost) {
    ShopItem *node = new (std::nothrow) ShopItem();
    if(node && node->init(itemImage, itemName, itemDescription, amount, cost)) {
        node->autorelease();
        return node;
    }
    CC_SAFE_DELETE(node);
    return nullptr;
}

bool ShopItem::init(const std::string &itemImage, const std::string &itemName, const std::string &itemDescription, int amount, int cost) {
    if(!Widget::init()) {
        return false;
    }
    
    _amount = amount;
    _itemName = itemName;
    _itemDescription = itemDescription;
    _cost = cost;

    auto _itemImage = Sprite::create(itemImage);
    _itemImage->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    this->addChild(_itemImage, 1, SceneTags::itemImageTag);

    this->setSelection(false);
    
    return true;
}

void ShopItem::setSelection(bool value) {
    this->removeChildByTag(SceneTags::bgImageTag);
    
    Sprite *bg = nullptr;
    
    if (value) {
        bg = Sprite::create("ShopItem/ShopItemBGSelected.png");
    }
    else {
        bg = Sprite::create("ShopItem/ShopItemBG.png");
    }
    
    bg->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
    this->setTouchEnabled(true);
    this->setContentSize(Size(bg->getContentSize().width, bg->getContentSize().height));
    bg->setPosition(Vec2(0, this->getContentSize().height / 2.0f));
    dynamic_cast<Sprite*>(this->getChildByTag(SceneTags::itemImageTag))->setPosition(Vec2(this->getContentSize().width / 2.0f, this->getContentSize().height / 2.0f));
    this->addChild(bg, 0, SceneTags::bgImageTag);
}

void ShopItem::setAmountVisible(bool value) {
    this->removeChildByTag(SceneTags::amountImageTag);
    
//    if (value) {
//        auto _amountImage = Sprite::create("ShopItem/ShopItemAmountBG.png");
//        _amountImage->setPosition(Vec2(this->getContentSize().width - _amountImage->getContentSize().width / 2, _amountImage->getContentSize().height / 2));
//        auto amountLabel = Label::createWithTTF(StringUtils::format("%i", _amount).c_str(), GameFont, 40);
//        amountLabel->setPosition(Vec2(_amountImage->getContentSize().width / 2, _amountImage->getContentSize().height / 2));
//        amountLabel->setColor(Color3B(57, 37, 27));
//        _amountImage->addChild(amountLabel);
//        this->addChild(_amountImage, 2, SceneTags::amountImageTag);
//    }
}

const std::string& ShopItem::getItemName() {
    return _itemName;
}

const std::string& ShopItem::getItemDescription() {
    return _itemDescription;
}

int ShopItem::getItemCost() {
    return _cost;
}