// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: MessageRequestPlayerBet.proto

package ProtoMessages;

public final class MessageRequestPlayerBetBase {
  private MessageRequestPlayerBetBase() {}
  public static void registerAllExtensions(
      com.google.protobuf.ExtensionRegistryLite registry) {
  }
  public interface MessageRequestPlayerBetOrBuilder extends
      // @@protoc_insertion_point(interface_extends:MessageRequestPlayerBet)
      com.google.protobuf.MessageLiteOrBuilder {

    /**
     * <code>required int64 roomId = 1 [default = 0];</code>
     */
    boolean hasRoomId();
    /**
     * <code>required int64 roomId = 1 [default = 0];</code>
     */
    long getRoomId();

    /**
     * <code>required int64 destPlayerId = 2 [default = 0];</code>
     */
    boolean hasDestPlayerId();
    /**
     * <code>required int64 destPlayerId = 2 [default = 0];</code>
     */
    long getDestPlayerId();

    /**
     * <code>required int64 amount = 3 [default = 0];</code>
     */
    boolean hasAmount();
    /**
     * <code>required int64 amount = 3 [default = 0];</code>
     */
    long getAmount();

    /**
     * <code>required .PlayerBetWinType winType = 4 [default = pbwtWin];</code>
     */
    boolean hasWinType();
    /**
     * <code>required .PlayerBetWinType winType = 4 [default = pbwtWin];</code>
     */
    ProtoMessages.PlayerBetWinTypeBase.PlayerBetWinType getWinType();
  }
  /**
   * Protobuf type {@code MessageRequestPlayerBet}
   */
  public  static final class MessageRequestPlayerBet extends
      com.google.protobuf.GeneratedMessageLite<
          MessageRequestPlayerBet, MessageRequestPlayerBet.Builder> implements
      // @@protoc_insertion_point(message_implements:MessageRequestPlayerBet)
      MessageRequestPlayerBetOrBuilder {
    private MessageRequestPlayerBet() {
    }
    private int bitField0_;
    public static final int ROOMID_FIELD_NUMBER = 1;
    private long roomId_;
    /**
     * <code>required int64 roomId = 1 [default = 0];</code>
     */
    public boolean hasRoomId() {
      return ((bitField0_ & 0x00000001) == 0x00000001);
    }
    /**
     * <code>required int64 roomId = 1 [default = 0];</code>
     */
    public long getRoomId() {
      return roomId_;
    }
    /**
     * <code>required int64 roomId = 1 [default = 0];</code>
     */
    private void setRoomId(long value) {
      bitField0_ |= 0x00000001;
      roomId_ = value;
    }
    /**
     * <code>required int64 roomId = 1 [default = 0];</code>
     */
    private void clearRoomId() {
      bitField0_ = (bitField0_ & ~0x00000001);
      roomId_ = 0L;
    }

    public static final int DESTPLAYERID_FIELD_NUMBER = 2;
    private long destPlayerId_;
    /**
     * <code>required int64 destPlayerId = 2 [default = 0];</code>
     */
    public boolean hasDestPlayerId() {
      return ((bitField0_ & 0x00000002) == 0x00000002);
    }
    /**
     * <code>required int64 destPlayerId = 2 [default = 0];</code>
     */
    public long getDestPlayerId() {
      return destPlayerId_;
    }
    /**
     * <code>required int64 destPlayerId = 2 [default = 0];</code>
     */
    private void setDestPlayerId(long value) {
      bitField0_ |= 0x00000002;
      destPlayerId_ = value;
    }
    /**
     * <code>required int64 destPlayerId = 2 [default = 0];</code>
     */
    private void clearDestPlayerId() {
      bitField0_ = (bitField0_ & ~0x00000002);
      destPlayerId_ = 0L;
    }

    public static final int AMOUNT_FIELD_NUMBER = 3;
    private long amount_;
    /**
     * <code>required int64 amount = 3 [default = 0];</code>
     */
    public boolean hasAmount() {
      return ((bitField0_ & 0x00000004) == 0x00000004);
    }
    /**
     * <code>required int64 amount = 3 [default = 0];</code>
     */
    public long getAmount() {
      return amount_;
    }
    /**
     * <code>required int64 amount = 3 [default = 0];</code>
     */
    private void setAmount(long value) {
      bitField0_ |= 0x00000004;
      amount_ = value;
    }
    /**
     * <code>required int64 amount = 3 [default = 0];</code>
     */
    private void clearAmount() {
      bitField0_ = (bitField0_ & ~0x00000004);
      amount_ = 0L;
    }

    public static final int WINTYPE_FIELD_NUMBER = 4;
    private int winType_;
    /**
     * <code>required .PlayerBetWinType winType = 4 [default = pbwtWin];</code>
     */
    public boolean hasWinType() {
      return ((bitField0_ & 0x00000008) == 0x00000008);
    }
    /**
     * <code>required .PlayerBetWinType winType = 4 [default = pbwtWin];</code>
     */
    public ProtoMessages.PlayerBetWinTypeBase.PlayerBetWinType getWinType() {
      ProtoMessages.PlayerBetWinTypeBase.PlayerBetWinType result = ProtoMessages.PlayerBetWinTypeBase.PlayerBetWinType.forNumber(winType_);
      return result == null ? ProtoMessages.PlayerBetWinTypeBase.PlayerBetWinType.pbwtWin : result;
    }
    /**
     * <code>required .PlayerBetWinType winType = 4 [default = pbwtWin];</code>
     */
    private void setWinType(ProtoMessages.PlayerBetWinTypeBase.PlayerBetWinType value) {
      if (value == null) {
        throw new NullPointerException();
      }
      bitField0_ |= 0x00000008;
      winType_ = value.getNumber();
    }
    /**
     * <code>required .PlayerBetWinType winType = 4 [default = pbwtWin];</code>
     */
    private void clearWinType() {
      bitField0_ = (bitField0_ & ~0x00000008);
      winType_ = 0;
    }

    public void writeTo(com.google.protobuf.CodedOutputStream output)
                        throws java.io.IOException {
      if (((bitField0_ & 0x00000001) == 0x00000001)) {
        output.writeInt64(1, roomId_);
      }
      if (((bitField0_ & 0x00000002) == 0x00000002)) {
        output.writeInt64(2, destPlayerId_);
      }
      if (((bitField0_ & 0x00000004) == 0x00000004)) {
        output.writeInt64(3, amount_);
      }
      if (((bitField0_ & 0x00000008) == 0x00000008)) {
        output.writeEnum(4, winType_);
      }
      unknownFields.writeTo(output);
    }

    public int getSerializedSize() {
      int size = memoizedSerializedSize;
      if (size != -1) return size;

      size = 0;
      if (((bitField0_ & 0x00000001) == 0x00000001)) {
        size += com.google.protobuf.CodedOutputStream
          .computeInt64Size(1, roomId_);
      }
      if (((bitField0_ & 0x00000002) == 0x00000002)) {
        size += com.google.protobuf.CodedOutputStream
          .computeInt64Size(2, destPlayerId_);
      }
      if (((bitField0_ & 0x00000004) == 0x00000004)) {
        size += com.google.protobuf.CodedOutputStream
          .computeInt64Size(3, amount_);
      }
      if (((bitField0_ & 0x00000008) == 0x00000008)) {
        size += com.google.protobuf.CodedOutputStream
          .computeEnumSize(4, winType_);
      }
      size += unknownFields.getSerializedSize();
      memoizedSerializedSize = size;
      return size;
    }

    public static ProtoMessages.MessageRequestPlayerBetBase.MessageRequestPlayerBet parseFrom(
        com.google.protobuf.ByteString data)
        throws com.google.protobuf.InvalidProtocolBufferException {
      return com.google.protobuf.GeneratedMessageLite.parseFrom(
          DEFAULT_INSTANCE, data);
    }
    public static ProtoMessages.MessageRequestPlayerBetBase.MessageRequestPlayerBet parseFrom(
        com.google.protobuf.ByteString data,
        com.google.protobuf.ExtensionRegistryLite extensionRegistry)
        throws com.google.protobuf.InvalidProtocolBufferException {
      return com.google.protobuf.GeneratedMessageLite.parseFrom(
          DEFAULT_INSTANCE, data, extensionRegistry);
    }
    public static ProtoMessages.MessageRequestPlayerBetBase.MessageRequestPlayerBet parseFrom(byte[] data)
        throws com.google.protobuf.InvalidProtocolBufferException {
      return com.google.protobuf.GeneratedMessageLite.parseFrom(
          DEFAULT_INSTANCE, data);
    }
    public static ProtoMessages.MessageRequestPlayerBetBase.MessageRequestPlayerBet parseFrom(
        byte[] data,
        com.google.protobuf.ExtensionRegistryLite extensionRegistry)
        throws com.google.protobuf.InvalidProtocolBufferException {
      return com.google.protobuf.GeneratedMessageLite.parseFrom(
          DEFAULT_INSTANCE, data, extensionRegistry);
    }
    public static ProtoMessages.MessageRequestPlayerBetBase.MessageRequestPlayerBet parseFrom(java.io.InputStream input)
        throws java.io.IOException {
      return com.google.protobuf.GeneratedMessageLite.parseFrom(
          DEFAULT_INSTANCE, input);
    }
    public static ProtoMessages.MessageRequestPlayerBetBase.MessageRequestPlayerBet parseFrom(
        java.io.InputStream input,
        com.google.protobuf.ExtensionRegistryLite extensionRegistry)
        throws java.io.IOException {
      return com.google.protobuf.GeneratedMessageLite.parseFrom(
          DEFAULT_INSTANCE, input, extensionRegistry);
    }
    public static ProtoMessages.MessageRequestPlayerBetBase.MessageRequestPlayerBet parseDelimitedFrom(java.io.InputStream input)
        throws java.io.IOException {
      return parseDelimitedFrom(DEFAULT_INSTANCE, input);
    }
    public static ProtoMessages.MessageRequestPlayerBetBase.MessageRequestPlayerBet parseDelimitedFrom(
        java.io.InputStream input,
        com.google.protobuf.ExtensionRegistryLite extensionRegistry)
        throws java.io.IOException {
      return parseDelimitedFrom(DEFAULT_INSTANCE, input, extensionRegistry);
    }
    public static ProtoMessages.MessageRequestPlayerBetBase.MessageRequestPlayerBet parseFrom(
        com.google.protobuf.CodedInputStream input)
        throws java.io.IOException {
      return com.google.protobuf.GeneratedMessageLite.parseFrom(
          DEFAULT_INSTANCE, input);
    }
    public static ProtoMessages.MessageRequestPlayerBetBase.MessageRequestPlayerBet parseFrom(
        com.google.protobuf.CodedInputStream input,
        com.google.protobuf.ExtensionRegistryLite extensionRegistry)
        throws java.io.IOException {
      return com.google.protobuf.GeneratedMessageLite.parseFrom(
          DEFAULT_INSTANCE, input, extensionRegistry);
    }

    public static Builder newBuilder() {
      return DEFAULT_INSTANCE.toBuilder();
    }
    public static Builder newBuilder(ProtoMessages.MessageRequestPlayerBetBase.MessageRequestPlayerBet prototype) {
      return DEFAULT_INSTANCE.toBuilder().mergeFrom(prototype);
    }

    /**
     * Protobuf type {@code MessageRequestPlayerBet}
     */
    public static final class Builder extends
        com.google.protobuf.GeneratedMessageLite.Builder<
          ProtoMessages.MessageRequestPlayerBetBase.MessageRequestPlayerBet, Builder> implements
        // @@protoc_insertion_point(builder_implements:MessageRequestPlayerBet)
        ProtoMessages.MessageRequestPlayerBetBase.MessageRequestPlayerBetOrBuilder {
      // Construct using ProtoMessages.MessageRequestPlayerBetBase.MessageRequestPlayerBet.newBuilder()
      private Builder() {
        super(DEFAULT_INSTANCE);
      }


      /**
       * <code>required int64 roomId = 1 [default = 0];</code>
       */
      public boolean hasRoomId() {
        return instance.hasRoomId();
      }
      /**
       * <code>required int64 roomId = 1 [default = 0];</code>
       */
      public long getRoomId() {
        return instance.getRoomId();
      }
      /**
       * <code>required int64 roomId = 1 [default = 0];</code>
       */
      public Builder setRoomId(long value) {
        copyOnWrite();
        instance.setRoomId(value);
        return this;
      }
      /**
       * <code>required int64 roomId = 1 [default = 0];</code>
       */
      public Builder clearRoomId() {
        copyOnWrite();
        instance.clearRoomId();
        return this;
      }

      /**
       * <code>required int64 destPlayerId = 2 [default = 0];</code>
       */
      public boolean hasDestPlayerId() {
        return instance.hasDestPlayerId();
      }
      /**
       * <code>required int64 destPlayerId = 2 [default = 0];</code>
       */
      public long getDestPlayerId() {
        return instance.getDestPlayerId();
      }
      /**
       * <code>required int64 destPlayerId = 2 [default = 0];</code>
       */
      public Builder setDestPlayerId(long value) {
        copyOnWrite();
        instance.setDestPlayerId(value);
        return this;
      }
      /**
       * <code>required int64 destPlayerId = 2 [default = 0];</code>
       */
      public Builder clearDestPlayerId() {
        copyOnWrite();
        instance.clearDestPlayerId();
        return this;
      }

      /**
       * <code>required int64 amount = 3 [default = 0];</code>
       */
      public boolean hasAmount() {
        return instance.hasAmount();
      }
      /**
       * <code>required int64 amount = 3 [default = 0];</code>
       */
      public long getAmount() {
        return instance.getAmount();
      }
      /**
       * <code>required int64 amount = 3 [default = 0];</code>
       */
      public Builder setAmount(long value) {
        copyOnWrite();
        instance.setAmount(value);
        return this;
      }
      /**
       * <code>required int64 amount = 3 [default = 0];</code>
       */
      public Builder clearAmount() {
        copyOnWrite();
        instance.clearAmount();
        return this;
      }

      /**
       * <code>required .PlayerBetWinType winType = 4 [default = pbwtWin];</code>
       */
      public boolean hasWinType() {
        return instance.hasWinType();
      }
      /**
       * <code>required .PlayerBetWinType winType = 4 [default = pbwtWin];</code>
       */
      public ProtoMessages.PlayerBetWinTypeBase.PlayerBetWinType getWinType() {
        return instance.getWinType();
      }
      /**
       * <code>required .PlayerBetWinType winType = 4 [default = pbwtWin];</code>
       */
      public Builder setWinType(ProtoMessages.PlayerBetWinTypeBase.PlayerBetWinType value) {
        copyOnWrite();
        instance.setWinType(value);
        return this;
      }
      /**
       * <code>required .PlayerBetWinType winType = 4 [default = pbwtWin];</code>
       */
      public Builder clearWinType() {
        copyOnWrite();
        instance.clearWinType();
        return this;
      }

      // @@protoc_insertion_point(builder_scope:MessageRequestPlayerBet)
    }
    private byte memoizedIsInitialized = -1;
    protected final Object dynamicMethod(
        com.google.protobuf.GeneratedMessageLite.MethodToInvoke method,
        Object arg0, Object arg1) {
      switch (method) {
        case NEW_MUTABLE_INSTANCE: {
          return new ProtoMessages.MessageRequestPlayerBetBase.MessageRequestPlayerBet();
        }
        case IS_INITIALIZED: {
          byte isInitialized = memoizedIsInitialized;
          if (isInitialized == 1) return DEFAULT_INSTANCE;
          if (isInitialized == 0) return null;

          boolean shouldMemoize = ((Boolean) arg0).booleanValue();
          if (!hasRoomId()) {
            if (shouldMemoize) {
              memoizedIsInitialized = 0;
            }
            return null;
          }
          if (!hasDestPlayerId()) {
            if (shouldMemoize) {
              memoizedIsInitialized = 0;
            }
            return null;
          }
          if (!hasAmount()) {
            if (shouldMemoize) {
              memoizedIsInitialized = 0;
            }
            return null;
          }
          if (!hasWinType()) {
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
          ProtoMessages.MessageRequestPlayerBetBase.MessageRequestPlayerBet other = (ProtoMessages.MessageRequestPlayerBetBase.MessageRequestPlayerBet) arg1;
          roomId_ = visitor.visitLong(
              hasRoomId(), roomId_,
              other.hasRoomId(), other.roomId_);
          destPlayerId_ = visitor.visitLong(
              hasDestPlayerId(), destPlayerId_,
              other.hasDestPlayerId(), other.destPlayerId_);
          amount_ = visitor.visitLong(
              hasAmount(), amount_,
              other.hasAmount(), other.amount_);
          winType_ = visitor.visitInt(hasWinType(), winType_,
              other.hasWinType(), other.winType_);
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
                  roomId_ = input.readInt64();
                  break;
                }
                case 16: {
                  bitField0_ |= 0x00000002;
                  destPlayerId_ = input.readInt64();
                  break;
                }
                case 24: {
                  bitField0_ |= 0x00000004;
                  amount_ = input.readInt64();
                  break;
                }
                case 32: {
                  int rawValue = input.readEnum();
                  ProtoMessages.PlayerBetWinTypeBase.PlayerBetWinType value = ProtoMessages.PlayerBetWinTypeBase.PlayerBetWinType.forNumber(rawValue);
                  if (value == null) {
                    super.mergeVarintField(4, rawValue);
                  } else {
                    bitField0_ |= 0x00000008;
                    winType_ = rawValue;
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
          if (PARSER == null) {    synchronized (ProtoMessages.MessageRequestPlayerBetBase.MessageRequestPlayerBet.class) {
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


    // @@protoc_insertion_point(class_scope:MessageRequestPlayerBet)
    private static final ProtoMessages.MessageRequestPlayerBetBase.MessageRequestPlayerBet DEFAULT_INSTANCE;
    static {
      DEFAULT_INSTANCE = new MessageRequestPlayerBet();
      DEFAULT_INSTANCE.makeImmutable();
    }

    public static ProtoMessages.MessageRequestPlayerBetBase.MessageRequestPlayerBet getDefaultInstance() {
      return DEFAULT_INSTANCE;
    }

    private static volatile com.google.protobuf.Parser<MessageRequestPlayerBet> PARSER;

    public static com.google.protobuf.Parser<MessageRequestPlayerBet> parser() {
      return DEFAULT_INSTANCE.getParserForType();
    }
  }


  static {
  }

  // @@protoc_insertion_point(outer_class_scope)
}
