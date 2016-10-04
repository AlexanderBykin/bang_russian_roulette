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

#include "DialogDuel.h"
#include "LanguageManager.h"
#include "MessageRequestRoomPlayerDuelist.pb.h"
#include "SocketThread.h"
#include "ProtoMessageType.pb.h"
#include "MessageResponseRoomPlayerDuelist.pb.h"
#include "Utils.h"
#include "MessageResponseRoundPlayerDuelist.pb.h"
#include "GlobalProperties.h"
#include "RoomPlayerDuelist.h"
#include "PlayerDuelistEntity.h"
#include "MessageRequestSetPlayerDuelist.pb.h"
#include "MessageResponseSetPlayerDuelist.pb.h"
#include "MessageResponseTimeToResults.pb.h"
#include "PluginGoogleAnalytics/PluginGoogleAnalytics.h"

DialogDuel* DialogDuel::create(long long roomId, Vector<Node*> players) {
    DialogDuel *node = new (std::nothrow) DialogDuel();
    if(node && node->init(roomId, players)) {
        node->autorelease();
        return node;
    }
    CC_SAFE_DELETE(node);
    return nullptr;
}

bool DialogDuel::init(long long roomId, Vector<Node*> players) {
    if(!DialogBase::init()) {
        return false;
    }
    
    sdkbox::PluginGoogleAnalytics::logScreen("DialogDuel");
    
    this->setCaption(LanguageManager::getString("DialogDuelCaption"));
    
    auto listenerDuelistPlayerTap = EventListenerCustom::create(RoomPlayerDuelistTapNotification, CC_CALLBACK_1(DialogDuel::onDuelistPlayerTap, this));
    
    _eventDispatcher->addEventListenerWithFixedPriority(listenerDuelistPlayerTap, 1);

    _players = players;
    _roomId = roomId;
    _duelistLayer = Node::create();
    
    this->addChild(_duelistLayer);
    
    this->getRoomPlayerDuelist();
    
    
    
//    MessageResponseRoomPlayerDuelist msg;
//    int i = 1;
//    for(auto item : _players) {
//        auto roomPlayer = dynamic_cast<RoomPlayer*>(item);
//        msg.set_roomid(_roomId);
//        auto duelistInfo = msg.add_playerlist();
//        duelistInfo->set_playerid(roomPlayer->getPlayerId());
////        duelistInfo->set_playerid(-1L);
//        duelistInfo->set_playerisduelist(_players.getIndex(item) % 2 == 0);
//        duelistInfo->set_playerposition(i);
//        duelistInfo->set_winamount(100);
//        i++;
//    }
//    this->callbackGetRoomPlayerDuelist(msg.SerializeAsString());
    
    
    
    return true;
}


void DialogDuel::onDuelistPlayerTap(EventCustom *event) {
    int position = *((int*)(event->getUserData()));
    this->setPlayerDuelistAtPosition(position);
}

RoomPlayer *DialogDuel::findPlayerByPlayerId(long long playerId) {
    for (auto subItem : _players) {
        auto roomPlayer = dynamic_cast<RoomPlayer*>(subItem);
        if (roomPlayer->getPlayerId() == playerId) {
            return roomPlayer;
        }
    }
    
    return nullptr;
}

void DialogDuel::markDuelistByPosition(int playerPosition, long long playerId, bool isDuelist, int winAmount) {
    for (auto child : _duelistLayer->getChildren()) {
        auto item = dynamic_cast<RoomPlayerDuelist*>(child);
        if (item->getPlayerDuelistEntity()->getPosition() == playerPosition && item->getPlayerDuelistEntity()->getPlayerId() <= 0) {
            item->getPlayerDuelistEntity()->setPlayerId(playerId);
            item->getPlayerDuelistEntity()->setIsDuelist(isDuelist);
            item->getPlayerDuelistEntity()->setWinAmount(winAmount);
            
            for (auto subItem : _players) {
                auto roomPlayer = dynamic_cast<RoomPlayer*>(subItem);
                if (roomPlayer->getPlayerId() == item->getPlayerDuelistEntity()->getPlayerId()) {
                    item->setPlayer(roomPlayer);
                    // убираем не дуэлянтов
                    if (!item->getPlayerDuelistEntity()->getIsDuelist()) {
                        roomPlayer->setPlayerId(-1);
                        EventCustom event(DuelistPlayerFoundDecreaseMoneyNotification);
                        event.setUserData(new int(item->getPlayerDuelistEntity()->getWinAmount()));
                        _eventDispatcher->dispatchEvent(&event);
                    }
                    break;
                }
            }
            
            item->updateState();
            break;
        }
    }
}

// api call

void DialogDuel::getRoomPlayerDuelist() {
    sdkbox::PluginGoogleAnalytics::logEvent("ApiCall", "getRoomPlayerDuelist", "", 0);
    MessageRequestRoomPlayerDuelist msg;
    msg.set_roomid(_roomId);
    SocketThread::getInstance()->getSocket()->Send(this->wrapMessage(eProtoMessageType::cmtGetRoomPlayersDuelist, msg));
}

void DialogDuel::setPlayerDuelistAtPosition(int position) {
    sdkbox::PluginGoogleAnalytics::logEvent("ApiCall", "setPlayerDuelistAtPosition", "", 0);
    MessageRequestSetPlayerDuelist msg;
    msg.set_roomid(_roomId);
    msg.set_position(position);
    SocketThread::getInstance()->getSocket()->Send(this->wrapMessage(eProtoMessageType::cmtSetPlayerDuelist, msg));
}


// api callbacks

void DialogDuel::processProtoMessage(const eProtoMessageType messageType, const std::string &messageBody) {
    switch (messageType) {
        case eProtoMessageType::cmtGetRoomPlayersDuelist: {
            this->callbackGetRoomPlayerDuelist(messageBody);
            break;
        }
            
        case eProtoMessageType::cmtSetPlayerDuelist: {
            this->callbackSetPlayerDuelist(messageBody);
            break;
        }
            
        case eProtoMessageType::cmtRoomResults: {
            this->callbackRoomResults(messageBody);
            break;
        }
            
        default:
            break;
    }
}

void DialogDuel::callbackGetRoomPlayerDuelist(const std::string &source) {
    sdkbox::PluginGoogleAnalytics::logEvent("ApiCallback", "callbackGetRoomPlayerDuelist", "", 0);
    if (source.empty())
        return;
    
    MessageResponseRoomPlayerDuelist msg;
    msg.ParseFromString(source);
    
    if (msg.roomid() != _roomId) {
        return;
    }
    
    _duelistLayer->removeAllChildrenWithCleanup(true);
    
    int itemIndex = 1;
    int itemCount = msg.playerlist().size();
    double offsetX = 70;
    int currentRow = 1;
    bool isRowChanged = false;
    Size winSize = Director::getInstance()->getVisibleSize();

    for (auto item : msg.playerlist()) {
        auto playerDuelist = RoomPlayerDuelist::create();
        playerDuelist->setPlayerDuelistEntity(PlayerDuelistEntity::create(item.playerid(), item.playerposition(), item.playerisduelist()));
        
        if (playerDuelist->getPlayerDuelistEntity()->getPlayerId() > 0) {
            playerDuelist->setPlayer(this->findPlayerByPlayerId(playerDuelist->getPlayerDuelistEntity()->getPlayerId()));
        }
        
        playerDuelist->updateState();
        //log(">>> duelist size(%f, %f)", playerDuelist->getContentSize().width, playerDuelist->getContentSize().height);

        double itemSize = playerDuelist->getContentSize().width;
        double x = 0;
        double y = 0;
        
        // размещаем шарики равномерно по диалогу
        switch (itemCount) {
            case 3: {
                x = this->_dialogRect.origin.x + (this->_dialogRect.size.width / 3 * itemIndex) - (itemSize / 2) - offsetX;
                y = winSize.height / 2;
                break;
            }
                
            case 4: {
                if (!isRowChanged) {
                    if (itemIndex > 2) {
                        isRowChanged = true;
                        currentRow = 2;
                        itemIndex -= 2;
                    } else {
                        currentRow = 1;
                    }
                }
                
                x = this->_dialogRect.origin.x + (this->_dialogRect.size.width / 2 * itemIndex) - itemSize - offsetX;
                y = (currentRow == 1)
                ? winSize.height / 2 + itemSize / 2
                : winSize.height / 2 - itemSize / 2 - offsetX / 2;
                break;
            }
                
            case 5: {
                if (!isRowChanged) {
                    if (itemIndex > 3) {
                        isRowChanged = true;
                        currentRow = 2;
                        itemIndex = 1;
                    } else {
                        currentRow = 1;
                    }
                }
                
                if (currentRow == 1) {
                    x = this->_dialogRect.origin.x + (this->_dialogRect.size.width / 3 * itemIndex) - (itemSize / 2) - offsetX;
                } else {
                    x = (itemIndex < 2)
                    ? this->_dialogRect.origin.x + this->_dialogRect.size.width / 2 - itemSize + offsetX / 2
                    : this->_dialogRect.origin.x + this->_dialogRect.size.width / 2 + itemSize - offsetX / 2;
                }
                
                y = (currentRow == 1)
                ? winSize.height / 2 + itemSize / 2
                : winSize.height / 2 - itemSize / 2 - offsetX / 2;
                break;
            }
                
            case 6: {
                if (!isRowChanged) {
                    if (itemIndex > 3) {
                        isRowChanged = true;
                        currentRow = 2;
                        itemIndex = 1;
                    } else {
                        currentRow = 1;
                    }
                }
                
                x = this->_dialogRect.origin.x + (this->_dialogRect.size.width / 3 * itemIndex) - (itemSize / 2) - offsetX;
                y = (currentRow == 1)
                ? winSize.height / 2 + itemSize / 2
                : winSize.height / 2 - itemSize / 2 - offsetX / 2;
                break;
            }
                
            default:
                break;
        }
        
        if (GlobalProperties::isDebug()) {
            log("itemIndex=%d currentRow=%d x=%f y=%f", itemIndex, currentRow, x, y);
            log("callbackGetRoomPlayerDuelist playerId=%lli position=%d duelist=%i", item.playerid(), item.playerposition(), item.playerisduelist());
        }
        
        playerDuelist->setPosition(Vec2(x, y));
        
        _duelistLayer->addChild(playerDuelist);
        
        itemIndex++;
    }
}

void DialogDuel::callbackSetPlayerDuelist(const std::string &source) {
    sdkbox::PluginGoogleAnalytics::logEvent("ApiCallback", "callbackSetPlayerDuelist", "", 0);
    if (source.size() == 0)
        return;
    
    MessageResponseSetPlayerDuelist msg;
    msg.ParseFromString(source);
    
    if (msg.roomid() != _roomId) {
        return;
    }
    
    this->markDuelistByPosition(msg.playerinfo().playerposition(), msg.playerinfo().playerid(), msg.playerinfo().playerisduelist(), msg.playerinfo().winamount());
}

void DialogDuel::callbackRoomResults(const std::string &source) {
    sdkbox::PluginGoogleAnalytics::logEvent("ApiCallback", "callbackRoomResults", "", 0);
    if (source.size() == 0)
        return;
    
    MessageResponseTimeToResults msg;
    msg.ParseFromString(source);
    auto resultType = msg.resulttype();
    
    if (msg.roomid() != _roomId || resultType != MessageResponseTimeToResults_eRoomResultType_rrtPlayerDuelist) {
        return;
    }
    
    for (auto roomDuelistResult : msg.duelistresults()) {
        this->markDuelistByPosition(roomDuelistResult.playerposition(), roomDuelistResult.playerid(), roomDuelistResult.playerisduelist(), roomDuelistResult.winamount());
    }
}
