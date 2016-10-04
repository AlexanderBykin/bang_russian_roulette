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

#include "SceneRoom.h"
#include "SceneManager.h"
#include "LanguageManager.h"
#include "extensions/cocos-ext.h"
#include "GlobalProperties.h"
#include "SocketThread.h"
#include "MessageResponse.pb.h"
#include "Utils.h"
#include "RoomLamp.h"
#include "DialogAction.h"
#include "DialogRole.h"
#include "DialogPutBullet.h"
#include "DialogUseItem.h"
#include "DialogPlayerInfo.h"
#include "MessageRequestRoomInfo.pb.h"
#include "MessageResponseRoomInfo.pb.h"
#include "MessageRequestRoomPlayerList.pb.h"
#include "MessageResponseRoomPlayerList.pb.h"
#include "MessageRequestSetPlayerTypeAndPosition.pb.h"
#include "MessageResponseSetPlayerTypeAndPosition.pb.h"
#include "MessageRequestAuth.pb.h"
#include "MessageResponseAuth.pb.h"
#include "MessageRequestRoomPlayerExit.pb.h"
#include "MessageRequestRotateDrum.pb.h"
#include "MessageResponseRotateDrum.pb.h"
#include "MessageRequestBang.pb.h"
#include "MessageRequestSetPlayerBullets.pb.h"
#include "MessageResponseTimeToResults.pb.h"
#include "MessageResponseTimeToEnd.pb.h"
#include "MessageResponseTimeToPutBullets.pb.h"
#include "MessageResponseTimeToRotateDrum.pb.h"
#include "MessageResponseTimeToShoot.pb.h"
#include "MessageResponseTimeToStart.pb.h"
#include "MessageResponseUsePlayerInventoryItem.pb.h"
#include "MessageRequestUsePlayerInventoryItem.pb.h"
#include "MessageRequestPlayerBet.pb.h"
#include "MessageResponsePlayerBet.pb.h"
#include "PlayerBetItem.h"
#include "ShopItemUsed.h"
#include "PlayerHandPistol.h"
#include "DialogDuel.h"
#include "PlayerKiller.h"
#include "SimpleAudioEngine.h"
#include "MessageRequestRoomPlayerInit.pb.h"
#include "MessageResponseRoomPlayerInit.pb.h"
#include "MessageResponseNoMoney.pb.h"
#include "PluginGoogleAnalytics/PluginGoogleAnalytics.h"
#include "AuthType.pb.h"
#include "audio/include/AudioEngine.h"
#include "MessageResponseRoundPlayerBang.pb.h"
#include "MessageResponseRoomPlayerBang.pb.h"
#include "Button9TextShadow.h"

USING_NS_CC_EXT;

SceneRoom* SceneRoom::create(long long roomId) {
    SceneRoom *node = new (std::nothrow) SceneRoom();
    if(node && node->init(roomId)) {
        node->autorelease();
        return node;
    }
    CC_SAFE_DELETE(node);
    return nullptr;
}

bool SceneRoom::init(long long roomId) {
    if(!Layer::init()) {
        return false;
    }
    
    sdkbox::PluginGoogleAnalytics::logScreen("SceneRoom");
    
    _listenerPlayerTap = EventListenerCustom::create(RoomPlayerTapNotification, CC_CALLBACK_1(SceneRoom::onPlayerTap, this));
    _listenerShopItemUsedDidFinishAnimation = EventListenerCustom::create(ShopItemUsedDidFinishAnimationNotification, CC_CALLBACK_1(SceneRoom::onShopItemUsedDidFinishAnimation, this));
    _listenerPlayerBetItemDidFinishAnimation = EventListenerCustom::create(PlayerBetItemDidFinishAnimationNotification, CC_CALLBACK_1(SceneRoom::onPlayerBetItemDidFinishAnimation, this));
    _listenerRoomPlayerFadeOutComplete = EventListenerCustom::create(RoomPlayerFadeOutCompleteNotification, CC_CALLBACK_1(SceneRoom::onRoomPlayerFadeOutComplete, this));
    _listenerShootDirectionFadeOutComplete = EventListenerCustom::create(ShootDirectionFadeOutCompleteNotification, CC_CALLBACK_1(SceneRoom::onShootDirectionFadeOutComplete, this));
    _listenerDuelistPlayerFoundDecreaseMoney = EventListenerCustom::create(DuelistPlayerFoundDecreaseMoneyNotification, CC_CALLBACK_1(SceneRoom::onDuelistPlayerFoundDecreaseMoney, this));
    
    _eventDispatcher->addEventListenerWithFixedPriority(_listenerPlayerTap, 1);
    _eventDispatcher->addEventListenerWithFixedPriority(_listenerShopItemUsedDidFinishAnimation, 1);
    _eventDispatcher->addEventListenerWithFixedPriority(_listenerPlayerBetItemDidFinishAnimation, 1);
    _eventDispatcher->addEventListenerWithFixedPriority(_listenerRoomPlayerFadeOutComplete, 1);
    _eventDispatcher->addEventListenerWithFixedPriority(_listenerShootDirectionFadeOutComplete, 1);
    _eventDispatcher->addEventListenerWithFixedPriority(_listenerDuelistPlayerFoundDecreaseMoney, 1);
    
    _roomId = roomId;
    
    auto winSize = Director::getInstance()->getVisibleSize();
    
    auto bg = Sprite::create("SceneRoom/SceneRoomBG.png");
    bg->setPosition(Vec2(winSize.width/2, winSize.height/2));
    this->addChild(bg, 0);
    
    
    auto btnBack = Button9TextShadow::create("SceneRoom/btnSceneRoomBackBG.png",
                                              Size(300, 120),
                                              LanguageManager::getString("RoomLobbyButton"),
                                              GameFont,
                                              47,
                                              Color3B(66, 158, 97),
                                              Color3B(0, 51, 14),
                                              CC_CALLBACK_1(SceneRoom::onMenuCallback, this));
    btnBack->setTag(miBackTag);
    btnBack->setAnchorPoint(Vec2::ANCHOR_TOP_RIGHT);
    btnBack->setPosition(Vec2(winSize.width-10, winSize.height-15));
    this->addChild(btnBack, miBackTag, miBackTag);

    
    auto lblRoom = Label::createWithTTF(LanguageManager::getString("RoomRoomLabel"), GameFont, 28);
    lblRoom->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
    lblRoom->setColor(Color3B(19, 124, 46));
    lblRoom->setPosition(Vec2(10, winSize.height - 10));
    this->addChild(lblRoom);
    
    auto txtRoom = Label::createWithTTF(StringUtils::format("%lli", _roomId), GameFont, 28);
    txtRoom->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
    txtRoom->setColor(Color3B(188, 167, 80));
    txtRoom->setPosition(Vec2(lblRoom->getPosition().x + lblRoom->getContentSize().width + 10, lblRoom->getPosition().y));
    this->addChild(txtRoom);

    auto lblRound = Label::createWithTTF(LanguageManager::getString("RoomRoundLabel"), GameFont, 28);
    lblRound->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
    lblRound->setColor(Color3B(19, 124, 46));
    lblRound->setPosition(Vec2(10, lblRoom->getPosition().y - lblRoom->getContentSize().height - 10));
    this->addChild(lblRound);
    
    auto txtRound = Label::createWithTTF("", GameFont, 28);
    txtRound->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
    txtRound->setColor(Color3B(188, 167, 80)); 
    txtRound->setPosition(Vec2(lblRound->getPosition().x + lblRound->getContentSize().width + 10, lblRound->getPosition().y));
    this->addChild(txtRound, txtRoundTag, txtRoundTag);
    
    auto lblBank = Label::createWithTTF(LanguageManager::getString("RoomBankLabel"), GameFont, 28);
    lblBank->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
    lblBank->setColor(Color3B(19, 124, 46));
    lblBank->setPosition(Vec2(10, lblRound->getPosition().y - lblRound->getContentSize().height - 10));
    this->addChild(lblBank);
    
    auto txtBank = Label::createWithTTF("", GameFont, 28);
    txtBank->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
    txtBank->setColor(Color3B(188, 167, 80));
    txtBank->setPosition(Vec2(lblBank->getPosition().x + lblBank->getContentSize().width + 10, lblBank->getPosition().y));
    this->addChild(txtBank, txtBankTag, txtBankTag);
    
    auto lblTime = Label::createWithTTF(LanguageManager::getString("RoomTimeLabel"), GameFont, 28);
    lblTime->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
    lblTime->setColor(Color3B(19, 124, 46));
    lblTime->setPosition(Vec2(10, lblBank->getPosition().y - lblBank->getContentSize().height - 10));
    this->addChild(lblTime);
    
    auto txtTime = Label::createWithTTF("", GameFont, 28);
    txtTime->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
    txtTime->setColor(Color3B(188, 167, 80));
    txtTime->setPosition(Vec2(lblTime->getPosition().x + lblTime->getContentSize().width + 10, lblTime->getPosition().y));
    this->addChild(txtTime, txtTimeTag, txtTimeTag);
    
    // killer
    
    auto playerKiller = PlayerKiller::create();
    playerKiller->setOpacity(0);
    this->addChild(playerKiller, killerTag, killerTag);
    
    // room lamp
    
    auto roomLamp = RoomLamp::create("0:00", false);
    roomLamp->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
    this->addChild(roomLamp, lampTag, lampTag);
    
    // hand pistols layer
    
    auto layerPlayerHandPistol = Node::create();
    this->addChild(layerPlayerHandPistol, layerPlayerHandPistolTag, layerPlayerHandPistolTag);
    
    // players layer
    
    auto layerPlayer = Node::create();
    this->addChild(layerPlayer, layerPlayerTag, layerPlayerTag);
    
    // shoot directions layer
    
    auto layerShootDirection = Node::create();
    this->addChild(layerShootDirection, layerShootDirectionTag, layerShootDirectionTag);
    
    this->setCurrentTime("0:00");
    this->setCurrentBank(0);
    this->setCurrentRound(0);
    
    
    auto listener = EventListenerKeyboard::create();
    listener->onKeyReleased = CC_CALLBACK_2(SceneRoom::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    
    // call api
    this->roomPlayerInit();
    
    this->schedule(CC_SCHEDULE_SELECTOR(SceneRoom::onTimerTick), 1.0);
    
    
    if (GlobalProperties::isDebug()) {
        auto lblTest = Label::createWithTTF("Только для тестирования\n(с) Шниперсон Александр", GameFont, 100);
        lblTest->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
        lblTest->setPosition(winSize.width/2, winSize.height/2);
        lblTest->setRotation(-45);
        lblTest->setOpacity(100);
        this->addChild(lblTest, 9999, 9999);
    }
    
    return true;
}

SceneRoom::~SceneRoom() {
    _eventDispatcher->removeEventListener(_listenerPlayerTap);
    _eventDispatcher->removeEventListener(_listenerShopItemUsedDidFinishAnimation);
    _eventDispatcher->removeEventListener(_listenerPlayerBetItemDidFinishAnimation);
    _eventDispatcher->removeEventListener(_listenerRoomPlayerFadeOutComplete);
    _eventDispatcher->removeEventListener(_listenerShootDirectionFadeOutComplete);
    _eventDispatcher->removeEventListener(_listenerDuelistPlayerFoundDecreaseMoney);
}

void SceneRoom::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event) {
    if(keyCode == EventKeyboard::KeyCode::KEY_BACK) {
        this->onMenuCallback(this->getChildByTag(miBackTag));
    }
}

void SceneRoom::setCurrentRound(int value) {
    _currentRound = value;
    auto label = dynamic_cast<Label*>(this->getChildByTag(txtRoundTag));
    label->setString(StringUtils::format("%d", _currentRound));
}

void SceneRoom::setCurrentBank(long long value) {
    _playerBank = value;
    auto label = dynamic_cast<Label*>(this->getChildByTag(txtBankTag));
    label->setString(StringUtils::format("%lli", _playerBank));
}

void SceneRoom::setCurrentTime(const std::string &value) {
    auto label = dynamic_cast<Label*>(this->getChildByTag(txtTimeTag));
    label->setString(value);
    auto lamp = dynamic_cast<RoomLamp*>(this->getChildByTag(lampTag));
    lamp->setText(value);
}

int SceneRoom::amountLivePlayers() {
    int result = 0;
    
    for (auto item : this->getChildByTag(layerPlayerTag)->getChildren()) {
        auto roomPlayer = dynamic_cast<RoomPlayer*>(item);
        if (roomPlayer->getPlayerId() > 0) {
            result++;
        }
    }
    
    return result;
}

ShootDirection* SceneRoom::findShootDirectionByPlayerPosition(int playerPosition) {
    for (auto item : this->getChildByTag(layerShootDirectionTag)->getChildren()) {
        auto shootDirection = dynamic_cast<ShootDirection*>(item);
        if (shootDirection->getPlayer()->getPlayerPosition() == playerPosition)
            return shootDirection;
    }
    return nullptr;
}

RoomPlayer* SceneRoom::findPlayerByPlayerId(long long playerId) {
    for (auto item : this->getChildByTag(layerPlayerTag)->getChildren()) {
        auto roomPlayer = dynamic_cast<RoomPlayer*>(item);
        if (roomPlayer->getPlayerId() == playerId)
            return roomPlayer;
    }
    
    return nullptr;
}

RoomPlayer* SceneRoom::findPlayerByPlayerPos(int playerPos) {
    for (auto item : this->getChildByTag(layerPlayerTag)->getChildren()) {
        auto roomPlayer = dynamic_cast<RoomPlayer*>(item);
        if (roomPlayer->getPlayerPosition() == playerPos)
            return roomPlayer;
    }
    
    return nullptr;
}

void SceneRoom::fadePlayerAndShootDirectionByPosition(int playerPosition, bool withCallback) {
    ShootDirection *shootDirection = this->findShootDirectionByPlayerPosition(playerPosition);
    if (shootDirection) {
        shootDirection->fadeOut(withCallback);
    }
    
    RoomPlayer *player = this->findPlayerByPlayerPos(playerPosition);
    if (player) {
        player->fadeOut(withCallback);
    }
}

void SceneRoom::fadeAndRemoveEmptyPlayers(bool withCallback) {
    for (auto item : this->getChildByTag(layerPlayerTag)->getChildren()) {
        auto roomPlayer = dynamic_cast<RoomPlayer*>(item);
        if (roomPlayer->getPlayerId() <= 0) {
            this->fadePlayerAndShootDirectionByPosition(roomPlayer->getPlayerPosition(), withCallback);
        }
    }
}

bool SceneRoom::isPlayerExists(long long playerId) {
    return (this->findPlayerByPlayerId(playerId) != nullptr);
}

int SceneRoom::amountEmptyPlayers() {
    int result = 0;
    
    for (auto item : this->getChildByTag(layerPlayerTag)->getChildren()) {
        auto roomPlayer = dynamic_cast<RoomPlayer*>(item);
        if (roomPlayer->getPlayerId() <= 0)
            result++;
    }
    
    return result;
}

void SceneRoom::recalculatePlayersRadian() {
    int playerAmount = this->getChildByTag(layerPlayerTag)->getChildrenCount();
    double radianAvg = Utils::getAverageAngleByAmount(playerAmount);
    double nextRadian = 0;
    
    for (auto item : this->getChildByTag(layerPlayerTag)->getChildren()) {
        auto roomPlayer = dynamic_cast<RoomPlayer*>(item);
        roomPlayer->animateRotationToRadian(nextRadian, false, false, playerAmount);
        nextRadian =  nextRadian - radianAvg;
    }
}

void SceneRoom::showDialog(DialogTypes dialogType) {
    this->hideDialog();
    
    if (dialogType == DialogTypes::DialogTypeNone) {
        return;
    }
    
    this->setControlsEnable(false);
    
    switch (dialogType) {
        case DialogTypes::DialogTypeBase: {
            sdkbox::PluginGoogleAnalytics::logEvent("ShowDialog", "Base", "", 0);
            auto dialog = DialogBase::create();
            this->addChild(dialog, 999, DialogTypes::DialogTypeBase);
            break;
        }
            
        case DialogTypes::DialogTypeAction: {
            sdkbox::PluginGoogleAnalytics::logEvent("ShowDialog", "Action", "", 0);
            auto dialog = DialogAction::create();
            dialog->setDelegate(this);
            this->addChild(dialog, 999, DialogTypes::DialogTypeAction);
            break;
        }
            
        case DialogTypes::DialogTypeRole: {
            sdkbox::PluginGoogleAnalytics::logEvent("ShowDialog", "Role", "", 0);
            DialogRole *dialog = DialogRole::create();
            dialog->setDelegate(this);
            this->addChild(dialog, 999, DialogTypes::DialogTypeRole);
            break;
        }
            
        case DialogTypes::DialogTypePlayerInfo: {
            sdkbox::PluginGoogleAnalytics::logEvent("ShowDialog", "PlayerInfo", "", 0);
            auto dialog = DialogPlayerInfo::create(_selectedPlayerId);
            dialog->setDelegate(this);
            _dialogSocketDelegate = dialog;
            this->addChild(dialog, 999, DialogTypes::DialogTypePlayerInfo);
            break;
        }
            
        case DialogTypes::DialogTypePutBullets: {
            sdkbox::PluginGoogleAnalytics::logEvent("ShowDialog", "PutBullets", "", 0);
            auto dialog = DialogPutBullet::create(_roundPossibleBullets);
            dialog->setDelegate(this);
            this->addChild(dialog, 999, DialogTypes::DialogTypePutBullets);
            break;
        }
            
        case DialogTypes::DialogTypeUseItems: {
            sdkbox::PluginGoogleAnalytics::logEvent("ShowDialog", "UseItems", "", 0);
            auto dialog = DialogUseItem::create();
            dialog->setDelegate(this);
            _dialogSocketDelegate = dialog;
            this->addChild(dialog, 999, DialogTypes::DialogTypeUseItems);
            break;
        }
            
        case DialogTypes::DialogTypeDuel: {
            sdkbox::PluginGoogleAnalytics::logEvent("ShowDialog", "Duel", "", 0);
            auto dialog = DialogDuel::create(_roomId, this->getChildByTag(layerPlayerTag)->getChildren());
            dialog->setDelegate(this);
            _dialogSocketDelegate = dialog;
            this->addChild(dialog, 999, DialogTypes::DialogTypeDuel);
            break;
        }
            
        default:
            break;
    }
    
    _currentDialog = dialogType;
}

void SceneRoom::hideDialog() {
    sdkbox::PluginGoogleAnalytics::logScreen("SceneRoom");
    
    _dialogSocketDelegate = nullptr;
    
    this->setControlsEnable(true);
    
    if (_currentDialog == DialogTypes::DialogTypeNone) {
        return;
    }

    sdkbox::PluginGoogleAnalytics::logEvent("HideDialog", StringUtils::format("DialogType_%d", _currentDialog), "", 0);

    this->removeChildByTag(_currentDialog);
    
    _currentDialog = DialogTypes::DialogTypeNone;
}

void SceneRoom::setControlsEnable(bool value) {
    auto btn = dynamic_cast<Button9TextShadow*>(this->getChildByTag(miBackTag));
    btn->setEnabled(value);
    auto layerPlayer = this->getChildByTag(layerPlayerTag);
    
    for (auto item : layerPlayer->getChildren()) {
        auto roomPlayer = dynamic_cast<RoomPlayer*>(item);
        roomPlayer->setTouchEnable(value);
    }
}

void SceneRoom::setPlayerHandPistolVisible(bool value) {
    auto _layerPlayerHandPistol = this->getChildByTag(layerPlayerHandPistolTag);
    if(value) {
        auto _layerPlayer = this->getChildByTag(layerPlayerTag);
        
        if (_layerPlayerHandPistol->getChildrenCount() > 0) {
            return;
        }
        
        for (auto item : _layerPlayer->getChildren()) {
            auto roomPlayer = dynamic_cast<RoomPlayer*>(item);
            if(roomPlayer->getPlayerId() > 0) {
                auto handPistol = PlayerHandPistol::create(roomPlayer);
                _layerPlayerHandPistol->addChild(handPistol);
                handPistol->showAnimated();
            }
        }
    } else {
        _layerPlayerHandPistol->removeAllChildren();
    }
}

void SceneRoom::setRotateDrumButtonVisible(bool value) {
    if(value) {
        auto btnRotate = Button9TextShadow::create("SceneRoom/btnSceneRoomRotateDrum.png", CC_CALLBACK_1(SceneRoom::onMenuCallback, this));
        btnRotate->setTag(miRotateDrumTag);
        btnRotate->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
        btnRotate->setPosition(Vec2(50, 50));
        this->addChild(btnRotate, miRotateDrumTag, miRotateDrumTag);
    } else {
        this->removeChildByTag(miRotateDrumTag);
    }
}

void SceneRoom::setShootButtonVisible(bool value) {
    if(value) {
        auto winSize = Director::getInstance()->getVisibleSize();
        
        auto btnShoot = Button9TextShadow::create("SceneRoom/btnSceneRoomBang.png", CC_CALLBACK_1(SceneRoom::onMenuCallback, this));
        btnShoot->setTag(miShootTag);
        btnShoot->setAnchorPoint(Vec2::ANCHOR_BOTTOM_RIGHT);
        btnShoot->setPosition(Vec2(winSize.width - 50, 50));
        this->addChild(btnShoot, miShootTag, miShootTag);
    } else {
        this->removeChildByTag(miShootTag);
    }
}

void SceneRoom::resetKillerState() {
    auto killer = dynamic_cast<PlayerKiller*>(this->getChildByTag(killerTag));
    killer->setIsShoot(false);
}

void SceneRoom::showGameWinner(RoomPlayer *player, MessageResponseRoundPlayerBang winnerInfo) {
    Size winSize = Director::getInstance()->getVisibleSize();
    
    player->runAction(MoveTo::create(1.0, Vec2(winSize.width / 2, winSize.height / 2)));
    
    for (auto item : this->getChildByTag(layerShootDirectionTag)->getChildren()) {
        auto shootDirection = dynamic_cast<ShootDirection*>(item);
        if (shootDirection->getPlayer()->getPlayerId() == player->getPlayerId()) {
            shootDirection->fadeOut(true);
        }
    }
    
    this->setCurrentBank(_playerBank - winnerInfo.winamount());
    
    auto lblWinner = Label::createWithTTF(LanguageManager::getString("RoomWinnerLabel"), GameFont, 50);
    lblWinner->setColor(Color3B::WHITE);
    //    lblWinner.anchorPoint = ccp(0.5, 0.5);
    lblWinner->setPosition(Vec2(winSize.width / 2, winSize.height / 100 * 80));
    lblWinner->setOpacity(0);
    this->addChild(lblWinner);
    lblWinner->runAction(RepeatForever::create(Sequence::create(FadeIn::create(1.0), FadeOut::create(1.0), nullptr)));
    
    auto lblWinAmount = Label::createWithTTF(StringUtils::format("+%i", winnerInfo.winamount()), GameFont, 50);
    lblWinAmount->setColor(Color3B::WHITE);
    //    lblWinAmount.anchorPoint = ccp(0.5, 0.5);
    lblWinAmount->setPosition(Vec2(winSize.width / 2, winSize.height / 100 * 20));
    lblWinAmount->setOpacity(0);
    this->addChild(lblWinAmount);
    lblWinAmount->runAction(RepeatForever::create(Sequence::create(FadeIn::create(1.0), FadeOut::create(1.0), nullptr)));
}

// event callbacks

void SceneRoom::onRoundGameResultDidSequenceAnimation() {
    double avgPerAnimation = 5.0 / 6;
    auto roomKiller = dynamic_cast<PlayerKiller*>(this->getChildByTag(killerTag));
    
    if (_roundGameResult.empty())
        return;
    
    auto roundResult = _roundGameResult[0];
    
    if (this->isPlayerExists(roundResult->getPlayerId())) {
        if (roundResult->getKilledPlayerId() == 0L) {
            this->runAction(CallFunc::create(CC_CALLBACK_0(SceneRoom::onPlayerShootButNoBulletWithPlayerId, this)));
        } else {
            this->runAction(Sequence::create(CallFunc::create(CC_CALLBACK_0(SceneRoom::onPlayerShootWithPlayerId, this)),
                                             DelayTime::create(avgPerAnimation / 2 - 0.1),
                                             CallFunc::create(CC_CALLBACK_0(SceneRoom::onPlayerKilledWithPlayerId, this)),
                                             nullptr));
        }
    } else {
        roomKiller->runAction(Sequence::create(FadeIn::create(avgPerAnimation / 2 - 0.1),
                                               CallFunc::create(CC_CALLBACK_0(SceneRoom::onKillerShootWithPlayerId, this)),
                                               FadeOut::create(avgPerAnimation / 2 - 0.1),
                                               nullptr));
    }
}

// вызываем когда игрока убил киллер
void SceneRoom::onKillerShootWithPlayerId() {
    long long killedPlayerId = *(new long long(_roundGameResult[0]->getKilledPlayerId()));
    _roundGameResult.erase(_roundGameResult.begin());
    auto roomKiller = dynamic_cast<PlayerKiller*>(this->getChildByTag(killerTag));
    roomKiller->setOpacity(255);
    roomKiller->setIsShoot(true);
    
    experimental::AudioEngine::play2d("Sounds/shoot_havebullet.mp3");
    
    for (auto item : this->getChildByTag(layerPlayerTag)->getChildren()) {
        auto roomPlayer = dynamic_cast<RoomPlayer*>(item);
        if (roomPlayer->getPlayerId() == killedPlayerId) {
            roomPlayer->setPlayerId(-1); // задаем как пустое место, далее при начале нового раунда сработает метод очистки пустых игроков
            roomPlayer->setPlayerState(RoomPlayer::RoomPlayerStateTypeKilled);
            break;
        }
    }
}

// вызываем когда игрок стрелял и был патрон
void SceneRoom::onPlayerShootWithPlayerId() {
    long long playerId = *(new long long(_roundGameResult[0]->getPlayerId()));
    auto roomKiller = dynamic_cast<PlayerKiller*>(this->getChildByTag(killerTag));
    roomKiller->setOpacity(0);
    
    experimental::AudioEngine::play2d("Sounds/shoot_havebullet.mp3");
    
    for (auto item : this->getChildByTag(layerPlayerHandPistolTag)->getChildren()) {
        auto handPistol = dynamic_cast<PlayerHandPistol*>(item);
        if (handPistol->getPlayer()->getPlayerId() == playerId) {
            handPistol->setHandPistolState(PlayerHandPistol::PlayerHandPistolStateKilled);
            break;
        }
    }
}

// вызываем когда игрок стрелял и небыло патрона
void SceneRoom::onPlayerShootButNoBulletWithPlayerId() {
    long long playerId = *(new long long(_roundGameResult[0]->getPlayerId()));
    _roundGameResult.erase(_roundGameResult.begin());
    auto roomKiller = dynamic_cast<PlayerKiller*>(this->getChildByTag(killerTag));
    roomKiller->setOpacity(0);
    
    experimental::AudioEngine::play2d("Sounds/shoot_nobullet.mp3");
    
    for (auto item : this->getChildByTag(layerPlayerHandPistolTag)->getChildren()) {
        auto handPistol = dynamic_cast<PlayerHandPistol*>(item);
        if (handPistol->getPlayer()->getPlayerId() == playerId) {
            handPistol->setHandPistolState(PlayerHandPistol::PlayerHandPistolStateNotKilled);
            break;
        }
    }
}

// вызываем когда стреляли в игрока и убили
void SceneRoom::onPlayerKilledWithPlayerId() {
    long long killedPlayerId = *(new long long(_roundGameResult[0]->getKilledPlayerId()));
    _roundGameResult.erase(_roundGameResult.begin());
    auto roomKiller = dynamic_cast<PlayerKiller*>(this->getChildByTag(killerTag));
    roomKiller->setOpacity(0);
    
    experimental::AudioEngine::play2d("Sounds/shoot_havebullet.mp3");
    
    for (auto item : this->getChildByTag(layerPlayerTag)->getChildren()) {
        auto roomPlayer = dynamic_cast<RoomPlayer*>(item);
        if (roomPlayer->getPlayerId() == killedPlayerId) {
            roomPlayer->setPlayerId(-1L); // задаем как пустое место, далее при начале нового раунда сработает метод очистки пустых игроков
            roomPlayer->setPlayerState(RoomPlayer::RoomPlayerStateTypeKilled);
            break;
        }
    }
}

void SceneRoom::onMenuCallback(Ref *ref){
    auto node = dynamic_cast<Node*>(ref);
    switch ((SceneTags)node->getTag()) {
        case miBackTag: {
            sdkbox::PluginGoogleAnalytics::logEvent("Button", "btnBack", "", 0);
            experimental::AudioEngine::play2d("Sounds/btnmenu_click.mp3");
            if (_currentDialog != DialogTypeNone)
                return;
            this->roomExit();
            SceneManager::goBack(BrrScenes::SceneLobby);
            break;
        }
            
        case miRotateDrumTag: {
            sdkbox::PluginGoogleAnalytics::logEvent("Button", "btnRotateDrum", "", 0);
            if (_currentDialog != DialogTypeNone)
                return;
            this->rotateDrum();
            break;
        }
            
        case miShootTag: {
            sdkbox::PluginGoogleAnalytics::logEvent("Button", "btnShoot", "", 0);
            if (_currentDialog != DialogTypeNone)
                return;
            this->setShootButtonVisible(false);
            this->bang();
            break;
        }
            
        default:
            break;
    }
}

void SceneRoom::onPlayerTap(EventCustom *event) {
    sdkbox::PluginGoogleAnalytics::logEvent("Button", "btnPlayerTap", "", 0);
    RoomPlayer *roomPlayer = (RoomPlayer*)event->getUserData();
    if (roomPlayer == nullptr)
        return;
    
    _selectedPlayerPos = roomPlayer->getPlayerPosition();
    _selectedPlayerId = roomPlayer->getPlayerId();

    if (_currentDialog != DialogTypes::DialogTypeNone)
        return;
    
    _plannedSitPosition = roomPlayer->getPlayerPosition();
    
    // Если желаемое место не занято открыть диалог смены роли и назначения места
    if (roomPlayer->getPlayerId() <= 0)
        this->showDialog(DialogTypes::DialogTypeRole);
    else
        this->showDialog(DialogTypes::DialogTypeAction);
}

void SceneRoom::onShopItemUsedDidFinishAnimation(EventCustom *event) {
    auto shopItem = (ShopItemUsed*)event->getUserData();
    auto layerPlayer = this->getChildByTag(layerPlayerTag);
    
    if (shopItem == nullptr || layerPlayer == nullptr) {
        return;
    }
    
    if (shopItem->getShopItemName().compare("brr_change_shoot_direction") == 0) {
        for (auto item : layerPlayer->getChildren()) {
            auto roomPlayer = dynamic_cast<RoomPlayer*>(item);
            if (roomPlayer->getPlayerId() == shopItem->getDestPlayerId()) {
                if (roomPlayer->getShootDirection() == PlayerShootDirection::psdDOUBLE) {
                    return;
                }
                
                roomPlayer->setShootDirection((roomPlayer->getShootDirection() == PlayerShootDirection::psdLEFT) ? PlayerShootDirection::psdRIGHT : PlayerShootDirection::psdLEFT);
                break;
            }
        }
    }
    
    this->removeChild(shopItem);
}

void SceneRoom::onPlayerBetItemDidFinishAnimation(EventCustom *event) {
    auto playerBetItem = (PlayerBetItem *) event->getUserData();
    
    if (playerBetItem == nullptr)
        return;
    
    this->setCurrentBank(_playerBank + playerBetItem->getAmount());
    
    this->removeChild(playerBetItem);
}

void SceneRoom::onRoomPlayerFadeOutComplete(EventCustom *event) {
    int playerPos = *((int*)(event->getUserData()));
    auto layerPlayer = this->getChildByTag(layerPlayerTag);
    
    if (!playerPos || !layerPlayer)
        return;
    
    auto tmpItem = this->findPlayerByPlayerPos(playerPos);
    if (tmpItem) {
        layerPlayer->removeChild(tmpItem);
    }
    
    if (this->amountEmptyPlayers() == 0 && this->amountLivePlayers() > 1) {
        this->recalculatePlayersRadian();
    }
}

void SceneRoom::onShootDirectionFadeOutComplete(EventCustom *event) {
    int playerPos = *((int*)(event->getUserData()));
    auto layerShootDirection = this->getChildByTag(layerShootDirectionTag);
    
    if (!playerPos || !layerShootDirection)
        return;
    
    for (int i = (int) layerShootDirection->getChildrenCount() - 1; i >= 0; i--) {
        auto tmpItem = (ShootDirection *) layerShootDirection->getChildren().at(i);
        if (tmpItem->getPlayer()->getPlayerPosition() == playerPos) {
            layerShootDirection->removeChild(tmpItem);
            break;
        }
    }
}

void SceneRoom::onDuelistPlayerFoundDecreaseMoney(EventCustom *event) {
    int money = *((int*)(event->getUserData()));
    
    if (!money)
        return;
    
    this->setCurrentBank(_playerBank - money);
}

void SceneRoom::onTimerTick(float value) {
    if (!_isTimerEnabled)
        return;
    
    //    NSLog(@"TimerTime '%d'", _timerTime);
    
    int minutes = (int) ((_timerTime > 60) ? fmod(_timerTime, 60) : 0);
    int seconds = (minutes > 0) ? _timerTime / minutes : _timerTime;
    
    auto timeString = StringUtils::format("%i:%02i", minutes, seconds);
    
    if (_timerTime > 0) {
        this->setCurrentTime(timeString);
        _timerTime--;
    }
    else {
        _isTimerEnabled = false;
        this->setCurrentTime("0:00");
    }
}

void SceneRoom::onDialogButtonTap(Ref* sender, int buttonIndex, std::map<std::string, std::string> userData) {
    DialogTypes closedDialog = _currentDialog;
    
    this->hideDialog();
    
    bool isPlayerInRoom = (GlobalProperties::getPlayerId() > 0 && this->isPlayerExists(GlobalProperties::getPlayerId()));
    
    switch (closedDialog) {
        case DialogTypeAction: {
            switch (buttonIndex) {
                case 1: {
                    sdkbox::PluginGoogleAnalytics::logEvent("Button", "btnPlayerInfo", "", 0);
                    this->showDialog(DialogTypePlayerInfo);
                    break;
                }
                    
                case 3: {
                    // Вещи разрешено использовать только Игрокам
                    if (!isPlayerInRoom) {
                        return;
                    }
                    sdkbox::PluginGoogleAnalytics::logEvent("Button", "btnUseItem", "", 0);
                    this->showDialog(DialogTypeUseItems);
                    break;
                }
                    
                default:
                    break;
            }
            break;
        }
            
        case DialogTypeRole: {
            switch ((DialogRole::DialogRoleSceneTags)buttonIndex) {
                case DialogRole::DialogRoleSceneTags::miRolePlayerTag: {
                    sdkbox::PluginGoogleAnalytics::logEvent("Button", "btnRolePlayer", "", 0);
                    this->setPlayerType(MessageRequestSetPlayerTypeAndPosition_ePlayerType_ptPLAYER, _plannedSitPosition);
                    break;
                }
                    
                case DialogRole::DialogRoleSceneTags::miRoleWatcherTag: {
                    sdkbox::PluginGoogleAnalytics::logEvent("Button", "btnRoleWatcher", "", 0);
                    this->setPlayerType(MessageRequestSetPlayerTypeAndPosition_ePlayerType_ptWATCHER, _plannedSitPosition);
                    break;
                }
                    
                default:
                    break;
            }
            break;
        }
            
        case DialogTypePutBullets: {
            this->setPistolBullets(userData);
            break;
        }
            
        case DialogTypeUseItems: {
            if (buttonIndex != (DialogBase::DialogBaseButtons::btnDoneTag) || userData.empty())
                return;
            
            if(auto roomPlayer = this->findPlayerByPlayerPos(_selectedPlayerPos)) {
                if(roomPlayer->getPlayerId() > 0L) {
                    for (auto item : userData) {
                        this->usePlayerInventoryItem(item.first, roomPlayer->getPlayerId());
                    }
                }
            }
            
            break;
        }
            
        default:
            break;
    }
    
}

// >>> api calls

void SceneRoom::authPlayer() {
    if(GlobalProperties::getLogin().empty() || GlobalProperties::getPassword().empty()) {
        return;
    }

    sdkbox::PluginGoogleAnalytics::logEvent("ApiCall", "authPlayer", "", 1);

    // TODO: we need to auth player at GooglePlay then call this method
    MessageRequestAuth msg;
    msg.set_authtype(eAuthType::atEmail);
    msg.set_login(GlobalProperties::getLogin());
    msg.set_password(GlobalProperties::getPassword());
    SocketThread::getInstance()->getSocket()->Send(this->wrapMessage(eProtoMessageType::cmtAuth, msg));
}

void SceneRoom::roomPlayerInit() {
    sdkbox::PluginGoogleAnalytics::logEvent("ApiCall", "roomPlayerInit", "", 1);
    MessageRequestRoomPlayerInit msg;
    msg.set_roomid(_roomId);
    SocketThread::getInstance()->getSocket()->Send(this->wrapMessage(eProtoMessageType::cmtRoomPlayerInit, msg));
}

void SceneRoom::usePlayerInventoryItem(const std::string &shopItemName, long long destPlayerId) {
    if (destPlayerId <= 0 || shopItemName.empty())
        return;

    sdkbox::PluginGoogleAnalytics::logEvent("ApiCall", "usePlayerInventoryItem", shopItemName, 1);

    MessageRequestUsePlayerInventoryItem msg;
    msg.set_roomid(_roomId);
    msg.set_shopitemname(shopItemName);
    msg.set_destplayerid(destPlayerId);
    SocketThread::getInstance()->getSocket()->Send(this->wrapMessage(eProtoMessageType::cmtUsePlayerInventoryItem, msg));
}

void SceneRoom::getRoomInfo() {
    sdkbox::PluginGoogleAnalytics::logEvent("ApiCall", "getRoomInfo", "", 1);
    MessageRequestRoomInfo msg;
    msg.set_roomid(_roomId);
    SocketThread::getInstance()->getSocket()->Send(this->wrapMessage(eProtoMessageType::cmtGetRoomInfo, msg));
}

void SceneRoom::getRoomPlayers() {
    sdkbox::PluginGoogleAnalytics::logEvent("ApiCall", "getRoomPlayers", "", 1);
    MessageRequestRoomPlayerList msg;
    msg.set_roomid(_roomId);
    SocketThread::getInstance()->getSocket()->Send(this->wrapMessage(eProtoMessageType::cmtGetRoomPlayers, msg));
}

void SceneRoom::roomExit() {
    sdkbox::PluginGoogleAnalytics::logEvent("ApiCall", "roomExit", "", 1);
    MessageRequestRoomPlayerExit msg;
    msg.set_roomid(_roomId);
    SocketThread::getInstance()->getSocket()->Send(this->wrapMessage(eProtoMessageType::cmtRoomExit, msg));
}

void SceneRoom::setPistolBullets(std::map<std::string, std::string> value) {
    if (value.size() == 0 || value.size() < 6)
        return;

    sdkbox::PluginGoogleAnalytics::logEvent("ApiCall", "setPistolBullets", "", 1);

    MessageRequestSetPlayerBullets msg;
    msg.set_roomid(_roomId);
    msg.set_b1(value.at("1").compare("1") == 0);
    msg.set_b2(value.at("2").compare("1") == 0);
    msg.set_b3(value.at("3").compare("1") == 0);
    msg.set_b4(value.at("4").compare("1") == 0);
    msg.set_b5(value.at("5").compare("1") == 0);
    msg.set_b6(value.at("6").compare("1") == 0);
    msg.set_b7(false);
    msg.set_b8(false);
    msg.set_b9(false);
    msg.set_b10(false);
    msg.set_b11(false);
    msg.set_b12(false);
    SocketThread::getInstance()->getSocket()->Send(this->wrapMessage(eProtoMessageType::cmtSetPistolBullets, msg));
}

void SceneRoom::setPlayerType(MessageRequestSetPlayerTypeAndPosition_ePlayerType playerType, int position) {
    std::string playerTypeStr = "";
    switch (playerType) {
        case MessageRequestSetPlayerTypeAndPosition_ePlayerType_ptINVESTOR:
            playerTypeStr = "investor";
            break;
        case MessageRequestSetPlayerTypeAndPosition_ePlayerType_ptPLAYER:
            playerTypeStr = "player";
            break;
        case MessageRequestSetPlayerTypeAndPosition_ePlayerType_ptWATCHER:
            playerTypeStr = "watcher";
            break;
    }
    
    sdkbox::PluginGoogleAnalytics::logEvent("ApiCall", "setPlayerType", playerTypeStr, 1);

    _plannedSitPosition = position;
    _plannedPlayerType = playerType;
    
    MessageRequestSetPlayerTypeAndPosition msg;
    msg.set_roomid(_roomId);
    msg.set_playertype(playerType);
    msg.set_position(position);
    
    SocketThread::getInstance()->getSocket()->Send(this->wrapMessage(eProtoMessageType::cmtSetPlayerTypeAndPosition, msg));
}

void SceneRoom::bang() {
    sdkbox::PluginGoogleAnalytics::logEvent("ApiCall", "bang", "", 1);

    MessageRequestBang msg;
    msg.set_roomid(_roomId);
    SocketThread::getInstance()->getSocket()->Send(this->wrapMessage(eProtoMessageType::cmtBang, msg));
}

void SceneRoom::rotateDrum() {
    sdkbox::PluginGoogleAnalytics::logEvent("ApiCall", "rotateDrum", "", 1);
    MessageRequestRotateDrum msg;
    msg.set_roomid(_roomId);
    SocketThread::getInstance()->getSocket()->Send(this->wrapMessage(eProtoMessageType::cmtRotateDrum, msg));
}

// >>> api callbacks

void SceneRoom::processProtoMessage(const eProtoMessageType messageType, const std::string &messageBody) {
    switch (messageType) {
        case eProtoMessageType::cmtRoomPlayerInit: {
            this->callbackRoomPlayerInit(messageBody);
            break;
        }
            
        case eProtoMessageType::cmtGetRoomInfo: {
            this->callbackGetRoomInfo(messageBody);
            break;
        }
            
        case eProtoMessageType::cmtGetRoomPlayers: {
            this->callbackGetRoomPlayers(messageBody);
            break;
        }
            
        case eProtoMessageType::cmtSetPlayerTypeAndPosition: {
            this->callbackSetPlayerTypeAndPosition(messageBody);
            break;
        }
            
        case eProtoMessageType::cmtRotateDrum: {
            this->callbackRotateDrum(messageBody);
            break;
        }
            
        case eProtoMessageType::cmtNeedAuth: {
            this->callbackNeedAuth(messageBody);
            break;
        }
            
        case eProtoMessageType::cmtAuth: {
            this->callbackAuth(messageBody);
            break;
        }
            
        case eProtoMessageType::cmtTimeToStart: {
            this->callbackTimeToStart(messageBody);
            break;
        }
            
        case eProtoMessageType::cmtTimeToPutBullets: {
            this->callbackTimeToPutBullets(messageBody);
            break;
        }
            
        case eProtoMessageType::cmtTimeToRotateDrum: {
            this->callbackTimeToRotateDrum(messageBody);
            break;
        }
            
        case eProtoMessageType::cmtTimeToShoot: {
            this->callbackTimeToShoot(messageBody);
            break;
        }
            
        case eProtoMessageType::cmtRoomResults: {
            this->callbackRoomResults(messageBody);
            if (_dialogSocketDelegate) {
                _dialogSocketDelegate->processProtoMessage(messageType, messageBody);
            }
            break;
        }
            
        case eProtoMessageType::cmtTimeToEnd: {
            this->callbackTimeToEnd(messageBody);
            break;
        }
            
        case eProtoMessageType::cmtGetShopItems: {
            if (_dialogSocketDelegate) {
                _dialogSocketDelegate->processProtoMessage(messageType, messageBody);
            }
            break;
        }
            
        case eProtoMessageType::cmtUsePlayerInventoryItem: {
            this->callbackUsePlayerInventoryItem(messageBody);
            break;
        }
            
        case eProtoMessageType::cmtPlayerBet: {
            this->callbackPlayerBet(messageBody);
            break;
        }
            
        case eProtoMessageType::cmtGetRoomPlayersDuelist: {
            if (_dialogSocketDelegate) {
                _dialogSocketDelegate->processProtoMessage(messageType, messageBody);
            }
            break;
        }
            
        case eProtoMessageType::cmtSetPlayerDuelist: {
            if (_dialogSocketDelegate) {
                _dialogSocketDelegate->processProtoMessage(messageType, messageBody);
            }
            break;
        }
            
        case eProtoMessageType::cmtGetMoney: {
            if (_dialogSocketDelegate) {
                _dialogSocketDelegate->processProtoMessage(messageType, messageBody);
            }
            break;
        }
            
        case eProtoMessageType::cmtGetPlayerInfo: {
            if (_dialogSocketDelegate) {
                _dialogSocketDelegate->processProtoMessage(messageType, messageBody);
            }
            break;
        }
            
        case eProtoMessageType::cmtNoMoney: {
            this->callbackNoMoney(messageBody);
            break;
        }
            
        case eProtoMessageType::cmtBang: {
            this->callbackBang(messageBody);
            break;
        }
            
        default:
            break;
    }
}

void SceneRoom::callbackRoomPlayerInit(const std::string &source) {
    if (source.empty())
        return;
    
    sdkbox::PluginGoogleAnalytics::logEvent("ApiCallback", "callbackRoomPlayerInit", "", 1);
    
    MessageResponseRoomPlayerInit msg;
    msg.ParseFromString(source);
    
    if (msg.roomid() != _roomId)
        return;
    
    this->getRoomInfo();
}

void SceneRoom::callbackPlayerBet(const std::string &source) {
    if (source.empty())
        return;
    
    sdkbox::PluginGoogleAnalytics::logEvent("ApiCallback", "callbackPlayerBet", "", 1);
    
    MessageResponsePlayerBet msg;
    msg.ParseFromString(source);
    
    if (msg.roomid() != _roomId)
        return;
    
    long sourcePlayerId = msg.sourceplayerid();
    long destPlayerId = msg.destplayerid();
    long amount = msg.amount();
    auto winType = msg.wintype();
    
    Vec2 startPoint = Vec2(0, 0);
    Vec2 destPoint = Vec2(0, 0);
    
    for (auto item : this->getChildByTag(layerPlayerTag)->getChildren()) {
        auto roomPlayer = dynamic_cast<RoomPlayer*>(item);
        if (roomPlayer->getPlayerId() == sourcePlayerId) {
            startPoint = roomPlayer->getPosition();
        }
        
        if (roomPlayer->getPlayerId() == destPlayerId) {
            destPoint = roomPlayer->getPosition();
        }
    }
    
    Size winSize = Director::getInstance()->getVisibleSize();

    if (startPoint.x == 0 && startPoint.y == 0) {
        startPoint = Vec2(winSize.width, 0);
    }
    
    auto playerBetItem = PlayerBetItem::create(startPoint, destPoint, amount, winType);
    this->addChild(playerBetItem, 500);
    playerBetItem->animate();
}

void SceneRoom::callbackUsePlayerInventoryItem(const std::string &source) {
    if (source.empty())
        return;
    
    sdkbox::PluginGoogleAnalytics::logEvent("ApiCallback", "callbackUsePlayerInventoryItem", "", 1);
    
    MessageResponseUsePlayerInventoryItem msg;
    msg.ParseFromString(source);
    
    if (msg.roomid() != _roomId)
        return;
    
    long sourcePlayerId = msg.playerid();
    long destPlayerId = msg.destplayerid();
    std::string shopItemName = msg.shopitemname();
    
    if (sourcePlayerId <= 0 || destPlayerId <= 0 || shopItemName.empty()) {
        return;
    }
    
    double sourcePlayerRadian = NAN;
    double destPlayerRadian = NAN;
    
    for (auto item : this->getChildByTag(layerPlayerTag)->getChildren()) {
        auto roomPlayer = dynamic_cast<RoomPlayer*>(item);
        if (roomPlayer->getPlayerId() == sourcePlayerId) {
            sourcePlayerRadian = roomPlayer->getRadian();
        }
        if (roomPlayer->getPlayerId() == destPlayerId) {
            destPlayerRadian = roomPlayer->getRadian();
        }
    }
    
    if (sourcePlayerRadian == NAN || destPlayerRadian == NAN)
        return;
    
    auto usedItem = ShopItemUsed::create(shopItemName, sourcePlayerRadian, destPlayerRadian, destPlayerId);
    this->addChild(usedItem, layerPlayerTag + 1);
    usedItem->animate();
}

void SceneRoom::callbackTimeToStart(const std::string &source) {
    if (source.empty())
        return;
    
    sdkbox::PluginGoogleAnalytics::logEvent("ApiCallback", "callbackTimeToStart", "", 1);
    
    MessageResponseTimeToStart msg;
    msg.ParseFromString(source);
    
    if (msg.roomid() != _roomId)
        return;
    
    _isTimerEnabled = false;
    _timerTime = msg.time();
    _shootDirection = msg.shootdirection();
    _isTimerEnabled = true;
    
    this->hideDialog();
    this->setPlayerHandPistolVisible(false);
    //    [self showPlayerHandPistol];
    auto _roomLamp = dynamic_cast<RoomLamp*>(this->getChildByTag(lampTag));
    _roomLamp->setIsLampOn(false);
    this->setRotateDrumButtonVisible(false);
    this->setShootButtonVisible(false);
    this->setCurrentRound(msg.currentround());
    
    for (auto item : this->getChildByTag(layerPlayerTag)->getChildren()) {
        auto roomPlayer = dynamic_cast<RoomPlayer*>(item);
        roomPlayer->setShootDirection((_shootDirection == RoomShootDirection::rsdLEFT) ? PlayerShootDirection::psdLEFT : PlayerShootDirection::psdRIGHT);
    }
    
    if(_currentRound > 1) {
        this->fadeAndRemoveEmptyPlayers(true);
    }
    
    if (msg.ischooseduelist()) {
        this->showDialog(DialogTypes::DialogTypeDuel);
    }
    
    if(GlobalProperties::isDebug()) {
        auto winSize = Director::getInstance()->getVisibleSize();
        this->removeChildByTag(shootDirectionTag);
        auto sdSprite = Sprite::create("SceneRoom/SceneRoomArrow.png");
        sdSprite->setFlippedX(_shootDirection == rsdLEFT);
        sdSprite->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
        sdSprite->setPosition(Vec2(10, winSize.height - 200));
        this->addChild(sdSprite, shootDirectionTag, shootDirectionTag);
    }
}

void SceneRoom::callbackTimeToPutBullets(const std::string &source) {
    if (source.empty())
        return;
    
    sdkbox::PluginGoogleAnalytics::logEvent("ApiCallback", "callbackTimeToPutBullets", "", 1);
    
    MessageResponseTimeToPutBullets msg;
    msg.ParseFromString(source);
    
    if (msg.roomid() != _roomId) {
        return;
    }
    
    //_isTimerEnabled = false;
    //_timerTime = int(msg.time());
    //_isTimerEnabled = true;
 
    _roundPossibleBullets = msg.possiblebullets();
    
    //this->fadeAndRemoveEmptyPlayers(true);
    
    if (isPlayerAtRoom()) {
        this->hideDialog();
        this->showDialog(DialogTypes::DialogTypePutBullets);
    }
}

bool SceneRoom::isPlayerAtRoom() {
    return (GlobalProperties::getPlayerId() > 0 && this->isPlayerExists(GlobalProperties::getPlayerId()));
}

void SceneRoom::callbackTimeToRotateDrum(const std::string &source) {
    if (source.empty())
        return;
    
    sdkbox::PluginGoogleAnalytics::logEvent("ApiCallback", "callbackTimeToRotateDrum", "", 1);
    
    MessageResponseTimeToRotateDrum msg;
    msg.ParseFromString(source);
    
    if (msg.roomid() != _roomId)
        return;
    
    _isTimerEnabled = false;
    _timerTime = int(msg.time());
    _isTimerEnabled = true;

    if (isPlayerAtRoom()) {
        this->hideDialog();
        this->setRotateDrumButtonVisible(true);
        this->setShootButtonVisible(true);
    }

    this->fadeAndRemoveEmptyPlayers(true);
    
    this->setPlayerHandPistolVisible(true);
}

void SceneRoom::callbackTimeToShoot(const std::string &source) {
    if (source.empty())
        return;

    sdkbox::PluginGoogleAnalytics::logEvent("ApiCallback", "callbackTimeToShoot", "", 1);
    
    MessageResponseTimeToShoot msg;
    msg.ParseFromString(source);
    
    if (msg.roomid() != _roomId)
        return;

    auto _roomLamp = dynamic_cast<RoomLamp*>(this->getChildByTag(lampTag));
    
    _isTimerEnabled = false;
    _timerTime = msg.time();
    _isTimerEnabled = true;
    
    if (isPlayerAtRoom()) {
        this->hideDialog();
    }
    
    this->setPlayerHandPistolVisible(true);
    _roomLamp->setIsLampOn(true);
    this->setRotateDrumButtonVisible(false);
}

void SceneRoom::callbackRoomResults(const std::string &source) {
    if (source.empty())
        return;
    
    sdkbox::PluginGoogleAnalytics::logEvent("ApiCallback", "callbackRoomResults", "", 1);
    
    MessageResponseTimeToResults msg;
    msg.ParseFromString(source);
    
    if (msg.roomid() != _roomId)
        return;

    _isTimerEnabled = false;
    _timerTime = msg.time();
    _isTimerEnabled = true;

    this->setRotateDrumButtonVisible(false);
    this->setShootButtonVisible(false);

    auto _roomLamp = dynamic_cast<RoomLamp*>(this->getChildByTag(lampTag));
    auto resultType = msg.resulttype();
    
    switch (resultType) {
        case MessageResponseTimeToResults_eRoomResultType_rrtPlayerBang: {
            if (isPlayerAtRoom()) {
                this->hideDialog();
            }
            this->setPlayerHandPistolVisible(true);
            _roomLamp->setIsLampOn(true);
            break;
        }
            
        case MessageResponseTimeToResults_eRoomResultType_rrtPlayerDuelist: {
            this->setPlayerHandPistolVisible(false);
            _roomLamp->setIsLampOn(false);
            break;
        }
            
        default:
            break;
    }
    
    _roundGameResult.clear();
    
    if (msg.gameresults_size() > 0) {
        Vector<FiniteTimeAction*> arrAnim;
        
        double avgPerAnimation = 5.0 / msg.gameresults_size();

        for (auto item : msg.gameresults()) {
            auto roundResult = RoomRoundGameResult::create(item.playerid(), item.playerposition(), item.killedplayerid(), item.killedplayerposition());
            roundResult->retain();
            _roundGameResult.push_back(roundResult);
            
            arrAnim.pushBack(CallFunc::create(CC_CALLBACK_0(SceneRoom::resetKillerState, this)));
            arrAnim.pushBack(CallFunc::create(CC_CALLBACK_0(SceneRoom::onRoundGameResultDidSequenceAnimation, this)));
            arrAnim.pushBack(DelayTime::create(avgPerAnimation));
        }
        
        this->runAction(Sequence::create(arrAnim));
    }
}

void SceneRoom::callbackNeedAuth(const std::string &source) {
    sdkbox::PluginGoogleAnalytics::logEvent("ApiCallback", "callbackNeedAuth", "", 1);
    
    //[self showDialog:DialogTypeAuth];
    this->authPlayer();
}

void SceneRoom::callbackAuth(const std::string &source) {
    if (source.empty())
        return;
    
    sdkbox::PluginGoogleAnalytics::logEvent("ApiCallback", "callbackAuth", "", 1);
    
    MessageResponseAuth msg;
    msg.ParseFromString(source);
    
    auto authErrorType = msg.errortype();
    
    if (authErrorType == MessageResponseAuth_eAuthErrorType_aetNone) {
        GlobalProperties::setPlayerId(msg.playerid());
        
        if (_plannedPlayerType == MessageRequestSetPlayerTypeAndPosition_ePlayerType_ptINVESTOR) {
            _currentPlayerType = _plannedPlayerType;
        }
        
        if (GlobalProperties::getPlayerId() > 0) {
            this->setPlayerType(_plannedPlayerType, _plannedSitPosition);
        }
    }
    else {
        GlobalProperties::setPlayerId(-1L);
    }
}

void SceneRoom::callbackGetRoomPlayers(const std::string &source) {
    if (source.empty())
        return;
    
    sdkbox::PluginGoogleAnalytics::logEvent("ApiCallback", "callbackGetRoomPlayers", "", 1);
    
    MessageResponseRoomPlayerList msg;
    msg.ParseFromString(source);
    
    if (msg.roomid() != _roomId)
        return;
    
    double radianAvg = Utils::getAverageAngleByAmount(msg.playerlist_size());
    double nextRadian = 0;
    auto _layerPlayer = this->getChildByTag(layerPlayerTag);
    auto _layerShootDirection = this->getChildByTag(layerShootDirectionTag);
    
    for (auto item : msg.playerlist()) {
        auto newPlayer = RoomPlayer::create(item.playerid(),
                                            item.playername(),
                                            item.playerposition(),
                                            item.playeravatar(),
                                            item.shootdirection(),
                                            nextRadian,
                                            RoomPlayer::RoomPlayerStateTypeDefault);
        _layerPlayer->addChild(newPlayer);
        _layerShootDirection->addChild(ShootDirection::create(newPlayer));
        nextRadian =  nextRadian - radianAvg;
    }
}

void SceneRoom::callbackTimeToEnd(const std::string &source) {
    if (source.empty())
        return;
    
    sdkbox::PluginGoogleAnalytics::logEvent("ApiCallback", "callbackTimeToEnd", "", 1);
    
    MessageResponseTimeToEnd msg;
    msg.ParseFromString(source);
    
    if (msg.roomid() != _roomId)
        return;
    
    auto _roomLamp = dynamic_cast<RoomLamp*>(this->getChildByTag(lampTag));
    
    _isTimerEnabled = false;
    _roomLamp->setIsLampOn(false);
    _roomLamp->setText(LanguageManager::getString("RoomGameEndLabel"));
    this->setCurrentTime("0:00");
    
    this->setRotateDrumButtonVisible(false);
    this->setShootButtonVisible(false);
    
    if (GlobalProperties::isDebug()) {
        log(">>> callbackTimeToEnd withWinner(%d)", msg.has_gamewinner());
    }
    
    if (this->amountLivePlayers() > 1) {
        this->setPlayerHandPistolVisible(true);
    } else {
        this->setPlayerHandPistolVisible(false);
        this->fadeAndRemoveEmptyPlayers(true);
        _roomLamp->fadeOut();
        
        if (msg.has_gamewinner()) {
            for (auto item : this->getChildByTag(layerPlayerTag)->getChildren()) {
                auto roomPlayer = dynamic_cast<RoomPlayer*>(item);
                if (roomPlayer->getPlayerId() == msg.gamewinner().playerid()) {
                    this->showGameWinner(roomPlayer, msg.gamewinner());
                    break;
                }
            }
        }
    }
}

void SceneRoom::callbackSetPlayerTypeAndPosition(const std::string &source) {
    if (source.empty())
        return;
    
    sdkbox::PluginGoogleAnalytics::logEvent("ApiCallback", "callbackSetPlayerTypeAndPosition", "", 1);
    
    MessageResponseSetPlayerTypeAndPosition msg;
    msg.ParseFromString(source);
    
    if (msg.roomid() != _roomId)
        return;
    
    long long playerId = msg.player().playerid();
    int playerPosition = msg.player().playerposition();
    std::string playerAvatar = msg.player().playeravatar();
    std::string playerName = msg.player().playername();
    
    RoomPlayer *player = nullptr;
    
    for (auto item : this->getChildByTag(layerPlayerTag)->getChildren()) {
        auto roomPlayer = dynamic_cast<RoomPlayer*>(item);
        if (playerPosition > 0 && roomPlayer->getPlayerPosition() == playerPosition) {
            player = roomPlayer;
            break;
        }
        
        if (playerPosition <= 0 && roomPlayer->getPlayerId() == playerId) {
            player = roomPlayer;
            break;
        }
    }
    
    if (!player || playerId <= 0L)
        return;
    
    if (player->getPlayerId() == playerId && playerPosition == 0) {
        player->setPlayerId(0L);
        player->setAvatar("");
    } else {
        if (playerId == GlobalProperties::getPlayerId()) {
            _currentPlayerType = MessageRequestSetPlayerTypeAndPosition_ePlayerType_ptPLAYER;
        }
        
        player->setPlayerId(playerId);
        player->setPlayerName(playerName);
        player->setAvatar(playerAvatar);
    }
}

void SceneRoom::callbackRotateDrum(const std::string &source) {
    if (source.empty())
        return;
    
    sdkbox::PluginGoogleAnalytics::logEvent("ApiCallback", "callbackRotateDrum", "", 1);
    experimental::AudioEngine::play2d("Sounds/rotate_drum.mp3");

    MessageResponseRotateDrum msg;
    msg.ParseFromString(source);
    
    if (msg.roomid() != _roomId)
        return;
    
    auto _layerPlayer = this->getChildByTag(layerPlayerTag);
    
    long destPlayerId = msg.playerid();
    int playerAmount = _layerPlayer->getChildrenCount();
    
    for (auto item : _layerPlayer->getChildren()) {
        auto player = dynamic_cast<RoomPlayer*>(item);
        player->animateRotationWithPlayerId(destPlayerId, (_shootDirection == RoomShootDirection::rsdRIGHT), true, playerAmount);
    }
}

void SceneRoom::callbackGetRoomInfo(const std::string &source) {
    if (source.empty()) {
        this->onMenuCallback(this->getChildByTag(miBackTag));
        return;
    }
    
    sdkbox::PluginGoogleAnalytics::logEvent("ApiCallback", "callbackGetRoomInfo", "", 1);
    
    MessageResponseRoomInfo msg;
    msg.ParseFromString(source);
    
    if (msg.roomid() != _roomId) {
        this->onMenuCallback(this->getChildByTag(miBackTag));
        return;
    }
    
    _bet = msg.bet();
    _investorBank = msg.investorbank();
    _maxPlayers = msg.maxplayers();
    _maxRounds = msg.maxrounds();
    _isGameStarted = msg.isgamestarted();
    _shootDirection = msg.shootdirection();
    this->setCurrentRound(msg.currentround());
    this->setCurrentBank(msg.playerbank());
    
    this->getRoomPlayers();
}

void SceneRoom::callbackNoMoney(const std::string &source) {
    if (source.empty()) {
        this->onMenuCallback(this->getChildByTag(miBackTag));
        return;
    }
    
    sdkbox::PluginGoogleAnalytics::logEvent("ApiCallback", "callbackNoMoney", "", 1);
    
    MessageResponseNoMoney msg;
    msg.ParseFromString(source);
    
    this->hideDialog();
    this->showDialog(DialogTypes::DialogTypeBase);
    auto dialog = dynamic_cast<DialogBase*>(this->getChildByTag(DialogTypeBase));
    
    dialog->addDoneButton(LanguageManager::getString("DialogBaseDoneButton"));
    
    Size winSize = Director::getInstance()->getVisibleSize();
    
    std::string dlgMessage = StringUtils::format(LanguageManager::getString("DialogNoMoneyMessage").c_str(), msg.need(), msg.amount());
    auto lblDialogMessage = Label::createWithTTF(dlgMessage, GameFont, 28);
    lblDialogMessage->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
    lblDialogMessage->setColor(Color3B(56, 37, 27));
    dialog->addChild(lblDialogMessage);
}

void SceneRoom::callbackBang(const std::string &source) {
    if (source.empty())
        return;
    
    sdkbox::PluginGoogleAnalytics::logEvent("ApiCallback", "callbackBang", "", 1);
    
    MessageResponseRoomPlayerBang msg;
    msg.ParseFromString(source);
    
    if (msg.roomid() != _roomId)
        return;
    
    Vector<FiniteTimeAction*> arrAnim;
    
    double avgPerAnimation = 0.3;
    
    auto roundResult = RoomRoundGameResult::create(msg.result().playerid(), msg.result().playerposition(), msg.result().killedplayerid(), msg.result().killedplayerposition());
    roundResult->retain();
    _roundGameResult.push_back(roundResult);
    
    arrAnim.pushBack(CallFunc::create(CC_CALLBACK_0(SceneRoom::resetKillerState, this)));
    arrAnim.pushBack(CallFunc::create(CC_CALLBACK_0(SceneRoom::onRoundGameResultDidSequenceAnimation, this)));
    arrAnim.pushBack(DelayTime::create(avgPerAnimation));
    
    this->runAction(Sequence::create(arrAnim));
}
