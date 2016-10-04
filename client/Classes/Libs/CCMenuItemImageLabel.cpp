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

#include "CCMenuItemImageLabel.h"
#include "LabelShadow.h"

int _zoomActionTag = 314;

MenuItemImageLabel* MenuItemImageLabel::create(const std::string &bgImage, const std::string &label, const std::string &labelFontName, float labelFontSize, const Color3B &labelColor, const Color3B &labelShadowColor, const ccMenuCallback& callback) {
    MenuItemImageLabel *node = new (std::nothrow) MenuItemImageLabel();
    if(node && node->init(bgImage, label, labelFontName, labelFontSize, labelColor, labelShadowColor, callback)) {
        node->autorelease();
        return node;
    }
    CC_SAFE_DELETE(node);
    return nullptr;
}

bool MenuItemImageLabel::init(const std::string &bgImage, const std::string &label, const std::string &labelFontName, float labelFontSize, const Color3B &labelColor, const Color3B &labelShadowColor, const ccMenuCallback& callback){
    if(!initWithNormalSprite(Sprite::create(bgImage), nullptr, nullptr, callback)){
        return false;
    }
    
    _originalScale = this->getScale();
    
    if(!label.empty()) {
        auto labelShadow = LabelShadow::create(label, labelFontName, labelFontSize, labelColor, labelShadowColor);
        labelShadow->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
        labelShadow->setPosition(this->getContentSize().width/2, this->getContentSize().height/2+6);
        this->addChild(labelShadow, 10, 10);
    }

    return true;
}

MenuItemImageLabel::~MenuItemImageLabel(){
}

void MenuItemImageLabel::activate() {
    if (isEnabled()) {
        this->stopAllActions();
        this->setScale(_originalScale);
        MenuItemSprite::activate();
    }
}

void MenuItemImageLabel::selected() {
    // subclass to change the default action
    if (isEnabled()) {
        MenuItemSprite::selected();
        
        this->stopActionByTag(_zoomActionTag);
            
        auto zoomAction = ScaleTo::create(0.1f, _originalScale * 1.125f);
        zoomAction->setTag(_zoomActionTag);
        this->runAction(zoomAction);
    }
}

void MenuItemImageLabel::unselected() {
    // subclass to change the default action
    if (isEnabled()) {
        MenuItemSprite::unselected();
        this->stopActionByTag(_zoomActionTag);
        auto zoomAction = ScaleTo::create(0.1f, _originalScale);
        zoomAction->setTag(_zoomActionTag);
        this->runAction(zoomAction);
    }
}

void MenuItemImageLabel::setText(const std::string &value) {
    if(auto lbl = dynamic_cast<LabelShadow*>(this->getChildByTag(10)))
        lbl->setText(value);
}
