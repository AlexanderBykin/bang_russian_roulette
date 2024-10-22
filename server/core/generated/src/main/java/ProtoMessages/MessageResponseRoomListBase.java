// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: MessageResponseRoomList.proto

package ProtoMessages;

public final class MessageResponseRoomListBase {
  private MessageResponseRoomListBase() {}
  public static void registerAllExtensions(
      com.google.protobuf.ExtensionRegistryLite registry) {
  }
  public interface MessageResponseRoomListOrBuilder extends
      // @@protoc_insertion_point(interface_extends:MessageResponseRoomList)
      com.google.protobuf.MessageLiteOrBuilder {

    /**
     * <code>repeated .MessageResponseRoomInfo roomList = 1;</code>
     */
    java.util.List<ProtoMessages.MessageResponseRoomInfoBase.MessageResponseRoomInfo> 
        getRoomListList();
    /**
     * <code>repeated .MessageResponseRoomInfo roomList = 1;</code>
     */
    ProtoMessages.MessageResponseRoomInfoBase.MessageResponseRoomInfo getRoomList(int index);
    /**
     * <code>repeated .MessageResponseRoomInfo roomList = 1;</code>
     */
    int getRoomListCount();
  }
  /**
   * Protobuf type {@code MessageResponseRoomList}
   */
  public  static final class MessageResponseRoomList extends
      com.google.protobuf.GeneratedMessageLite<
          MessageResponseRoomList, MessageResponseRoomList.Builder> implements
      // @@protoc_insertion_point(message_implements:MessageResponseRoomList)
      MessageResponseRoomListOrBuilder {
    private MessageResponseRoomList() {
      roomList_ = emptyProtobufList();
    }
    public static final int ROOMLIST_FIELD_NUMBER = 1;
    private com.google.protobuf.Internal.ProtobufList<ProtoMessages.MessageResponseRoomInfoBase.MessageResponseRoomInfo> roomList_;
    /**
     * <code>repeated .MessageResponseRoomInfo roomList = 1;</code>
     */
    public java.util.List<ProtoMessages.MessageResponseRoomInfoBase.MessageResponseRoomInfo> getRoomListList() {
      return roomList_;
    }
    /**
     * <code>repeated .MessageResponseRoomInfo roomList = 1;</code>
     */
    public java.util.List<? extends ProtoMessages.MessageResponseRoomInfoBase.MessageResponseRoomInfoOrBuilder> 
        getRoomListOrBuilderList() {
      return roomList_;
    }
    /**
     * <code>repeated .MessageResponseRoomInfo roomList = 1;</code>
     */
    public int getRoomListCount() {
      return roomList_.size();
    }
    /**
     * <code>repeated .MessageResponseRoomInfo roomList = 1;</code>
     */
    public ProtoMessages.MessageResponseRoomInfoBase.MessageResponseRoomInfo getRoomList(int index) {
      return roomList_.get(index);
    }
    /**
     * <code>repeated .MessageResponseRoomInfo roomList = 1;</code>
     */
    public ProtoMessages.MessageResponseRoomInfoBase.MessageResponseRoomInfoOrBuilder getRoomListOrBuilder(
        int index) {
      return roomList_.get(index);
    }
    private void ensureRoomListIsMutable() {
      if (!roomList_.isModifiable()) {
        roomList_ =
            com.google.protobuf.GeneratedMessageLite.mutableCopy(roomList_);
       }
    }

    /**
     * <code>repeated .MessageResponseRoomInfo roomList = 1;</code>
     */
    private void setRoomList(
        int index, ProtoMessages.MessageResponseRoomInfoBase.MessageResponseRoomInfo value) {
      if (value == null) {
        throw new NullPointerException();
      }
      ensureRoomListIsMutable();
      roomList_.set(index, value);
    }
    /**
     * <code>repeated .MessageResponseRoomInfo roomList = 1;</code>
     */
    private void setRoomList(
        int index, ProtoMessages.MessageResponseRoomInfoBase.MessageResponseRoomInfo.Builder builderForValue) {
      ensureRoomListIsMutable();
      roomList_.set(index, builderForValue.build());
    }
    /**
     * <code>repeated .MessageResponseRoomInfo roomList = 1;</code>
     */
    private void addRoomList(ProtoMessages.MessageResponseRoomInfoBase.MessageResponseRoomInfo value) {
      if (value == null) {
        throw new NullPointerException();
      }
      ensureRoomListIsMutable();
      roomList_.add(value);
    }
    /**
     * <code>repeated .MessageResponseRoomInfo roomList = 1;</code>
     */
    private void addRoomList(
        int index, ProtoMessages.MessageResponseRoomInfoBase.MessageResponseRoomInfo value) {
      if (value == null) {
        throw new NullPointerException();
      }
      ensureRoomListIsMutable();
      roomList_.add(index, value);
    }
    /**
     * <code>repeated .MessageResponseRoomInfo roomList = 1;</code>
     */
    private void addRoomList(
        ProtoMessages.MessageResponseRoomInfoBase.MessageResponseRoomInfo.Builder builderForValue) {
      ensureRoomListIsMutable();
      roomList_.add(builderForValue.build());
    }
    /**
     * <code>repeated .MessageResponseRoomInfo roomList = 1;</code>
     */
    private void addRoomList(
        int index, ProtoMessages.MessageResponseRoomInfoBase.MessageResponseRoomInfo.Builder builderForValue) {
      ensureRoomListIsMutable();
      roomList_.add(index, builderForValue.build());
    }
    /**
     * <code>repeated .MessageResponseRoomInfo roomList = 1;</code>
     */
    private void addAllRoomList(
        java.lang.Iterable<? extends ProtoMessages.MessageResponseRoomInfoBase.MessageResponseRoomInfo> values) {
      ensureRoomListIsMutable();
      com.google.protobuf.AbstractMessageLite.addAll(
          values, roomList_);
    }
    /**
     * <code>repeated .MessageResponseRoomInfo roomList = 1;</code>
     */
    private void clearRoomList() {
      roomList_ = emptyProtobufList();
    }
    /**
     * <code>repeated .MessageResponseRoomInfo roomList = 1;</code>
     */
    private void removeRoomList(int index) {
      ensureRoomListIsMutable();
      roomList_.remove(index);
    }

    public void writeTo(com.google.protobuf.CodedOutputStream output)
                        throws java.io.IOException {
      for (int i = 0; i < roomList_.size(); i++) {
        output.writeMessage(1, roomList_.get(i));
      }
      unknownFields.writeTo(output);
    }

    public int getSerializedSize() {
      int size = memoizedSerializedSize;
      if (size != -1) return size;

      size = 0;
      for (int i = 0; i < roomList_.size(); i++) {
        size += com.google.protobuf.CodedOutputStream
          .computeMessageSize(1, roomList_.get(i));
      }
      size += unknownFields.getSerializedSize();
      memoizedSerializedSize = size;
      return size;
    }

    public static ProtoMessages.MessageResponseRoomListBase.MessageResponseRoomList parseFrom(
        com.google.protobuf.ByteString data)
        throws com.google.protobuf.InvalidProtocolBufferException {
      return com.google.protobuf.GeneratedMessageLite.parseFrom(
          DEFAULT_INSTANCE, data);
    }
    public static ProtoMessages.MessageResponseRoomListBase.MessageResponseRoomList parseFrom(
        com.google.protobuf.ByteString data,
        com.google.protobuf.ExtensionRegistryLite extensionRegistry)
        throws com.google.protobuf.InvalidProtocolBufferException {
      return com.google.protobuf.GeneratedMessageLite.parseFrom(
          DEFAULT_INSTANCE, data, extensionRegistry);
    }
    public static ProtoMessages.MessageResponseRoomListBase.MessageResponseRoomList parseFrom(byte[] data)
        throws com.google.protobuf.InvalidProtocolBufferException {
      return com.google.protobuf.GeneratedMessageLite.parseFrom(
          DEFAULT_INSTANCE, data);
    }
    public static ProtoMessages.MessageResponseRoomListBase.MessageResponseRoomList parseFrom(
        byte[] data,
        com.google.protobuf.ExtensionRegistryLite extensionRegistry)
        throws com.google.protobuf.InvalidProtocolBufferException {
      return com.google.protobuf.GeneratedMessageLite.parseFrom(
          DEFAULT_INSTANCE, data, extensionRegistry);
    }
    public static ProtoMessages.MessageResponseRoomListBase.MessageResponseRoomList parseFrom(java.io.InputStream input)
        throws java.io.IOException {
      return com.google.protobuf.GeneratedMessageLite.parseFrom(
          DEFAULT_INSTANCE, input);
    }
    public static ProtoMessages.MessageResponseRoomListBase.MessageResponseRoomList parseFrom(
        java.io.InputStream input,
        com.google.protobuf.ExtensionRegistryLite extensionRegistry)
        throws java.io.IOException {
      return com.google.protobuf.GeneratedMessageLite.parseFrom(
          DEFAULT_INSTANCE, input, extensionRegistry);
    }
    public static ProtoMessages.MessageResponseRoomListBase.MessageResponseRoomList parseDelimitedFrom(java.io.InputStream input)
        throws java.io.IOException {
      return parseDelimitedFrom(DEFAULT_INSTANCE, input);
    }
    public static ProtoMessages.MessageResponseRoomListBase.MessageResponseRoomList parseDelimitedFrom(
        java.io.InputStream input,
        com.google.protobuf.ExtensionRegistryLite extensionRegistry)
        throws java.io.IOException {
      return parseDelimitedFrom(DEFAULT_INSTANCE, input, extensionRegistry);
    }
    public static ProtoMessages.MessageResponseRoomListBase.MessageResponseRoomList parseFrom(
        com.google.protobuf.CodedInputStream input)
        throws java.io.IOException {
      return com.google.protobuf.GeneratedMessageLite.parseFrom(
          DEFAULT_INSTANCE, input);
    }
    public static ProtoMessages.MessageResponseRoomListBase.MessageResponseRoomList parseFrom(
        com.google.protobuf.CodedInputStream input,
        com.google.protobuf.ExtensionRegistryLite extensionRegistry)
        throws java.io.IOException {
      return com.google.protobuf.GeneratedMessageLite.parseFrom(
          DEFAULT_INSTANCE, input, extensionRegistry);
    }

    public static Builder newBuilder() {
      return DEFAULT_INSTANCE.toBuilder();
    }
    public static Builder newBuilder(ProtoMessages.MessageResponseRoomListBase.MessageResponseRoomList prototype) {
      return DEFAULT_INSTANCE.toBuilder().mergeFrom(prototype);
    }

    /**
     * Protobuf type {@code MessageResponseRoomList}
     */
    public static final class Builder extends
        com.google.protobuf.GeneratedMessageLite.Builder<
          ProtoMessages.MessageResponseRoomListBase.MessageResponseRoomList, Builder> implements
        // @@protoc_insertion_point(builder_implements:MessageResponseRoomList)
        ProtoMessages.MessageResponseRoomListBase.MessageResponseRoomListOrBuilder {
      // Construct using ProtoMessages.MessageResponseRoomListBase.MessageResponseRoomList.newBuilder()
      private Builder() {
        super(DEFAULT_INSTANCE);
      }


      /**
       * <code>repeated .MessageResponseRoomInfo roomList = 1;</code>
       */
      public java.util.List<ProtoMessages.MessageResponseRoomInfoBase.MessageResponseRoomInfo> getRoomListList() {
        return java.util.Collections.unmodifiableList(
            instance.getRoomListList());
      }
      /**
       * <code>repeated .MessageResponseRoomInfo roomList = 1;</code>
       */
      public int getRoomListCount() {
        return instance.getRoomListCount();
      }/**
       * <code>repeated .MessageResponseRoomInfo roomList = 1;</code>
       */
      public ProtoMessages.MessageResponseRoomInfoBase.MessageResponseRoomInfo getRoomList(int index) {
        return instance.getRoomList(index);
      }
      /**
       * <code>repeated .MessageResponseRoomInfo roomList = 1;</code>
       */
      public Builder setRoomList(
          int index, ProtoMessages.MessageResponseRoomInfoBase.MessageResponseRoomInfo value) {
        copyOnWrite();
        instance.setRoomList(index, value);
        return this;
      }
      /**
       * <code>repeated .MessageResponseRoomInfo roomList = 1;</code>
       */
      public Builder setRoomList(
          int index, ProtoMessages.MessageResponseRoomInfoBase.MessageResponseRoomInfo.Builder builderForValue) {
        copyOnWrite();
        instance.setRoomList(index, builderForValue);
        return this;
      }
      /**
       * <code>repeated .MessageResponseRoomInfo roomList = 1;</code>
       */
      public Builder addRoomList(ProtoMessages.MessageResponseRoomInfoBase.MessageResponseRoomInfo value) {
        copyOnWrite();
        instance.addRoomList(value);
        return this;
      }
      /**
       * <code>repeated .MessageResponseRoomInfo roomList = 1;</code>
       */
      public Builder addRoomList(
          int index, ProtoMessages.MessageResponseRoomInfoBase.MessageResponseRoomInfo value) {
        copyOnWrite();
        instance.addRoomList(index, value);
        return this;
      }
      /**
       * <code>repeated .MessageResponseRoomInfo roomList = 1;</code>
       */
      public Builder addRoomList(
          ProtoMessages.MessageResponseRoomInfoBase.MessageResponseRoomInfo.Builder builderForValue) {
        copyOnWrite();
        instance.addRoomList(builderForValue);
        return this;
      }
      /**
       * <code>repeated .MessageResponseRoomInfo roomList = 1;</code>
       */
      public Builder addRoomList(
          int index, ProtoMessages.MessageResponseRoomInfoBase.MessageResponseRoomInfo.Builder builderForValue) {
        copyOnWrite();
        instance.addRoomList(index, builderForValue);
        return this;
      }
      /**
       * <code>repeated .MessageResponseRoomInfo roomList = 1;</code>
       */
      public Builder addAllRoomList(
          java.lang.Iterable<? extends ProtoMessages.MessageResponseRoomInfoBase.MessageResponseRoomInfo> values) {
        copyOnWrite();
        instance.addAllRoomList(values);
        return this;
      }
      /**
       * <code>repeated .MessageResponseRoomInfo roomList = 1;</code>
       */
      public Builder clearRoomList() {
        copyOnWrite();
        instance.clearRoomList();
        return this;
      }
      /**
       * <code>repeated .MessageResponseRoomInfo roomList = 1;</code>
       */
      public Builder removeRoomList(int index) {
        copyOnWrite();
        instance.removeRoomList(index);
        return this;
      }

      // @@protoc_insertion_point(builder_scope:MessageResponseRoomList)
    }
    private byte memoizedIsInitialized = -1;
    protected final Object dynamicMethod(
        com.google.protobuf.GeneratedMessageLite.MethodToInvoke method,
        Object arg0, Object arg1) {
      switch (method) {
        case NEW_MUTABLE_INSTANCE: {
          return new ProtoMessages.MessageResponseRoomListBase.MessageResponseRoomList();
        }
        case IS_INITIALIZED: {
          byte isInitialized = memoizedIsInitialized;
          if (isInitialized == 1) return DEFAULT_INSTANCE;
          if (isInitialized == 0) return null;

          boolean shouldMemoize = ((Boolean) arg0).booleanValue();
          for (int i = 0; i < getRoomListCount(); i++) {
            if (!getRoomList(i).isInitialized()) {
              if (shouldMemoize) {
                memoizedIsInitialized = 0;
              }
              return null;
            }
          }
          if (shouldMemoize) memoizedIsInitialized = 1;
          return DEFAULT_INSTANCE;

        }
        case MAKE_IMMUTABLE: {
          roomList_.makeImmutable();
          return null;
        }
        case NEW_BUILDER: {
          return new Builder();
        }
        case VISIT: {
          Visitor visitor = (Visitor) arg0;
          ProtoMessages.MessageResponseRoomListBase.MessageResponseRoomList other = (ProtoMessages.MessageResponseRoomListBase.MessageResponseRoomList) arg1;
          roomList_= visitor.visitList(roomList_, other.roomList_);
          if (visitor == com.google.protobuf.GeneratedMessageLite.MergeFromVisitor
              .INSTANCE) {
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
                case 10: {
                  if (!roomList_.isModifiable()) {
                    roomList_ =
                        com.google.protobuf.GeneratedMessageLite.mutableCopy(roomList_);
                  }
                  roomList_.add(
                      input.readMessage(ProtoMessages.MessageResponseRoomInfoBase.MessageResponseRoomInfo.parser(), extensionRegistry));
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
          if (PARSER == null) {    synchronized (ProtoMessages.MessageResponseRoomListBase.MessageResponseRoomList.class) {
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


    // @@protoc_insertion_point(class_scope:MessageResponseRoomList)
    private static final ProtoMessages.MessageResponseRoomListBase.MessageResponseRoomList DEFAULT_INSTANCE;
    static {
      DEFAULT_INSTANCE = new MessageResponseRoomList();
      DEFAULT_INSTANCE.makeImmutable();
    }

    public static ProtoMessages.MessageResponseRoomListBase.MessageResponseRoomList getDefaultInstance() {
      return DEFAULT_INSTANCE;
    }

    private static volatile com.google.protobuf.Parser<MessageResponseRoomList> PARSER;

    public static com.google.protobuf.Parser<MessageResponseRoomList> parser() {
      return DEFAULT_INSTANCE.getParserForType();
    }
  }


  static {
  }

  // @@protoc_insertion_point(outer_class_scope)
}
