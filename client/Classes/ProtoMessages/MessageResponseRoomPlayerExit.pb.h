// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: MessageResponseRoomPlayerExit.proto

#ifndef PROTOBUF_MessageResponseRoomPlayerExit_2eproto__INCLUDED
#define PROTOBUF_MessageResponseRoomPlayerExit_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 3000000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 3000000 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/message_lite.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
// @@protoc_insertion_point(includes)

// Internal implementation detail -- do not call these.
void protobuf_AddDesc_MessageResponseRoomPlayerExit_2eproto();
void protobuf_AssignDesc_MessageResponseRoomPlayerExit_2eproto();
void protobuf_ShutdownFile_MessageResponseRoomPlayerExit_2eproto();

class MessageResponseRoomPlayerExit;

// ===================================================================

class MessageResponseRoomPlayerExit : public ::google::protobuf::MessageLite /* @@protoc_insertion_point(class_definition:MessageResponseRoomPlayerExit) */ {
 public:
  MessageResponseRoomPlayerExit();
  virtual ~MessageResponseRoomPlayerExit();

  MessageResponseRoomPlayerExit(const MessageResponseRoomPlayerExit& from);

  inline MessageResponseRoomPlayerExit& operator=(const MessageResponseRoomPlayerExit& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::std::string& unknown_fields() const {
    return _unknown_fields_.GetNoArena(
        &::google::protobuf::internal::GetEmptyStringAlreadyInited());
  }

  inline ::std::string* mutable_unknown_fields() {
    return _unknown_fields_.MutableNoArena(
        &::google::protobuf::internal::GetEmptyStringAlreadyInited());
  }

  static const MessageResponseRoomPlayerExit& default_instance();

  #ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
  // Returns the internal default instance pointer. This function can
  // return NULL thus should not be used by the user. This is intended
  // for Protobuf internal code. Please use default_instance() declared
  // above instead.
  static inline const MessageResponseRoomPlayerExit* internal_default_instance() {
    return default_instance_;
  }
  #endif

  void Swap(MessageResponseRoomPlayerExit* other);

  // implements Message ----------------------------------------------

  inline MessageResponseRoomPlayerExit* New() const { return New(NULL); }

  MessageResponseRoomPlayerExit* New(::google::protobuf::Arena* arena) const;
  void CheckTypeAndMergeFrom(const ::google::protobuf::MessageLite& from);
  void CopyFrom(const MessageResponseRoomPlayerExit& from);
  void MergeFrom(const MessageResponseRoomPlayerExit& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  void DiscardUnknownFields();
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  void InternalSwap(MessageResponseRoomPlayerExit* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return _arena_ptr_;
  }
  inline ::google::protobuf::Arena* MaybeArenaPtr() const {
    return _arena_ptr_;
  }
  public:

  ::std::string GetTypeName() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // required int64 roomId = 1 [default = 0];
  bool has_roomid() const;
  void clear_roomid();
  static const int kRoomIdFieldNumber = 1;
  ::google::protobuf::int64 roomid() const;
  void set_roomid(::google::protobuf::int64 value);

  // required int64 playerId = 2 [default = 0];
  bool has_playerid() const;
  void clear_playerid();
  static const int kPlayerIdFieldNumber = 2;
  ::google::protobuf::int64 playerid() const;
  void set_playerid(::google::protobuf::int64 value);

  // required int32 position = 3 [default = 0];
  bool has_position() const;
  void clear_position();
  static const int kPositionFieldNumber = 3;
  ::google::protobuf::int32 position() const;
  void set_position(::google::protobuf::int32 value);

  // @@protoc_insertion_point(class_scope:MessageResponseRoomPlayerExit)
 private:
  inline void set_has_roomid();
  inline void clear_has_roomid();
  inline void set_has_playerid();
  inline void clear_has_playerid();
  inline void set_has_position();
  inline void clear_has_position();

  // helper for ByteSize()
  int RequiredFieldsByteSizeFallback() const;

  ::google::protobuf::internal::ArenaStringPtr _unknown_fields_;
  ::google::protobuf::Arena* _arena_ptr_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::int64 roomid_;
  ::google::protobuf::int64 playerid_;
  ::google::protobuf::int32 position_;
  #ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
  friend void  protobuf_AddDesc_MessageResponseRoomPlayerExit_2eproto_impl();
  #else
  friend void  protobuf_AddDesc_MessageResponseRoomPlayerExit_2eproto();
  #endif
  friend void protobuf_AssignDesc_MessageResponseRoomPlayerExit_2eproto();
  friend void protobuf_ShutdownFile_MessageResponseRoomPlayerExit_2eproto();

  void InitAsDefaultInstance();
  static MessageResponseRoomPlayerExit* default_instance_;
};
// ===================================================================


// ===================================================================

#if !PROTOBUF_INLINE_NOT_IN_HEADERS
// MessageResponseRoomPlayerExit

// required int64 roomId = 1 [default = 0];
inline bool MessageResponseRoomPlayerExit::has_roomid() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void MessageResponseRoomPlayerExit::set_has_roomid() {
  _has_bits_[0] |= 0x00000001u;
}
inline void MessageResponseRoomPlayerExit::clear_has_roomid() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void MessageResponseRoomPlayerExit::clear_roomid() {
  roomid_ = GOOGLE_LONGLONG(0);
  clear_has_roomid();
}
inline ::google::protobuf::int64 MessageResponseRoomPlayerExit::roomid() const {
  // @@protoc_insertion_point(field_get:MessageResponseRoomPlayerExit.roomId)
  return roomid_;
}
inline void MessageResponseRoomPlayerExit::set_roomid(::google::protobuf::int64 value) {
  set_has_roomid();
  roomid_ = value;
  // @@protoc_insertion_point(field_set:MessageResponseRoomPlayerExit.roomId)
}

// required int64 playerId = 2 [default = 0];
inline bool MessageResponseRoomPlayerExit::has_playerid() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void MessageResponseRoomPlayerExit::set_has_playerid() {
  _has_bits_[0] |= 0x00000002u;
}
inline void MessageResponseRoomPlayerExit::clear_has_playerid() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void MessageResponseRoomPlayerExit::clear_playerid() {
  playerid_ = GOOGLE_LONGLONG(0);
  clear_has_playerid();
}
inline ::google::protobuf::int64 MessageResponseRoomPlayerExit::playerid() const {
  // @@protoc_insertion_point(field_get:MessageResponseRoomPlayerExit.playerId)
  return playerid_;
}
inline void MessageResponseRoomPlayerExit::set_playerid(::google::protobuf::int64 value) {
  set_has_playerid();
  playerid_ = value;
  // @@protoc_insertion_point(field_set:MessageResponseRoomPlayerExit.playerId)
}

// required int32 position = 3 [default = 0];
inline bool MessageResponseRoomPlayerExit::has_position() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void MessageResponseRoomPlayerExit::set_has_position() {
  _has_bits_[0] |= 0x00000004u;
}
inline void MessageResponseRoomPlayerExit::clear_has_position() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void MessageResponseRoomPlayerExit::clear_position() {
  position_ = 0;
  clear_has_position();
}
inline ::google::protobuf::int32 MessageResponseRoomPlayerExit::position() const {
  // @@protoc_insertion_point(field_get:MessageResponseRoomPlayerExit.position)
  return position_;
}
inline void MessageResponseRoomPlayerExit::set_position(::google::protobuf::int32 value) {
  set_has_position();
  position_ = value;
  // @@protoc_insertion_point(field_set:MessageResponseRoomPlayerExit.position)
}

#endif  // !PROTOBUF_INLINE_NOT_IN_HEADERS

// @@protoc_insertion_point(namespace_scope)

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_MessageResponseRoomPlayerExit_2eproto__INCLUDED
