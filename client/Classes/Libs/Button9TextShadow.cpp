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

#include "Button9TextShadow.h"
#include "LabelShadow.h"

Button9TextShadow* Button9TextShadow::create(const std::string &bgImage, const cocos2d::Size &size, const std::string &label, const std::string &labelFontName, float labelFontSize, const cocos2d::Color3B &labelColor, const cocos2d::Color3B &labelShadowColor, const ccMenuCallback &callback) {
    Button9TextShadow *node = new (std::nothrow) Button9TextShadow();
    if(node && node->init(bgImage, size, label, labelFontName, labelFontSize, labelColor, labelShadowColor, callback)) {
        node->autorelease();
        return node;
    }
    CC_SAFE_DELETE(node);
    return nullptr;
}

bool Button9TextShadow::init(const std::string &bgImage, const cocos2d::Size &size, const std::string &label, const std::string &labelFontName, float labelFontSize, const cocos2d::Color3B &labelColor, const cocos2d::Color3B &labelShadowColor, const ccMenuCallback &callback) {
    if (!Button::init(bgImage)) {
        return false;
    }
    
    this->setScale9Enabled(true);
    this->setContentSize(size);
    this->setPressedActionEnabled(true);
    this->tapCallback = callback;
    this->addTouchEventListener(CC_CALLBACK_2(Button9TextShadow::touchEvent, this));
    
    contentNode = Node::create();
    contentNode->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    contentNode->setContentSize(size);
    contentNode->setPosition(size.width / 2, size.height / 2);
    this->addChild(contentNode, 1, 1);
    
    this->_lblNormalColor = labelColor;
    this->_lblShadowNormalColor = labelShadowColor;
    
    auto labelShadow = LabelShadow::create(label, labelFontName, labelFontSize, _lblNormalColor, _lblShadowNormalColor);
    labelShadow->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    labelShadow->setPosition(size.width / 2, size.height / 2 + 6);
    contentNode->addChild(labelShadow, 10, 10);
    
    return true;
}

Button9TextShadow* Button9TextShadow::create(const std::string &bgImage, const ccMenuCallback& callback) {
    Button9TextShadow *node = new (std::nothrow) Button9TextShadow();
    if(node && node->init(bgImage, callback)) {
        node->autorelease();
        return node;
    }
    CC_SAFE_DELETE(node);
    return nullptr;
}

bool Button9TextShadow::init(const std::string &bgImage, const ccMenuCallback& callback) {
    if (!Button::init(bgImage)) {
        return false;
    }

    this->setScale9Enabled(false);
    this->setPressedActionEnabled(false);
    this->tapCallback = callback;
    this->addTouchEventListener(CC_CALLBACK_2(Button9TextShadow::touchEvent, this));

    return true;
}

Button9TextShadow* Button9TextShadow::create(const std::string &bgImage, const std::string &bgImageSelected, const ccMenuCallback& callback) {
    Button9TextShadow *node = new (std::nothrow) Button9TextShadow();
    if(node && node->init(bgImage, bgImageSelected, callback)) {
        node->autorelease();
        return node;
    }
    CC_SAFE_DELETE(node);
    return nullptr;
}

bool Button9TextShadow::init(const std::string &bgImage, const std::string &bgImageSelected, const ccMenuCallback& callback) {
    if (!Button::init(bgImage, bgImageSelected)) {
        return false;
    }
    
    this->setScale9Enabled(false);
    this->setPressedActionEnabled(false);
    this->tapCallback = callback;
    this->addTouchEventListener(CC_CALLBACK_2(Button9TextShadow::touchEvent, this));
    
    return true;
}

void Button9TextShadow::addContentChild(Node* node) {
    if(node != nullptr) {
        contentNode->addChild(node);
    }
}

void Button9TextShadow::setSelectedResources(const std::string &bgImage, const cocos2d::Color3B &labelColor, const cocos2d::Color3B &labelShadowColor) {
    this->loadTexturePressed(bgImage);
    this->_lblSelectedColor = labelColor;
    this->_lblShadowSelectedColor = labelShadowColor;
}

void Button9TextShadow::setText(const std::string &value) {
    if(auto lbl = dynamic_cast<LabelShadow*>(contentNode->getChildByTag(10))) {
        lbl->setText(value);
    }
}

void Button9TextShadow::onPressStateChangedToNormal() {
    Button::onPressStateChangedToNormal();
    if(contentNode != nullptr) {
        if(_pressedActionEnabled)
            contentNode->setScale(1.0f);
        auto lbl = dynamic_cast<LabelShadow*>(contentNode->getChildByTag(10));
        if(lbl && _pressedTextureLoaded) {
            lbl->setTextColor(_lblNormalColor);
            lbl->setTextShadowColor(_lblShadowNormalColor);
        }
    }
}

void Button9TextShadow::onPressStateChangedToPressed() {
    Button::onPressStateChangedToPressed();
    if(contentNode != nullptr) {
        if(_pressedActionEnabled)
            contentNode->setScale(1.0f + _zoomScale);
        auto lbl = dynamic_cast<LabelShadow*>(contentNode->getChildByTag(10));
        if(lbl && _pressedTextureLoaded) {
            lbl->setTextColor(_lblSelectedColor);
            lbl->setTextShadowColor(_lblShadowSelectedColor);
        }
    }
}

void Button9TextShadow::touchEvent(Ref *pSender, TouchEventType type) {
    switch (type) {
        case ui::Widget::TouchEventType::ENDED:
            if (tapCallback != nullptr) {
                tapCallback(this);
            }
            break;
        default:
            break;
    }
}