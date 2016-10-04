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

#ifndef __BrrClient__RoomPlayer__
#define __BrrClient__RoomPlayer__

#include "cocos2d.h"
#include "PlayerShootDirection.pb.h"
#include "RotateRadianDelegate.h"

USING_NS_CC;

#define RoomPlayerTapNotification "RoomPlayerTap"
#define RoomPlayerFadeOutCompleteNotification "RoomPlayerFadeOutComplete"
#define PlayerEntityChangeAvatarNotification "PlayerEntityChangeAvatar"
#define PlayerEntityChangeShootDirectionNotification "PlayerEntityChangeShootDirection"
#define PlayerEntityChangeCurrentRadianNotification "PlayerEntityChangeCurrentRadian"

class RoomPlayer : public Layer, public RotateRadianDelegate {
public:
    enum RoomPlayerStateTypes {
        RoomPlayerStateTypeKilled = 50,
        RoomPlayerStateTypeSelected,
        RoomPlayerStateTypeCurrent,
        RoomPlayerStateTypeEnemy,
        RoomPlayerStateTypeDefault
    };
    static RoomPlayer* create(long long playerId, const std::string &playerName, int playerPosition, const std::string &avatar, PlayerShootDirection shootDirection, double radian, RoomPlayerStateTypes playerState);
    bool init(long long playerId, const std::string &playerName, int playerPosition, const std::string &avatar, PlayerShootDirection shootDirection, double radian, RoomPlayerStateTypes playerState);
    long long getPlayerId();
    void setPlayerId(long long value);
    void setPlayerState(RoomPlayerStateTypes value);
    int getPlayerPosition();
    bool getIsDuelist();
    void setPlayerPosition(int value);
    void setPlayerName(const std::string &value);
    double getRadian();
    void setRadian(double value);
    const std::string& getAvatar();
    void setAvatar(const std::string &value);
    PlayerShootDirection getShootDirection();
    void setShootDirection(PlayerShootDirection value);
    void setOpacity(GLubyte value);
    int getPlayerAmount();
    void setPlayerAmount(int value);
    void fadeOut(bool withCallback);
    void updatePosition();
    void animateRotationToRadian(double radian, bool roomClockWise, bool withRoomClockWise, int playerAmount);
    void setTouchEnable(bool value);
    void animateRotationWithPlayerId(long long destPlayerId, bool roomClockWise, bool withRoomClockWise, int playerAmount);
private:
    enum SceneTags {
        bgTag = 100,
        avatarTag,
        lblPosTag,
        animationTag
    };
    long long _playerId = 0L;
    int _playerAmount = 0;
    double _currentRadian = 0.0;
    std::string _avatar;
    std::string _playerName;
    Vec2 _center;
    double _radius;
    int _playerPosition = 0;
    PlayerShootDirection _shootDirection;
    RoomPlayerStateTypes _playerState = RoomPlayerStateTypeDefault;
    EventListenerTouchOneByOne* _touchListener;
    bool _sendCallbackAfterAnimation;
    RoomPlayerStateTypes _prevPlayerState;
    double _destRadian;
    void animationRotationDidFinish();
    void didFinishFadeOut();
    bool onTouchBegan(Touch *touch, Event *event);
    void onTouchEnded(Touch *touch, Event *event);
};

#endif /* defined(__BrrClient__RoomPlayer__) */
