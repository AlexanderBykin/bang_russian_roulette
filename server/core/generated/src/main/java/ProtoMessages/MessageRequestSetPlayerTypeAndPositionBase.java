// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: MessageRequestSetPlayerTypeAndPosition.proto

package ProtoMessages;

public final class MessageRequestSetPlayerTypeAndPositionBase {
  private MessageRequestSetPlayerTypeAndPositionBase() {}
  public static void registerAllExtensions(
      com.google.protobuf.ExtensionRegistryLite registry) {
  }
  public interface MessageRequestSetPlayerTypeAndPositionOrBuilder extends
      // @@protoc_insertion_point(interface_extends:MessageRequestSetPlayerTypeAndPosition)
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
     * <code>required .MessageRequestSetPlayerTypeAndPosition.ePlayerType playerType = 2 [default = ptWATCHER];</code>
     */
    boolean hasPlayerType();
    /**
     * <code>required .MessageRequestSetPlayerTypeAndPosition.ePlayerType playerType = 2 [default = ptWATCHER];</code>
     */
    ProtoMessages.MessageRequestSetPlayerTypeAndPositionBase.MessageRequestSetPlayerTypeAndPosition.ePlayerType getPlayerType();

    /**
     * <code>required int32 position = 3 [default = 0];</code>
     */
    boolean hasPosition();
    /**
     * <code>required int32 position = 3 [default = 0];</code>
     */
    int getPosition();
  }
  /**
   * Protobuf type {@code MessageRequestSetPlayerTypeAndPosition}
   */
  public  static final class MessageRequestSetPlayerTypeAndPosition extends
      com.google.protobuf.GeneratedMessageLite<
          MessageRequestSetPlayerTypeAndPosition, MessageRequestSetPlayerTypeAndPosition.Builder> implements
      // @@protoc_insertion_point(message_implements:MessageRequestSetPlayerTypeAndPosition)
      MessageRequestSetPlayerTypeAndPositionOrBuilder {
    private MessageRequestSetPlayerTypeAndPosition() {
    }
    /**
     * Protobuf enum {@code MessageRequestSetPlayerTypeAndPosition.ePlayerType}
     */
    public enum ePlayerType
        implements com.google.protobuf.Internal.EnumLite {
      /**
       * <code>ptWATCHER = 0;</code>
       */
      ptWATCHER(0),
      /**
       * <code>ptINVESTOR = 1;</code>
       */
      ptINVESTOR(1),
      /**
       * <code>ptPLAYER = 2;</code>
       */
      ptPLAYER(2),
      ;

      /**
       * <code>ptWATCHER = 0;</code>
       */
      public static final int ptWATCHER_VALUE = 0;
      /**
       * <code>ptINVESTOR = 1;</code>
       */
      public static final int ptINVESTOR_VALUE = 1;
      /**
       * <code>ptPLAYER = 2;</code>
       */
      public static final int ptPLAYER_VALUE = 2;


      public final int getNumber() {
        return value;
      }

      /**
       * @deprecated Use {@link #forNumber(int)} instead.
       */
      @java.lang.Deprecated
      public static ePlayerType valueOf(int value) {
        return forNumber(value);
      }

      public static ePlayerType forNumber(int value) {
        switch (value) {
          case 0: return ptWATCHER;
          case 1: return ptINVESTOR;
          case 2: return ptPLAYER;
          default: return null;
        }
      }

      public static com.google.protobuf.Internal.EnumLiteMap<ePlayerType>
          internalGetValueMap() {
        return internalValueMap;
      }
      private static final com.google.protobuf.Internal.EnumLiteMap<
          ePlayerType> internalValueMap =
            new com.google.protobuf.Internal.EnumLiteMap<ePlayerType>() {
              public ePlayerType findValueByNumber(int number) {
                return ePlayerType.forNumber(number);
              }
            };

      private final int value;

      private ePlayerType(int value) {
        this.value = value;
      }

      // @@protoc_insertion_point(enum_scope:MessageRequestSetPlayerTypeAndPosition.ePlayerType)
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

    public static final int PLAYERTYPE_FIELD_NUMBER = 2;
    private int playerType_;
    /**
     * <code>required .MessageRequestSetPlayerTypeAndPosition.ePlayerType playerType = 2 [default = ptWATCHER];</code>
     */
    public boolean hasPlayerType() {
      return ((bitField0_ & 0x00000002) == 0x00000002);
    }
    /**
     * <code>required .MessageRequestSetPlayerTypeAndPosition.ePlayerType playerType = 2 [default = ptWATCHER];</code>
     */
    public ProtoMessages.MessageRequestSetPlayerTypeAndPositionBase.MessageRequestSetPlayerTypeAndPosition.ePlayerType getPlayerType() {
      ProtoMessages.MessageRequestSetPlayerTypeAndPositionBase.MessageRequestSetPlayerTypeAndPosition.ePlayerType result = ProtoMessages.MessageRequestSetPlayerTypeAndPositionBase.MessageRequestSetPlayerTypeAndPosition.ePlayerType.forNumber(playerType_);
      return result == null ? ProtoMessages.MessageRequestSetPlayerTypeAndPositionBase.MessageRequestSetPlayerTypeAndPosition.ePlayerType.ptWATCHER : result;
    }
    /**
     * <code>required .MessageRequestSetPlayerTypeAndPosition.ePlayerType playerType = 2 [default = ptWATCHER];</code>
     */
    private void setPlayerType(ProtoMessages.MessageRequestSetPlayerTypeAndPositionBase.MessageRequestSetPlayerTypeAndPosition.ePlayerType value) {
      if (value == null) {
        throw new NullPointerException();
      }
      bitField0_ |= 0x00000002;
      playerType_ = value.getNumber();
    }
    /**
     * <code>required .MessageRequestSetPlayerTypeAndPosition.ePlayerType playerType = 2 [default = ptWATCHER];</code>
     */
    private void clearPlayerType() {
      bitField0_ = (bitField0_ & ~0x00000002);
      playerType_ = 0;
    }

    public static final int POSITION_FIELD_NUMBER = 3;
    private int position_;
    /**
     * <code>required int32 position = 3 [default = 0];</code>
     */
    public boolean hasPosition() {
      return ((bitField0_ & 0x00000004) == 0x00000004);
    }
    /**
     * <code>required int32 position = 3 [default = 0];</code>
     */
    public int getPosition() {
      return position_;
    }
    /**
     * <code>required int32 position = 3 [default = 0];</code>
     */
    private void setPosition(int value) {
      bitField0_ |= 0x00000004;
      position_ = value;
    }
    /**
     * <code>required int32 position = 3 [default = 0];</code>
     */
    private void clearPosition() {
      bitField0_ = (bitField0_ & ~0x00000004);
      position_ = 0;
    }

    public void writeTo(com.google.protobuf.CodedOutputStream output)
                        throws java.io.IOException {
      if (((bitField0_ & 0x00000001) == 0x00000001)) {
        output.writeInt64(1, roomId_);
      }
      if (((bitField0_ & 0x00000002) == 0x00000002)) {
        output.writeEnum(2, playerType_);
      }
      if (((bitField0_ & 0x00000004) == 0x00000004)) {
        output.writeInt32(3, position_);
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
          .computeEnumSize(2, playerType_);
      }
      if (((bitField0_ & 0x00000004) == 0x00000004)) {
        size += com.google.protobuf.CodedOutputStream
          .computeInt32Size(3, position_);
      }
      size += unknownFields.getSerializedSize();
      memoizedSerializedSize = size;
      return size;
    }

    public static ProtoMessages.MessageRequestSetPlayerTypeAndPositionBase.MessageRequestSetPlayerTypeAndPosition parseFrom(
        com.google.protobuf.ByteString data)
        throws com.google.protobuf.InvalidProtocolBufferException {
      return com.google.protobuf.GeneratedMessageLite.parseFrom(
          DEFAULT_INSTANCE, data);
    }
    public static ProtoMessages.MessageRequestSetPlayerTypeAndPositionBase.MessageRequestSetPlayerTypeAndPosition parseFrom(
        com.google.protobuf.ByteString data,
        com.google.protobuf.ExtensionRegistryLite extensionRegistry)
        throws com.google.protobuf.InvalidProtocolBufferException {
      return com.google.protobuf.GeneratedMessageLite.parseFrom(
          DEFAULT_INSTANCE, data, extensionRegistry);
    }
    public static ProtoMessages.MessageRequestSetPlayerTypeAndPositionBase.MessageRequestSetPlayerTypeAndPosition parseFrom(byte[] data)
        throws com.google.protobuf.InvalidProtocolBufferException {
      return com.google.protobuf.GeneratedMessageLite.parseFrom(
          DEFAULT_INSTANCE, data);
    }
    public static ProtoMessages.MessageRequestSetPlayerTypeAndPositionBase.MessageRequestSetPlayerTypeAndPosition parseFrom(
        byte[] data,
        com.google.protobuf.ExtensionRegistryLite extensionRegistry)
        throws com.google.protobuf.InvalidProtocolBufferException {
      return com.google.protobuf.GeneratedMessageLite.parseFrom(
          DEFAULT_INSTANCE, data, extensionRegistry);
    }
    public static ProtoMessages.MessageRequestSetPlayerTypeAndPositionBase.MessageRequestSetPlayerTypeAndPosition parseFrom(java.io.InputStream input)
        throws java.io.IOException {
      return com.google.protobuf.GeneratedMessageLite.parseFrom(
          DEFAULT_INSTANCE, input);
    }
    public static ProtoMessages.MessageRequestSetPlayerTypeAndPositionBase.MessageRequestSetPlayerTypeAndPosition parseFrom(
        java.io.InputStream input,
        com.google.protobuf.ExtensionRegistryLite extensionRegistry)
        throws java.io.IOException {
      return com.google.protobuf.GeneratedMessageLite.parseFrom(
          DEFAULT_INSTANCE, input, extensionRegistry);
    }
    public static ProtoMessages.MessageRequestSetPlayerTypeAndPositionBase.MessageRequestSetPlayerTypeAndPosition parseDelimitedFrom(java.io.InputStream input)
        throws java.io.IOException {
      return parseDelimitedFrom(DEFAULT_INSTANCE, input);
    }
    public static ProtoMessages.MessageRequestSetPlayerTypeAndPositionBase.MessageRequestSetPlayerTypeAndPosition parseDelimitedFrom(
        java.io.InputStream input,
        com.google.protobuf.ExtensionRegistryLite extensionRegistry)
        throws java.io.IOException {
      return parseDelimitedFrom(DEFAULT_INSTANCE, input, extensionRegistry);
    }
    public static ProtoMessages.MessageRequestSetPlayerTypeAndPositionBase.MessageRequestSetPlayerTypeAndPosition parseFrom(
        com.google.protobuf.CodedInputStream input)
        throws java.io.IOException {
      return com.google.protobuf.GeneratedMessageLite.parseFrom(
          DEFAULT_INSTANCE, input);
    }
    public static ProtoMessages.MessageRequestSetPlayerTypeAndPositionBase.MessageRequestSetPlayerTypeAndPosition parseFrom(
        com.google.protobuf.CodedInputStream input,
        com.google.protobuf.ExtensionRegistryLite extensionRegistry)
        throws java.io.IOException {
      return com.google.protobuf.GeneratedMessageLite.parseFrom(
          DEFAULT_INSTANCE, input, extensionRegistry);
    }

    public static Builder newBuilder() {
      return DEFAULT_INSTANCE.toBuilder();
    }
    public static Builder newBuilder(ProtoMessages.MessageRequestSetPlayerTypeAndPositionBase.MessageRequestSetPlayerTypeAndPosition prototype) {
      return DEFAULT_INSTANCE.toBuilder().mergeFrom(prototype);
    }

    /**
     * Protobuf type {@code MessageRequestSetPlayerTypeAndPosition}
     */
    public static final class Builder extends
        com.google.protobuf.GeneratedMessageLite.Builder<
          ProtoMessages.MessageRequestSetPlayerTypeAndPositionBase.MessageRequestSetPlayerTypeAndPosition, Builder> implements
        // @@protoc_insertion_point(builder_implements:MessageRequestSetPlayerTypeAndPosition)
        ProtoMessages.MessageRequestSetPlayerTypeAndPositionBase.MessageRequestSetPlayerTypeAndPositionOrBuilder {
      // Construct using ProtoMessages.MessageRequestSetPlayerTypeAndPositionBase.MessageRequestSetPlayerTypeAndPosition.newBuilder()
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
       * <code>required .MessageRequestSetPlayerTypeAndPosition.ePlayerType playerType = 2 [default = ptWATCHER];</code>
       */
      public boolean hasPlayerType() {
        return instance.hasPlayerType();
      }
      /**
       * <code>required .MessageRequestSetPlayerTypeAndPosition.ePlayerType playerType = 2 [default = ptWATCHER];</code>
       */
      public ProtoMessages.MessageRequestSetPlayerTypeAndPositionBase.MessageRequestSetPlayerTypeAndPosition.ePlayerType getPlayerType() {
        return instance.getPlayerType();
      }
      /**
       * <code>required .MessageRequestSetPlayerTypeAndPosition.ePlayerType playerType = 2 [default = ptWATCHER];</code>
       */
      public Builder setPlayerType(ProtoMessages.MessageRequestSetPlayerTypeAndPositionBase.MessageRequestSetPlayerTypeAndPosition.ePlayerType value) {
        copyOnWrite();
        instance.setPlayerType(value);
        return this;
      }
      /**
       * <code>required .MessageRequestSetPlayerTypeAndPosition.ePlayerType playerType = 2 [default = ptWATCHER];</code>
       */
      public Builder clearPlayerType() {
        copyOnWrite();
        instance.clearPlayerType();
        return this;
      }

      /**
       * <code>required int32 position = 3 [default = 0];</code>
       */
      public boolean hasPosition() {
        return instance.hasPosition();
      }
      /**
       * <code>required int32 position = 3 [default = 0];</code>
       */
      public int getPosition() {
        return instance.getPosition();
      }
      /**
       * <code>required int32 position = 3 [default = 0];</code>
       */
      public Builder setPosition(int value) {
        copyOnWrite();
        instance.setPosition(value);
        return this;
      }
      /**
       * <code>required int32 position = 3 [default = 0];</code>
       */
      public Builder clearPosition() {
        copyOnWrite();
        instance.clearPosition();
        return this;
      }

      // @@protoc_insertion_point(builder_scope:MessageRequestSetPlayerTypeAndPosition)
    }
    private byte memoizedIsInitialized = -1;
    protected final Object dynamicMethod(
        com.google.protobuf.GeneratedMessageLite.MethodToInvoke method,
        Object arg0, Object arg1) {
      switch (method) {
        case NEW_MUTABLE_INSTANCE: {
          return new ProtoMessages.MessageRequestSetPlayerTypeAndPositionBase.MessageRequestSetPlayerTypeAndPosition();
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
          if (!hasPlayerType()) {
            if (shouldMemoize) {
              memoizedIsInitialized = 0;
            }
            return null;
          }
          if (!hasPosition()) {
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
          ProtoMessages.MessageRequestSetPlayerTypeAndPositionBase.MessageRequestSetPlayerTypeAndPosition other = (ProtoMessages.MessageRequestSetPlayerTypeAndPositionBase.MessageRequestSetPlayerTypeAndPosition) arg1;
          roomId_ = visitor.visitLong(
              hasRoomId(), roomId_,
              other.hasRoomId(), other.roomId_);
          playerType_ = visitor.visitInt(hasPlayerType(), playerType_,
              other.hasPlayerType(), other.playerType_);
          position_ = visitor.visitInt(
              hasPosition(), position_,
              other.hasPosition(), other.position_);
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
                  int rawValue = input.readEnum();
                  ProtoMessages.MessageRequestSetPlayerTypeAndPositionBase.MessageRequestSetPlayerTypeAndPosition.ePlayerType value = ProtoMessages.MessageRequestSetPlayerTypeAndPositionBase.MessageRequestSetPlayerTypeAndPosition.ePlayerType.forNumber(rawValue);
                  if (value == null) {
                    super.mergeVarintField(2, rawValue);
                  } else {
                    bitField0_ |= 0x00000002;
                    playerType_ = rawValue;
                  }
                  break;
                }
                case 24: {
                  bitField0_ |= 0x00000004;
                  position_ = input.readInt32();
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
          if (PARSER == null) {    synchronized (ProtoMessages.MessageRequestSetPlayerTypeAndPositionBase.MessageRequestSetPlayerTypeAndPosition.class) {
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


    // @@protoc_insertion_point(class_scope:MessageRequestSetPlayerTypeAndPosition)
    private static final ProtoMessages.MessageRequestSetPlayerTypeAndPositionBase.MessageRequestSetPlayerTypeAndPosition DEFAULT_INSTANCE;
    static {
      DEFAULT_INSTANCE = new MessageRequestSetPlayerTypeAndPosition();
      DEFAULT_INSTANCE.makeImmutable();
    }

    public static ProtoMessages.MessageRequestSetPlayerTypeAndPositionBase.MessageRequestSetPlayerTypeAndPosition getDefaultInstance() {
      return DEFAULT_INSTANCE;
    }

    private static volatile com.google.protobuf.Parser<MessageRequestSetPlayerTypeAndPosition> PARSER;

    public static com.google.protobuf.Parser<MessageRequestSetPlayerTypeAndPosition> parser() {
      return DEFAULT_INSTANCE.getParserForType();
    }
  }


  static {
  }

  // @@protoc_insertion_point(outer_class_scope)
}
