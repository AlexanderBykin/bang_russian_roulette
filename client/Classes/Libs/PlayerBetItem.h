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

#ifndef __BrrClient__PlayerBetItem__
#define __BrrClient__PlayerBetItem__

#include "cocos2d.h"
#include "PlayerBetWinType.pb.h"

USING_NS_CC;

#define PlayerBetItemDidFinishAnimationNotification "PlayerBetItemDidFinishAnimation"

class PlayerBetItem : public Layer {
public:
    static PlayerBetItem* create(Vec2 startPoint, Vec2 destPoint, int amount, PlayerBetWinType winType);
    bool init(Vec2 startPoint, Vec2 destPoint, int amount, PlayerBetWinType winType);
    void animate();
    int getAmount();
private:
    Vec2 _startPoint;
    Vec2 _destPoint;
    int _amount;
    Vec2 _finishPoint;
    PlayerBetWinType _winType;
    void didFinishAnimation1();
    void didFinishAnimation2();
};

#endif 
