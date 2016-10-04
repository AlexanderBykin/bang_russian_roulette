// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: MessageResponseNoMoney.proto

#ifndef PROTOBUF_MessageResponseNoMoney_2eproto__INCLUDED
#define PROTOBUF_MessageResponseNoMoney_2eproto__INCLUDED

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
void protobuf_AddDesc_MessageResponseNoMoney_2eproto();
void protobuf_AssignDesc_MessageResponseNoMoney_2eproto();
void protobuf_ShutdownFile_MessageResponseNoMoney_2eproto();

class MessageResponseNoMoney;

// ===================================================================

class MessageResponseNoMoney : public ::google::protobuf::MessageLite /* @@protoc_insertion_point(class_definition:MessageResponseNoMoney) */ {
 public:
  MessageResponseNoMoney();
  virtual ~MessageResponseNoMoney();

  MessageResponseNoMoney(const MessageResponseNoMoney& from);

  inline MessageResponseNoMoney& operator=(const MessageResponseNoMoney& from) {
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

  static const MessageResponseNoMoney& default_instance();

  #ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
  // Returns the internal default instance pointer. This function can
  // return NULL thus should not be used by the user. This is intended
  // for Protobuf internal code. Please use default_instance() declared
  // above instead.
  static inline const MessageResponseNoMoney* internal_default_instance() {
    return default_instance_;
  }
  #endif

  void Swap(MessageResponseNoMoney* other);

  // implements Message ----------------------------------------------

  inline MessageResponseNoMoney* New() const { return New(NULL); }

  MessageResponseNoMoney* New(::google::protobuf::Arena* arena) const;
  void CheckTypeAndMergeFrom(const ::google::protobuf::MessageLite& from);
  void CopyFrom(const MessageResponseNoMoney& from);
  void MergeFrom(const MessageResponseNoMoney& from);
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
  void InternalSwap(MessageResponseNoMoney* other);
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

  // required int64 amount = 1 [default = 0];
  bool has_amount() const;
  void clear_amount();
  static const int kAmountFieldNumber = 1;
  ::google::protobuf::int64 amount() const;
  void set_amount(::google::protobuf::int64 value);

  // required int64 need = 2 [default = 0];
  bool has_need() const;
  void clear_need();
  static const int kNeedFieldNumber = 2;
  ::google::protobuf::int64 need() const;
  void set_need(::google::protobuf::int64 value);

  // @@protoc_insertion_point(class_scope:MessageResponseNoMoney)
 private:
  inline void set_has_amount();
  inline void clear_has_amount();
  inline void set_has_need();
  inline void clear_has_need();

  // helper for ByteSize()
  int RequiredFieldsByteSizeFallback() const;

  ::google::protobuf::internal::ArenaStringPtr _unknown_fields_;
  ::google::protobuf::Arena* _arena_ptr_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::int64 amount_;
  ::google::protobuf::int64 need_;
  #ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
  friend void  protobuf_AddDesc_MessageResponseNoMoney_2eproto_impl();
  #else
  friend void  protobuf_AddDesc_MessageResponseNoMoney_2eproto();
  #endif
  friend void protobuf_AssignDesc_MessageResponseNoMoney_2eproto();
  friend void protobuf_ShutdownFile_MessageResponseNoMoney_2eproto();

  void InitAsDefaultInstance();
  static MessageResponseNoMoney* default_instance_;
};
// ===================================================================


// ===================================================================

#if !PROTOBUF_INLINE_NOT_IN_HEADERS
// MessageResponseNoMoney

// required int64 amount = 1 [default = 0];
inline bool MessageResponseNoMoney::has_amount() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void MessageResponseNoMoney::set_has_amount() {
  _has_bits_[0] |= 0x00000001u;
}
inline void MessageResponseNoMoney::clear_has_amount() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void MessageResponseNoMoney::clear_amount() {
  amount_ = GOOGLE_LONGLONG(0);
  clear_has_amount();
}
inline ::google::protobuf::int64 MessageResponseNoMoney::amount() const {
  // @@protoc_insertion_point(field_get:MessageResponseNoMoney.amount)
  return amount_;
}
inline void MessageResponseNoMoney::set_amount(::google::protobuf::int64 value) {
  set_has_amount();
  amount_ = value;
  // @@protoc_insertion_point(field_set:MessageResponseNoMoney.amount)
}

// required int64 need = 2 [default = 0];
inline bool MessageResponseNoMoney::has_need() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void MessageResponseNoMoney::set_has_need() {
  _has_bits_[0] |= 0x00000002u;
}
inline void MessageResponseNoMoney::clear_has_need() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void MessageResponseNoMoney::clear_need() {
  need_ = GOOGLE_LONGLONG(0);
  clear_has_need();
}
inline ::google::protobuf::int64 MessageResponseNoMoney::need() const {
  // @@protoc_insertion_point(field_get:MessageResponseNoMoney.need)
  return need_;
}
inline void MessageResponseNoMoney::set_need(::google::protobuf::int64 value) {
  set_has_need();
  need_ = value;
  // @@protoc_insertion_point(field_set:MessageResponseNoMoney.need)
}

#endif  // !PROTOBUF_INLINE_NOT_IN_HEADERS

// @@protoc_insertion_point(namespace_scope)

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_MessageResponseNoMoney_2eproto__INCLUDED