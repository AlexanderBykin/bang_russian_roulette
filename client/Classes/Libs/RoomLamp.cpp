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

#include "RoomLamp.h"
#include "GlobalProperties.h"

RoomLamp* RoomLamp::create(const std::string &label, bool isOn) {
    RoomLamp *node = new (std::nothrow) RoomLamp();
    if(node && node->init(label, isOn)) {
        node->autorelease();
        return node;
    }
    CC_SAFE_DELETE(node);
    return nullptr;
}

bool RoomLamp::init(const std::string &label, bool isOn) {
    if(!Layer::init()) {
        return false;
    }
    
    auto lbl = Label::createWithTTF(label, GameFont, 48);
    lbl->setPosition(Vec2(0, 0));
    this->addChild(lbl, lblTag, lblTag);
    
    this->setText(label);
    this->setIsLampOn(isOn);
    
    return true;
}

void RoomLamp::setIsLampOn(bool value) {
    _isLampOn = value;

    this->removeChildByTag(lampTag);
    Sprite *lamp = nullptr;
    
    if (_isLampOn) {
        lamp = Sprite::create("SceneRoom/SceneRoomLampOn.png");
    }
    else {
        lamp = Sprite::create("SceneRoom/SceneRoomLampOff.png");
    }
    
    this->addChild(lamp, lampTag, lampTag);
    this->setContentSize(lamp->getContentSize());
}

void RoomLamp::setText(const std::string &text) {
    _text = text;
    
    auto label = dynamic_cast<Label*>(this->getChildByTag(lblTag));
    
    label->setString(_text);
    if (_isLampOn) {
        label->setColor(Color3B(170, 101, 17));
    }
    else {
        label->setColor(Color3B(151, 239, 187));
    }
}

void RoomLamp::setOpacity(GLubyte value) {
    this->getChildByTag(lampTag)->setOpacity(value);
    this->getChildByTag(lblTag)->setOpacity(value);
}

void RoomLamp::fadeOut() {
    this->runAction(FadeOut::create(1.0));
}
