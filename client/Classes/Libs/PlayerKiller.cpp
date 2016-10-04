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

#include "PlayerKiller.h"

bool PlayerKiller::init() {
    if(!Layer::init()) {
        return false;
    }
    
    this->setIsShoot(false);
    
    return true;
}

void PlayerKiller::setIsShoot(bool value) {
    this->removeChildByTag(killerTag);

    Sprite *killerSprite = nullptr;
    
    if (value) {
        killerSprite = Sprite::create("SceneRoom/SceneRoomKillerShoot.png");
    } else {
        killerSprite = Sprite::create("SceneRoom/SceneRoomKiller.png");
    }
    
    Size winSize = Director::getInstance()->getVisibleSize();
    
    killerSprite->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    killerSprite->setPosition(Vec2(0, winSize.height - killerSprite->getContentSize().height));
    this->addChild(killerSprite, killerTag, killerTag);
    
    /*if(value){
     [self scheduleOnce:@selector(restoreKillerAfterShoot:) delay:0.6f];
     }*/
}

/*-(void)restoreKillerAfterShoot:(ccTime)delta{
 [self isShoot:NO];
 }*/

void PlayerKiller::setOpacity(GLubyte value) {
    if (auto sprite = dynamic_cast<Sprite*>(this->getChildByTag(killerTag))) {
        sprite->setOpacity(value);
    }
}