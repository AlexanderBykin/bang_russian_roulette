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

#ifndef __BrrClient__PlayerDuelistEntity__
#define __BrrClient__PlayerDuelistEntity__

#include "cocos2d.h"

USING_NS_CC;

class PlayerDuelistEntity : public Ref {
public:
    static PlayerDuelistEntity *create(long long playerId, int position, bool isDuelist);
    bool init(long long playerId, int position, bool isDuelist);
    long long getPlayerId();
    int getPosition();
    bool getIsDuelist();
    int getWinAmount();
    void setPlayerId(long long value);
    void setPosition(int value);
    void setIsDuelist(bool value);
    void setWinAmount(int value);
private:
    long long _playerId = 0L;
    int _position = 0;
    bool _isDuelist = false;
    int _winAmount = 0;
};

#endif /* defined(__BrrClient__PlayerDuelistEntity__) */
