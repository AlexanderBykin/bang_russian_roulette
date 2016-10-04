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

#include "RoomRoundGameResult.h"

RoomRoundGameResult* RoomRoundGameResult::create(long long playerId, int position, long long killedPlayerId, int killedPlayerPosition) {
    RoomRoundGameResult *node = new (std::nothrow) RoomRoundGameResult();
    if(node && node->init(playerId, position, killedPlayerId, killedPlayerPosition)) {
        node->autorelease();
        return node;
    }
    CC_SAFE_DELETE(node);
    return nullptr;
}

bool RoomRoundGameResult::init(long long playerId, int position, long long killedPlayerId, int killedPlayerPosition) {
    _playerId = playerId;
    _position = position;
    _killedPlayerId = killedPlayerId;
    _killedPlayerPosition = killedPlayerPosition;
    return true;
}

long long RoomRoundGameResult::getPlayerId() {
    return _playerId;
}

int RoomRoundGameResult::getPosition() {
    return _position;
}

long long RoomRoundGameResult::getKilledPlayerId() {
    return _killedPlayerId;
}

int RoomRoundGameResult::getKilledPlayerPosition() {
    return _killedPlayerPosition;
}