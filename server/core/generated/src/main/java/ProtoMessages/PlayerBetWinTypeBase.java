// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: PlayerBetWinType.proto

package ProtoMessages;

public final class PlayerBetWinTypeBase {
  private PlayerBetWinTypeBase() {}
  public static void registerAllExtensions(
      com.google.protobuf.ExtensionRegistryLite registry) {
  }
  /**
   * Protobuf enum {@code PlayerBetWinType}
   */
  public enum PlayerBetWinType
      implements com.google.protobuf.Internal.EnumLite {
    /**
     * <code>pbwtWin = 0;</code>
     */
    pbwtWin(0),
    /**
     * <code>pbwtLose = 1;</code>
     */
    pbwtLose(1),
    ;

    /**
     * <code>pbwtWin = 0;</code>
     */
    public static final int pbwtWin_VALUE = 0;
    /**
     * <code>pbwtLose = 1;</code>
     */
    public static final int pbwtLose_VALUE = 1;


    public final int getNumber() {
      return value;
    }

    /**
     * @deprecated Use {@link #forNumber(int)} instead.
     */
    @java.lang.Deprecated
    public static PlayerBetWinType valueOf(int value) {
      return forNumber(value);
    }

    public static PlayerBetWinType forNumber(int value) {
      switch (value) {
        case 0: return pbwtWin;
        case 1: return pbwtLose;
        default: return null;
      }
    }

    public static com.google.protobuf.Internal.EnumLiteMap<PlayerBetWinType>
        internalGetValueMap() {
      return internalValueMap;
    }
    private static final com.google.protobuf.Internal.EnumLiteMap<
        PlayerBetWinType> internalValueMap =
          new com.google.protobuf.Internal.EnumLiteMap<PlayerBetWinType>() {
            public PlayerBetWinType findValueByNumber(int number) {
              return PlayerBetWinType.forNumber(number);
            }
          };

    private final int value;

    private PlayerBetWinType(int value) {
      this.value = value;
    }

    // @@protoc_insertion_point(enum_scope:PlayerBetWinType)
  }


  static {
  }

  // @@protoc_insertion_point(outer_class_scope)
}
