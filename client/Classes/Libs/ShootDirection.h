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

#ifndef __BrrClient__ShootDirection__
#define __BrrClient__ShootDirection__

#include "cocos2d.h"
#include "RoomPlayer.h"

USING_NS_CC;

#define ShootDirectionFadeOutCompleteNotification "ShootDirectionFadeOutComplete"

class ShootDirection : public Layer {
public:
    static ShootDirection* create(RoomPlayer* player);
    bool init(RoomPlayer* player);
    void setOpacity(GLubyte value);
    void fadeOut(bool withCallback);
    RoomPlayer *getPlayer();
    ~ShootDirection();
private:
    enum SceneTags {
        bgTag = 100,
        lblPosTag
    };
    bool _isAnimationEnabled;
    double _radius;
    Vec2 _center;
    bool _isClockWise;
    bool _sendCallbackAfterAnimation;
    RoomPlayer* _player;
    EventListenerCustom *_listenerPlayerEntityChangeShootDirection;
    EventListenerCustom *_listenerPlayerEntityChangeRadian;
    void updateShootDirection();
    void updatePosition();
    void didFinishFadeOut();
    void onPlayerEntityDidChangeShootDirection(EventCustom *event);
    void onPlayerEntityDidChangeCurrentRadian(EventCustom *event);
};

#endif /* defined(__BrrClient__PlayerShootDirection__) */