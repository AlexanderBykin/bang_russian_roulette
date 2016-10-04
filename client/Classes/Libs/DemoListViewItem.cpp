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

#include "DemoListViewItem.h"
#include "GlobalProperties.h"

DemoListViewItem* DemoListViewItem::create(const std::string text, int maxWidth, TextHAlignment hAlignment) {
    DemoListViewItem *node = new (std::nothrow) DemoListViewItem();
    if(node && node->init(text, maxWidth, hAlignment)) {
        node->autorelease();
        return node;
    }
    CC_SAFE_DELETE(node);
    return nullptr;
}

bool DemoListViewItem::init(const std::string text, int maxWidth, TextHAlignment hAlignment) {
    if(!Widget::init()) {
        return false;
    }
    
    auto lblText = Label::createWithTTF(text, GameFont, 30);
    lblText->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    lblText->setDimensions(maxWidth, 0);
    lblText->setHorizontalAlignment(hAlignment);
    this->addChild(lblText);
    
    this->setContentSize(Size(lblText->getContentSize().width, lblText->getContentSize().height));
    
    return true;
}