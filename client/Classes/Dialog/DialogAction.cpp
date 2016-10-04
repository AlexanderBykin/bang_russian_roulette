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

#include "DialogAction.h"
#include "LanguageManager.h"
#include "CCMenuItemImageLabel.h"
#include "GlobalProperties.h"
#include "audio/include/AudioEngine.h"

bool DialogAction::init() {
    if(!DialogBase::init()) {
        return false;
    }
    
    this->setCaption(LanguageManager::getString("DialogActionCaption"));
    this->setIsCloseable(true);
    
    Size winSize = Director::getInstance()->getVisibleSize();
    
    // action buttons
    
    auto btnPlayerInfo = MenuItemImageLabel::create("Dialog/btnDialogActionPlayerInfo.png",
                                                    "",
                                                    GameFont,
                                                    0,
                                                    Color3B(0, 0, 0),
                                                    Color3B(0, 0, 0),
                                                    CC_CALLBACK_1(DialogAction::onMenuCallback, this));
    btnPlayerInfo->setTag(1);
    
    // отключаем до продумывания букмекерской системы
    /*CCMenuItem *btnPlayerBet = [[CCMenuItemButton alloc] initWithLabel:@"" andFontName:@"" andFontSize:0 andTextColor:ccc3(0, 0, 0) andShadowTextColor:ccc3(0, 0, 0) andBgImage:[CCSprite spriteWithFile:@"btnDialogActionPlayerBet.png"] target:self selector:@selector(btnClick:)];
     btnPlayerBet.tag = 2;*/
    
    auto btnPlayerInventory = MenuItemImageLabel::create("Dialog/btnDialogActionPlayerUseItem.png",
                                                         "",
                                                         GameFont,
                                                         0,
                                                         Color3B(0, 0, 0),
                                                         Color3B(0, 0, 0),
                                                         CC_CALLBACK_1(DialogAction::onMenuCallback, this));
    btnPlayerInventory->setTag(3);
    
    auto mButtons = Menu::create(btnPlayerInfo, /*btnPlayerBet,*/ btnPlayerInventory, nullptr);
    mButtons->alignItemsHorizontallyWithPadding(130);
    mButtons->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
    this->addChild(mButtons);
    
    // button labels
    
    auto lblPlayerInfo = Label::createWithTTF(LanguageManager::getString("DialogActionInfoLabel"), GameFont, 38);
    lblPlayerInfo->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    lblPlayerInfo->setPosition(Vec2(winSize.width / 2 - 200, 300));
    lblPlayerInfo->setColor(Color3B(56, 37, 27));
    this->addChild(lblPlayerInfo);
    
    // отключаем до продумывания букмекерской системы
    /*CCLabelTTF *lblPlayerBet = [CCLabelTTF labelWithString:[LanguageManager localizedString:@"DialogActionBetLabel"] fontName:GameFontBold fontSize:[BRRUtilities getValueByInterfaceIdiomPhone:14 orPad:28]];
     lblPlayerBet.position = ccp([BRRUtilities getValueByInterfaceIdiomPhone:240 orPad:510], [BRRUtilities getValueByInterfaceIdiomPhone:90 orPad:250]);
     lblPlayerBet.color = ccc3(56, 37, 27);
     [self addChild:lblPlayerBet];*/
    
    auto lblPlayerInventory = Label::createWithTTF(LanguageManager::getString("DialogActionInventoryLabel"), GameFont, 38);
    lblPlayerInventory->setPosition(Vec2(winSize.width / 2 + 200, 300));
    lblPlayerInventory->setColor(Color3B(56, 37, 27));
    this->addChild(lblPlayerInventory);
    
    return true;
}

void DialogAction::onMenuCallback(cocos2d::Ref *sender) {
    auto node = dynamic_cast<Node*>(sender);
    experimental::AudioEngine::play2d("Sounds/btnmenu_click.mp3");
    if(_delegate) {
        _delegate->onDialogButtonTap(this, node->getTag(), {});
    }
}