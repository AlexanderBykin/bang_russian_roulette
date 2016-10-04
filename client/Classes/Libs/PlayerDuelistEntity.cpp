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

#include "PlayerDuelistEntity.h"

PlayerDuelistEntity *PlayerDuelistEntity::create(long long playerId, int position, bool isDuelist) {
    PlayerDuelistEntity *node = new (std::nothrow) PlayerDuelistEntity();
    if(node && node->init(playerId, position, isDuelist)) {
        node->autorelease();
        return node;
    }
    CC_SAFE_DELETE(node);
    return nullptr;
}

bool PlayerDuelistEntity::init(long long playerId, int position, bool isDuelist) {
    _playerId = playerId;
    _position = position;
    _isDuelist = isDuelist;
    
    return true;
}

long long PlayerDuelistEntity::getPlayerId() {
    return _playerId;
}

int PlayerDuelistEntity::getPosition() {
    return _position;
}

bool PlayerDuelistEntity::getIsDuelist() {
    return _isDuelist;
}

int PlayerDuelistEntity::getWinAmount() {
    return _winAmount;
}

void PlayerDuelistEntity::setPlayerId(long long value) {
    _playerId = value;
}

void PlayerDuelistEntity::setPosition(int value) {
    _position = value;
}

void PlayerDuelistEntity::setIsDuelist(bool value) {
    _isDuelist = value;
}

void PlayerDuelistEntity::setWinAmount(int value) {
    _winAmount = value;
}
