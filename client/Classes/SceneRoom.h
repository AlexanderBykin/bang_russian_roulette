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

#ifndef __BrrClient__SceneRoom__
#define __BrrClient__SceneRoom__

#include "cocos2d.h"
#include "ProtoMessageDelegate.h"
#include "MessageRequestSetPlayerTypeAndPosition.pb.h"
#include "RoomPlayer.h"
#include "RoomShootDirection.pb.h"
#include "DialogBase.h"
#include "ShootDirection.h"
#include "RoomRoundGameResult.h"
#include "MessageResponseRoundPlayerBang.pb.h"

USING_NS_CC;

class SceneRoom : public Layer, public ProtoMessageDelegate, public DialogDelegate {
public:
    static SceneRoom *create(long long roomId);
    bool init(long long roomId);
    void processProtoMessage(const eProtoMessageType messageType, const std::string &messageBody) override;
    void onDialogButtonTap(Ref* sender, int buttonIndex, std::map<std::string, std::string> userData) override;
    ~SceneRoom();
    void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event) override;
private:
    enum SceneTags {
        lampTag = 100,
        killerTag,
        layerShootDirectionTag,
        layerPlayerHandPistolTag,
        layerPlayerTag,
        miBackTag,
        txtBankTag,
        txtRoundTag,
        txtTimeTag,
        miRotateDrumTag,
        miShootTag,
        shootDirectionTag
    };
    EventListenerCustom *_listenerPlayerTap;
    EventListenerCustom *_listenerShopItemUsedDidFinishAnimation;
    EventListenerCustom *_listenerPlayerBetItemDidFinishAnimation;
    EventListenerCustom *_listenerRoomPlayerFadeOutComplete;
    EventListenerCustom *_listenerShootDirectionFadeOutComplete;
    EventListenerCustom *_listenerDuelistPlayerFoundDecreaseMoney;
    long long _roomId = 0L;
    MessageRequestSetPlayerTypeAndPosition_ePlayerType _plannedPlayerType = MessageRequestSetPlayerTypeAndPosition_ePlayerType_ptWATCHER;
    int _maxPlayers = 0;
    int _bet = 0;
    int _maxRounds = 0;
    long long _investorBank = 0L;
    int _currentRound = 0;
    long long _playerBank = 0L;
    bool _isGameStarted = false;
    int _roundPossibleBullets = 0;
    MessageRequestSetPlayerTypeAndPosition_ePlayerType _currentPlayerType;
    RoomShootDirection _shootDirection;
    std::vector<RoomRoundGameResult*> _roundGameResult;
    int _plannedSitPosition = 0;
    int _selectedPlayerPos = -1;
    long long _selectedPlayerId = -1L;
    bool _isTimerEnabled = false;
    int _timerTime = 0;
    ProtoMessageDelegate *_dialogSocketDelegate;
    DialogTypes _currentDialog;
    void setCurrentRound(int value);
    void setCurrentBank(long long value);
    void setCurrentTime(const std::string &value);
    void showDialog(DialogTypes dialogType);
    void hideDialog();
    void setControlsEnable(bool value);
    void recalculatePlayersRadian();
    int amountEmptyPlayers();
    bool isPlayerExists(long long playerId);
    void fadeAndRemoveEmptyPlayers(bool withCallback);
    void fadePlayerAndShootDirectionByPosition(int playerPosition, bool withCallback);
    ShootDirection* findShootDirectionByPlayerPosition(int playerPosition);
    RoomPlayer* findPlayerByPlayerId(long long playerId);
    RoomPlayer* findPlayerByPlayerPos(int playerPos);
    int amountLivePlayers();
    bool isPlayerAtRoom();
    void setPlayerHandPistolVisible(bool value);
    void setRotateDrumButtonVisible(bool value);
    void setShootButtonVisible(bool value);
    void resetKillerState();
    void showGameWinner(RoomPlayer *player, MessageResponseRoundPlayerBang winnerInfo);
    // event callbacks
    void onRoundGameResultDidSequenceAnimation();
    void onKillerShootWithPlayerId();
    void onPlayerShootWithPlayerId();
    void onPlayerShootButNoBulletWithPlayerId();
    void onPlayerKilledWithPlayerId();
    void onMenuCallback(cocos2d::Ref* ref);
    void onPlayerTap(EventCustom *event);
    void onShopItemUsedDidFinishAnimation(EventCustom *event);
    void onPlayerBetItemDidFinishAnimation(EventCustom *event);
    void onRoomPlayerFadeOutComplete(EventCustom *event);
    void onShootDirectionFadeOutComplete(EventCustom *event);
    void onDuelistPlayerFoundDecreaseMoney(EventCustom *event);
    void onTimerTick(float value);
    // api calls
    void authPlayer();
    void roomPlayerInit();
    void usePlayerInventoryItem(const std::string &shopItemName, long long destPlayerId);
    void getRoomInfo();
    void getRoomPlayers();
    void roomExit();
    void setPistolBullets(std::map<std::string, std::string> value);
    void setPlayerType(MessageRequestSetPlayerTypeAndPosition_ePlayerType playerType, int position);
    void rotateDrum();
    void bang();
    // api callbacks
    void callbackRoomPlayerInit(const std::string &source);
    void callbackGetRoomInfo(const std::string &source);
    void callbackGetRoomPlayers(const std::string &source);
    void callbackSetPlayerTypeAndPosition(const std::string &source);
    void callbackRotateDrum(const std::string &source);
    void callbackNeedAuth(const std::string &source);
    void callbackAuth(const std::string &source);
    void callbackTimeToStart(const std::string &source);
    void callbackTimeToPutBullets(const std::string &source);
    void callbackTimeToRotateDrum(const std::string &source);
    void callbackTimeToShoot(const std::string &source);
    void callbackRoomResults(const std::string &source);
    void callbackTimeToEnd(const std::string &source);
    void callbackUsePlayerInventoryItem(const std::string &source);
    void callbackPlayerBet(const std::string &source);
    void callbackNoMoney(const std::string &source);
    void callbackBang(const std::string &source);
};

#endif /* defined(__BrrClient__SceneRoom__) */
