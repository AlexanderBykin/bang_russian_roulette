// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: MessageResponseShopItem.proto

package ProtoMessages;

public final class MessageResponseShopItemBase {
  private MessageResponseShopItemBase() {}
  public static void registerAllExtensions(
      com.google.protobuf.ExtensionRegistryLite registry) {
  }
  public interface MessageResponseShopItemOrBuilder extends
      // @@protoc_insertion_point(interface_extends:MessageResponseShopItem)
      com.google.protobuf.MessageLiteOrBuilder {

    /**
     * <code>required string name = 1 [default = ""];</code>
     */
    boolean hasName();
    /**
     * <code>required string name = 1 [default = ""];</code>
     */
    java.lang.String getName();
    /**
     * <code>required string name = 1 [default = ""];</code>
     */
    com.google.protobuf.ByteString
        getNameBytes();

    /**
     * <code>required string imageName = 2 [default = ""];</code>
     */
    boolean hasImageName();
    /**
     * <code>required string imageName = 2 [default = ""];</code>
     */
    java.lang.String getImageName();
    /**
     * <code>required string imageName = 2 [default = ""];</code>
     */
    com.google.protobuf.ByteString
        getImageNameBytes();

    /**
     * <code>required string description = 3 [default = ""];</code>
     */
    boolean hasDescription();
    /**
     * <code>required string description = 3 [default = ""];</code>
     */
    java.lang.String getDescription();
    /**
     * <code>required string description = 3 [default = ""];</code>
     */
    com.google.protobuf.ByteString
        getDescriptionBytes();

    /**
     * <code>required int32 cost = 4 [default = 0];</code>
     */
    boolean hasCost();
    /**
     * <code>required int32 cost = 4 [default = 0];</code>
     */
    int getCost();

    /**
     * <code>optional int32 amount = 5 [default = 0];</code>
     */
    boolean hasAmount();
    /**
     * <code>optional int32 amount = 5 [default = 0];</code>
     */
    int getAmount();

    /**
     * <code>required .MessageResponseShopItem.eUsageType usageType = 6 [default = utPlayer];</code>
     */
    boolean hasUsageType();
    /**
     * <code>required .MessageResponseShopItem.eUsageType usageType = 6 [default = utPlayer];</code>
     */
    ProtoMessages.MessageResponseShopItemBase.MessageResponseShopItem.eUsageType getUsageType();
  }
  /**
   * Protobuf type {@code MessageResponseShopItem}
   */
  public  static final class MessageResponseShopItem extends
      com.google.protobuf.GeneratedMessageLite<
          MessageResponseShopItem, MessageResponseShopItem.Builder> implements
      // @@protoc_insertion_point(message_implements:MessageResponseShopItem)
      MessageResponseShopItemOrBuilder {
    private MessageResponseShopItem() {
      name_ = "";
      imageName_ = "";
      description_ = "";
    }
    /**
     * Protobuf enum {@code MessageResponseShopItem.eUsageType}
     */
    public enum eUsageType
        implements com.google.protobuf.Internal.EnumLite {
      /**
       * <code>utPlayer = 0;</code>
       */
      utPlayer(0),
      /**
       * <code>utEnemy = 1;</code>
       */
      utEnemy(1),
      /**
       * <code>utBoth = 2;</code>
       */
      utBoth(2),
      /**
       * <code>utNone = 3;</code>
       */
      utNone(3),
      ;

      /**
       * <code>utPlayer = 0;</code>
       */
      public static final int utPlayer_VALUE = 0;
      /**
       * <code>utEnemy = 1;</code>
       */
      public static final int utEnemy_VALUE = 1;
      /**
       * <code>utBoth = 2;</code>
       */
      public static final int utBoth_VALUE = 2;
      /**
       * <code>utNone = 3;</code>
       */
      public static final int utNone_VALUE = 3;


      public final int getNumber() {
        return value;
      }

      /**
       * @deprecated Use {@link #forNumber(int)} instead.
       */
      @java.lang.Deprecated
      public static eUsageType valueOf(int value) {
        return forNumber(value);
      }

      public static eUsageType forNumber(int value) {
        switch (value) {
          case 0: return utPlayer;
          case 1: return utEnemy;
          case 2: return utBoth;
          case 3: return utNone;
          default: return null;
        }
      }

      public static com.google.protobuf.Internal.EnumLiteMap<eUsageType>
          internalGetValueMap() {
        return internalValueMap;
      }
      private static final com.google.protobuf.Internal.EnumLiteMap<
          eUsageType> internalValueMap =
            new com.google.protobuf.Internal.EnumLiteMap<eUsageType>() {
              public eUsageType findValueByNumber(int number) {
                return eUsageType.forNumber(number);
              }
            };

      private final int value;

      private eUsageType(int value) {
        this.value = value;
      }

      // @@protoc_insertion_point(enum_scope:MessageResponseShopItem.eUsageType)
    }

    private int bitField0_;
    public static final int NAME_FIELD_NUMBER = 1;
    private java.lang.String name_;
    /**
     * <code>required string name = 1 [default = ""];</code>
     */
    public boolean hasName() {
      return ((bitField0_ & 0x00000001) == 0x00000001);
    }
    /**
     * <code>required string name = 1 [default = ""];</code>
     */
    public java.lang.String getName() {
      return name_;
    }
    /**
     * <code>required string name = 1 [default = ""];</code>
     */
    public com.google.protobuf.ByteString
        getNameBytes() {
      return com.google.protobuf.ByteString.copyFromUtf8(name_);
    }
    /**
     * <code>required string name = 1 [default = ""];</code>
     */
    private void setName(
        java.lang.String value) {
      if (value == null) {
    throw new NullPointerException();
  }
  bitField0_ |= 0x00000001;
      name_ = value;
    }
    /**
     * <code>required string name = 1 [default = ""];</code>
     */
    private void clearName() {
      bitField0_ = (bitField0_ & ~0x00000001);
      name_ = getDefaultInstance().getName();
    }
    /**
     * <code>required string name = 1 [default = ""];</code>
     */
    private void setNameBytes(
        com.google.protobuf.ByteString value) {
      if (value == null) {
    throw new NullPointerException();
  }
  bitField0_ |= 0x00000001;
      name_ = value.toStringUtf8();
    }

    public static final int IMAGENAME_FIELD_NUMBER = 2;
    private java.lang.String imageName_;
    /**
     * <code>required string imageName = 2 [default = ""];</code>
     */
    public boolean hasImageName() {
      return ((bitField0_ & 0x00000002) == 0x00000002);
    }
    /**
     * <code>required string imageName = 2 [default = ""];</code>
     */
    public java.lang.String getImageName() {
      return imageName_;
    }
    /**
     * <code>required string imageName = 2 [default = ""];</code>
     */
    public com.google.protobuf.ByteString
        getImageNameBytes() {
      return com.google.protobuf.ByteString.copyFromUtf8(imageName_);
    }
    /**
     * <code>required string imageName = 2 [default = ""];</code>
     */
    private void setImageName(
        java.lang.String value) {
      if (value == null) {
    throw new NullPointerException();
  }
  bitField0_ |= 0x00000002;
      imageName_ = value;
    }
    /**
     * <code>required string imageName = 2 [default = ""];</code>
     */
    private void clearImageName() {
      bitField0_ = (bitField0_ & ~0x00000002);
      imageName_ = getDefaultInstance().getImageName();
    }
    /**
     * <code>required string imageName = 2 [default = ""];</code>
     */
    private void setImageNameBytes(
        com.google.protobuf.ByteString value) {
      if (value == null) {
    throw new NullPointerException();
  }
  bitField0_ |= 0x00000002;
      imageName_ = value.toStringUtf8();
    }

    public static final int DESCRIPTION_FIELD_NUMBER = 3;
    private java.lang.String description_;
    /**
     * <code>required string description = 3 [default = ""];</code>
     */
    public boolean hasDescription() {
      return ((bitField0_ & 0x00000004) == 0x00000004);
    }
    /**
     * <code>required string description = 3 [default = ""];</code>
     */
    public java.lang.String getDescription() {
      return description_;
    }
    /**
     * <code>required string description = 3 [default = ""];</code>
     */
    public com.google.protobuf.ByteString
        getDescriptionBytes() {
      return com.google.protobuf.ByteString.copyFromUtf8(description_);
    }
    /**
     * <code>required string description = 3 [default = ""];</code>
     */
    private void setDescription(
        java.lang.String value) {
      if (value == null) {
    throw new NullPointerException();
  }
  bitField0_ |= 0x00000004;
      description_ = value;
    }
    /**
     * <code>required string description = 3 [default = ""];</code>
     */
    private void clearDescription() {
      bitField0_ = (bitField0_ & ~0x00000004);
      description_ = getDefaultInstance().getDescription();
    }
    /**
     * <code>required string description = 3 [default = ""];</code>
     */
    private void setDescriptionBytes(
        com.google.protobuf.ByteString value) {
      if (value == null) {
    throw new NullPointerException();
  }
  bitField0_ |= 0x00000004;
      description_ = value.toStringUtf8();
    }

    public static final int COST_FIELD_NUMBER = 4;
    private int cost_;
    /**
     * <code>required int32 cost = 4 [default = 0];</code>
     */
    public boolean hasCost() {
      return ((bitField0_ & 0x00000008) == 0x00000008);
    }
    /**
     * <code>required int32 cost = 4 [default = 0];</code>
     */
    public int getCost() {
      return cost_;
    }
    /**
     * <code>required int32 cost = 4 [default = 0];</code>
     */
    private void setCost(int value) {
      bitField0_ |= 0x00000008;
      cost_ = value;
    }
    /**
     * <code>required int32 cost = 4 [default = 0];</code>
     */
    private void clearCost() {
      bitField0_ = (bitField0_ & ~0x00000008);
      cost_ = 0;
    }

    public static final int AMOUNT_FIELD_NUMBER = 5;
    private int amount_;
    /**
     * <code>optional int32 amount = 5 [default = 0];</code>
     */
    public boolean hasAmount() {
      return ((bitField0_ & 0x00000010) == 0x00000010);
    }
    /**
     * <code>optional int32 amount = 5 [default = 0];</code>
     */
    public int getAmount() {
      return amount_;
    }
    /**
     * <code>optional int32 amount = 5 [default = 0];</code>
     */
    private void setAmount(int value) {
      bitField0_ |= 0x00000010;
      amount_ = value;
    }
    /**
     * <code>optional int32 amount = 5 [default = 0];</code>
     */
    private void clearAmount() {
      bitField0_ = (bitField0_ & ~0x00000010);
      amount_ = 0;
    }

    public static final int USAGETYPE_FIELD_NUMBER = 6;
    private int usageType_;
    /**
     * <code>required .MessageResponseShopItem.eUsageType usageType = 6 [default = utPlayer];</code>
     */
    public boolean hasUsageType() {
      return ((bitField0_ & 0x00000020) == 0x00000020);
    }
    /**
     * <code>required .MessageResponseShopItem.eUsageType usageType = 6 [default = utPlayer];</code>
     */
    public ProtoMessages.MessageResponseShopItemBase.MessageResponseShopItem.eUsageType getUsageType() {
      ProtoMessages.MessageResponseShopItemBase.MessageResponseShopItem.eUsageType result = ProtoMessages.MessageResponseShopItemBase.MessageResponseShopItem.eUsageType.forNumber(usageType_);
      return result == null ? ProtoMessages.MessageResponseShopItemBase.MessageResponseShopItem.eUsageType.utPlayer : result;
    }
    /**
     * <code>required .MessageResponseShopItem.eUsageType usageType = 6 [default = utPlayer];</code>
     */
    private void setUsageType(ProtoMessages.MessageResponseShopItemBase.MessageResponseShopItem.eUsageType value) {
      if (value == null) {
        throw new NullPointerException();
      }
      bitField0_ |= 0x00000020;
      usageType_ = value.getNumber();
    }
    /**
     * <code>required .MessageResponseShopItem.eUsageType usageType = 6 [default = utPlayer];</code>
     */
    private void clearUsageType() {
      bitField0_ = (bitField0_ & ~0x00000020);
      usageType_ = 0;
    }

    public void writeTo(com.google.protobuf.CodedOutputStream output)
                        throws java.io.IOException {
      if (((bitField0_ & 0x00000001) == 0x00000001)) {
        output.writeString(1, getName());
      }
      if (((bitField0_ & 0x00000002) == 0x00000002)) {
        output.writeString(2, getImageName());
      }
      if (((bitField0_ & 0x00000004) == 0x00000004)) {
        output.writeString(3, getDescription());
      }
      if (((bitField0_ & 0x00000008) == 0x00000008)) {
        output.writeInt32(4, cost_);
      }
      if (((bitField0_ & 0x00000010) == 0x00000010)) {
        output.writeInt32(5, amount_);
      }
      if (((bitField0_ & 0x00000020) == 0x00000020)) {
        output.writeEnum(6, usageType_);
      }
      unknownFields.writeTo(output);
    }

    public int getSerializedSize() {
      int size = memoizedSerializedSize;
      if (size != -1) return size;

      size = 0;
      if (((bitField0_ & 0x00000001) == 0x00000001)) {
        size += com.google.protobuf.CodedOutputStream
          .computeStringSize(1, getName());
      }
      if (((bitField0_ & 0x00000002) == 0x00000002)) {
        size += com.google.protobuf.CodedOutputStream
          .computeStringSize(2, getImageName());
      }
      if (((bitField0_ & 0x00000004) == 0x00000004)) {
        size += com.google.protobuf.CodedOutputStream
          .computeStringSize(3, getDescription());
      }
      if (((bitField0_ & 0x00000008) == 0x00000008)) {
        size += com.google.protobuf.CodedOutputStream
          .computeInt32Size(4, cost_);
      }
      if (((bitField0_ & 0x00000010) == 0x00000010)) {
        size += com.google.protobuf.CodedOutputStream
          .computeInt32Size(5, amount_);
      }
      if (((bitField0_ & 0x00000020) == 0x00000020)) {
        size += com.google.protobuf.CodedOutputStream
          .computeEnumSize(6, usageType_);
      }
      size += unknownFields.getSerializedSize();
      memoizedSerializedSize = size;
      return size;
    }

    public static ProtoMessages.MessageResponseShopItemBase.MessageResponseShopItem parseFrom(
        com.google.protobuf.ByteString data)
        throws com.google.protobuf.InvalidProtocolBufferException {
      return com.google.protobuf.GeneratedMessageLite.parseFrom(
          DEFAULT_INSTANCE, data);
    }
    public static ProtoMessages.MessageResponseShopItemBase.MessageResponseShopItem parseFrom(
        com.google.protobuf.ByteString data,
        com.google.protobuf.ExtensionRegistryLite extensionRegistry)
        throws com.google.protobuf.InvalidProtocolBufferException {
      return com.google.protobuf.GeneratedMessageLite.parseFrom(
          DEFAULT_INSTANCE, data, extensionRegistry);
    }
    public static ProtoMessages.MessageResponseShopItemBase.MessageResponseShopItem parseFrom(byte[] data)
        throws com.google.protobuf.InvalidProtocolBufferException {
      return com.google.protobuf.GeneratedMessageLite.parseFrom(
          DEFAULT_INSTANCE, data);
    }
    public static ProtoMessages.MessageResponseShopItemBase.MessageResponseShopItem parseFrom(
        byte[] data,
        com.google.protobuf.ExtensionRegistryLite extensionRegistry)
        throws com.google.protobuf.InvalidProtocolBufferException {
      return com.google.protobuf.GeneratedMessageLite.parseFrom(
          DEFAULT_INSTANCE, data, extensionRegistry);
    }
    public static ProtoMessages.MessageResponseShopItemBase.MessageResponseShopItem parseFrom(java.io.InputStream input)
        throws java.io.IOException {
      return com.google.protobuf.GeneratedMessageLite.parseFrom(
          DEFAULT_INSTANCE, input);
    }
    public static ProtoMessages.MessageResponseShopItemBase.MessageResponseShopItem parseFrom(
        java.io.InputStream input,
        com.google.protobuf.ExtensionRegistryLite extensionRegistry)
        throws java.io.IOException {
      return com.google.protobuf.GeneratedMessageLite.parseFrom(
          DEFAULT_INSTANCE, input, extensionRegistry);
    }
    public static ProtoMessages.MessageResponseShopItemBase.MessageResponseShopItem parseDelimitedFrom(java.io.InputStream input)
        throws java.io.IOException {
      return parseDelimitedFrom(DEFAULT_INSTANCE, input);
    }
    public static ProtoMessages.MessageResponseShopItemBase.MessageResponseShopItem parseDelimitedFrom(
        java.io.InputStream input,
        com.google.protobuf.ExtensionRegistryLite extensionRegistry)
        throws java.io.IOException {
      return parseDelimitedFrom(DEFAULT_INSTANCE, input, extensionRegistry);
    }
    public static ProtoMessages.MessageResponseShopItemBase.MessageResponseShopItem parseFrom(
        com.google.protobuf.CodedInputStream input)
        throws java.io.IOException {
      return com.google.protobuf.GeneratedMessageLite.parseFrom(
          DEFAULT_INSTANCE, input);
    }
    public static ProtoMessages.MessageResponseShopItemBase.MessageResponseShopItem parseFrom(
        com.google.protobuf.CodedInputStream input,
        com.google.protobuf.ExtensionRegistryLite extensionRegistry)
        throws java.io.IOException {
      return com.google.protobuf.GeneratedMessageLite.parseFrom(
          DEFAULT_INSTANCE, input, extensionRegistry);
    }

    public static Builder newBuilder() {
      return DEFAULT_INSTANCE.toBuilder();
    }
    public static Builder newBuilder(ProtoMessages.MessageResponseShopItemBase.MessageResponseShopItem prototype) {
      return DEFAULT_INSTANCE.toBuilder().mergeFrom(prototype);
    }

    /**
     * Protobuf type {@code MessageResponseShopItem}
     */
    public static final class Builder extends
        com.google.protobuf.GeneratedMessageLite.Builder<
          ProtoMessages.MessageResponseShopItemBase.MessageResponseShopItem, Builder> implements
        // @@protoc_insertion_point(builder_implements:MessageResponseShopItem)
        ProtoMessages.MessageResponseShopItemBase.MessageResponseShopItemOrBuilder {
      // Construct using ProtoMessages.MessageResponseShopItemBase.MessageResponseShopItem.newBuilder()
      private Builder() {
        super(DEFAULT_INSTANCE);
      }


      /**
       * <code>required string name = 1 [default = ""];</code>
       */
      public boolean hasName() {
        return instance.hasName();
      }
      /**
       * <code>required string name = 1 [default = ""];</code>
       */
      public java.lang.String getName() {
        return instance.getName();
      }
      /**
       * <code>required string name = 1 [default = ""];</code>
       */
      public com.google.protobuf.ByteString
          getNameBytes() {
        return instance.getNameBytes();
      }
      /**
       * <code>required string name = 1 [default = ""];</code>
       */
      public Builder setName(
          java.lang.String value) {
        copyOnWrite();
        instance.setName(value);
        return this;
      }
      /**
       * <code>required string name = 1 [default = ""];</code>
       */
      public Builder clearName() {
        copyOnWrite();
        instance.clearName();
        return this;
      }
      /**
       * <code>required string name = 1 [default = ""];</code>
       */
      public Builder setNameBytes(
          com.google.protobuf.ByteString value) {
        copyOnWrite();
        instance.setNameBytes(value);
        return this;
      }

      /**
       * <code>required string imageName = 2 [default = ""];</code>
       */
      public boolean hasImageName() {
        return instance.hasImageName();
      }
      /**
       * <code>required string imageName = 2 [default = ""];</code>
       */
      public java.lang.String getImageName() {
        return instance.getImageName();
      }
      /**
       * <code>required string imageName = 2 [default = ""];</code>
       */
      public com.google.protobuf.ByteString
          getImageNameBytes() {
        return instance.getImageNameBytes();
      }
      /**
       * <code>required string imageName = 2 [default = ""];</code>
       */
      public Builder setImageName(
          java.lang.String value) {
        copyOnWrite();
        instance.setImageName(value);
        return this;
      }
      /**
       * <code>required string imageName = 2 [default = ""];</code>
       */
      public Builder clearImageName() {
        copyOnWrite();
        instance.clearImageName();
        return this;
      }
      /**
       * <code>required string imageName = 2 [default = ""];</code>
       */
      public Builder setImageNameBytes(
          com.google.protobuf.ByteString value) {
        copyOnWrite();
        instance.setImageNameBytes(value);
        return this;
      }

      /**
       * <code>required string description = 3 [default = ""];</code>
       */
      public boolean hasDescription() {
        return instance.hasDescription();
      }
      /**
       * <code>required string description = 3 [default = ""];</code>
       */
      public java.lang.String getDescription() {
        return instance.getDescription();
      }
      /**
       * <code>required string description = 3 [default = ""];</code>
       */
      public com.google.protobuf.ByteString
          getDescriptionBytes() {
        return instance.getDescriptionBytes();
      }
      /**
       * <code>required string description = 3 [default = ""];</code>
       */
      public Builder setDescription(
          java.lang.String value) {
        copyOnWrite();
        instance.setDescription(value);
        return this;
      }
      /**
       * <code>required string description = 3 [default = ""];</code>
       */
      public Builder clearDescription() {
        copyOnWrite();
        instance.clearDescription();
        return this;
      }
      /**
       * <code>required string description = 3 [default = ""];</code>
       */
      public Builder setDescriptionBytes(
          com.google.protobuf.ByteString value) {
        copyOnWrite();
        instance.setDescriptionBytes(value);
        return this;
      }

      /**
       * <code>required int32 cost = 4 [default = 0];</code>
       */
      public boolean hasCost() {
        return instance.hasCost();
      }
      /**
       * <code>required int32 cost = 4 [default = 0];</code>
       */
      public int getCost() {
        return instance.getCost();
      }
      /**
       * <code>required int32 cost = 4 [default = 0];</code>
       */
      public Builder setCost(int value) {
        copyOnWrite();
        instance.setCost(value);
        return this;
      }
      /**
       * <code>required int32 cost = 4 [default = 0];</code>
       */
      public Builder clearCost() {
        copyOnWrite();
        instance.clearCost();
        return this;
      }

      /**
       * <code>optional int32 amount = 5 [default = 0];</code>
       */
      public boolean hasAmount() {
        return instance.hasAmount();
      }
      /**
       * <code>optional int32 amount = 5 [default = 0];</code>
       */
      public int getAmount() {
        return instance.getAmount();
      }
      /**
       * <code>optional int32 amount = 5 [default = 0];</code>
       */
      public Builder setAmount(int value) {
        copyOnWrite();
        instance.setAmount(value);
        return this;
      }
      /**
       * <code>optional int32 amount = 5 [default = 0];</code>
       */
      public Builder clearAmount() {
        copyOnWrite();
        instance.clearAmount();
        return this;
      }

      /**
       * <code>required .MessageResponseShopItem.eUsageType usageType = 6 [default = utPlayer];</code>
       */
      public boolean hasUsageType() {
        return instance.hasUsageType();
      }
      /**
       * <code>required .MessageResponseShopItem.eUsageType usageType = 6 [default = utPlayer];</code>
       */
      public ProtoMessages.MessageResponseShopItemBase.MessageResponseShopItem.eUsageType getUsageType() {
        return instance.getUsageType();
      }
      /**
       * <code>required .MessageResponseShopItem.eUsageType usageType = 6 [default = utPlayer];</code>
       */
      public Builder setUsageType(ProtoMessages.MessageResponseShopItemBase.MessageResponseShopItem.eUsageType value) {
        copyOnWrite();
        instance.setUsageType(value);
        return this;
      }
      /**
       * <code>required .MessageResponseShopItem.eUsageType usageType = 6 [default = utPlayer];</code>
       */
      public Builder clearUsageType() {
        copyOnWrite();
        instance.clearUsageType();
        return this;
      }

      // @@protoc_insertion_point(builder_scope:MessageResponseShopItem)
    }
    private byte memoizedIsInitialized = -1;
    protected final Object dynamicMethod(
        com.google.protobuf.GeneratedMessageLite.MethodToInvoke method,
        Object arg0, Object arg1) {
      switch (method) {
        case NEW_MUTABLE_INSTANCE: {
          return new ProtoMessages.MessageResponseShopItemBase.MessageResponseShopItem();
        }
        case IS_INITIALIZED: {
          byte isInitialized = memoizedIsInitialized;
          if (isInitialized == 1) return DEFAULT_INSTANCE;
          if (isInitialized == 0) return null;

          boolean shouldMemoize = ((Boolean) arg0).booleanValue();
          if (!hasName()) {
            if (shouldMemoize) {
              memoizedIsInitialized = 0;
            }
            return null;
          }
          if (!hasImageName()) {
            if (shouldMemoize) {
              memoizedIsInitialized = 0;
            }
            return null;
          }
          if (!hasDescription()) {
            if (shouldMemoize) {
              memoizedIsInitialized = 0;
            }
            return null;
          }
          if (!hasCost()) {
            if (shouldMemoize) {
              memoizedIsInitialized = 0;
            }
            return null;
          }
          if (!hasUsageType()) {
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
          ProtoMessages.MessageResponseShopItemBase.MessageResponseShopItem other = (ProtoMessages.MessageResponseShopItemBase.MessageResponseShopItem) arg1;
          name_ = visitor.visitString(
              hasName(), name_,
              other.hasName(), other.name_);
          imageName_ = visitor.visitString(
              hasImageName(), imageName_,
              other.hasImageName(), other.imageName_);
          description_ = visitor.visitString(
              hasDescription(), description_,
              other.hasDescription(), other.description_);
          cost_ = visitor.visitInt(
              hasCost(), cost_,
              other.hasCost(), other.cost_);
          amount_ = visitor.visitInt(
              hasAmount(), amount_,
              other.hasAmount(), other.amount_);
          usageType_ = visitor.visitInt(hasUsageType(), usageType_,
              other.hasUsageType(), other.usageType_);
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
                case 10: {
                  String s = input.readString();
                  bitField0_ |= 0x00000001;
                  name_ = s;
                  break;
                }
                case 18: {
                  String s = input.readString();
                  bitField0_ |= 0x00000002;
                  imageName_ = s;
                  break;
                }
                case 26: {
                  String s = input.readString();
                  bitField0_ |= 0x00000004;
                  description_ = s;
                  break;
                }
                case 32: {
                  bitField0_ |= 0x00000008;
                  cost_ = input.readInt32();
                  break;
                }
                case 40: {
                  bitField0_ |= 0x00000010;
                  amount_ = input.readInt32();
                  break;
                }
                case 48: {
                  int rawValue = input.readEnum();
                  ProtoMessages.MessageResponseShopItemBase.MessageResponseShopItem.eUsageType value = ProtoMessages.MessageResponseShopItemBase.MessageResponseShopItem.eUsageType.forNumber(rawValue);
                  if (value == null) {
                    super.mergeVarintField(6, rawValue);
                  } else {
                    bitField0_ |= 0x00000020;
                    usageType_ = rawValue;
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
          if (PARSER == null) {    synchronized (ProtoMessages.MessageResponseShopItemBase.MessageResponseShopItem.class) {
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


    // @@protoc_insertion_point(class_scope:MessageResponseShopItem)
    private static final ProtoMessages.MessageResponseShopItemBase.MessageResponseShopItem DEFAULT_INSTANCE;
    static {
      DEFAULT_INSTANCE = new MessageResponseShopItem();
      DEFAULT_INSTANCE.makeImmutable();
    }

    public static ProtoMessages.MessageResponseShopItemBase.MessageResponseShopItem getDefaultInstance() {
      return DEFAULT_INSTANCE;
    }

    private static volatile com.google.protobuf.Parser<MessageResponseShopItem> PARSER;

    public static com.google.protobuf.Parser<MessageResponseShopItem> parser() {
      return DEFAULT_INSTANCE.getParserForType();
    }
  }


  static {
  }

  // @@protoc_insertion_point(outer_class_scope)
}
