// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: MessageResponseShopItem.proto

#ifndef PROTOBUF_MessageResponseShopItem_2eproto__INCLUDED
#define PROTOBUF_MessageResponseShopItem_2eproto__INCLUDED

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
#include <google/protobuf/generated_enum_util.h>
// @@protoc_insertion_point(includes)

// Internal implementation detail -- do not call these.
void protobuf_AddDesc_MessageResponseShopItem_2eproto();
void protobuf_AssignDesc_MessageResponseShopItem_2eproto();
void protobuf_ShutdownFile_MessageResponseShopItem_2eproto();

class MessageResponseShopItem;

enum MessageResponseShopItem_eUsageType {
  MessageResponseShopItem_eUsageType_utPlayer = 0,
  MessageResponseShopItem_eUsageType_utEnemy = 1,
  MessageResponseShopItem_eUsageType_utBoth = 2,
  MessageResponseShopItem_eUsageType_utNone = 3
};
bool MessageResponseShopItem_eUsageType_IsValid(int value);
const MessageResponseShopItem_eUsageType MessageResponseShopItem_eUsageType_eUsageType_MIN = MessageResponseShopItem_eUsageType_utPlayer;
const MessageResponseShopItem_eUsageType MessageResponseShopItem_eUsageType_eUsageType_MAX = MessageResponseShopItem_eUsageType_utNone;
const int MessageResponseShopItem_eUsageType_eUsageType_ARRAYSIZE = MessageResponseShopItem_eUsageType_eUsageType_MAX + 1;

// ===================================================================

class MessageResponseShopItem : public ::google::protobuf::MessageLite /* @@protoc_insertion_point(class_definition:MessageResponseShopItem) */ {
 public:
  MessageResponseShopItem();
  virtual ~MessageResponseShopItem();

  MessageResponseShopItem(const MessageResponseShopItem& from);

  inline MessageResponseShopItem& operator=(const MessageResponseShopItem& from) {
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

  static const MessageResponseShopItem& default_instance();

  #ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
  // Returns the internal default instance pointer. This function can
  // return NULL thus should not be used by the user. This is intended
  // for Protobuf internal code. Please use default_instance() declared
  // above instead.
  static inline const MessageResponseShopItem* internal_default_instance() {
    return default_instance_;
  }
  #endif

  void Swap(MessageResponseShopItem* other);

  // implements Message ----------------------------------------------

  inline MessageResponseShopItem* New() const { return New(NULL); }

  MessageResponseShopItem* New(::google::protobuf::Arena* arena) const;
  void CheckTypeAndMergeFrom(const ::google::protobuf::MessageLite& from);
  void CopyFrom(const MessageResponseShopItem& from);
  void MergeFrom(const MessageResponseShopItem& from);
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
  void InternalSwap(MessageResponseShopItem* other);
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

  typedef MessageResponseShopItem_eUsageType eUsageType;
  static const eUsageType utPlayer =
    MessageResponseShopItem_eUsageType_utPlayer;
  static const eUsageType utEnemy =
    MessageResponseShopItem_eUsageType_utEnemy;
  static const eUsageType utBoth =
    MessageResponseShopItem_eUsageType_utBoth;
  static const eUsageType utNone =
    MessageResponseShopItem_eUsageType_utNone;
  static inline bool eUsageType_IsValid(int value) {
    return MessageResponseShopItem_eUsageType_IsValid(value);
  }
  static const eUsageType eUsageType_MIN =
    MessageResponseShopItem_eUsageType_eUsageType_MIN;
  static const eUsageType eUsageType_MAX =
    MessageResponseShopItem_eUsageType_eUsageType_MAX;
  static const int eUsageType_ARRAYSIZE =
    MessageResponseShopItem_eUsageType_eUsageType_ARRAYSIZE;

  // accessors -------------------------------------------------------

  // required string name = 1 [default = ""];
  bool has_name() const;
  void clear_name();
  static const int kNameFieldNumber = 1;
  const ::std::string& name() const;
  void set_name(const ::std::string& value);
  void set_name(const char* value);
  void set_name(const char* value, size_t size);
  ::std::string* mutable_name();
  ::std::string* release_name();
  void set_allocated_name(::std::string* name);

  // required string imageName = 2 [default = ""];
  bool has_imagename() const;
  void clear_imagename();
  static const int kImageNameFieldNumber = 2;
  const ::std::string& imagename() const;
  void set_imagename(const ::std::string& value);
  void set_imagename(const char* value);
  void set_imagename(const char* value, size_t size);
  ::std::string* mutable_imagename();
  ::std::string* release_imagename();
  void set_allocated_imagename(::std::string* imagename);

  // required string description = 3 [default = ""];
  bool has_description() const;
  void clear_description();
  static const int kDescriptionFieldNumber = 3;
  const ::std::string& description() const;
  void set_description(const ::std::string& value);
  void set_description(const char* value);
  void set_description(const char* value, size_t size);
  ::std::string* mutable_description();
  ::std::string* release_description();
  void set_allocated_description(::std::string* description);

  // required int32 cost = 4 [default = 0];
  bool has_cost() const;
  void clear_cost();
  static const int kCostFieldNumber = 4;
  ::google::protobuf::int32 cost() const;
  void set_cost(::google::protobuf::int32 value);

  // optional int32 amount = 5 [default = 0];
  bool has_amount() const;
  void clear_amount();
  static const int kAmountFieldNumber = 5;
  ::google::protobuf::int32 amount() const;
  void set_amount(::google::protobuf::int32 value);

  // required .MessageResponseShopItem.eUsageType usageType = 6 [default = utPlayer];
  bool has_usagetype() const;
  void clear_usagetype();
  static const int kUsageTypeFieldNumber = 6;
  ::MessageResponseShopItem_eUsageType usagetype() const;
  void set_usagetype(::MessageResponseShopItem_eUsageType value);

  // @@protoc_insertion_point(class_scope:MessageResponseShopItem)
 private:
  inline void set_has_name();
  inline void clear_has_name();
  inline void set_has_imagename();
  inline void clear_has_imagename();
  inline void set_has_description();
  inline void clear_has_description();
  inline void set_has_cost();
  inline void clear_has_cost();
  inline void set_has_amount();
  inline void clear_has_amount();
  inline void set_has_usagetype();
  inline void clear_has_usagetype();

  // helper for ByteSize()
  int RequiredFieldsByteSizeFallback() const;

  ::google::protobuf::internal::ArenaStringPtr _unknown_fields_;
  ::google::protobuf::Arena* _arena_ptr_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::internal::ArenaStringPtr name_;
  ::google::protobuf::internal::ArenaStringPtr imagename_;
  ::google::protobuf::internal::ArenaStringPtr description_;
  ::google::protobuf::int32 cost_;
  ::google::protobuf::int32 amount_;
  int usagetype_;
  #ifdef GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER
  friend void  protobuf_AddDesc_MessageResponseShopItem_2eproto_impl();
  #else
  friend void  protobuf_AddDesc_MessageResponseShopItem_2eproto();
  #endif
  friend void protobuf_AssignDesc_MessageResponseShopItem_2eproto();
  friend void protobuf_ShutdownFile_MessageResponseShopItem_2eproto();

  void InitAsDefaultInstance();
  static MessageResponseShopItem* default_instance_;
};
// ===================================================================


// ===================================================================

#if !PROTOBUF_INLINE_NOT_IN_HEADERS
// MessageResponseShopItem

// required string name = 1 [default = ""];
inline bool MessageResponseShopItem::has_name() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void MessageResponseShopItem::set_has_name() {
  _has_bits_[0] |= 0x00000001u;
}
inline void MessageResponseShopItem::clear_has_name() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void MessageResponseShopItem::clear_name() {
  name_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  clear_has_name();
}
inline const ::std::string& MessageResponseShopItem::name() const {
  // @@protoc_insertion_point(field_get:MessageResponseShopItem.name)
  return name_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void MessageResponseShopItem::set_name(const ::std::string& value) {
  set_has_name();
  name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:MessageResponseShopItem.name)
}
inline void MessageResponseShopItem::set_name(const char* value) {
  set_has_name();
  name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:MessageResponseShopItem.name)
}
inline void MessageResponseShopItem::set_name(const char* value, size_t size) {
  set_has_name();
  name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:MessageResponseShopItem.name)
}
inline ::std::string* MessageResponseShopItem::mutable_name() {
  set_has_name();
  // @@protoc_insertion_point(field_mutable:MessageResponseShopItem.name)
  return name_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* MessageResponseShopItem::release_name() {
  // @@protoc_insertion_point(field_release:MessageResponseShopItem.name)
  clear_has_name();
  return name_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void MessageResponseShopItem::set_allocated_name(::std::string* name) {
  if (name != NULL) {
    set_has_name();
  } else {
    clear_has_name();
  }
  name_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), name);
  // @@protoc_insertion_point(field_set_allocated:MessageResponseShopItem.name)
}

// required string imageName = 2 [default = ""];
inline bool MessageResponseShopItem::has_imagename() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void MessageResponseShopItem::set_has_imagename() {
  _has_bits_[0] |= 0x00000002u;
}
inline void MessageResponseShopItem::clear_has_imagename() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void MessageResponseShopItem::clear_imagename() {
  imagename_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  clear_has_imagename();
}
inline const ::std::string& MessageResponseShopItem::imagename() const {
  // @@protoc_insertion_point(field_get:MessageResponseShopItem.imageName)
  return imagename_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void MessageResponseShopItem::set_imagename(const ::std::string& value) {
  set_has_imagename();
  imagename_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:MessageResponseShopItem.imageName)
}
inline void MessageResponseShopItem::set_imagename(const char* value) {
  set_has_imagename();
  imagename_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:MessageResponseShopItem.imageName)
}
inline void MessageResponseShopItem::set_imagename(const char* value, size_t size) {
  set_has_imagename();
  imagename_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:MessageResponseShopItem.imageName)
}
inline ::std::string* MessageResponseShopItem::mutable_imagename() {
  set_has_imagename();
  // @@protoc_insertion_point(field_mutable:MessageResponseShopItem.imageName)
  return imagename_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* MessageResponseShopItem::release_imagename() {
  // @@protoc_insertion_point(field_release:MessageResponseShopItem.imageName)
  clear_has_imagename();
  return imagename_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void MessageResponseShopItem::set_allocated_imagename(::std::string* imagename) {
  if (imagename != NULL) {
    set_has_imagename();
  } else {
    clear_has_imagename();
  }
  imagename_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), imagename);
  // @@protoc_insertion_point(field_set_allocated:MessageResponseShopItem.imageName)
}

// required string description = 3 [default = ""];
inline bool MessageResponseShopItem::has_description() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void MessageResponseShopItem::set_has_description() {
  _has_bits_[0] |= 0x00000004u;
}
inline void MessageResponseShopItem::clear_has_description() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void MessageResponseShopItem::clear_description() {
  description_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  clear_has_description();
}
inline const ::std::string& MessageResponseShopItem::description() const {
  // @@protoc_insertion_point(field_get:MessageResponseShopItem.description)
  return description_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void MessageResponseShopItem::set_description(const ::std::string& value) {
  set_has_description();
  description_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:MessageResponseShopItem.description)
}
inline void MessageResponseShopItem::set_description(const char* value) {
  set_has_description();
  description_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:MessageResponseShopItem.description)
}
inline void MessageResponseShopItem::set_description(const char* value, size_t size) {
  set_has_description();
  description_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:MessageResponseShopItem.description)
}
inline ::std::string* MessageResponseShopItem::mutable_description() {
  set_has_description();
  // @@protoc_insertion_point(field_mutable:MessageResponseShopItem.description)
  return description_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* MessageResponseShopItem::release_description() {
  // @@protoc_insertion_point(field_release:MessageResponseShopItem.description)
  clear_has_description();
  return description_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void MessageResponseShopItem::set_allocated_description(::std::string* description) {
  if (description != NULL) {
    set_has_description();
  } else {
    clear_has_description();
  }
  description_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), description);
  // @@protoc_insertion_point(field_set_allocated:MessageResponseShopItem.description)
}

// required int32 cost = 4 [default = 0];
inline bool MessageResponseShopItem::has_cost() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void MessageResponseShopItem::set_has_cost() {
  _has_bits_[0] |= 0x00000008u;
}
inline void MessageResponseShopItem::clear_has_cost() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void MessageResponseShopItem::clear_cost() {
  cost_ = 0;
  clear_has_cost();
}
inline ::google::protobuf::int32 MessageResponseShopItem::cost() const {
  // @@protoc_insertion_point(field_get:MessageResponseShopItem.cost)
  return cost_;
}
inline void MessageResponseShopItem::set_cost(::google::protobuf::int32 value) {
  set_has_cost();
  cost_ = value;
  // @@protoc_insertion_point(field_set:MessageResponseShopItem.cost)
}

// optional int32 amount = 5 [default = 0];
inline bool MessageResponseShopItem::has_amount() const {
  return (_has_bits_[0] & 0x00000010u) != 0;
}
inline void MessageResponseShopItem::set_has_amount() {
  _has_bits_[0] |= 0x00000010u;
}
inline void MessageResponseShopItem::clear_has_amount() {
  _has_bits_[0] &= ~0x00000010u;
}
inline void MessageResponseShopItem::clear_amount() {
  amount_ = 0;
  clear_has_amount();
}
inline ::google::protobuf::int32 MessageResponseShopItem::amount() const {
  // @@protoc_insertion_point(field_get:MessageResponseShopItem.amount)
  return amount_;
}
inline void MessageResponseShopItem::set_amount(::google::protobuf::int32 value) {
  set_has_amount();
  amount_ = value;
  // @@protoc_insertion_point(field_set:MessageResponseShopItem.amount)
}

// required .MessageResponseShopItem.eUsageType usageType = 6 [default = utPlayer];
inline bool MessageResponseShopItem::has_usagetype() const {
  return (_has_bits_[0] & 0x00000020u) != 0;
}
inline void MessageResponseShopItem::set_has_usagetype() {
  _has_bits_[0] |= 0x00000020u;
}
inline void MessageResponseShopItem::clear_has_usagetype() {
  _has_bits_[0] &= ~0x00000020u;
}
inline void MessageResponseShopItem::clear_usagetype() {
  usagetype_ = 0;
  clear_has_usagetype();
}
inline ::MessageResponseShopItem_eUsageType MessageResponseShopItem::usagetype() const {
  // @@protoc_insertion_point(field_get:MessageResponseShopItem.usageType)
  return static_cast< ::MessageResponseShopItem_eUsageType >(usagetype_);
}
inline void MessageResponseShopItem::set_usagetype(::MessageResponseShopItem_eUsageType value) {
  assert(::MessageResponseShopItem_eUsageType_IsValid(value));
  set_has_usagetype();
  usagetype_ = value;
  // @@protoc_insertion_point(field_set:MessageResponseShopItem.usageType)
}

#endif  // !PROTOBUF_INLINE_NOT_IN_HEADERS

// @@protoc_insertion_point(namespace_scope)

#ifndef SWIG
namespace google {
namespace protobuf {

template <> struct is_proto_enum< ::MessageResponseShopItem_eUsageType> : ::google::protobuf::internal::true_type {};

}  // namespace protobuf
}  // namespace google
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_MessageResponseShopItem_2eproto__INCLUDED