// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: MessageResponseRoomPlayerInfo.proto

package ProtoMessages;

public final class MessageResponseRoomPlayerInfoBase {
  private MessageResponseRoomPlayerInfoBase() {}
  public static void registerAllExtensions(
      com.google.protobuf.ExtensionRegistryLite registry) {
  }
  public interface MessageResponseRoomPlayerInfoOrBuilder extends
      // @@protoc_insertion_point(interface_extends:MessageResponseRoomPlayerInfo)
      com.google.protobuf.MessageLiteOrBuilder {

    /**
     * <code>required int64 playerId = 1 [default = 0];</code>
     */
    boolean hasPlayerId();
    /**
     * <code>required int64 playerId = 1 [default = 0];</code>
     */
    long getPlayerId();

    /**
     * <code>required string playerName = 2 [default = ""];</code>
     */
    boolean hasPlayerName();
    /**
     * <code>required string playerName = 2 [default = ""];</code>
     */
    java.lang.String getPlayerName();
    /**
     * <code>required string playerName = 2 [default = ""];</code>
     */
    com.google.protobuf.ByteString
        getPlayerNameBytes();

    /**
     * <code>required int32 playerPosition = 3 [default = 0];</code>
     */
    boolean hasPlayerPosition();
    /**
     * <code>required int32 playerPosition = 3 [default = 0];</code>
     */
    int getPlayerPosition();

    /**
     * <code>required bytes playerAvatar = 4 [default = "&#92;000"];</code>
     */
    boolean hasPlayerAvatar();
    /**
     * <code>required bytes playerAvatar = 4 [default = "&#92;000"];</code>
     */
    com.google.protobuf.ByteString getPlayerAvatar();

    /**
     * <code>required .PlayerShootDirection shootDirection = 5 [default = psdLEFT];</code>
     */
    boolean hasShootDirection();
    /**
     * <code>required .PlayerShootDirection shootDirection = 5 [default = psdLEFT];</code>
     */
    ProtoMessages.PlayerShootDirectionBase.PlayerShootDirection getShootDirection();
  }
  /**
   * Protobuf type {@code MessageResponseRoomPlayerInfo}
   */
  public  static final class MessageResponseRoomPlayerInfo extends
      com.google.protobuf.GeneratedMessageLite<
          MessageResponseRoomPlayerInfo, MessageResponseRoomPlayerInfo.Builder> implements
      // @@protoc_insertion_point(message_implements:MessageResponseRoomPlayerInfo)
      MessageResponseRoomPlayerInfoOrBuilder {
    private MessageResponseRoomPlayerInfo() {
      playerName_ = "";
      playerAvatar_ = PLAYERAVATAR_DEFAULT_VALUE;
    }
    private int bitField0_;
    public static final int PLAYERID_FIELD_NUMBER = 1;
    private long playerId_;
    /**
     * <code>required int64 playerId = 1 [default = 0];</code>
     */
    public boolean hasPlayerId() {
      return ((bitField0_ & 0x00000001) == 0x00000001);
    }
    /**
     * <code>required int64 playerId = 1 [default = 0];</code>
     */
    public long getPlayerId() {
      return playerId_;
    }
    /**
     * <code>required int64 playerId = 1 [default = 0];</code>
     */
    private void setPlayerId(long value) {
      bitField0_ |= 0x00000001;
      playerId_ = value;
    }
    /**
     * <code>required int64 playerId = 1 [default = 0];</code>
     */
    private void clearPlayerId() {
      bitField0_ = (bitField0_ & ~0x00000001);
      playerId_ = 0L;
    }

    public static final int PLAYERNAME_FIELD_NUMBER = 2;
    private java.lang.String playerName_;
    /**
     * <code>required string playerName = 2 [default = ""];</code>
     */
    public boolean hasPlayerName() {
      return ((bitField0_ & 0x00000002) == 0x00000002);
    }
    /**
     * <code>required string playerName = 2 [default = ""];</code>
     */
    public java.lang.String getPlayerName() {
      return playerName_;
    }
    /**
     * <code>required string playerName = 2 [default = ""];</code>
     */
    public com.google.protobuf.ByteString
        getPlayerNameBytes() {
      return com.google.protobuf.ByteString.copyFromUtf8(playerName_);
    }
    /**
     * <code>required string playerName = 2 [default = ""];</code>
     */
    private void setPlayerName(
        java.lang.String value) {
      if (value == null) {
    throw new NullPointerException();
  }
  bitField0_ |= 0x00000002;
      playerName_ = value;
    }
    /**
     * <code>required string playerName = 2 [default = ""];</code>
     */
    private void clearPlayerName() {
      bitField0_ = (bitField0_ & ~0x00000002);
      playerName_ = getDefaultInstance().getPlayerName();
    }
    /**
     * <code>required string playerName = 2 [default = ""];</code>
     */
    private void setPlayerNameBytes(
        com.google.protobuf.ByteString value) {
      if (value == null) {
    throw new NullPointerException();
  }
  bitField0_ |= 0x00000002;
      playerName_ = value.toStringUtf8();
    }

    public static final int PLAYERPOSITION_FIELD_NUMBER = 3;
    private int playerPosition_;
    /**
     * <code>required int32 playerPosition = 3 [default = 0];</code>
     */
    public boolean hasPlayerPosition() {
      return ((bitField0_ & 0x00000004) == 0x00000004);
    }
    /**
     * <code>required int32 playerPosition = 3 [default = 0];</code>
     */
    public int getPlayerPosition() {
      return playerPosition_;
    }
    /**
     * <code>required int32 playerPosition = 3 [default = 0];</code>
     */
    private void setPlayerPosition(int value) {
      bitField0_ |= 0x00000004;
      playerPosition_ = value;
    }
    /**
     * <code>required int32 playerPosition = 3 [default = 0];</code>
     */
    private void clearPlayerPosition() {
      bitField0_ = (bitField0_ & ~0x00000004);
      playerPosition_ = 0;
    }

    public static final int PLAYERAVATAR_FIELD_NUMBER = 4;
    private static final com.google.protobuf.ByteString PLAYERAVATAR_DEFAULT_VALUE = com.google.protobuf.Internal.bytesDefaultValue("\000");
    private com.google.protobuf.ByteString playerAvatar_;
    /**
     * <code>required bytes playerAvatar = 4 [default = "&#92;000"];</code>
     */
    public boolean hasPlayerAvatar() {
      return ((bitField0_ & 0x00000008) == 0x00000008);
    }
    /**
     * <code>required bytes playerAvatar = 4 [default = "&#92;000"];</code>
     */
    public com.google.protobuf.ByteString getPlayerAvatar() {
      return playerAvatar_;
    }
    /**
     * <code>required bytes playerAvatar = 4 [default = "&#92;000"];</code>
     */
    private void setPlayerAvatar(com.google.protobuf.ByteString value) {
      if (value == null) {
    throw new NullPointerException();
  }
  bitField0_ |= 0x00000008;
      playerAvatar_ = value;
    }
    /**
     * <code>required bytes playerAvatar = 4 [default = "&#92;000"];</code>
     */
    private void clearPlayerAvatar() {
      bitField0_ = (bitField0_ & ~0x00000008);
      playerAvatar_ = getDefaultInstance().getPlayerAvatar();
    }

    public static final int SHOOTDIRECTION_FIELD_NUMBER = 5;
    private int shootDirection_;
    /**
     * <code>required .PlayerShootDirection shootDirection = 5 [default = psdLEFT];</code>
     */
    public boolean hasShootDirection() {
      return ((bitField0_ & 0x00000010) == 0x00000010);
    }
    /**
     * <code>required .PlayerShootDirection shootDirection = 5 [default = psdLEFT];</code>
     */
    public ProtoMessages.PlayerShootDirectionBase.PlayerShootDirection getShootDirection() {
      ProtoMessages.PlayerShootDirectionBase.PlayerShootDirection result = ProtoMessages.PlayerShootDirectionBase.PlayerShootDirection.forNumber(shootDirection_);
      return result == null ? ProtoMessages.PlayerShootDirectionBase.PlayerShootDirection.psdLEFT : result;
    }
    /**
     * <code>required .PlayerShootDirection shootDirection = 5 [default = psdLEFT];</code>
     */
    private void setShootDirection(ProtoMessages.PlayerShootDirectionBase.PlayerShootDirection value) {
      if (value == null) {
        throw new NullPointerException();
      }
      bitField0_ |= 0x00000010;
      shootDirection_ = value.getNumber();
    }
    /**
     * <code>required .PlayerShootDirection shootDirection = 5 [default = psdLEFT];</code>
     */
    private void clearShootDirection() {
      bitField0_ = (bitField0_ & ~0x00000010);
      shootDirection_ = 0;
    }

    public void writeTo(com.google.protobuf.CodedOutputStream output)
                        throws java.io.IOException {
      if (((bitField0_ & 0x00000001) == 0x00000001)) {
        output.writeInt64(1, playerId_);
      }
      if (((bitField0_ & 0x00000002) == 0x00000002)) {
        output.writeString(2, getPlayerName());
      }
      if (((bitField0_ & 0x00000004) == 0x00000004)) {
        output.writeInt32(3, playerPosition_);
      }
      if (((bitField0_ & 0x00000008) == 0x00000008)) {
        output.writeBytes(4, playerAvatar_);
      }
      if (((bitField0_ & 0x00000010) == 0x00000010)) {
        output.writeEnum(5, shootDirection_);
      }
      unknownFields.writeTo(output);
    }

    public int getSerializedSize() {
      int size = memoizedSerializedSize;
      if (size != -1) return size;

      size = 0;
      if (((bitField0_ & 0x00000001) == 0x00000001)) {
        size += com.google.protobuf.CodedOutputStream
          .computeInt64Size(1, playerId_);
      }
      if (((bitField0_ & 0x00000002) == 0x00000002)) {
        size += com.google.protobuf.CodedOutputStream
          .computeStringSize(2, getPlayerName());
      }
      if (((bitField0_ & 0x00000004) == 0x00000004)) {
        size += com.google.protobuf.CodedOutputStream
          .computeInt32Size(3, playerPosition_);
      }
      if (((bitField0_ & 0x00000008) == 0x00000008)) {
        size += com.google.protobuf.CodedOutputStream
          .computeBytesSize(4, playerAvatar_);
      }
      if (((bitField0_ & 0x00000010) == 0x00000010)) {
        size += com.google.protobuf.CodedOutputStream
          .computeEnumSize(5, shootDirection_);
      }
      size += unknownFields.getSerializedSize();
      memoizedSerializedSize = size;
      return size;
    }

    public static ProtoMessages.MessageResponseRoomPlayerInfoBase.MessageResponseRoomPlayerInfo parseFrom(
        com.google.protobuf.ByteString data)
        throws com.google.protobuf.InvalidProtocolBufferException {
      return com.google.protobuf.GeneratedMessageLite.parseFrom(
          DEFAULT_INSTANCE, data);
    }
    public static ProtoMessages.MessageResponseRoomPlayerInfoBase.MessageResponseRoomPlayerInfo parseFrom(
        com.google.protobuf.ByteString data,
        com.google.protobuf.ExtensionRegistryLite extensionRegistry)
        throws com.google.protobuf.InvalidProtocolBufferException {
      return com.google.protobuf.GeneratedMessageLite.parseFrom(
          DEFAULT_INSTANCE, data, extensionRegistry);
    }
    public static ProtoMessages.MessageResponseRoomPlayerInfoBase.MessageResponseRoomPlayerInfo parseFrom(byte[] data)
        throws com.google.protobuf.InvalidProtocolBufferException {
      return com.google.protobuf.GeneratedMessageLite.parseFrom(
          DEFAULT_INSTANCE, data);
    }
    public static ProtoMessages.MessageResponseRoomPlayerInfoBase.MessageResponseRoomPlayerInfo parseFrom(
        byte[] data,
        com.google.protobuf.ExtensionRegistryLite extensionRegistry)
        throws com.google.protobuf.InvalidProtocolBufferException {
      return com.google.protobuf.GeneratedMessageLite.parseFrom(
          DEFAULT_INSTANCE, data, extensionRegistry);
    }
    public static ProtoMessages.MessageResponseRoomPlayerInfoBase.MessageResponseRoomPlayerInfo parseFrom(java.io.InputStream input)
        throws java.io.IOException {
      return com.google.protobuf.GeneratedMessageLite.parseFrom(
          DEFAULT_INSTANCE, input);
    }
    public static ProtoMessages.MessageResponseRoomPlayerInfoBase.MessageResponseRoomPlayerInfo parseFrom(
        java.io.InputStream input,
        com.google.protobuf.ExtensionRegistryLite extensionRegistry)
        throws java.io.IOException {
      return com.google.protobuf.GeneratedMessageLite.parseFrom(
          DEFAULT_INSTANCE, input, extensionRegistry);
    }
    public static ProtoMessages.MessageResponseRoomPlayerInfoBase.MessageResponseRoomPlayerInfo parseDelimitedFrom(java.io.InputStream input)
        throws java.io.IOException {
      return parseDelimitedFrom(DEFAULT_INSTANCE, input);
    }
    public static ProtoMessages.MessageResponseRoomPlayerInfoBase.MessageResponseRoomPlayerInfo parseDelimitedFrom(
        java.io.InputStream input,
        com.google.protobuf.ExtensionRegistryLite extensionRegistry)
        throws java.io.IOException {
      return parseDelimitedFrom(DEFAULT_INSTANCE, input, extensionRegistry);
    }
    public static ProtoMessages.MessageResponseRoomPlayerInfoBase.MessageResponseRoomPlayerInfo parseFrom(
        com.google.protobuf.CodedInputStream input)
        throws java.io.IOException {
      return com.google.protobuf.GeneratedMessageLite.parseFrom(
          DEFAULT_INSTANCE, input);
    }
    public static ProtoMessages.MessageResponseRoomPlayerInfoBase.MessageResponseRoomPlayerInfo parseFrom(
        com.google.protobuf.CodedInputStream input,
        com.google.protobuf.ExtensionRegistryLite extensionRegistry)
        throws java.io.IOException {
      return com.google.protobuf.GeneratedMessageLite.parseFrom(
          DEFAULT_INSTANCE, input, extensionRegistry);
    }

    public static Builder newBuilder() {
      return DEFAULT_INSTANCE.toBuilder();
    }
    public static Builder newBuilder(ProtoMessages.MessageResponseRoomPlayerInfoBase.MessageResponseRoomPlayerInfo prototype) {
      return DEFAULT_INSTANCE.toBuilder().mergeFrom(prototype);
    }

    /**
     * Protobuf type {@code MessageResponseRoomPlayerInfo}
     */
    public static final class Builder extends
        com.google.protobuf.GeneratedMessageLite.Builder<
          ProtoMessages.MessageResponseRoomPlayerInfoBase.MessageResponseRoomPlayerInfo, Builder> implements
        // @@protoc_insertion_point(builder_implements:MessageResponseRoomPlayerInfo)
        ProtoMessages.MessageResponseRoomPlayerInfoBase.MessageResponseRoomPlayerInfoOrBuilder {
      // Construct using ProtoMessages.MessageResponseRoomPlayerInfoBase.MessageResponseRoomPlayerInfo.newBuilder()
      private Builder() {
        super(DEFAULT_INSTANCE);
      }


      /**
       * <code>required int64 playerId = 1 [default = 0];</code>
       */
      public boolean hasPlayerId() {
        return instance.hasPlayerId();
      }
      /**
       * <code>required int64 playerId = 1 [default = 0];</code>
       */
      public long getPlayerId() {
        return instance.getPlayerId();
      }
      /**
       * <code>required int64 playerId = 1 [default = 0];</code>
       */
      public Builder setPlayerId(long value) {
        copyOnWrite();
        instance.setPlayerId(value);
        return this;
      }
      /**
       * <code>required int64 playerId = 1 [default = 0];</code>
       */
      public Builder clearPlayerId() {
        copyOnWrite();
        instance.clearPlayerId();
        return this;
      }

      /**
       * <code>required string playerName = 2 [default = ""];</code>
       */
      public boolean hasPlayerName() {
        return instance.hasPlayerName();
      }
      /**
       * <code>required string playerName = 2 [default = ""];</code>
       */
      public java.lang.String getPlayerName() {
        return instance.getPlayerName();
      }
      /**
       * <code>required string playerName = 2 [default = ""];</code>
       */
      public com.google.protobuf.ByteString
          getPlayerNameBytes() {
        return instance.getPlayerNameBytes();
      }
      /**
       * <code>required string playerName = 2 [default = ""];</code>
       */
      public Builder setPlayerName(
          java.lang.String value) {
        copyOnWrite();
        instance.setPlayerName(value);
        return this;
      }
      /**
       * <code>required string playerName = 2 [default = ""];</code>
       */
      public Builder clearPlayerName() {
        copyOnWrite();
        instance.clearPlayerName();
        return this;
      }
      /**
       * <code>required string playerName = 2 [default = ""];</code>
       */
      public Builder setPlayerNameBytes(
          com.google.protobuf.ByteString value) {
        copyOnWrite();
        instance.setPlayerNameBytes(value);
        return this;
      }

      /**
       * <code>required int32 playerPosition = 3 [default = 0];</code>
       */
      public boolean hasPlayerPosition() {
        return instance.hasPlayerPosition();
      }
      /**
       * <code>required int32 playerPosition = 3 [default = 0];</code>
       */
      public int getPlayerPosition() {
        return instance.getPlayerPosition();
      }
      /**
       * <code>required int32 playerPosition = 3 [default = 0];</code>
       */
      public Builder setPlayerPosition(int value) {
        copyOnWrite();
        instance.setPlayerPosition(value);
        return this;
      }
      /**
       * <code>required int32 playerPosition = 3 [default = 0];</code>
       */
      public Builder clearPlayerPosition() {
        copyOnWrite();
        instance.clearPlayerPosition();
        return this;
      }

      /**
       * <code>required bytes playerAvatar = 4 [default = "&#92;000"];</code>
       */
      public boolean hasPlayerAvatar() {
        return instance.hasPlayerAvatar();
      }
      /**
       * <code>required bytes playerAvatar = 4 [default = "&#92;000"];</code>
       */
      public com.google.protobuf.ByteString getPlayerAvatar() {
        return instance.getPlayerAvatar();
      }
      /**
       * <code>required bytes playerAvatar = 4 [default = "&#92;000"];</code>
       */
      public Builder setPlayerAvatar(com.google.protobuf.ByteString value) {
        copyOnWrite();
        instance.setPlayerAvatar(value);
        return this;
      }
      /**
       * <code>required bytes playerAvatar = 4 [default = "&#92;000"];</code>
       */
      public Builder clearPlayerAvatar() {
        copyOnWrite();
        instance.clearPlayerAvatar();
        return this;
      }

      /**
       * <code>required .PlayerShootDirection shootDirection = 5 [default = psdLEFT];</code>
       */
      public boolean hasShootDirection() {
        return instance.hasShootDirection();
      }
      /**
       * <code>required .PlayerShootDirection shootDirection = 5 [default = psdLEFT];</code>
       */
      public ProtoMessages.PlayerShootDirectionBase.PlayerShootDirection getShootDirection() {
        return instance.getShootDirection();
      }
      /**
       * <code>required .PlayerShootDirection shootDirection = 5 [default = psdLEFT];</code>
       */
      public Builder setShootDirection(ProtoMessages.PlayerShootDirectionBase.PlayerShootDirection value) {
        copyOnWrite();
        instance.setShootDirection(value);
        return this;
      }
      /**
       * <code>required .PlayerShootDirection shootDirection = 5 [default = psdLEFT];</code>
       */
      public Builder clearShootDirection() {
        copyOnWrite();
        instance.clearShootDirection();
        return this;
      }

      // @@protoc_insertion_point(builder_scope:MessageResponseRoomPlayerInfo)
    }
    private byte memoizedIsInitialized = -1;
    protected final Object dynamicMethod(
        com.google.protobuf.GeneratedMessageLite.MethodToInvoke method,
        Object arg0, Object arg1) {
      switch (method) {
        case NEW_MUTABLE_INSTANCE: {
          return new ProtoMessages.MessageResponseRoomPlayerInfoBase.MessageResponseRoomPlayerInfo();
        }
        case IS_INITIALIZED: {
          byte isInitialized = memoizedIsInitialized;
          if (isInitialized == 1) return DEFAULT_INSTANCE;
          if (isInitialized == 0) return null;

          boolean shouldMemoize = ((Boolean) arg0).booleanValue();
          if (!hasPlayerId()) {
            if (shouldMemoize) {
              memoizedIsInitialized = 0;
            }
            return null;
          }
          if (!hasPlayerName()) {
            if (shouldMemoize) {
              memoizedIsInitialized = 0;
            }
            return null;
          }
          if (!hasPlayerPosition()) {
            if (shouldMemoize) {
              memoizedIsInitialized = 0;
            }
            return null;
          }
          if (!hasPlayerAvatar()) {
            if (shouldMemoize) {
              memoizedIsInitialized = 0;
            }
            return null;
          }
          if (!hasShootDirection()) {
            if (shouldMemoize) {
              memoizedIsInitialized = 0;
            }
            return null;
          }
          if (shouldMemoize) memoizedIsInitialized = 1;
          return DEFAULT_INSTANCE;

        }
        case MAKE_IMMUTABLE: {
          return null;
        }
        case NEW_BUILDER: {
          return new Builder();
        }
        case VISIT: {
          Visitor visitor = (Visitor) arg0;
          ProtoMessages.MessageResponseRoomPlayerInfoBase.MessageResponseRoomPlayerInfo other = (ProtoMessages.MessageResponseRoomPlayerInfoBase.MessageResponseRoomPlayerInfo) arg1;
          playerId_ = visitor.visitLong(
              hasPlayerId(), playerId_,
              other.hasPlayerId(), other.playerId_);
          playerName_ = visitor.visitString(
              hasPlayerName(), playerName_,
              other.hasPlayerName(), other.playerName_);
          playerPosition_ = visitor.visitInt(
              hasPlayerPosition(), playerPosition_,
              other.hasPlayerPosition(), other.playerPosition_);
          playerAvatar_ = visitor.visitByteString(
              hasPlayerAvatar(), playerAvatar_,
              other.hasPlayerAvatar(), other.playerAvatar_);
          shootDirection_ = visitor.visitInt(hasShootDirection(), shootDirection_,
              other.hasShootDirection(), other.shootDirection_);
          if (visitor == com.google.protobuf.GeneratedMessageLite.MergeFromVisitor
              .INSTANCE) {
            bitField0_ |= other.bitField0_;
          }
          return this;
        }
        case MERGE_FROM_STREAM: {
          com.google.protobuf.CodedInputStream input =
              (com.google.protobuf.CodedInputStream) arg0;
          com.google.protobuf.ExtensionRegistryLite extensionRegistry =
              (com.google.protobuf.ExtensionRegistryLite) arg1;
          try {
            boolean done = false;
            while (!done) {
              int tag = input.readTag();
              switch (tag) {
                case 0:
                  done = true;
                  break;
                default: {
                  if (!parseUnknownField(tag, input)) {
                    done = true;
                  }
                  break;
                }
                case 8: {
                  bitField0_ |= 0x00000001;
                  playerId_ = input.readInt64();
                  break;
                }
                case 18: {
                  String s = input.readString();
                  bitField0_ |= 0x00000002;
                  playerName_ = s;
                  break;
                }
                case 24: {
                  bitField0_ |= 0x00000004;
                  playerPosition_ = input.readInt32();
                  break;
                }
                case 34: {
                  bitField0_ |= 0x00000008;
                  playerAvatar_ = input.readBytes();
                  break;
                }
                case 40: {
                  int rawValue = input.readEnum();
                  ProtoMessages.PlayerShootDirectionBase.PlayerShootDirection value = ProtoMessages.PlayerShootDirectionBase.PlayerShootDirection.forNumber(rawValue);
                  if (value == null) {
                    super.mergeVarintField(5, rawValue);
                  } else {
                    bitField0_ |= 0x00000010;
                    shootDirection_ = rawValue;
                  }
                  break;
                }
              }
            }
          } catch (com.google.protobuf.InvalidProtocolBufferException e) {
            throw new RuntimeException(e.setUnfinishedMessage(this));
          } catch (java.io.IOException e) {
            throw new RuntimeException(
                new com.google.protobuf.InvalidProtocolBufferException(
                    e.getMessage()).setUnfinishedMessage(this));
          } finally {
          }
        }
        case GET_DEFAULT_INSTANCE: {
          return DEFAULT_INSTANCE;
        }
        case GET_PARSER: {
          if (PARSER == null) {    synchronized (ProtoMessages.MessageResponseRoomPlayerInfoBase.MessageResponseRoomPlayerInfo.class) {
              if (PARSER == null) {
                PARSER = new DefaultInstanceBasedParser(DEFAULT_INSTANCE);
              }
            }
          }
          return PARSER;
        }
      }
      throw new UnsupportedOperationException();
    }


    // @@protoc_insertion_point(class_scope:MessageResponseRoomPlayerInfo)
    private static final ProtoMessages.MessageResponseRoomPlayerInfoBase.MessageResponseRoomPlayerInfo DEFAULT_INSTANCE;
    static {
      DEFAULT_INSTANCE = new MessageResponseRoomPlayerInfo();
      DEFAULT_INSTANCE.makeImmutable();
    }

    public static ProtoMessages.MessageResponseRoomPlayerInfoBase.MessageResponseRoomPlayerInfo getDefaultInstance() {
      return DEFAULT_INSTANCE;
    }

    private static volatile com.google.protobuf.Parser<MessageResponseRoomPlayerInfo> PARSER;

    public static com.google.protobuf.Parser<MessageResponseRoomPlayerInfo> parser() {
      return DEFAULT_INSTANCE.getParserForType();
    }
  }


  static {
  }

  // @@protoc_insertion_point(outer_class_scope)
}
