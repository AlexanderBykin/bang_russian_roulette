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

#include "DialogRole.h"
#include "LanguageManager.h"
#include "CCMenuItemImageLabel.h"
#include "GlobalProperties.h"
#include "audio/include/AudioEngine.h"

bool DialogRole::init() {
    if(!DialogBase::init()) {
        return false;
    }
    
    this->setCaption(LanguageManager::getString("DialogRoleCaption"));
    this->setIsCloseable(true);
    
    Size winSize = Director::getInstance()->getVisibleSize();
    
    auto btnRolePlayer = MenuItemImageLabel::create("Dialog/btnDialogRolePlayer.png",
                                                    "",
                                                    GameFont,
                                                    0,
                                                    Color3B(0, 0, 0),
                                                    Color3B(0, 0, 0),
                                                    CC_CALLBACK_1(DialogRole::onMenuCallback, this));
    btnRolePlayer->setTag(miRolePlayerTag);
    
    // убираем до момента когда будет продумана букмекерская система
    /*CCMenuItem *btnRoleInvestor = [[CCMenuItemButton alloc] initWithLabel:@"" andFontName:@"" andFontSize:0 andTextColor:ccc3(0, 0, 0) andShadowTextColor:ccc3(0, 0, 0) andBgImage:[CCSprite spriteWithFile:@"btnDialogRoleInvestor.png"] target:self selector:@selector(btnClick:)];
     btnRoleInvestor.tag = 2;*/
    
    auto btnRoleWatcher = MenuItemImageLabel::create("Dialog/btnDialogRoleWatcher.png",
                                                     "",
                                                     GameFont,
                                                     0,
                                                     Color3B(0, 0, 0),
                                                     Color3B(0, 0, 0),
                                                     CC_CALLBACK_1(DialogRole::onMenuCallback, this));
    btnRoleWatcher->setTag(miRoleWatcherTag);
    
    auto mButtons = Menu::create(btnRolePlayer, /*btnRoleInvestor,*/ btnRoleWatcher, nullptr);
    mButtons->alignItemsHorizontallyWithPadding(130);
    mButtons->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
    this->addChild(mButtons);
    
    // button labels
    
    auto lblRolePlayer = Label::createWithTTF(LanguageManager::getString("DialogRolePlayerLabel"), GameFont, 38);
    lblRolePlayer->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    lblRolePlayer->setPosition(Vec2(winSize.width / 2 - 200, 300));
    lblRolePlayer->setColor(Color3B(56, 37, 27));
    this->addChild(lblRolePlayer);
    
    // убираем до момента когда будет продумана букмекерская система
    /*CCLabelTTF *lblRoleInvestor = [CCLabelTTF labelWithString:[LanguageManager localizedString:@"DialogRoleInvestorLabel"] fontName:GameFontBold fontSize:[BRRUtilities getValueByInterfaceIdiomPhone:14 orPad:28]];
     lblRoleInvestor.position = ccp([BRRUtilities getValueByInterfaceIdiomPhone:240 orPad:510], [BRRUtilities getValueByInterfaceIdiomPhone:90 orPad:250]);
     lblRoleInvestor.color = ccc3(56, 37, 27);
     [self addChild:lblRoleInvestor];*/
    
    auto lblRoleWatcher = Label::createWithTTF(LanguageManager::getString("DialogRoleWatcherLabel"), GameFont, 38);
    lblRoleWatcher->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    lblRoleWatcher->setPosition(Vec2(winSize.width / 2 + 200, 300));
    lblRoleWatcher->setColor(Color3B(56, 37, 27));
    this->addChild(lblRoleWatcher);
    
    return true;
}

void DialogRole::onMenuCallback(cocos2d::Ref *sender) {
    auto node = dynamic_cast<Node*>(sender);
    experimental::AudioEngine::play2d("Sounds/btnmenu_click.mp3");
    if(_delegate) {
        _delegate->onDialogButtonTap(this, node->getTag(), {});
    }
}