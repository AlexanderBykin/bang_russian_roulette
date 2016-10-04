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

#ifndef __BrrClient__DialogPutBullet__
#define __BrrClient__DialogPutBullet__

#include "cocos2d.h"
#include "DialogBase.h"

USING_NS_CC;

class DialogPutBullet : public DialogBase {
public:
    static DialogPutBullet *create(int possibleAmountBullets);
    bool init(int possibleAmountBullets);
private:
    enum SceneTags {
        lblAvailableBulletsTag = 100
    };
    int _possibleAmountBullets = 0;
    bool _bullets[6];
    void setAvailableBullets(int value);
    void onMenuCallback(Ref* sender);
};

#endif /* defined(__BrrClient__DialogPutBullet__) */
