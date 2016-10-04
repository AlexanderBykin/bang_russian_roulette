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

#ifndef __BrrClient__DialogDuel__
#define __BrrClient__DialogDuel__

#include "cocos2d.h"
#include "DialogBase.h"
#include "ProtoMessageDelegate.h"
#include "MessageResponse.pb.h"
#include "RoomPlayer.h"

USING_NS_CC;

#define DuelistPlayerFoundDecreaseMoneyNotification "DuelistPlayerFoundDecreaseMoney"

class DialogDuel : public DialogBase, public ProtoMessageDelegate {
public:
    static DialogDuel* create(long long roomId, Vector<Node*> players);
    bool init(long long roomId, Vector<Node*> players);
    void processProtoMessage(const eProtoMessageType messageType, const std::string &messageBody);
private:
    long long _roomId = 0L;
    Vector<Node*> _players;
    Node *_duelistLayer;
    RoomPlayer *findPlayerByPlayerId(long long playerId);
    void markDuelistByPosition(int playerPosition, long long playerId, bool isDuelist, int winAmount);
    // event callbacks
    void onMenuCallback(Ref* sender);
    void onDuelistPlayerTap(EventCustom *event);
    // api call
    void getRoomPlayerDuelist();
    void setPlayerDuelistAtPosition(int position);
    // api callbacks
    void callbackGetRoomPlayerDuelist(const std::string &source);
    void callbackSetPlayerDuelist(const std::string &source);
    void callbackRoomResults(const std::string &source);
};

#endif /* defined(__BrrClient__DialogDuel__) */
