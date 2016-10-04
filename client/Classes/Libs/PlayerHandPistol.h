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

#ifndef __BrrClient__PlayerHandPistol__
#define __BrrClient__PlayerHandPistol__

#include "cocos2d.h"
#include "RotateRadianDelegate.h"
#include "RoomPlayer.h"

USING_NS_CC;

class PlayerHandPistol : public Layer, public RotateRadianDelegate {
public:
    enum PlayerHandPistolState {
        PlayerHandPistolStateHand,
        PlayerHandPistolStateKilled,
        PlayerHandPistolStateNotKilled
    };
    static PlayerHandPistol* create(RoomPlayer *player);
    bool init(RoomPlayer *player);
    void updatePosition();
    void updateRotation();
    void showAnimated();
    void setRadian(double value);
    RoomPlayer* getPlayer();
    void setHandPistolState(PlayerHandPistolState value);
    ~PlayerHandPistol();
private:
    enum SceneTags {
        pistol1Tag = 100,
        pistol2Tag
    };
    RoomPlayer *_player;
    PlayerHandPistolState _handPistolState;
    double _radius;
    Vec2 _center;
    bool _isClockWise;
    EventListenerCustom *_listenerPlayerEntityChangeShootDirection;
    EventListenerCustom *_listenerPlayerEntityChangeRadian;
    void onPlayerEntityDidChangeShootDirection(EventCustom *event);
    void onPlayerEntityDidChangeCurrentRadian(EventCustom *event);
};

#endif 