// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: MessageResponseSetPlayerTypeAndPosition.proto

#ifndef PROTOBUF_MessageResponseSetPlayerTypeAndPosition_2eproto__INCLUDED
#define PROTOBUF_MessageResponseSetPlayerTypeAndPosition_2eproto__INCLUDED

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
#include "MessageResponseRoomPlayerInfo.pb.h"
// @@protoc_insertion_point(includes)

// Internal implementation detail -- do not call these.
void protobuf_AddDesc_MessageResponseSetPlayerTypeAndPosition_2eproto();
void protobuf_AssignDesc_MessageResponseSetPlayerTypeAndPosition_2eproto();
void protobuf_ShutdownFile_MessageResponseSetPlayerTypeAndPosition_2eproto();

class MessageResponseSetPlayerTypeAndPosition;

// ===================================================================

class MessageResponseSetPlayerTypeAndPosition : public ::google::protobuf::MessageLite /* @@protoc_insertion_point(class_definition:MessageResponseSetPlayerTypeAndPosition) */ {
 public:
  MessageResponseSetPlayerTypeAndPosition();
  virtual ~MessageResponseSetPlayerTypeAndPosition();

  MessageResponseSetPlayerTypeAndPosition(const MessageResponseSetPlayerTypeAndPosition& from);

  inline MessageResponseSetPlayerTypeAndPosition& operator=(const MessageResponseSetPlayerTypeAndPosition& from) {
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

  static const MessageResponseSetPlayerTypeAndPosition& default_instance();

  #ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
  // Returns the internal default instance pointer. This function can
  // return NULL thus should not be used by the user. This is intended
  // for Protobuf internal code. Please use default_instance() declared
  // above instead.
  static inline const MessageResponseSetPlayerTypeAndPosition* internal_default_instance() {
    return default_instance_;
  }
  #endif

  void Swap(MessageResponseSetPlayerTypeAndPosition* other);

  // implements Message ----------------------------------------------

  inline MessageResponseSetPlayerTypeAndPosition* New() const { return New(NULL); }

  MessageResponseSetPlayerTypeAndPosition* New(::google::protobuf::Arena* arena) const;
  void CheckTypeAndMergeFrom(const ::google::protobuf::MessageLite& from);
  void CopyFrom(const MessageResponseSetPlayerTypeAndPosition& from);
  void MergeFrom(const MessageResponseSetPlayerTypeAndPosition& from);
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
  void InternalSwap(MessageResponseSetPlayerTypeAndPosition* other);
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

  // required .MessageResponseRoomPlayerInfo player = 2;
  bool has_player() const;
  void clear_player();
  static const int kPlayerFieldNumber = 2;
  const ::MessageResponseRoomPlayerInfo& player() const;
  ::MessageResponseRoomPlayerInfo* mutable_player();
  ::MessageResponseRoomPlayerInfo* release_player();
  void set_allocated_player(::MessageResponseRoomPlayerInfo* player);

  // @@protoc_insertion_point(class_scope:MessageResponseSetPlayerTypeAndPosition)
 private:
  inline void set_has_roomid();
  inline void clear_has_roomid();
  inline void set_has_player();
  inline void clear_has_player();

  // helper for ByteSize()
  int RequiredFieldsByteSizeFallback() const;

  ::google::protobuf::internal::ArenaStringPtr _unknown_fields_;
  ::google::protobuf::Arena* _arena_ptr_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::int64 roomid_;
  ::MessageResponseRoomPlayerInfo* player_;
  #ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
  friend void  protobuf_AddDesc_MessageResponseSetPlayerTypeAndPosition_2eproto_impl();
  #else
  friend void  protobuf_AddDesc_MessageResponseSetPlayerTypeAndPosition_2eproto();
  #endif
  friend void protobuf_AssignDesc_MessageResponseSetPlayerTypeAndPosition_2eproto();
  friend void protobuf_ShutdownFile_MessageResponseSetPlayerTypeAndPosition_2eproto();

  void InitAsDefaultInstance();
  static MessageResponseSetPlayerTypeAndPosition* default_instance_;
};
// ===================================================================


// ===================================================================

#if !PROTOBUF_INLINE_NOT_IN_HEADERS
// MessageResponseSetPlayerTypeAndPosition

// required int64 roomId = 1 [default = 0];
inline bool MessageResponseSetPlayerTypeAndPosition::has_roomid() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void MessageResponseSetPlayerTypeAndPosition::set_has_roomid() {
  _has_bits_[0] |= 0x00000001u;
}
inline void MessageResponseSetPlayerTypeAndPosition::clear_has_roomid() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void MessageResponseSetPlayerTypeAndPosition::clear_roomid() {
  roomid_ = GOOGLE_LONGLONG(0);
  clear_has_roomid();
}
inline ::google::protobuf::int64 MessageResponseSetPlayerTypeAndPosition::roomid() const {
  // @@protoc_insertion_point(field_get:MessageResponseSetPlayerTypeAndPosition.roomId)
  return roomid_;
}
inline void MessageResponseSetPlayerTypeAndPosition::set_roomid(::google::protobuf::int64 value) {
  set_has_roomid();
  roomid_ = value;
  // @@protoc_insertion_point(field_set:MessageResponseSetPlayerTypeAndPosition.roomId)
}

// required .MessageResponseRoomPlayerInfo player = 2;
inline bool MessageResponseSetPlayerTypeAndPosition::has_player() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void MessageResponseSetPlayerTypeAndPosition::set_has_player() {
  _has_bits_[0] |= 0x00000002u;
}
inline void MessageResponseSetPlayerTypeAndPosition::clear_has_player() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void MessageResponseSetPlayerTypeAndPosition::clear_player() {
  if (player_ != NULL) player_->::MessageResponseRoomPlayerInfo::Clear();
  clear_has_player();
}
inline const ::MessageResponseRoomPlayerInfo& MessageResponseSetPlayerTypeAndPosition::player() const {
  // @@protoc_insertion_point(field_get:MessageResponseSetPlayerTypeAndPosition.player)
#ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
  return player_ != NULL ? *player_ : *default_instance().player_;
#else
  return player_ != NULL ? *player_ : *default_instance_->player_;
#endif
}
inline ::MessageResponseRoomPlayerInfo* MessageResponseSetPlayerTypeAndPosition::mutable_player() {
  set_has_player();
  if (player_ == NULL) {
    player_ = new ::MessageResponseRoomPlayerInfo;
  }
  // @@protoc_insertion_point(field_mutable:MessageResponseSetPlayerTypeAndPosition.player)
  return player_;
}
inline ::MessageResponseRoomPlayerInfo* MessageResponseSetPlayerTypeAndPosition::release_player() {
  // @@protoc_insertion_point(field_release:MessageResponseSetPlayerTypeAndPosition.player)
  clear_has_player();
  ::MessageResponseRoomPlayerInfo* temp = player_;
  player_ = NULL;
  return temp;
}
inline void MessageResponseSetPlayerTypeAndPosition::set_allocated_player(::MessageResponseRoomPlayerInfo* player) {
  delete player_;
  player_ = player;
  if (player) {
    set_has_player();
  } else {
    clear_has_player();
  }
  // @@protoc_insertion_point(field_set_allocated:MessageResponseSetPlayerTypeAndPosition.player)
}

#endif  // !PROTOBUF_INLINE_NOT_IN_HEADERS

// @@protoc_insertion_point(namespace_scope)

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_MessageResponseSetPlayerTypeAndPosition_2eproto__INCLUDED