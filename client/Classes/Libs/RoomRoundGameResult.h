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

#ifndef __BrrClient__RoomRoundGameResult__
#define __BrrClient__RoomRoundGameResult__

#include "cocos2d.h"

USING_NS_CC;

class RoomRoundGameResult : public Ref {
public:
    static RoomRoundGameResult* create(long long playerId, int position, long long killedPlayerId, int killedPlayerPosition);
    bool init(long long playerId, int position, long long killedPlayerId, int killedPlayerPosition);
    long long getPlayerId();
    int getPosition();
    long long getKilledPlayerId();
    int getKilledPlayerPosition();
private:
    long long _playerId;
    int _position;
    long long _killedPlayerId;
    int _killedPlayerPosition;
};

#endif 
