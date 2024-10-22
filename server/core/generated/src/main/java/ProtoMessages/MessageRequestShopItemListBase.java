// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: MessageRequestShopItemList.proto

package ProtoMessages;

public final class MessageRequestShopItemListBase {
  private MessageRequestShopItemListBase() {}
  public static void registerAllExtensions(
      com.google.protobuf.ExtensionRegistryLite registry) {
  }
  public interface MessageRequestShopItemListOrBuilder extends
      // @@protoc_insertion_point(interface_extends:MessageRequestShopItemList)
      com.google.protobuf.MessageLiteOrBuilder {

    /**
     * <code>required .MessageRequestShopItemList.eShopItemType shopItemType = 1 [default = sitITEMS];</code>
     */
    boolean hasShopItemType();
    /**
     * <code>required .MessageRequestShopItemList.eShopItemType shopItemType = 1 [default = sitITEMS];</code>
     */
    ProtoMessages.MessageRequestShopItemListBase.MessageRequestShopItemList.eShopItemType getShopItemType();

    /**
     * <code>required string lang = 2 [default = ""];</code>
     */
    boolean hasLang();
    /**
     * <code>required string lang = 2 [default = ""];</code>
     */
    java.lang.String getLang();
    /**
     * <code>required string lang = 2 [default = ""];</code>
     */
    com.google.protobuf.ByteString
        getLangBytes();
  }
  /**
   * Protobuf type {@code MessageRequestShopItemList}
   */
  public  static final class MessageRequestShopItemList extends
      com.google.protobuf.GeneratedMessageLite<
          MessageRequestShopItemList, MessageRequestShopItemList.Builder> implements
      // @@protoc_insertion_point(message_implements:MessageRequestShopItemList)
      MessageRequestShopItemListOrBuilder {
    private MessageRequestShopItemList() {
      lang_ = "";
    }
    /**
     * Protobuf enum {@code MessageRequestShopItemList.eShopItemType}
     */
    public enum eShopItemType
        implements com.google.protobuf.Internal.EnumLite {
      /**
       * <code>sitITEMS = 0;</code>
       */
      sitITEMS(0),
      /**
       * <code>sitCOLLECTIONITEMS = 1;</code>
       */
      sitCOLLECTIONITEMS(1),
      /**
       * <code>sitCOLLECTIONMONEY = 2;</code>
       */
      sitCOLLECTIONMONEY(2),
      /**
       * <code>sitINVENTORY = 3;</code>
       */
      sitINVENTORY(3),
      /**
       * <code>sitINVENTORYWITHSHOP = 4;</code>
       */
      sitINVENTORYWITHSHOP(4),
      /**
       * <code>sitVIDEOAD = 5;</code>
       */
      sitVIDEOAD(5),
      ;

      /**
       * <code>sitITEMS = 0;</code>
       */
      public static final int sitITEMS_VALUE = 0;
      /**
       * <code>sitCOLLECTIONITEMS = 1;</code>
       */
      public static final int sitCOLLECTIONITEMS_VALUE = 1;
      /**
       * <code>sitCOLLECTIONMONEY = 2;</code>
       */
      public static final int sitCOLLECTIONMONEY_VALUE = 2;
      /**
       * <code>sitINVENTORY = 3;</code>
       */
      public static final int sitINVENTORY_VALUE = 3;
      /**
       * <code>sitINVENTORYWITHSHOP = 4;</code>
       */
      public static final int sitINVENTORYWITHSHOP_VALUE = 4;
      /**
       * <code>sitVIDEOAD = 5;</code>
       */
      public static final int sitVIDEOAD_VALUE = 5;


      public final int getNumber() {
        return value;
      }

      /**
       * @deprecated Use {@link #forNumber(int)} instead.
       */
      @java.lang.Deprecated
      public static eShopItemType valueOf(int value) {
        return forNumber(value);
      }

      public static eShopItemType forNumber(int value) {
        switch (value) {
          case 0: return sitITEMS;
          case 1: return sitCOLLECTIONITEMS;
          case 2: return sitCOLLECTIONMONEY;
          case 3: return sitINVENTORY;
          case 4: return sitINVENTORYWITHSHOP;
          case 5: return sitVIDEOAD;
          default: return null;
        }
      }

      public static com.google.protobuf.Internal.EnumLiteMap<eShopItemType>
          internalGetValueMap() {
        return internalValueMap;
      }
      private static final com.google.protobuf.Internal.EnumLiteMap<
          eShopItemType> internalValueMap =
            new com.google.protobuf.Internal.EnumLiteMap<eShopItemType>() {
              public eShopItemType findValueByNumber(int number) {
                return eShopItemType.forNumber(number);
              }
            };

      private final int value;

      private eShopItemType(int value) {
        this.value = value;
      }

      // @@protoc_insertion_point(enum_scope:MessageRequestShopItemList.eShopItemType)
    }

    private int bitField0_;
    public static final int SHOPITEMTYPE_FIELD_NUMBER = 1;
    private int shopItemType_;
    /**
     * <code>required .MessageRequestShopItemList.eShopItemType shopItemType = 1 [default = sitITEMS];</code>
     */
    public boolean hasShopItemType() {
      return ((bitField0_ & 0x00000001) == 0x00000001);
    }
    /**
     * <code>required .MessageRequestShopItemList.eShopItemType shopItemType = 1 [default = sitITEMS];</code>
     */
    public ProtoMessages.MessageRequestShopItemListBase.MessageRequestShopItemList.eShopItemType getShopItemType() {
      ProtoMessages.MessageRequestShopItemListBase.MessageRequestShopItemList.eShopItemType result = ProtoMessages.MessageRequestShopItemListBase.MessageRequestShopItemList.eShopItemType.forNumber(shopItemType_);
      return result == null ? ProtoMessages.MessageRequestShopItemListBase.MessageRequestShopItemList.eShopItemType.sitITEMS : result;
    }
    /**
     * <code>required .MessageRequestShopItemList.eShopItemType shopItemType = 1 [default = sitITEMS];</code>
     */
    private void setShopItemType(ProtoMessages.MessageRequestShopItemListBase.MessageRequestShopItemList.eShopItemType value) {
      if (value == null) {
        throw new NullPointerException();
      }
      bitField0_ |= 0x00000001;
      shopItemType_ = value.getNumber();
    }
    /**
     * <code>required .MessageRequestShopItemList.eShopItemType shopItemType = 1 [default = sitITEMS];</code>
     */
    private void clearShopItemType() {
      bitField0_ = (bitField0_ & ~0x00000001);
      shopItemType_ = 0;
    }

    public static final int LANG_FIELD_NUMBER = 2;
    private java.lang.String lang_;
    /**
     * <code>required string lang = 2 [default = ""];</code>
     */
    public boolean hasLang() {
      return ((bitField0_ & 0x00000002) == 0x00000002);
    }
    /**
     * <code>required string lang = 2 [default = ""];</code>
     */
    public java.lang.String getLang() {
      return lang_;
    }
    /**
     * <code>required string lang = 2 [default = ""];</code>
     */
    public com.google.protobuf.ByteString
        getLangBytes() {
      return com.google.protobuf.ByteString.copyFromUtf8(lang_);
    }
    /**
     * <code>required string lang = 2 [default = ""];</code>
     */
    private void setLang(
        java.lang.String value) {
      if (value == null) {
    throw new NullPointerException();
  }
  bitField0_ |= 0x00000002;
      lang_ = value;
    }
    /**
     * <code>required string lang = 2 [default = ""];</code>
     */
    private void clearLang() {
      bitField0_ = (bitField0_ & ~0x00000002);
      lang_ = getDefaultInstance().getLang();
    }
    /**
     * <code>required string lang = 2 [default = ""];</code>
     */
    private void setLangBytes(
        com.google.protobuf.ByteString value) {
      if (value == null) {
    throw new NullPointerException();
  }
  bitField0_ |= 0x00000002;
      lang_ = value.toStringUtf8();
    }

    public void writeTo(com.google.protobuf.CodedOutputStream output)
                        throws java.io.IOException {
      if (((bitField0_ & 0x00000001) == 0x00000001)) {
        output.writeEnum(1, shopItemType_);
      }
      if (((bitField0_ & 0x00000002) == 0x00000002)) {
        output.writeString(2, getLang());
      }
      unknownFields.writeTo(output);
    }

    public int getSerializedSize() {
      int size = memoizedSerializedSize;
      if (size != -1) return size;

      size = 0;
      if (((bitField0_ & 0x00000001) == 0x00000001)) {
        size += com.google.protobuf.CodedOutputStream
          .computeEnumSize(1, shopItemType_);
      }
      if (((bitField0_ & 0x00000002) == 0x00000002)) {
        size += com.google.protobuf.CodedOutputStream
          .computeStringSize(2, getLang());
      }
      size += unknownFields.getSerializedSize();
      memoizedSerializedSize = size;
      return size;
    }

    public static ProtoMessages.MessageRequestShopItemListBase.MessageRequestShopItemList parseFrom(
        com.google.protobuf.ByteString data)
        throws com.google.protobuf.InvalidProtocolBufferException {
      return com.google.protobuf.GeneratedMessageLite.parseFrom(
          DEFAULT_INSTANCE, data);
    }
    public static ProtoMessages.MessageRequestShopItemListBase.MessageRequestShopItemList parseFrom(
        com.google.protobuf.ByteString data,
        com.google.protobuf.ExtensionRegistryLite extensionRegistry)
        throws com.google.protobuf.InvalidProtocolBufferException {
      return com.google.protobuf.GeneratedMessageLite.parseFrom(
          DEFAULT_INSTANCE, data, extensionRegistry);
    }
    public static ProtoMessages.MessageRequestShopItemListBase.MessageRequestShopItemList parseFrom(byte[] data)
        throws com.google.protobuf.InvalidProtocolBufferException {
      return com.google.protobuf.GeneratedMessageLite.parseFrom(
          DEFAULT_INSTANCE, data);
    }
    public static ProtoMessages.MessageRequestShopItemListBase.MessageRequestShopItemList parseFrom(
        byte[] data,
        com.google.protobuf.ExtensionRegistryLite extensionRegistry)
        throws com.google.protobuf.InvalidProtocolBufferException {
      return com.google.protobuf.GeneratedMessageLite.parseFrom(
          DEFAULT_INSTANCE, data, extensionRegistry);
    }
    public static ProtoMessages.MessageRequestShopItemListBase.MessageRequestShopItemList parseFrom(java.io.InputStream input)
        throws java.io.IOException {
      return com.google.protobuf.GeneratedMessageLite.parseFrom(
          DEFAULT_INSTANCE, input);
    }
    public static ProtoMessages.MessageRequestShopItemListBase.MessageRequestShopItemList parseFrom(
        java.io.InputStream input,
        com.google.protobuf.ExtensionRegistryLite extensionRegistry)
        throws java.io.IOException {
      return com.google.protobuf.GeneratedMessageLite.parseFrom(
          DEFAULT_INSTANCE, input, extensionRegistry);
    }
    public static ProtoMessages.MessageRequestShopItemListBase.MessageRequestShopItemList parseDelimitedFrom(java.io.InputStream input)
        throws java.io.IOException {
      return parseDelimitedFrom(DEFAULT_INSTANCE, input);
    }
    public static ProtoMessages.MessageRequestShopItemListBase.MessageRequestShopItemList parseDelimitedFrom(
        java.io.InputStream input,
        com.google.protobuf.ExtensionRegistryLite extensionRegistry)
        throws java.io.IOException {
      return parseDelimitedFrom(DEFAULT_INSTANCE, input, extensionRegistry);
    }
    public static ProtoMessages.MessageRequestShopItemListBase.MessageRequestShopItemList parseFrom(
        com.google.protobuf.CodedInputStream input)
        throws java.io.IOException {
      return com.google.protobuf.GeneratedMessageLite.parseFrom(
          DEFAULT_INSTANCE, input);
    }
    public static ProtoMessages.MessageRequestShopItemListBase.MessageRequestShopItemList parseFrom(
        com.google.protobuf.CodedInputStream input,
        com.google.protobuf.ExtensionRegistryLite extensionRegistry)
        throws java.io.IOException {
      return com.google.protobuf.GeneratedMessageLite.parseFrom(
          DEFAULT_INSTANCE, input, extensionRegistry);
    }

    public static Builder newBuilder() {
      return DEFAULT_INSTANCE.toBuilder();
    }
    public static Builder newBuilder(ProtoMessages.MessageRequestShopItemListBase.MessageRequestShopItemList prototype) {
      return DEFAULT_INSTANCE.toBuilder().mergeFrom(prototype);
    }

    /**
     * Protobuf type {@code MessageRequestShopItemList}
     */
    public static final class Builder extends
        com.google.protobuf.GeneratedMessageLite.Builder<
          ProtoMessages.MessageRequestShopItemListBase.MessageRequestShopItemList, Builder> implements
        // @@protoc_insertion_point(builder_implements:MessageRequestShopItemList)
        ProtoMessages.MessageRequestShopItemListBase.MessageRequestShopItemListOrBuilder {
      // Construct using ProtoMessages.MessageRequestShopItemListBase.MessageRequestShopItemList.newBuilder()
      private Builder() {
        super(DEFAULT_INSTANCE);
      }


      /**
       * <code>required .MessageRequestShopItemList.eShopItemType shopItemType = 1 [default = sitITEMS];</code>
       */
      public boolean hasShopItemType() {
        return instance.hasShopItemType();
      }
      /**
       * <code>required .MessageRequestShopItemList.eShopItemType shopItemType = 1 [default = sitITEMS];</code>
       */
      public ProtoMessages.MessageRequestShopItemListBase.MessageRequestShopItemList.eShopItemType getShopItemType() {
        return instance.getShopItemType();
      }
      /**
       * <code>required .MessageRequestShopItemList.eShopItemType shopItemType = 1 [default = sitITEMS];</code>
       */
      public Builder setShopItemType(ProtoMessages.MessageRequestShopItemListBase.MessageRequestShopItemList.eShopItemType value) {
        copyOnWrite();
        instance.setShopItemType(value);
        return this;
      }
      /**
       * <code>required .MessageRequestShopItemList.eShopItemType shopItemType = 1 [default = sitITEMS];</code>
       */
      public Builder clearShopItemType() {
        copyOnWrite();
        instance.clearShopItemType();
        return this;
      }

      /**
       * <code>required string lang = 2 [default = ""];</code>
       */
      public boolean hasLang() {
        return instance.hasLang();
      }
      /**
       * <code>required string lang = 2 [default = ""];</code>
       */
      public java.lang.String getLang() {
        return instance.getLang();
      }
      /**
       * <code>required string lang = 2 [default = ""];</code>
       */
      public com.google.protobuf.ByteString
          getLangBytes() {
        return instance.getLangBytes();
      }
      /**
       * <code>required string lang = 2 [default = ""];</code>
       */
      public Builder setLang(
          java.lang.String value) {
        copyOnWrite();
        instance.setLang(value);
        return this;
      }
      /**
       * <code>required string lang = 2 [default = ""];</code>
       */
      public Builder clearLang() {
        copyOnWrite();
        instance.clearLang();
        return this;
      }
      /**
       * <code>required string lang = 2 [default = ""];</code>
       */
      public Builder setLangBytes(
          com.google.protobuf.ByteString value) {
        copyOnWrite();
        instance.setLangBytes(value);
        return this;
      }

      // @@protoc_insertion_point(builder_scope:MessageRequestShopItemList)
    }
    private byte memoizedIsInitialized = -1;
    protected final Object dynamicMethod(
        com.google.protobuf.GeneratedMessageLite.MethodToInvoke method,
        Object arg0, Object arg1) {
      switch (method) {
        case NEW_MUTABLE_INSTANCE: {
          return new ProtoMessages.MessageRequestShopItemListBase.MessageRequestShopItemList();
        }
        case IS_INITIALIZED: {
          byte isInitialized = memoizedIsInitialized;
          if (isInitialized == 1) return DEFAULT_INSTANCE;
          if (isInitialized == 0) return null;

          boolean shouldMemoize = ((Boolean) arg0).booleanValue();
          if (!hasShopItemType()) {
            if (shouldMemoize) {
              memoizedIsInitialized = 0;
            }
            return null;
          }
          if (!hasLang()) {
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
          ProtoMessages.MessageRequestShopItemListBase.MessageRequestShopItemList other = (ProtoMessages.MessageRequestShopItemListBase.MessageRequestShopItemList) arg1;
          shopItemType_ = visitor.visitInt(hasShopItemType(), shopItemType_,
              other.hasShopItemType(), other.shopItemType_);
          lang_ = visitor.visitString(
              hasLang(), lang_,
              other.hasLang(), other.lang_);
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
                  int rawValue = input.readEnum();
                  ProtoMessages.MessageRequestShopItemListBase.MessageRequestShopItemList.eShopItemType value = ProtoMessages.MessageRequestShopItemListBase.MessageRequestShopItemList.eShopItemType.forNumber(rawValue);
                  if (value == null) {
                    super.mergeVarintField(1, rawValue);
                  } else {
                    bitField0_ |= 0x00000001;
                    shopItemType_ = rawValue;
                  }
                  break;
                }
                case 18: {
                  String s = input.readString();
                  bitField0_ |= 0x00000002;
                  lang_ = s;
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
          if (PARSER == null) {    synchronized (ProtoMessages.MessageRequestShopItemListBase.MessageRequestShopItemList.class) {
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


    // @@protoc_insertion_point(class_scope:MessageRequestShopItemList)
    private static final ProtoMessages.MessageRequestShopItemListBase.MessageRequestShopItemList DEFAULT_INSTANCE;
    static {
      DEFAULT_INSTANCE = new MessageRequestShopItemList();
      DEFAULT_INSTANCE.makeImmutable();
    }

    public static ProtoMessages.MessageRequestShopItemListBase.MessageRequestShopItemList getDefaultInstance() {
      return DEFAULT_INSTANCE;
    }

    private static volatile com.google.protobuf.Parser<MessageRequestShopItemList> PARSER;

    public static com.google.protobuf.Parser<MessageRequestShopItemList> parser() {
      return DEFAULT_INSTANCE.getParserForType();
    }
  }


  static {
  }

  // @@protoc_insertion_point(outer_class_scope)
}
