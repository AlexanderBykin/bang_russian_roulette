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

#include "CCMenuItemImageLabelSelectable.h"
#include "LabelShadow.h"

MenuItemImageLabelSelectable* MenuItemImageLabelSelectable::create(const std::string &bgImage, const std::string &bgSelectedImage, const std::string &label, const std::string &labelFontName, float labelFontSize, const Color3B &labelColor, const Color3B &labelShadowColor, const Color3B &labelSelectedColor, const Color3B &labelSelectedShadowColor, const ccMenuCallback& callback){
    MenuItemImageLabelSelectable *node = new (std::nothrow) MenuItemImageLabelSelectable();
    if(node && node->init(bgImage, bgSelectedImage, label, labelFontName, labelFontSize, labelColor, labelShadowColor, labelSelectedColor, labelSelectedShadowColor, callback)) {
        node->autorelease();
        return node;
    }
    CC_SAFE_DELETE(node);
    return nullptr;
}

bool MenuItemImageLabelSelectable::init(const std::string &bgImage, const std::string &bgSelectedImage, const std::string &label, const std::string &labelFontName, float labelFontSize, const Color3B &labelColor, const Color3B &labelShadowColor, const Color3B &labelSelectedColor, const Color3B &labelSelectedShadowColor, const ccMenuCallback& callback){
    if(!initWithNormalSprite(Sprite::create(bgImage), Sprite::create(bgSelectedImage), nullptr, callback)){
        return false;
    }
    
    _labelColor = labelColor;
    _labelShadowColor = labelShadowColor;
    _labelSelectedColor = labelSelectedColor;
    _labelSelectedShadowColor = labelSelectedShadowColor;
    
    auto labelShadow = LabelShadow::create(label,labelFontName, labelFontSize, _labelColor, _labelShadowColor);
    labelShadow->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    labelShadow->setPosition(Vec2(this->getContentSize().width/2, this->getContentSize().height/2+6));
    this->addChild(labelShadow, 10, _labelShadowTag);
    
    return true;
}

MenuItemImageLabelSelectable::~MenuItemImageLabelSelectable(){
}

void MenuItemImageLabelSelectable::selected() {
    LabelShadow *text = dynamic_cast<LabelShadow*>(this->getChildByTag(_labelShadowTag));
    text->setTextColor(_labelSelectedColor);
    text->setTextShadowColor(_labelSelectedShadowColor);
    MenuItemSprite::selected();
}

void MenuItemImageLabelSelectable::unselected() {
    LabelShadow *text = dynamic_cast<LabelShadow*>(this->getChildByTag(_labelShadowTag));
    text->setTextColor(_labelColor);
    text->setTextShadowColor(_labelShadowColor);
    MenuItemSprite::unselected();
}