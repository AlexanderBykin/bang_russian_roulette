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

#ifndef __BrrClient__RoomPlayerDuelist__
#define __BrrClient__RoomPlayerDuelist__

#include "cocos2d.h"
#include "PlayerDuelistEntity.h"
#include "RoomPlayer.h"

USING_NS_CC;

#define RoomPlayerDuelistTapNotification "RoomPlayerDuelistTap"

class RoomPlayerDuelist : public Layer {
public:
    enum RoomPlayerDuelistDuelStateTypes {
        stDefault,
        stIsDuelist,
        stIsNotDuelist
    };
    bool init()  override;
    CREATE_FUNC(RoomPlayerDuelist);
    PlayerDuelistEntity *getPlayerDuelistEntity();
    void setPlayerDuelistEntity(PlayerDuelistEntity *value);
    void setPlayer(RoomPlayer *value);
    void updateState();
private:
    enum SceneTags {
        bgTag = 100,
        avatarTag,
        winAmountTag
    };
    EventListenerTouchOneByOne* _touchListener;
    RoomPlayerDuelistDuelStateTypes _playerDuelState = RoomPlayerDuelistDuelStateTypes::stDefault;
    PlayerDuelistEntity *_playerDuelistEntity;
    RoomPlayer *_player;
    void setPlayerDuelState(RoomPlayerDuelistDuelStateTypes value);
    void onUpdateAfterDelay(float value);
    bool onTouchBegan(Touch *touch, Event *event) override;
    void onTouchEnded(Touch *touch, Event *event) override;
};

#endif