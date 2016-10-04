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

#include "LabelShadow.h"

LabelShadow* LabelShadow::create(const std::string &text, const std::string &fontName, float fontSize, const Color3B &textColor, const Color3B &textShadowColor) {
    LabelShadow *node = new (std::nothrow) LabelShadow();
    if(node && node->init(text, fontName, fontSize, textColor, textShadowColor)) {
        node->autorelease();
        return node;
    }
    CC_SAFE_DELETE(node);
    return nullptr;
}

bool LabelShadow::init(const std::string &text, const std::string &fontName, float fontSize, const Color3B &textColor, const Color3B &textShadowColor) {
    if(!Node::init()) {
        return false;
    }
    
    auto label = Label::createWithTTF(text, fontName, fontSize);
    label->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    label->setColor(textColor);
    this->addChild(label, 10, _labelTag);
    label->setPosition(this->getContentSize().width/2, this->getContentSize().height/2);
    
    auto labelShadow = Label::createWithTTF(text, fontName, fontSize);
    labelShadow->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    labelShadow->setColor(textShadowColor);
    this->addChild(labelShadow, 9, _labelShadowTag);
    this->setShadowOffset(2);
    
    return true;
}

void LabelShadow::setTextColor(const Color3B &color) {
    dynamic_cast<Label*>(this->getChildByTag(_labelTag))->setColor(color);
}

void LabelShadow::setTextShadowColor(const Color3B &color) {
    dynamic_cast<Label*>(this->getChildByTag(_labelShadowTag))->setColor(color);
}

void LabelShadow::setAnchorPoint(const Vec2& point) {
    Node::setAnchorPoint(point);
    this->getChildByTag(_labelTag)->setAnchorPoint(point);
    this->getChildByTag(_labelShadowTag)->setAnchorPoint(point);
}

void LabelShadow::setShadowOffset(const float offset) {
    auto label = this->getChildByTag(_labelTag);
    this->getChildByTag(_labelShadowTag)->setPosition(Vec2(label->getPosition().x+offset, label->getPosition().y-offset));
}

void LabelShadow::setText(const std::string &value) {
    dynamic_cast<Label*>(this->getChildByTag(_labelTag))->setString(value);
    dynamic_cast<Label*>(this->getChildByTag(_labelShadowTag))->setString(value);    
}